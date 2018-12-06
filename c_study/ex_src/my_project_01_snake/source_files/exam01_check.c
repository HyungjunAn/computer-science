#include<stdio.h>

#define TRUE 1
#define FALSE 0
#define NUMBER_LENGTH  13 /* 제품번호 길이 */
#define	INDEX_FACTORY_INFO (7-1)

int my_ctoi(const char ch);
int my_atoi(const char *p);
char *my_strcpy(char *p1, const char *p2, int size);
void dateExtract(char *serialNumber, int *year, int *mon, int *day);
int dateCheck(int year, int mon, int day);
int identificationCheck(char *serialNumber);
int yearCheck(int year);

int main()
{
	char serialNumber[20];
	const char *errMsg[] = { "D-ERR", "I-ERR", "VALID" }; // 결과 출력 시 사용하는 문자열
	int year, mon, day;

	scanf("%s", serialNumber); // 제품번호 입력
	dateExtract(serialNumber, &year, &mon, &day);
	if(dateCheck(year, mon, day) == FALSE)   // 생산날짜 오류체크
	{
		printf("%s\n", errMsg[0]);
	}
	else if(identificationCheck(serialNumber) == FALSE)  // 인식자번호 오류체크
	{
		printf("%s\n", errMsg[1]);
	}
	else {  // 정상제품 번호
		printf("%s\n", errMsg[2]);
	}
	return 0;
}

int my_ctoi(const char ch) {
	return ch - '0';
}
char *my_strcpy(char *p1, const char *p2, int size)
{
	int i = 0;
	for (i = 0; i != size && *(p2+i)!='\0'; ++i) {
		*(p1+i) = *(p2+i);
	}
	*(p1+i) = '\0';
	return p1;
}
int my_atoi(const char *p) {
	int n = 0;
	size_t i = 0;
	for (i = 0; *(p+i) != '\0'; ++i) {
		n = n*10 + my_ctoi(*(p+i));
	}
	return n;
}

void dateExtract(char *serialNumber, int *year, int *mon, int *day) {
	char buffer[NUMBER_LENGTH + 1];

	my_strcpy(buffer, serialNumber,   2);
	*year = my_atoi(buffer);
	int facProdNum = my_ctoi(serialNumber[INDEX_FACTORY_INFO]);
	if (facProdNum == 1 || facProdNum == 2) {
		*year += 1900;
	}
	else {
		*year += 2000;
	}

	my_strcpy(buffer, serialNumber+2, 2);
	*mon = my_atoi(buffer);

	my_strcpy(buffer, serialNumber+4, 2);
	*day = my_atoi(buffer);
}
int dateCheck(int year, int mon, int day) {
	int endDayofFeb;
	if (mon > 12) {
		return FALSE;
	}
	switch (mon) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return (day <= 31)? TRUE: FALSE;
		break;
	case 2:
		endDayofFeb = (yearCheck(year) == TRUE)? 29: 28;
		return (day <= endDayofFeb)? TRUE: FALSE;
		break;
	default:
		return (day <= 30)? TRUE: FALSE;
		break;
	}
}
int identificationCheck(char *serialNumber) {
	int n = 0;
	int i;
	for (i = 0; i < NUMBER_LENGTH - 1; ++i) {
		n += my_ctoi(serialNumber[i]);
	}
	int endNumber = my_ctoi(serialNumber[NUMBER_LENGTH - 1]);
	return (endNumber == n % 10)? TRUE: FALSE;
}
int yearCheck(int year) {
	if (year % 4 != 0) {
		return FALSE;
	}
	else if (year % 100 != 0) {
		return TRUE;
	}
	else if (year % 400 != 0) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}
