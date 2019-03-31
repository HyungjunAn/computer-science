// LCD: Hello, world
// $ gcc hello.c ssd1306_i2c.c -lwiringPi
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <wiringPi.h>
#include "ssd1306_i2c.h"

int main() {
	char str[32] = " Hello, Pi";
	str[0] = 95 + 32;
	str[0] = 96 + 32;

	int fd = ssd1306I2CSetup(0x3C);  // i2c address를 인자로 전달하면 됩니다.
	displayOn(fd);


	// Text 출력 함수
	// draw_line(행, 열, 문자열)
	draw_line(1, 1, str);
	draw_line(2, 2, str);
	draw_line(3, 3, str);
	draw_line(4, 4, str);
	updateDisplay(fd);
	getchar();

	int i;
	//for(i = 0; i < 1024; i++) {
	clearDisplay(fd);
	sendData(fd, 0xff);
	sendData(fd, 0xff);
	sendData(fd, 0xff);
	//}
	getchar();

	sendData(fd, 0xff);
	getchar();

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

	clearDisplay(fd);
	getchar();
}













