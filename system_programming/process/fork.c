#include <unistd.h>

#include <stdio.h>

// COW(Copy On Write)
// - fork 시 메모리 복제는 프로세스가 생성될 때가 아니라 어느 한 쪽이 write를 했을 때이다.

// 1. 프로세스 생성함수 fork()
int ex1(void)
{
	fork();
	printf("good!\n");
	return 0;
}
signal
// 2. 부모 자식 프로세스의 구분
waitpid
int ex2(int tab, int n)
{
	int i;
	pid_t pid;

	if (n == tab)
		return 0;

	pid = fork();
	for (i = 0; i < tab; ++i)
		printf("\t");

	if (pid > 0) {
		// 부모
		printf("parent...\n");
		wait(3);
	} else if (pid == 0) {
		// 자식
		printf("child...\n");
		exit(3);
	} else {
		printf("error...\n");
	}
	return 0;
}
int main(void) {
	//ex1();
	ex2(0, 3);
	return 0;
}
