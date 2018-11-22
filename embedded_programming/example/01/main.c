#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <wiringPi.h>
#include <softPwm.h>

#include "gpio_num.h"

int map[][3] = {
	{1, 0, 0},
	{0, 0, 1},
};
int N = sizeof(map) / sizeof(map[0]);
int M = sizeof(map[0]) / sizeof(map[0][0]);

void init_led(void)
{
	int i;
	for (i = 0; i < LED_NUM; ++i) {
		pinMode(LED[i], INPUT);
	}
	for (i = 0; i < N; ++i) {
		pinMode(LED[i], PWM_OUTPUT) ;
		softPwmCreate(LED[i], 0, 100);
	}
}
void exit_program(int signo)
{
	int i;
	for (i = 0; i < N; ++i) {
		digitalWrite(LED[i], LOW);
	}
	exit(1);
}  

int main(void)
{
	int i;
	int j;

	wiringPiSetup();
	init_led();
	signal(SIGINT, exit_program);

	while (1) {
		for (i = 0; i < M; ++i) {
			for (j = 0; j < N; ++j) {
				softPwmWrite(LED[0], 0);
				delay(500);
				softPwmWrite(LED[0], 50);
				delay(500);
				softPwmWrite(LED[0], 99);
				delay(500);
				softPwmWrite(LED[0], 50);
				delay(500);
			}
		}
	}
	return 0;
}
