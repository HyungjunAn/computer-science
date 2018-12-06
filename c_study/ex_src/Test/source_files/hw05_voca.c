#include<stdio.h>
#include<string.h>
#define WORD_CNT (10)  // 단어 개수 symbolic 상수
#define WORD_LENGTH (20)  // 단어 길이 symbolic 상수
#define MEAN_LENGTH (80)  // 뜻 길이 symbolic 상수

struct Vocabulay {
	char word[20];    // 단어를 저장하는 멤버
	char mean[80];    // 단어의 뜻을 저장하는 멤버
	int len;          // 단어의 길이를 저장하는 멤버
};

int menu(const char **menuList, size_t menuCnt);
void inputWord(struct Vocabulay *voca, size_t *vocaCnt);
void outputWord(struct Vocabulay *voca, size_t *vocaCnt);
void searchWord(struct Vocabulay *voca, size_t *vocaCnt);
void deleteWord(struct Vocabulay *voca, size_t *vocaCnt);
int inputInt(const char *);
char* inputStr(const char *message, char *str, size_t size);
void myflush(void);

int main()
{
	struct Vocabulay voca[10];
	size_t vCnt = 0;
	const char *menuList[] = { "input", "output", "search", "delete", "quit" };
	size_t menuCnt = sizeof(menuList) / sizeof(menuList[0]);
	int choiceMenu;
	while (1) {
		choiceMenu = menu(menuList, menuCnt);
		if (choiceMenu == 5) {
			break;
		}
		switch (choiceMenu) {
		case 1: inputWord(voca, &vCnt); break;
		case 2: outputWord(voca, &vCnt); break;
		case 3: searchWord(voca, &vCnt); break;
		case 4: deleteWord(voca, &vCnt); break;
		default:;
		}
	}
	return 0;
}

int menu(const char **menuList, size_t menuCnt)
{
	size_t i;
	int choiceMenu;
	char inputMessage[100];
	do {
		printf("-------------------\n");
		for (i = 0; i < menuCnt; i++) {
			printf("%d. %s\n", i + 1, menuList[i]);
		}
		printf("-------------------\n");
		sprintf(inputMessage, "메뉴를 선택하세요(1~%d) : ", menuCnt);
		choiceMenu = inputInt(inputMessage);
	} while (choiceMenu < 1 || choiceMenu>menuCnt);
	myflush();
	return choiceMenu;
}

void inputWord(struct Vocabulay *voca, size_t *vocaCnt)
{
	char word[WORD_LENGTH];
	char mean[MEAN_LENGTH];

	printf("\n");
	while (1) {
		if (*vocaCnt == WORD_CNT) {
			printf("단어장이 꽉찼습니다. 주 메뉴로 돌아갑니다.\n");
			printf("\n");
			return;
		}
		inputStr("# 단어를 입력하시오: ", word, WORD_LENGTH);
		if (strcmp(word, "end") == 0) {
			printf("\n");
			return;
		}
		inputStr("# 뜻을 입력하시오: ", mean, MEAN_LENGTH);
		printf("\n");
		if (strcmp(mean, "end") == 0) {
			return;
		}
		strcpy(voca[*vocaCnt].word, word);
		strcpy(voca[*vocaCnt].mean, mean);
		voca[*vocaCnt].len = strlen(word);
		++(*vocaCnt);
	}
	return;
}

void outputWord(struct Vocabulay *voca, size_t *vocaCnt)
{
	int i;
	printf("\n");
	for (i = 0; i < *vocaCnt; ++i) {
		printf("%d. %s(%d) : %s\n", i+1, voca[i].word, voca[i].len, voca[i].mean);
	}
	printf("\n");
	return;
}

void searchWord(struct Vocabulay *voca, size_t *vocaCnt)
{
	int i;
	char word[WORD_LENGTH];

	printf("\n");
	while (1) {
		inputStr("# 검색할 단어를 입력하시오 : ", word, WORD_LENGTH);
		if (strcmp(word, "end") == 0) {
			printf("\n");
			return;
		}
		for (i = 0; i < *vocaCnt; ++i) {
			if (strcmp(voca[i].word, word) == 0) {
				break;
			}
		}
		if (i == *vocaCnt) {
			printf("Not found!!!\n");
		}
		else {
			printf("단어의 뜻: %s\n", voca[i].mean);
		}
		printf("\n");
	}
	return;
}

void deleteWord(struct Vocabulay *voca, size_t *vocaCnt)
{
	int i, start_i;
	char word[WORD_LENGTH];
	char answer[2];

	printf("\n");
	while (1) {
		inputStr("# 삭제할 단어를 입력하시오 : ", word, WORD_LENGTH);
		if (strcmp(word, "end") == 0) {
			printf("\n");
			return;
		}

		for (i = 0; i < *vocaCnt; ++i) {
			if (strcmp(voca[i].word, word) == 0) {
				break;
			}
		}
		if (i == *vocaCnt) {
			printf("Not found!!!\n");
		}
		else {
			inputStr("# 정말로 삭제하시겠습니까?(y/n) : ", answer, 2);
			if (strcmp(answer, "y") == 0) {
				start_i = i;
				for (i = start_i; i < *vocaCnt - 1; ++i) {
					voca[i] = voca[i+1];
				}
				--(*vocaCnt);
				printf("삭제되었습니다.\n");

			}
			else {
				printf("삭제가 취소되었습니다.\n");
			}
		}
		printf("\n");
	}
	return;
}

int inputInt(const char *message)
{
	int number, res;
	while (1) {
		printf(message);
		res = scanf("%d", &number);
		if (res == 1) {
			break;
		}
		else {
			myflush();
		}
	}
	return number;
}
char* inputStr(const char *message, char *str, size_t size) {
	printf(message);
	fgets(str, size, stdin);
	if (str[strlen(str) - 1] == '\n') {
		str[strlen(str) - 1] = '\0';
	}
	else {
		myflush();
	}
	return str;
}

void myflush(void) // 입력 버퍼 비우기 함수
{
	while (getchar() != '\n');
}
