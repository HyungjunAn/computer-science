#include <stdio.h>

unsigned char getBit(unsigned char num, int i);
void setBit(unsigned char* num, int i);
void clearBit(unsigned char* num, int i);
void reverseBit(unsigned char* num);

int inputInt(const char *str, int min_n, int max_n);

void fan_on(unsigned char *fan);
void fan_off(unsigned char *fan);
void fan_reverse(unsigned char *fan);
void display(unsigned char fan_set);

int control_menu(void);
void printWrongInput(void);
void cleaningBuffer(void);



int main()
{
	unsigned char fan_set=0;
	int res=0;

	while(1)
	{
		res=control_menu();
		switch (res) {
			case 1:
				fan_on(&fan_set);
				break;
			case 2:
				fan_off(&fan_set);
				break;
			case 3:
				fan_reverse(&fan_set);
				break;
			case 4:
				display(fan_set);
				return 0;
			default:
				break;
		}
	}
	return 0;
}


void fan_on(unsigned char *fan) {
	printf("-----------------------------------------------\n");
	printf("                     Fan 열기 작업 실행 화면\n");
	printf("-----------------------------------------------\n");
	int input = inputInt("* OPEN할 FAN 번호를 입력하시오(1-8) : ", 1, 8);
	setBit(fan, input - 1);
	display(*fan);
}
void fan_off(unsigned char *fan) {
	printf("-----------------------------------------------\n");
	printf("                     Fan 닫기 작업 실행 화면\n");
	printf("-----------------------------------------------\n");
	int input = inputInt("* CLOSE할 FAN 번호를 입력하시오(1-8) : ", 1, 8);
	clearBit(fan, input - 1);
	display(*fan);
}
void fan_reverse(unsigned char *fan) {
	printf("-----------------------------------------------\n");
	printf("                     Fan 전체 전환 작업 실행 화면\n");
	printf("-----------------------------------------------\n");
	printf("            전체 FAN의 상태가 전환되었습니다. (ON, OFF 상태 뒤바뀜)\n");
	reverseBit(fan);
	display(*fan);
}
void display(unsigned char fan_set) {
	printf("-----------------------------------------------\n");
	int i;
	for (i = 0; i < 8; ++i) {
		printf("%d번FAN  ", 8-i);
	}
	printf("\n");
	for (i = 0; i < 8; ++i) {
		printf("%6s  ", (getBit(fan_set, 8-i-1) == 1)? "ON": "OFF");
	}
	printf("\n");
	printf("-----------------------------------------------\n");
	printf("\n");
}

int control_menu(void)
{
	int number;
	while (1) {
		number = -1;
		printf("1. 환풍구 열기 / 2. 환풍구 닫기 / 3. 환풍구 전체 전환 / 4. 종료 : ");
		scanf("%d", &number);
		cleaningBuffer();

		switch (number) {
		case 1:
		case 2:
		case 3:
		case 4:
			return number;
		default:
			printWrongInput();
			break;
		}
	}
}

int inputInt(const char *str, int min_n, int max_n) {
	int input;
	int check_scanf;
	while (1) {
		printf("%s", str);
		check_scanf = scanf("%d", &input);
		cleaningBuffer();

		if (check_scanf == 1 && input >= min_n && input <= max_n) {
			return input;
		}
		else {
			printWrongInput();
		}
	}
}


void printWrongInput(void) {
	printf("잘못 입력하셨습니다. 다시 입력하세요.\n\n");
}

void cleaningBuffer(void) {
	while (getchar() != '\n') {
	}
}
unsigned char getBit(unsigned char num, int i)
{
	int n = 1 << i;
	return ((num & n) > 0)? 1: 0;
}

void setBit(unsigned char* num, int i)
{
	int n = 1 << i;
	*num |= n;
}

void clearBit(unsigned char* num, int i)
{
	int n = 1 << i;
	n = ~n;
	*num &= n;
}

void reverseBit(unsigned char* num)
{
	*num = ~(*num);
}
