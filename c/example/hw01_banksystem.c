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
		printf("# 메뉴를 선택하시오(i-입금, o-출금, q-종료) : ");
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
	money = inputInt("# 입금액을 입력하세요 : ");
	*pAccount += money;
	printAccount(*pAccount);
}

void withdraw(int *pAccount) {
	int money;
	money = inputInt("# 출금액을 입력하세요 : ");

	if (*pAccount < money) {
		printf("* 잔액이 부족합니다.\n");
	}
	else {
		*pAccount -= money;
	}
	printAccount(*pAccount);
}

void printAccount(int account) {
	printf("* 현재 잔액은 %d원 입니다.\n\n", account);
}

void printWrongInput(void) {
	printf("* 잘못 입력하셨습니다.\n");
}

void cleaningBuffer(void) {
	while (getchar() != '\n') {
	}
}

