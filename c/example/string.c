/*
 * string.c
 *
 *  Created on: 2018. 10. 18.
 *      Author: pyjune
 */
#include <stdio.h>

//p1�� ��ġ�� p2���ڿ� ����(return value : p1�� ������ġ)
char *myStrcpy(char *p1,const char *p2);
// ���ڿ��� ���� ���ϱ�(return value : ���ڿ��� ����) - '\0'���ڸ� ������ ���ڿ��� ���� ��
size_t myStrlen(const char *p);
// p1���ڿ��� p2���ڿ� �� (return value : ���������� p1�� �տ� ������ ����, p1�� p2�� ������ 0, p1�� �ڿ� ������ ���)
//  - ���ڿ� �� ��� : byte �� byte�� �ƽ�Ű�ڵ� ��
int myStrcmp(const char *p1,const char *p2);
// p1 ���ڿ����� c���� �˻� (return value : ù��°�� �˻��� c������ �ּ� / ��ã�� ��� NULL pointer��ȯ)
const char *myStrchr(const char *p1, int c);
// p1 ���ڿ����� p2���ڿ� �˻� (return value : p2�� ��ġ�ϴ� �κ��� �����ּ� / ��ã�� ��� NULL pointer��ȯ)
const char *myStrstr(const char *p1,const char *p2);
// p2 ���ڿ��� p1���ڿ� �ڿ� ���� (return value : p1�� ������ġ)
char *myStrcat(char *p1,const char *p2);
// ���ڿ��� 10�� ������ ��ȯ (return value : ��ȯ�� 10���� / ��ȯ�Ұ����� ���ڰ� ���Ե� ��� 0 ��ȯ)
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
	printf("myAtoi(\"123400\") : %d\n", myAtoi("-123400"));
	return 0;
}

//p1�� ��ġ�� p2���ڿ� ����(return value : p1�� ������ġ)
char *myStrcpy(char *p1,const char *p2)
{
	int i = 0;
	while(*(p2+i)!='\0')
	{
		*(p1+i) = *(p2+i);
		i++;
	}
	*(p1+i) = '\0';
	return p1;
}
// ���ڿ��� ���� ���ϱ�(return value : ���ڿ��� ����) - '\0'���ڸ� ������ ���ڿ��� ���� ��
size_t myStrlen(const char *p)
{
	size_t i = 0;
	while(*(p+i)!='\0')
	{
		i++;
	}
	return i;
}
// p1���ڿ��� p2���ڿ� �� (return value : ���������� p1�� �տ� ������ ����, p1�� p2�� ������ 0, p1�� �ڿ� ������ ���)
//  - ���ڿ� �� ��� : byte �� byte�� �ƽ�Ű�ڵ� ��
int myStrcmp(const char *p1,const char *p2)
{
	size_t i = 0;
	while((*(p1+i))!='\0')
	{
		if(*(p1+i)!=*(p2+i))
			break;
		i++;
	}
	return (*(p1+i)-*(p2+i));
}
// p1 ���ڿ����� c���� �˻� (return value : ù��°�� �˻��� c������ �ּ� / ��ã�� ��� NULL pointer��ȯ)
const char *myStrchr(const char *p1, int c)
{
	size_t i = 0;
	while(*(p1+i)!='\0')
	{
		if(*(p1+i) == c)
			return (p1+i);
		i++;
	}
	return NULL;
}
// p1 ���ڿ����� p2���ڿ� �˻� (return value : p2�� ��ġ�ϴ� �κ��� �����ּ� / ��ã�� ��� NULL pointer��ȯ)
const char *myStrstr(const char *p1,const char *p2)
{
	size_t i = 0;
	size_t j = 0;;
	while(*(p1+i) != '\0')
	{
		j = 0;
		while((*(p1+i+j) != '\0') && (*(p2+j) != '\0'))
		{
			if(*(p1+i+j) != *(p2+j))
				break;
			j++;
		}
		if(*(p2+j) == '\0')
			return (p1+i);
		i++;
	}
	return NULL;
}
// p2 ���ڿ��� p1���ڿ� �ڿ� ���� (return value : p1�� ������ġ)
char *myStrcat(char *p1,const char *p2)
{
	size_t i = 0;
	size_t j = 0;
	while(*(p1+i) != '\0')
	{
		i++;
	}
	while(*(p2+j) != '\0')
	{
		*(p1+i+j) = *(p2+j);
		j++;
	}
	*(p1+i+j) = '\0';
	return p1;
}
// ���ڿ��� 10�� ������ ��ȯ (return value : ��ȯ�� 10���� / ��ȯ�Ұ����� ���ڰ� ���Ե� ��� 0 ��ȯ)
int myAtoi(const char *p)
{
	int n = 0;
	size_t i = 0;
	int s = 1;
	if(p[0]=='-')
	{
		s = -1;
		i++;
	}
	while(*(p+i) != '\0')
	{
		if((*(p+i) < '0') || (*(p+i) > '9'))
		{
			return 0;
		}
		n = n*10 + (*(p+i) - '0');
		i++;
	}
	return (n * s);
}