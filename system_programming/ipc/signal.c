#include <unistd.h>
#include <signal.h>

#include <stdio.h>

int main(void) {
	printf("SIGINT 동작 무시\n");
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	getchar();
	getchar();

	printf("SIGINT 재동작\n");
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
