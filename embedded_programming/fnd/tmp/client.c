#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>

#include "gpio_num.h"
#include <wiringPi.h>
#include <mcp3422.h>

double getTemp(void);
int getCds(void);
void setRaspberryPi(void);

int main()
{
	struct sockaddr_in saddr;
	char buf[512];
	int cnt = 0;

	int csock = socket(PF_INET, SOCK_STREAM, 0);
	if (csock == -1) {
		perror("socket");
		return 1;
	}

	memset(&saddr, 0, sizeof saddr);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(csock, (struct sockaddr*)&saddr, sizeof saddr) == -1) {
		perror("connect");
		return 1;
	}

	setRaspberryPi();
	while (1) {
		char sensor_type;
		int data_len;
		int cds;
		double temp;

		if (++cnt % 2) {
			sensor_type = 't';
			write(csock, &sensor_type, sizeof(sensor_type));
			temp = getTemp();
			data_len = sizeof(temp);
			write(csock, &data_len, sizeof(data_len));
			write(csock, &temp, sizeof(temp));

			//printf("temp: %.2lf\n", temp);
		}
		else {
			sensor_type = 'c';
			write(csock, &sensor_type, sizeof(sensor_type));
			cds = getCds();
			data_len = sizeof(cds);
			write(csock, &data_len, sizeof(data_len));
			write(csock, &cds, sizeof(cds));

			//printf("cds: %d\n", cds);
		}
	}
	close(csock);
}
double getTemp(void)
{
	int reading = analogRead(TMP36);
	double voltage = reading / 1000.0;
	return (voltage - 0.5) * 100;
}
int getCds(void)
{
	return analogRead(CDS);
}

void setRaspberryPi(void)
{
	wiringPiSetup();
	mcp3422Setup(400, 0x6a, 0, 0);
}








