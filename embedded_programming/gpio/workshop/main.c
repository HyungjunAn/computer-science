#include <stdio.h>
#include <stdlib.h>

#include <signal.h>

#include <pthread.h>
#include "ctrl_led_sw.h"

int map1[][LED_NUM] = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}};
int line_map1 = sizeof(map1) / sizeof(map1[0]);

int map2[][LED_NUM] = {
	{1, 1, 1, 1},
	{0, 1, 1, 1},
	{1, 0, 1, 1},
	{1, 1, 0, 1},
	{1, 1, 1, 0}};
int line_map2 = sizeof(map2) / sizeof(map2[0]);


void *thread_routine(void* arg)
{
	while (1) {
		if (isSwitchOn(0) == 0) {
			print_led_map(map1, line_map1, 1000);
		}
	}
}

void interrupt_handler(void)
{
	print_led_map(map2, line_map2, 1000);
}

void exit_program(int signo)
{
	printf("프로그램 종료!\n");
	exit(1);
}  

int main(void)
{
	init_led_sw();
	signal(SIGINT, exit_program);
	if (setSwitchInterrupt(1, interrupt_handler) < 0)
	{
		printf("error: setSwitchInterrupt\n");
		exit(1);
	}

	pthread_t thread;
	pthread_create(&thread, NULL, thread_routine, NULL);

	while (1) {
		if (waitSwitchInterrupt(1, 5000) == -1) {
			printf("error: waitForInterrupt\n");
			exit(1);
		}
	}
	return 0;
}
