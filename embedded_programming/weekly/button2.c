#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <wiringPi.h>


// Interrupt 기반

#define SW 4

// ISR(Interrupt Service Routine)
//  : 등록한 인터럽트가 발생하면 호출되는 함수

void blink(void)
{
	static time_t t = -1;
	time_t target;
	int sec = 3;
	if (t != -1) {
		printf("버튼 뗌\n");
		t = -1;
		return;
	}
	printf("버튼 누름\n");
	t = time(NULL);
	target = t + sec;

	while (t < target) {
		t = time(NULL);
	}
	printf("%ds 경과\n", sec);

#if 0
	int sec = 3;
	printf("인터럽트 신호 발생...\n");
	switch (waitForInterrupt(SW, sec * 1000)) {
		case 0: 
			printf("%ds 경과\n", sec);
			break;
		case -1:
			printf("error...\n");
			exit(1);
	}
	wiringPiISR(SW, INT_EDGE_FALLING, blink);
#endif
}

// INT_EDGE_FALLING: 5V -> 0V  : 버튼을 누르는 시점
// INT_EDGE_RISING: 0V -> 5V   : 버튼을 띄는 시점

int main()
{
	wiringPiSetup();

	// 1. 인터럽트를 사용하기 위해서는 INPUT 모드로 사용해야 합니다.
	pinMode(SW, INPUT);
	// 2. wiringPiISR을 통해 인터럽트 핸들러를 등록한다.
	while (1) {
		time_t t = 0;
		time_t target;
		int sec = 3;
		if (digitalRead(SW) == 0) {
			printf("버튼 누름\n");
			t = time(NULL);
			target = t + sec;
		}
		while (t) {
			if (t >= target) {
				printf("경과\n", sec);
			}
			if (digitalRead(SW) == 0) {
				t = time(NULL);
			}
			else {
				t = 0;
				printf("버튼 뗌\n");
			}
		}
	}
	wiringPiISR(SW, INT_EDGE_BOTH, blink);

	while (1) {
		;
	}
}












