/*
 * string.c
 *
 *  Created on: 2018. 10. 18.
 *      Author: pyjune
 */
#include <stdio.h>

//p1의 위치에 p2문자열 복사(return value : p1의 시작위치)
char *myStrcpy(char *p1,const char *p2);
// 문자열의 길이 구하기(return value : 문자열의 길이) - '\0'문자를 제외한 문자열의 글자 수
size_t myStrlen(const char *p);
// p1문자열과 p2문자열 비교 (return value : 사전순서상 p1이 앞에 있으면 음수, p1과 p2가 같으면 0, p1이 뒤에 있으면 양수)
//  - 문자열 비교 방법 : byte 대 byte로 아스키코드 비교
int myStrcmp(const char *p1,const char *p2);
// p1 문자열에서 c문자 검색 (return value : 첫번째로 검색된 c문자의 주소 / 못찾은 경우 NULL pointer반환)
const char *myStrchr(const char *p1, int c);
// p1 문자열에서 p2문자열 검색 (return value : p2와 일치하는 부분의 시작주소 / 못찾은 경우 NULL pointer반환)
const char *myStrstr(const char *p1,const char *p2);
// p2 문자열을 p1문자열 뒤에 연결 (return value : p1의 시작위치)
char *myStrcat(char *p1,const char *p2);
// 문자열을 10진 정수로 변환 (return value : 변환된 10진수 / 변환불가능한 문자가 포함된 경우 0 반환)
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

//p1의 위치에 p2문자열 복사(return value : p1의 시작위치)
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
// 문자열의 길이 구하기(return value : 문자열의 길이) - '\0'문자를 제외한 문자열의 글자 수
size_t myStrlen(const char *p)
{
	size_t i = 0;
	while(*(p+i)!='\0')
	{
		i++;
	}
	return i;
}
// p1문자열과 p2문자열 비교 (return value : 사전순서상 p1이 앞에 있으면 음수, p1과 p2가 같으면 0, p1이 뒤에 있으면 양수)
//  - 문자열 비교 방법 : byte 대 byte로 아스키코드 비교
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
// p1 문자열에서 c문자 검색 (return value : 첫번째로 검색된 c문자의 주소 / 못찾은 경우 NULL pointer반환)
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
// p1 문자열에서 p2문자열 검색 (return value : p2와 일치하는 부분의 시작주소 / 못찾은 경우 NULL pointer반환)
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
// p2 문자열을 p1문자열 뒤에 연결 (return value : p1의 시작위치)
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
// 문자열을 10진 정수로 변환 (return value : 변환된 10진수 / 변환불가능한 문자가 포함된 경우 0 반환)
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