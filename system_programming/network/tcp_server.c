/*
 * TCP/IP 
 * => Socket Programming
 *
 * Socket
 * 1. Socket: data read / write
 * 2. Listen Socket(Server Socket): accept
 *
 * Server
 * 1. socket
 * 2. bind
 * 3. listen
 * 4. accept
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
	int csock;
	int len;
	char buf[100];

	// 1. socket
	// SOCK_STREAM: TCP
	// SOCK_DGRAM:  UDP
	int ssock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&saddr, 0, sizeof saddr);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000); // big endian of 5000;
	saddr.sin_addr.s_addr = INADDR_ANY;

	// 2. bind: set address
	// OOP implementation in C(Like message queue)
	if (bind(ssock, (struct sockaddr*)&saddr, sizeof(saddr)) == -1) {
		perror("bind");
		return 1;
	}

	// 3. listen: waiting connection
	listen(ssock, SOMAXCONN);

	memset(&caddr, 0, sizeof(caddr));
	caddrlen = sizeof(caddr);

	// 4. accept: create session
	csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
	printf("connection!!\n");

	// test
	// > $ telnet 127.0.0.1 5000


	// Echo Server
	while (1) {
		len = read(csock, buf, sizeof(buf));
		if (len == 0) {
			printf("End Connection!!\n");
		}
		else if (len == -1) {
			perror("read");
			break;
		}
		write(csock, buf, len);
	}

	// when server socket is killed, 
	close(csock);
	return 0;
}
