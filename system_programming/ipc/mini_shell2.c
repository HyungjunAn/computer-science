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
char *piped_user_cmd[2];
char *tokenized_cmd[2][TOKEN_NUM_MAX + 1];

int pipe_num;
int pipe_token_num[2];

int split_user_cmd_with_pipe(void);
int cd_process(void);
int clear_prompt(void);
int run_user_cmd(void);
int get_user_cmd(void);
int tokenizing(void);
int freeToken(void);

int main(void)
{
	char *argv[] = {"ls", "-l", NULL};
	int ret;
	int flag;
	
	if (!clear_prompt()) {
		return 1;
	}

	flag = 0;
	while (flag == 0) {
		getcwd(path, PATH_LEN_MAX);
		printf("[%s] > ", path);
		if (get_user_cmd()
			&& split_user_cmd_with_pipe()
			&& tokenizing()
			&& run_user_cmd()) {
			;
		}
		freeToken();
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
int split_user_cmd_with_pipe(void) {
	char *p;
	char split_key[] = "|";
	int i = 0;
	for (p = strtok(user_cmd, split_key); p != NULL; p = strtok(NULL, split_key)) {
		piped_user_cmd[i++] = strdup(p);
		if (i  == 2) {
			break;
		}
	}
	pipe_num = i;
	return i;
}
int tokenizing() {
	char *p;
	char split_key[] = " ";
	int i = 0;
	int j = 0;
	for (i = 0; i < pipe_num; ++i) {
		j = 0;
		for (p = strtok(piped_user_cmd[i], split_key); p != NULL; p = strtok(NULL, split_key)) {
			if (strlen(p) > ARG_LEN_MAX || j == TOKEN_NUM_MAX) {
				return 0;
			}
			tokenized_cmd[i][j++] = strdup(p);
		}
		tokenized_cmd[i][j] = NULL;
		pipe_token_num[i] = j;
	}
	return i;
}
int freeToken() {
	int i;
	int j;
	for (i = 0; i < pipe_num; ++i) {
		for (j = 0; j < pipe_token_num[i]; ++j) {
			free(tokenized_cmd[i][j]);
		}
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
	if (tokenized_cmd[0][1] == NULL
			|| strcmp(tokenized_cmd[0][1], "~") == 0) {
		user_id = getuid();
		u_info=getpwuid(user_id);
		chdir(u_info->pw_dir);
	} else if (strcmp(tokenized_cmd[0][1], ".") == 0) {
		;
	} else if (strcmp(tokenized_cmd[0][1], "..") == 0) {
		chdir("..");
	} else {
		if (chdir(tokenized_cmd[0][1]) == -1) {
			perror("cd: ");
			return 0;
		}
	}
	return 1;
}
int run_user_cmd(void) {
	pid_t pid;
	if (strcmp(tokenized_cmd[0][0], "cd") == 0) {
		cd_process();
		return 1;
	}
	pid = fork();
	if (pid == 0) {
		if (pipe_num == 2) {
			int fd[2];
			if (pipe(fd) == -1) {
				perror("pipe");
				return 1;
			}
			if ((pid = fork()) > 0) {
				wait(NULL);
				close(fd[1]);
				dup2(fd[0], 0);
				execvp(tokenized_cmd[1][0], tokenized_cmd[1]);
			} else if (pid == 0) {
				close(fd[0]);
				dup2(fd[1], 1);
				execvp(tokenized_cmd[0][0], tokenized_cmd[0]);
			} else {
				perror("fork");
				return 0;
			}
		}
		else {
			execvp(tokenized_cmd[0][0], tokenized_cmd[0]);
		}
	} else if (pid < 0) {
		return 0;
	}
	wait(NULL);
	return 1;
}
