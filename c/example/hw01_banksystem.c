#include <stdio.h>

char menu(void);
int inputInt(const char *str);
void deposit(int *pAccount);
void withdraw(int *pAccount);
void printAccount(int account);
void printWrongInput(void);
void cleaningBuffer(void);

int main(void) {
	int account = 0;
	char ch;
	printAccount(account);
	while (1) {
		ch = menu();
		switch (ch) {
		case 'i':
			deposit(&account);
			break;
		case 'o':
			withdraw(&account);
			break;
		case 'q':
			printAccount(account);
			return 0;
		default:
			return 0;
		}

	}

}

char menu(void) {
	char ch;
	while (1) {
		ch = 'z';
		printf("# �޴��� �����Ͻÿ�(i-�Ա�, o-���, q-����) : ");
		scanf("%c", &ch);
		cleaningBuffer();

		switch (ch) {
		case 'i':
		case 'o':
		case 'q':
			return ch;
		default:
			printWrongInput();
			printf("\n");
		}
	}
}

int inputInt(const char *str) {
	int input;
	while (1) {
		input = -1;
		printf("%s", str);
		scanf("%d", &input);
		cleaningBuffer();

		if (input < 0) {
			printWrongInput();
		}
		else {
			return input;
		}
	}
}

void deposit(int *pAccount) {
	int money;
	money = inputInt("# �Աݾ��� �Է��ϼ��� : ");
	*pAccount += money;
	printAccount(*pAccount);
}

void withdraw(int *pAccount) {
	int money;
	money = inputInt("# ��ݾ��� �Է��ϼ��� : ");

	if (*pAccount < money) {
		printf("* �ܾ��� �����մϴ�.\n");
	}
	else {
		*pAccount -= money;
	}
	printAccount(*pAccount);
}

void printAccount(int account) {
	printf("* ���� �ܾ��� %d�� �Դϴ�.\n\n", account);
}

void printWrongInput(void) {
	printf("* �߸� �Է��ϼ̽��ϴ�.\n");
}

void cleaningBuffer(void) {
	while (getchar() != '\n') {
	}
}

