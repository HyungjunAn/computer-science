#include<stdio.h>
#include<string.h>
#define WORD_CNT (10)  // �ܾ� ���� symbolic ���
#define WORD_LENGTH (20)  // �ܾ� ���� symbolic ���
#define MEAN_LENGTH (80)  // �� ���� symbolic ���

struct Vocabulay {
	char word[20];    // �ܾ �����ϴ� ���
	char mean[80];    // �ܾ��� ���� �����ϴ� ���
	int len;          // �ܾ��� ���̸� �����ϴ� ���
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
		sprintf(inputMessage, "�޴��� �����ϼ���(1~%d) : ", menuCnt);
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
			printf("�ܾ����� ��á���ϴ�. �� �޴��� ���ư��ϴ�.\n");
			printf("\n");
			return;
		}
		inputStr("# �ܾ �Է��Ͻÿ�: ", word, WORD_LENGTH);
		if (strcmp(word, "end") == 0) {
			printf("\n");
			return;
		}
		inputStr("# ���� �Է��Ͻÿ�: ", mean, MEAN_LENGTH);
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
		inputStr("# �˻��� �ܾ �Է��Ͻÿ� : ", word, WORD_LENGTH);
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
			printf("�ܾ��� ��: %s\n", voca[i].mean);
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
		inputStr("# ������ �ܾ �Է��Ͻÿ� : ", word, WORD_LENGTH);
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
			inputStr("# ������ �����Ͻðڽ��ϱ�?(y/n) : ", answer, 2);
			if (strcmp(answer, "y") == 0) {
				start_i = i;
				for (i = start_i; i < *vocaCnt - 1; ++i) {
					voca[i] = voca[i+1];
				}
				--(*vocaCnt);
				printf("�����Ǿ����ϴ�.\n");

			}
			else {
				printf("������ ��ҵǾ����ϴ�.\n");
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

void myflush(void) // �Է� ���� ���� �Լ�
{
	while (getchar() != '\n');
}
