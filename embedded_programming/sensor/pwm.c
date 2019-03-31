
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include <wiringPi.h>
#include <softPwm.h>

// PWM 제어를 통해서 LED 밝기를 조절하고자 한다. 

#define LED2   23 // BCM: 13(PWM1)  - Red
#define LED1   26 // BCM: 12(PWM0)  - Green
#define LED3   22 // BCM: 12(PWM0)  - Green

void func(void)
{
	pwmWrite(LED1, 0);
	pwmWrite(LED2, 0);
}


void off_led(int signo)
{
	pwmWrite(LED1, 0);
	pwmWrite(LED2, 0);
	softPwmWrite(LED3, 0);
	exit(1);
}

int main()
{
	int bright;
	wiringPiSetup();

	pinMode(LED1, PWM_OUTPUT);
	pinMode(LED2, PWM_OUTPUT);
	pinMode(LED3, OUTPUT);

	pwmWrite(LED1, 0);
	pwmWrite(LED2, 0);

	softPwmCreate(LED3, 0, 1024);
	softPwmWrite(LED3, 0);

	signal(SIGINT, off_led);

	while (1) {
		for (bright = 0; bright < 1024 ; ++bright) {
			pwmWrite(LED1, bright);
			pwmWrite(LED2, bright);
			softPwmWrite(LED3, bright);
			delay(1);
		}

		for (bright = 1024; bright >= 0 ; --bright) {
			pwmWrite(LED1, bright);
			pwmWrite(LED2, bright);
			softPwmWrite(LED3, bright);
			delay(1);
		}
	}
}













