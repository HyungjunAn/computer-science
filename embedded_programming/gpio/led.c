#include <stdio.h>
#include <wiringPi.h>


// LED PIN
#define SW  4
#define LED 27

void blink(void)
{
	digitalWrite(LED, 0);
	if (digitalRead(SW) == 0) {
		digitalWrite(LED, HIGH);
		printf("digitalRead(SW) == 0\n");
	}
	else {
		printf("digitalRead(SW) == 1\n");
	}
}

int main(void)
{
	wiringPiSetup();

	pinMode(SW, INPUT);
	pinMode(LED, OUTPUT);

	while (1) {
	}


	printf("Raspberry Pi Blink....\n");
	
	wiringPiSetup(); 		// 라이브러리 초기화

	pinMode(LED, OUTPUT); 		// echo out > direction

	while (1) {
		digitalWrite(LED, HIGH);
		delay(500);
		digitalWrite(LED, LOW);
		delay(500);
	}
}
