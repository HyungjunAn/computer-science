#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wiringPi.h>
#include <mcp3422.h>    // ADC
#include <softServo.h>

#include "gpio_num.h"

volatile int cds;
volatile double temp;
char *szNum;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

ssize_t readn(int fd, void *vptr, size_t n);

void setRaspberryPi(void);
void* thread_routine_temp(void *arg);
void* thread_routine_cds(void* arg);
void switch1_action(void);
void switch2_action(void);
void* thread_routine_switch1(void* arg);
void* thread_routine_switch2(void* arg);
void forwards(int count);
void show_digit(int select, int value, int dot);
void *fnd_thread(void *arg);

int main()
{
	int ssock;
	int option;
	struct sockaddr_in saddr;

	int csock;
	struct sockaddr_in caddr;
	socklen_t caddrlen;

	ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1) {
		perror("socket");
		return -1;
	}

	option = 1;
	setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option);

	memset(&saddr, 0, sizeof saddr);
	saddr.sin_family = AF_INET;	
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = INADDR_ANY;  // 0.0.0.0
	if (bind(ssock, (struct sockaddr*)&saddr, sizeof saddr) == -1) {
		perror("bind");
		return 1;
	}

	if (listen(ssock, SOMAXCONN) == -1) {
		perror("listen");
		return 1;
	}

	memset(&caddr, 0, sizeof caddr);
	caddrlen = sizeof caddr;
	csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
	if (csock == -1) {
		perror("accept");
		return 1;
	}


	setRaspberryPi();
	pthread_t thread[5];
	pthread_create(&thread[0], NULL, thread_routine_cds, NULL);
	pthread_create(&thread[1], NULL, thread_routine_temp, NULL);
	wiringPiISR(SW[0], INT_EDGE_BOTH, switch1_action);
	wiringPiISR(SW[1], INT_EDGE_BOTH, switch2_action);
	pthread_create(&thread[2], NULL, thread_routine_switch1, NULL);
	pthread_create(&thread[3], NULL, thread_routine_switch2, NULL);
	pthread_create(&thread[4], NULL, fnd_thread, NULL);

	while (1) {
		char data[512];
		char sensor_type;
		int data_len;
		int len;

		len = readn(csock, &sensor_type, sizeof(sensor_type));
		if (len <= 0) {
			break;
		}

		len = readn(csock, &data_len, sizeof(data_len));
		if (len <= 0) {
			break;
		}

		len = readn(csock, data, data_len);
		if (len <= 0) {
			break;
		}

		if (sensor_type == 'c') {
			cds = *(int*)data;
			//printf("CDS: %d\n", cds);
		}
		else if (sensor_type == 't') {
			temp = *(double*)data;
			//printf("TMP: %.2lf\n", temp);
		}
	}
	close(csock);
	close(ssock);
}

void setRaspberryPi(void)
{
	wiringPiSetup();
	int i;
	for (i = 0; i < SW_NUM; ++i) {
		pinMode(SW[i], INPUT);
	}
	for (i = 0; i < STEP_PIN_NUM; ++i) {
		pinMode(STEP_PIN[i], OUTPUT);
	}
	for (i = 1; i <= S7_PIN_NUM; ++i) {
		pinMode(i, OUTPUT);
	}
	for (i = 0; i < S7_S_NUM; ++i) {
		pinMode(S7_S[i], OUTPUT);
	}
	softServoSetup(SERVO, -1, -1, -1, -1, -1, -1, -1);
}

void* thread_routine_cds(void* arg)
{
	while (1) {
		if (cds < 1024) {
			forwards(100);
		}
	}
}

void* thread_routine_temp(void* arg)
{
	while (1) {
		//printf("temp: %lf\n", temp);
		if (temp > 25) {
			//printf("move servo\n");
;
			softServoWrite(SERVO, -250);
			delay(800);
			softServoWrite(SERVO, 1250);
			delay(800);
		}
	}
}

void show_digit(int select, int value, int dot) {
	int i, j;
	int n = S7_NUMARR[value - '0'];

	for (i = 1; i <= 3; ++i) {
		digitalWrite(i, i == select);
	}
	
	for (i = 0; i < 7; ++i) {
		digitalWrite(S7_S[i], n & (1 << (7-i)));  // !!
	}

	digitalWrite(0, dot);
}

void switch1_action(void)
{
	char buf[256];
	sprintf(buf, "%04.1lf", temp);
	szNum = buf;
}
void switch2_action(void)
{
	char buf[256];
	sprintf(buf, "%04.1lf", (cds / 2048.0) * 100);
	szNum = buf;
}
void* thread_routine_switch1(void* arg)
{
	while (1) {
		switch (waitForInterrupt(SW[0], 5000)) {
			case 0: 
				//printf("Timeout...\n");
				break;
			case -1:
				printf("error...\n");
				exit(1);
		}
	}
}
void* thread_routine_switch2(void* arg)
{
	while (1) {
		switch (waitForInterrupt(SW[1], 5000)) {
			case 0: 
				//printf("Timeout...\n");
				break;
			case -1:
				printf("error...\n");
				exit(1);
		}
	}
}
void *fnd_thread(void *arg)
 {
	while (1) {
		pthread_mutex_lock(&mutex);
		char* p = NULL;
		if (szNum != NULL) {
			p = strdup(szNum);
		}
		pthread_mutex_unlock(&mutex);

		if (p == NULL)
			continue;

		show_digit(3, p[3], 0);
		delay(1);
		show_digit(2, p[1], 1);
		delay(1);
		show_digit(1, p[0], 0);
		delay(1);

		free(p);
	}
}

void forwards(int count) {
	int i, j;

	for (i = 0; i < STEP_SEQ_NUM; ++i) {
		for (j = 0; j < STEP_PIN_NUM; ++j) {
			digitalWrite(STEP_PIN[j], STEP_SEQ[i][j]);
		}
		delayMicroseconds(800);
	}
}
