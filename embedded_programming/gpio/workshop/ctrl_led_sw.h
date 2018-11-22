#ifndef _CTRL_LED_SW_H_
#define _CTRL_LED_SW_H_

#include <wiringPi.h>

#define LED_NUM 4
#define SW_NUM 2

extern int LED[];
extern int SW[];

void init_led_sw(void);
void set_led(int arr[4]);
void init_led(void);
void init_sw(void);

void off_led(void);
void print_led_map(int arr[][4], int line, int delayTime);

int isSwitchOn(int switch_num);
int setSwitchInterrupt(int switch_num, void (*interrupt_handler)(void));
int waitSwitchInterrupt(int switch_num, int delayTime);

#endif
