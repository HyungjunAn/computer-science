#include <stdio.h>
#include <wiringPi.h>

int main()
{
	wiringPiSetup();
	pinMode(27, INPUT);
}
