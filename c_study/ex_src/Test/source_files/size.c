#include <stdio.h>

void func(char **pStr) {
	printf("�μ��� �� : %c\n", pStr[0][0]);
	pStr[0][0] = 'c';
}

int main() {
	char *str1[] = {"INPUT", "OUTPUT", "SEARCH", "QUIT"};
	char (*str2)[10] = {"INPUT", "OUTPUT", "SEARCH", "QUIT"};
	printf("������ �迭: %I64u\n", sizeof(str1));
	printf("�迭 ������: %I64u\n", sizeof(str2));

	printf("\n");

	int *arr1[] = {{1,2,3,4}, {1,2,3,4}, {1,2,3,4}, {1,2,3,4}};
	int (*arr2)[10] = {{1,2,3,4}, {1,2,3,4}, {1,2,3,4}, {1,2,3,4}};
	printf("������ �迭: %I64u\n", sizeof(arr1));
	printf("�迭 ������: %I64u\n", sizeof(arr2));

	return 0;
}
