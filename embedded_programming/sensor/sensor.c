#include <stdio.h>
#include <wiringPi.h>

#include <mcp3422.h>

#define TMP36 401
#define CDS 400

int main(void)
{
	wiringPiSetup();
	mcp3422Setup(400, 0x6a, 0, 0);

	while (1) {
		printf("%d\n", analogRead(CDS));
		int reading = analogRead(TMP36);
		double voltage = reading / 1000.;

		double temp = (voltage - 0.5) * 100;
		printf("%lf, %lf\n", voltage, temp);
		delay(1000);
	}
	return 0;
}
