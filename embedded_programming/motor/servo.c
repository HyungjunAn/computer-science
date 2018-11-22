#include <stdio.h>

#include <wiringPi.h>
#include <softServo.h>


#define SERVO 25

int main(void)
{
	wiringPiSetup();


	softServoSetup(SERVO, -1, -1, -1, -1, -1, -1, -1);

	int degree = -250;
	while (1) {
		getchar();
		softServoWrite(SERVO, degree);
		delay(5);
		degree += 100;
	}
	return 0;
}
