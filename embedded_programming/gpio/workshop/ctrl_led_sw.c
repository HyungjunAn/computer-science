#include "ctrl_led_sw.h"

int LED[] = {27, 24, 28, 29};
int SW[] = {4, 5};


void init_led_sw(void) 
{
	wiringPiSetup();
	init_led();
	init_sw();
}
void set_led(int arr[4])
{
	int i = 0;
	for (i = 0; i < LED_NUM; ++i) {
		if (arr[i] != 0) {
			digitalWrite(LED[i], HIGH);
		}
		else {
			digitalWrite(LED[i], LOW);
		}
	}
}
void init_led(void)
{
	int i;
	for (i = 0; i < LED_NUM; ++i) {
		pinMode(LED[i], OUTPUT);
	}
}
void init_sw(void)
{
	int i;
	for (i = 0; i < SW_NUM; ++i) {
		pinMode(SW[i], INPUT);
	}
}

void off_led(void)
{
	int i;
	for (i = 0; i < LED_NUM; ++i) {
		digitalWrite(LED[i], LOW);
	}
}
void print_led_map(int map[][4], int line, int delayTime)
{
	int i;
	for (i = 0; i < line; ++i) {
		set_led(map[i]);
		delay(delayTime);
	}
	off_led();
}

int isSwitchOn(int switch_num)
{
	return digitalRead(SW[switch_num]);
}

int setSwitchInterrupt(int switch_num, void (*interrupt_handler)(void))
{
	return wiringPiISR(SW[switch_num], INT_EDGE_FALLING, interrupt_handler);
}
int waitSwitchInterrupt(int switch_num, int delayTime)
{
	return waitForInterrupt(SW[switch_num], delayTime);
}
