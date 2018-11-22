/*
 * TCP/IP 
 * => Socket Programming: Client
 *
 * Server
 * 1. socket
 * 2. connect
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

// Need for Internet Protocol
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string.h>

int main(void)
{
	struct sockaddr_in saddr;
	struct sockaddr_in caddr;
	socklen_t caddrlen;
	char buf[100];
	int ret;

	// 1. socket
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&saddr, 0, sizeof saddr);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000); // big endian of 5000;
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// 2. connect
	connect(sock, (struct sockaddr*)&saddr, sizeof(saddr));


	// Echo Server

	while ((ret = read(0, buf, sizeof buf)) > 0) {
		write(sock, buf, ret);

		ret = read(sock, buf, sizeof buf);
		write(1, buf, ret);
	}
	close(sock);

	// useage
	// > $ telnet 127.0.0.1 5000
	return 0;
}
