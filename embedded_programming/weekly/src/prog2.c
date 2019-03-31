#include <pthread.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <mcp3422.h>  
#include <wiringPi.h>

#define CDS   400

int led[4] = { 27, 24, 28, 29 };
int fnd_led[8] = {11, 10, 13, 12, 14, 15, 16, 0};
const int led_num[10] = {
	0xFC,
	0x60,
	0xDA,
	0xF2,
	0x66,
	0xB6,
	0xBE,
	0xE0,
	0xFE,
	0xF6,
};
int cds;

int fnd_value;
int led_value;

void show_digit(int select, int value) {
	int i;
	int n = led_num[value];

	for (i = 1; i <= 3; ++i) {
		digitalWrite(i, i == select);
	}
	for (i = 0; i < 7; ++i) {
		digitalWrite(fnd_led[i], n & (1 << (7-i)));
	}
}

void *fnd_thread(void *arg) {
	int arr[3] = {0, 0, 0};
	int i;
	while (1) {
		int n = fnd_value;
		i = 0;
		while (i != 3) {
			show_digit(3 - i, n % 10);
			i++;
			n /= 10;
			delay(1);
		}
	}
	return 0;
}

void *led_thread(void *arg) {
	int i;
	while (1) {
		int n = led_value / 512 + 1;
		for (i = 0; i < 4; ++i) {
			digitalWrite(led[i], (i<n));
		}
	}
	return 0;
}

void init_fnd() {
	int i;
	for (i = 1; i <= 3; ++i) {
		pinMode(i, OUTPUT);
	}

	for (i = 0; i < 8; ++i) {
		pinMode(fnd_led[i], OUTPUT);
	}
}

void init_led() {
	int i;
	for (i = 0; i < 4; ++i) {
		pinMode(led[i], OUTPUT);
	}
}

int main()
{
	pthread_t thread;

	wiringPiSetup();
	init_fnd();
	init_led();

	mcp3422Setup(400, 0x6a, 0, 0); 
	pthread_create(&thread, NULL, fnd_thread, NULL);
	pthread_create(&thread, NULL, led_thread, NULL);

	while (1) {
		int cds = analogRead(CDS);

		led_value = cds;
		fnd_value = cds / 2048. * 100;
		printf("cds: %d, fnd: %d, led: %d\n", cds, fnd_value, led_value / 512 + 1);
		delay(100);
	}
}
