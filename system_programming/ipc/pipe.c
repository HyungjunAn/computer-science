#include <unistd.h>
#include <signal.h>

#include <stdio.h>
int pipefd[2];

// ./a.out ps sort
int main(int argc, char **argv)
{
	int pipe1[2];
	int pipe2[2];
	pid_t pid;

	if (pipe(pipe1) == -1 ) {
		perror("pipe1");
		return 1;
	}
	if (pipe(pipe2) == -1 ) {
		perror("pipe2");
		return 1;
	}
	if (argc != 3) {
		perror("argc");
		return 1;
	}
	if ((pid = fork()) > 0) {
		// close unused pipe
		close(fd[0]);
		dup2(fd[1], 1);
		execlp(argv[1], argv[1], NULL);
	}
	else if (pid == 0) {
		close(fd[1]);
		dup2(fd[0], 0);
		execlp(argv[2], argv[2], NULL);
	}
	else {
		perror("fork");
		return 1;
	}
	return 0;
}
