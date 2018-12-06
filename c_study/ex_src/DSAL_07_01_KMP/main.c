#include <stdio.h>
#include <string.h>
#include <limits.h>

#define LEN_MAX 100

int next_data[LEN_MAX];
int cnt;

void mkNextData(const char *str) {
	int i;
	int j = 0;
	int wLen = strlen(str);

	for (i = 1; i < wLen; ++i) {
		while (j > 0 && str[i] != str[j]) {
			j = next_data[j];
		}
		if (str[i] == str[j]) {
			next_data[i+1] = ++j;
		}
	}
	next_data[0] = -1;
}


int find(const char *sentence, const char *word) {
	int i = 0;
	int j = 0;
	int sLen = strlen(sentence);
	int wLen = strlen(word);

	while (i < sLen) {
		while (j < wLen && sentence[i+j] == word[j]) {
			++j;
			++cnt;
		}
		if (j == wLen) {
			//return i;
		}

		i = i + j - next_data[j];
		if (j != 0) {
			j = next_data[j];
		}
	}
	return -1;
}

int main(void) {
	char sentence[] = "ABCABCDABABCDABCDABDE";
	char word[LEN_MAX] = "ABCDABD";
	mkNextData(word);
	int i;
	int wLen = strlen(word);
	printf(" %s\n", word);
	for (i = 0; i <= wLen; ++i) {
		printf("%d", next_data[i]);
	}

	printf("\n");
	int n = find(sentence, word);
	if (n == -1) {
		printf("not found\n");
	}
	else {
		printf("%s\n", sentence + n);
	}
	printf("%d %d %d\n", (int)strlen(sentence), (int)strlen(word), cnt);
	getchar();

	return 0;
}
