#include <stdio.h>

char *myStrcpy(char *p1,const char *p2);
size_t myStrlen(const char *p);
int myStrcmp(const char *p1,const char *p2);
const char *myStrchr(const char *p1, int c);
const char *myStrstr(const char *p1,const char *p2);
char *myStrcat(char *p1,const char *p2);
int myAtoi(const char *p);

int main(void)
{

	char str1[40];
	char str2[40] = "ab";

	printf("myStrcpy(str1, \"myStrcpy\") : %s\n", myStrcpy(str1, "myStrcpy"));
	printf("myStrlen(\"myStrlen\") : %I64d\n", myStrlen("myStrlen"));
	printf("myStrcmp(\"abc\", \"abd\") : %d\n", myStrcmp("abc", "abd"));
	printf("myStrcmp(\"abd\", str2) : %d\n", myStrcmp("abd", str2));
	printf("myStrcmp(\"abc\", \"abc\") : %d\n", myStrcmp("abc", "abc"));
	printf("myStrchr(\"abcdedg\", 'd') : %s\n", myStrchr("abcdedg", 'd'));
	printf("myStrstr(\"zxcvasdfqwert\", \"dfq\") : %s\n", myStrstr("zxcvasdfqwert", "dfq"));
	printf("myStrcat(str1, \"myStrcat\") : %s\n", myStrcat(str1, "myStrcat"));
	printf("myAtoi(\"123400\") : %d\n", myAtoi("123400"));
	return 0;
}

//p1�� ��ġ�� p2���ڿ� ����(return value : p1�� ������ġ)
char *myStrcpy(char *p1,const char *p2)
{
	int i = 0;
	while (p2[i] != '\0') {
		p1[i] = p2[i];
		i++;
	}
	p1[i] = '\0';
	return p1;
}
// ���ڿ��� ���� ���ϱ�(return value : ���ڿ��� ����) - '\0'���ڸ� ������ ���ڿ��� ���� ��
size_t myStrlen(const char *p)
{
	size_t size = 0;
	while (p[size] != '\0') {
		size++;
	}
	return size;
}
// p1���ڿ��� p2���ڿ� �� (return value : ���������� p1�� �տ� ������ ����, p1�� p2�� ������ 0, p1�� �ڿ� ������ ���)
//  - ���ڿ� �� ��� : byte �� byte�� �ƽ�Ű�ڵ� ��
int myStrcmp(const char *p1,const char *p2)
{
	int i;
	int check;
	while (p1[i] != '\0' || p2[i] != '\0') {
		if (p1[i] != p2[i]) {
			break;
		}
		i++;
	}
	check = p1[i] - p2[i];

	if (check > 0) {
		return 1;
	}
	else if (check < 0) {
		return -1;
	}
	else {
		return 0;
	}
}
// p1 ���ڿ����� c���� �˻� (return value : ù��°�� �˻��� c������ �ּ� / ��ã�� ��� NULL pointer��ȯ)
const char *myStrchr(const char *p1, int c)
{
	int i = 0;
	while (p1[i] != '\0') {
		if (p1[i] == c) {
			return p1 + i;
		}
		++i;
	}
	return NULL;
}
// p1 ���ڿ����� p2���ڿ� �˻� (return value : p2�� ��ġ�ϴ� �κ��� �����ּ� / ��ã�� ��� NULL pointer��ȯ)
const char *myStrstr(const char *p1,const char *p2)
{
	int i, j;
	size_t matching_cnt;

	size_t p2_len = myStrlen(p2);
	for (i = 0; p1[i] != '\0'; ++i) {
		matching_cnt = 0;
		for (j = 0; p2[j] != '\0'; ++j) {
			if (p1[i+j] != '\0' && p1[i+j] == p2[j]) {
				matching_cnt++;
			}
		}
		if (matching_cnt == p2_len) {
			return p1+i;
		}
	}
	return NULL;
}
// p2 ���ڿ��� p1���ڿ� �ڿ� ���� (return value : p1�� ������ġ)
char *myStrcat(char *p1,const char *p2)
{
	size_t p1_size = myStrlen(p1);
	int i = 0;
	while (p2[i] != '\0') {
		p1[p1_size + i] = p2[i];
		i++;
	}
	p1[p1_size + i] = '\0';
	return p1;
}
// ���ڿ��� 10�� ������ ��ȯ (return value : ��ȯ�� 10���� / ��ȯ�Ұ����� ���ڰ� ���Ե� ��� 0 ��ȯ)

int myAtoi(const char *p)
{
	size_t p_size = myStrlen(p);
	int isNegative = 0;

	int boundary_i = 0;
	if (p[0] == '-') {
		isNegative = 1;
		boundary_i = 1;
	}
	int i = p_size - 1;
	int sum = 0;
	int mul = 1;
	while (boundary_i <= i) {
		if (p[i] < '0' || p[i] > '9') {
			return 0;
		}
		sum += (p[i] - '0') * mul;
		mul *= 10;
		--i;
	}
	return (isNegative != 0)? -sum: sum;
}
