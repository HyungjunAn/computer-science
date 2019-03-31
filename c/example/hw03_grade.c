#include<stdio.h>
#include<string.h>
#define STUDENT_CNT (10)
#define NAME_LENGTH (20 + 1)
#define SUBJECT_CNT (3)

int menu();
void inputData(char name[][NAME_LENGTH], int score[][SUBJECT_CNT]);
void updateData(char name[][NAME_LENGTH], int score[][SUBJECT_CNT]);
void outputData(char name[][NAME_LENGTH], int score[][SUBJECT_CNT]);
int inputInt(const char *);
void myflush(void);

int main()
{
	char name[STUDENT_CNT][NAME_LENGTH];
	int score[STUDENT_CNT][SUBJECT_CNT];

	int choiceMenu;

	inputData(name, score);
	while (1) {
		choiceMenu = menu();
		if (choiceMenu == 3) {
			break;
		}
		switch (choiceMenu) {
		case 1: updateData(name, score); break;
		case 2: outputData(name, score); break;
		default:;
		}
	}
	return 0;
}

int menu()
{
	char menuList[][20] = { "update", "output", "quit" };
	int  menuCnt = (int)(sizeof(menuList) / sizeof(menuList[0]));
	int i;
	int choiceMenu;

	do {
		printf("-------------------\n");
		for (i = 0; i < menuCnt; i++) {
			printf("%d. %s\n", i + 1, menuList[i]);
		}
		printf("-------------------\n");
		choiceMenu = inputInt( "�޴��� �����ϼ���(1~3) : ");

	} while (choiceMenu < 1 || choiceMenu>menuCnt);
	return choiceMenu;
}

void inputData(char name[][NAME_LENGTH], int score[][SUBJECT_CNT])
{
	char subjectName[SUBJECT_CNT][50] = { "���� ���� : ","���� ���� : ", "���� ���� : " };
	int i, j;
	int input;

	for (i = 0; i < STUDENT_CNT; ++i) {
		printf("# %d�� �л� ���� �Է� : ", i+1);
		scanf("%s", name[i]);
		for (j = 0; j < SUBJECT_CNT; ++j) {
			do {
				input = inputInt(subjectName[j]);
			}
			while (input < 0 || input > 100);
			score[i][j] = input;
		}
	}
	return;
}

void updateData(char name[][NAME_LENGTH], int score[][SUBJECT_CNT])
{
	char subjectName[SUBJECT_CNT][50] = { "���� ���� ���Է� : ", "���� ���� ���Է� : ", "���� ���� ���Է� : " };
	int i, the_i;
	int input;
	char str[NAME_LENGTH];

	printf("# ������ �л����� �Է� : ");
	scanf("%s", str);
	for (i = 0; i < STUDENT_CNT; ++i) {
		if (strcmp(str, name[i]) == 0) {
			break;
		}
	}
	if (i == STUDENT_CNT) {
		printf("Not found!!!\n");
		return;
	}

	the_i = i;
	printf("# %s�� ���� ���Է�\n", name[the_i]);

	for (i = 0; i < SUBJECT_CNT; ++i) {
		do {
			input = inputInt(subjectName[i]);
		}
		while (input < 0 || input > 100);
		score[the_i][i] = input;
	}
	return;
}

void outputData(char name[][NAME_LENGTH], int score[][SUBJECT_CNT])
{
	int i, j;
	int sum;

	for (i = 0; i < STUDENT_CNT; ++i) {
		printf("%d. %s", i+1, name[i]);
		sum = 0;
		for (j = 0; j < SUBJECT_CNT; ++j) {
			sum += score[i][j];
			printf(" %d", score[i][j]);
		}
		printf(" %d %.2lf\n", sum, (double)sum / SUBJECT_CNT);
	}
	return;
}

int inputInt(const char *message)
{
	int number, res;
	while (1) {
		printf(message);
		res = scanf("%d", &number);
		myflush();
		if (res == 1) {
			break;
		}
	}
	return number;
}

void myflush(void) // �Է� ���� ���� �Լ�
{
	while (getchar() != '\n');
}
