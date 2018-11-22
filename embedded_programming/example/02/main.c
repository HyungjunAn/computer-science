// LCD: Hello, world
// $ gcc hello.c ssd1306_i2c.c -lwiringPi
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include <softTone.h>
#include "ssd1306_i2c.h"

#define PIN 21

int scale [8] = {262, 294, 330, 349, 392, 440, 494, 525,};
int music[] = {5, 3, 3, 4, 2, 2, 1, 2, 3, 4, 5, 5, 5,};
int bit[]   = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2,};
int len = sizeof(music) / sizeof(music[0]);

int fd;

void interupt_handler(int signo)
{
	clearDisplay(fd);
	exit(1);
}

int getTime(char *str) {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
#if 0
	int tm_sec;    /* Seconds (0-60) */
	int tm_min;    /* Minutes (0-59) */
	int tm_hour;   /* Hours (0-23) */
	int tm_mday;   /* Day of the month (1-31) */
	int tm_mon;    /* Month (0-11) */
	int tm_year;   /* Year - 1900 */
	int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
	int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
	int tm_isdst;  /* Daylight saving time */
#endif
	sprintf(str, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	return rawtime;
}


void setAlram() {

}

int main() {
	char start_time[1000];
	char cur_time[1000];
	char countDown[1000];
	int target_sec;
	int cur_sec;
	int sec;

	wiringPiSetup() ;
	softToneCreate(PIN) ;
	fd = ssd1306I2CSetup(0x3C);  // i2c address를 인자로 전달하면 됩니다.


	displayOn(fd);
	signal(SIGINT, interupt_handler);

	scanf("%d", &sec);
	target_sec = getTime(start_time) + sec;
	cur_sec = !target_sec;
	while (target_sec != cur_sec) {
		cur_sec = getTime(cur_time);
		sprintf(countDown, "Remain: %02ds", target_sec - cur_sec);

		draw_line(1, 1, start_time);
		draw_line(2, 1, cur_time);
		draw_line(3, 1, countDown);
		updateDisplay(fd);
	}
	while (1) {
	int i;
		for (i = 0 ; i < len; ++i) {
			softToneWrite (PIN, scale[music[i] - 1]);
			//delay (200 * bit[i]);
		}
	}
	getchar();
	getchar();
	interupt_handler(0);
}
