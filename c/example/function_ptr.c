#include<stdio.h>
int plus(int, int);
int minus(int, int);
int multi(int, int);

int main()
{
	int i, j, res;
	int (*fpAry[2][2])(int, int) = {{plus, minus}, {multi, plus}};

	int size = sizeof(fpAry) / sizeof(fpAry[0]);
	printf("size = %d\n", size);

	for (i = 0; i<size; i++) {
		for (j = 0; j<size; j++) {
			res=fpAry[i][j](10,20);
			printf("res = %d\n", res);
		}
	}
	return 0;
} // end of main()
int plus(int a, int b)
{
	return a+b;
}
int minus(int a, int b)
{
	return a-b;
}
int multi(int a, int b)
{
	return a*b;
}
