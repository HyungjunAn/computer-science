#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define 	MAXBUFF 	1024

void client(int readfd, int writefd){
	int len;
	char ch;
	char user_cmd[MAXBUFF + 1];

	printf("client> ");
	fgets(user_cmd, MAXBUFF, stdin);
	len = strlen(user_cmd);
	user_cmd[len - 1] = '\0';
	len--;
	write(writefd, user_cmd, len);

	while (read(readfd, &ch, 1) == 1) {
		printf("%c", ch);
	}
}


void server(int readfd, int writefd){
	char *p;
	char *cmd;
	char *arg;

	char ch;
	char user_cmd[MAXBUFF + 1];
	char buff[MAXBUFF + 1];
	int i = 0;
	struct dirent* dirent_p;
	DIR* dp;
	char sz_list[] = "list: ";
	char unkown[] = "Unknown command...\n";
	int n = read(readfd, user_cmd, MAXBUFF);
	user_cmd[n] = '\0';

	p = strtok(user_cmd, " ");
	cmd = strdup(p);
	p = strtok(NULL, "");
	if (p != NULL) {
		arg = strdup(p);
		while (isspace(arg[0])) {
			arg++;
		}
	}
	if (strcmp(cmd, "list") == 0) {
		DIR* dp = opendir(".");
		if (dp == NULL) {
			perror("opendir");
			return;
		}
		while ((dirent_p = readdir(dp)) != NULL) {
			write(writefd, sz_list, strlen(sz_list));
			write(writefd, dirent_p->d_name, strlen(dirent_p->d_name));
			write(writefd, "\n", 1);
		}
		closedir(dp);
	} else if (strcmp(cmd, "read") == 0) {
		if (strcmp(arg, "") == 0) {
			printf("error");
			return;
		} 
		int fd = open(arg, 0);
		while ((n = read(fd, buff, MAXBUFF)) > 0)
			write(writefd, buff, n);
		close(fd);
	} else {
		write(writefd, unkown, strlen(unkown));
	}

	return;
}

int main(void){
	int 	childpid, pipe1[2], pipe2[2];

	if(pipe(pipe1) < 0 || pipe(pipe2) < 0)
		printf("pipe error");

	childpid = fork();
	if (childpid > 0) {
		close(pipe1[0]);
		close(pipe2[1]);
		client(pipe2[0], pipe1[1]);
		while(wait((int *) 0) != childpid);
		close(pipe1[1]);
		close(pipe2[0]);
	} else { 		
		close(pipe1[1]);
		close(pipe2[0]);
		server(pipe1[0], pipe2[1]);
		close(pipe1[0]);
		close(pipe2[1]);
	}
} 

