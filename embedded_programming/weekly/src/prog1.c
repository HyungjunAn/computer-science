#include <wiringPi.h>
#include <softServo.h>
#include <mcp3422.h>  
#include <pthread.h>

#include <stdio.h>

#define SERVO 25
#define VR    403

int value;
void *servo_thread(void *arg) {
	int min_servo = -250;
	int max_servo = 1250;
	int servo_range = max_servo - min_servo;
	int servo;
	double angle;

	int min_value = 0;
	int max_value = 2047;
	int value_range = max_value - min_value;

	while (1) {
		servo = min_servo + ((((value - min_value) * servo_range)) / value_range);
		angle = ((double)(servo - min_servo) / servo_range) * 180;
		
		printf("value: %d, angle: %lf\n", value, angle);
		softServoWrite(SERVO, servo);
		delay(1);
	}
	return 0;
}

int main() {
	pthread_t thread;
	wiringPiSetup();
	mcp3422Setup(400, 0x6a, 0, 0);
	softServoSetup(SERVO, -1, -1, -1, -1, -1, -1, -1);

	pthread_create(&thread, NULL, servo_thread, NULL);

	while (1) {
		value = analogRead(VR);
		delay(1);
	}
}
