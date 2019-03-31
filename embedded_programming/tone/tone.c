#include <wiringPi.h>
#include <softTone.h>

#include <stdio.h>

#define PIN 21

int scale [8] = { 262, 294, 330, 349, 392, 440, 494, 525 } ;
int music[] = {
	5, 3, 3, 4, 2, 2, 1, 2, 3, 4, 5, 5, 5, 
};
int bit[] = {
	1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2,
};
int len = sizeof(music) / sizeof(music[0]);
int main ()
	int i ;
	wiringPiSetup() ;
	softToneCreate(PIN) ;

	while (1)
	{
		for (i = 0 ; i < len; ++i)
		{
			softToneWrite (PIN, scale[music[i] - 1]);
			delay (200 * bit[i]);
		}
	}
}

