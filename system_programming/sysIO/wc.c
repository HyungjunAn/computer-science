#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv) {
	FILE *fp;
	int ch;
	int flag = 0;

	int width = atoi(argv[2]);
	int char_cnt = 0;
	int line_cnt = 0;
	int word_cnt = 0;

	fp = fopen(argv[1], "r");

	while ((ch = fgetc(fp)) != EOF) {
		char_cnt++;
		if (ch == '\n') {
			++line_cnt;
		}

		if (!isspace(ch)) {
			if (flag == 0)
			{
				word_cnt++;
				flag = 1;
			}
		} else {
			flag = 0;
		}
	}
	printf("%*d %*d %*d %*s\n",
			width, word_cnt, width, line_cnt, width, char_cnt, width, argv[1]);
}
