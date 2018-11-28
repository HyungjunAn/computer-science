#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <wiringPi.h>
#include <mcp3422.h>  
#include <softTone.h>
#include "ssd1306_i2c.h"

#define CDS   400
#define TMP36 401
#define PIN 21

int scale [8] = {262, 294, 330, 349, 392, 440, 494, 525,};

int music0[] = {8, 7, 6, 5, 4, 3, 2, 1};
int bit0[]   = {1, 1, 1, 1, 1, 1, 1, 1};
int len0 = sizeof(music0) / sizeof(music0[0]);

int music1[] = {5, 5, 6, 6, 5, 5, 3, 5, 5, 3, 3, 2};
int bit1[]   = {1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2};
int len1 = sizeof(music1) / sizeof(music1[0]);

int music2[] = {5, 3, 3, 4, 2, 2, 1, 2, 3, 4, 5, 5, 5,};
int bit2[]   = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2,};
//int music2[] = {3, 3, 4, 5, 5, 4, 3, 2, 1, 1, 2, 3, 3, 2, 2, 3, 3, 4, 5, 5, 4, 3, 2, 1, 1, 2, 3, 2, 1, 1, };
//int bit2[]   = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 1, 4, };
int len2 = sizeof(music2) / sizeof(music2[0]);

int fd;
double tmp;
int cds;

double get_temp() {
	int reading = analogRead(TMP36);
	double voltage = reading / 1000.;
	double temp = (voltage - 0.5) * 100;

	return temp;
}

int get_cds(void)
{
	return analogRead(CDS);
}

void interupt_handler(int signo)
{
	clearDisplay(fd);
	exit(1);
}

void playMusic(int *music, int *bit, int len)
{
	int i;
	for (i = 0 ; i < len; ++i) {
		softToneWrite (PIN, scale[music[i] - 1]);
		delay (200 * bit[i]);
		softToneWrite (PIN, 0);
		delay (10);
	}
	softToneWrite (PIN, 0);
}

void *thread_routine(void *arg)
{
	while (1) {
		if (tmp > 30 && cds < 1024) {
			playMusic(music0, bit0, len0);
		}
		else if(tmp > 30) {
			playMusic(music1, bit1, len1);
		}
		else if(cds < 1024) {
			playMusic(music2, bit2, len2);
		}
	}
}
int main()
{
	char szTmp[1000];
	char szCds[1000]; 
	pthread_t thread;

	wiringPiSetup();
	mcp3422Setup(400, 0x6a, 0, 0); 

	softToneCreate(PIN) ;
	fd = ssd1306I2CSetup(0x3C);  // i2c address를 인자로 전달하면 됩니다.

	displayOn(fd);
	signal(SIGINT, interupt_handler);

	pthread_create(&thread, NULL, thread_routine,NULL);
	while (1) {
		tmp = get_temp();
		cds = get_cds();
		sprintf(szTmp, "TEMP: %04.1lf", tmp);
		sprintf(szCds, "CDS : %-4d", cds);
		draw_line(1, 1, szTmp);
		draw_line(2, 1, szCds);
		updateDisplay(fd);
	}
	return 0;
}


