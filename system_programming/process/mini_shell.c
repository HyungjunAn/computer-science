#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_LEN_MAX 256
#define INPUT_LEN_MAX 1024
#define TOKEN_NUM_MAX 32
#define ARG_LEN_MAX 32

#define DIRFLAG_NONE 0x00
#define DIRFLAG_HOME 0x01
#define DIRFLAG_UP   0x02


char path[PATH_LEN_MAX + 1];
char user_cmd[INPUT_LEN_MAX + 1];
char *tokenized_cmd[TOKEN_NUM_MAX + 1];

int cd_process(void);
int clear_prompt(void);
int run_user_cmd(void);
int get_user_cmd(void);
int tokenizing(void);
int freeToken(int tokenNum);

int main(void)
{
	char *argv[] = {"ls", "-l", NULL};
	int ret;
	int flag;
	int tokenNum;
	
	if (!clear_prompt()) {
		return 1;
	}

	flag = 0;
	while (flag == 0) {
		getcwd(path, PATH_LEN_MAX);
		printf("[%s] > ", path);
		tokenNum = 0;
		if (get_user_cmd()
			&& (tokenNum = tokenizing())
			&& run_user_cmd()) {
			;
		}
		freeToken(tokenNum);
	}
	printf("Bye Bye~\n");
	return 0;
}
int get_user_cmd(void) {
	int len;
	fgets(user_cmd, INPUT_LEN_MAX, stdin);
	
	len = strlen(user_cmd);
	if (user_cmd[len - 1] == '\n') {
		user_cmd[len - 1] ='\0';
	}
	return 1;
}
int tokenizing(void) {
	char *p;
	char split_key[] = "\\ ";
	int i = 0;
	for (p = strtok(user_cmd, split_key); p != NULL; p = strtok(NULL, split_key)) {
		if (strlen(p) > ARG_LEN_MAX || i == TOKEN_NUM_MAX) {
			return 0;
		}
		tokenized_cmd[i++] = strdup(p);
	}
	tokenized_cmd[i] = NULL;
	return i;
}
int freeToken(int tokenNum) {
	int i;
	for (i = 0; i < tokenNum; ++i) {
		free(tokenized_cmd[i]);
	}
	return 1;
}
int clear_prompt(void) {
	int status;
	char *cmd[] = {"clear", NULL};
	pid_t pid = fork();
	if (pid == 0) {
		execvp(cmd[0], cmd);
		exit(3);
	} else if (pid < 0) {
		return 0;
	}
	wait(&status);
	return 1;
}
int cd_process(void) {
	uid_t user_id;
	struct passwd *u_info;
	if (tokenized_cmd[1] == NULL
			|| strcmp(tokenized_cmd[1], "~") == 0) {
		user_id = getuid();
		u_info=getpwuid(user_id);
		chdir(u_info->pw_dir);
	} else if (strcmp(tokenized_cmd[1], ".") == 0) {
		;
	} else if (strcmp(tokenized_cmd[1], "..") == 0) {
		chdir("..");
	} else {
		if (chdir(tokenized_cmd[1]) == -1) {
			perror("cd: ");
			return 0;
		}
	}
	return 1;
}
int run_user_cmd(void) {
	pid_t pid;
	if (strcmp(tokenized_cmd[0], "cd") == 0) {
		cd_process();
		return 1;
	}

	pid = fork();
	if (pid == 0) {
		execvp(tokenized_cmd[0], tokenized_cmd);
		exit(3);
	} else if (pid < 0) {
		return 0;
	}
	wait(NULL);
	return 1;
}
