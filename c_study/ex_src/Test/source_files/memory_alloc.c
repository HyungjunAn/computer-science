#include<stdio.h>
#include<malloc.h>
int ** myAlloc(int row, int col);
void dataInput(int **pp, int row, int col);
void dataOutput(int **pp, int row, int col);
void myDelete(int **pp, int row);
int main()
{
	int  **ip;
	int  col, row;
	printf("row �� �Է� : ");
	scanf("%d", &row);
	printf("column �� �Է� : ");
	scanf("%d", &col);
	ip = myAlloc(row, col);
	if (ip == NULL) {
		return 1;
	}
	dataInput(ip, row, col);
	dataOutput(ip, row, col);
	myDelete(ip, row);
	return 0;
}
// 4���� ����� ���� �Լ� �����ϱ�
int ** myAlloc(int row, int col) {
	int **pp = (int **)malloc(sizeof(int*) * row);
	int i;
	for (i = 0; i < row; ++i) {
		pp[i] = (int *)malloc(sizeof(int) * col);
	}
	return pp;
}
void dataInput(int **pp, int row, int col) {
	int i, j;
	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j) {
			printf("%d, %d ������ �Է�: ", i+1, j+1);
			scanf("%d", &pp[i][j]);
		}
	}
}
void dataOutput(int **pp, int row, int col) {
	int i, j;
	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j) {
			printf("%d ", pp[i][j]);
		}
		printf("\n");
	}
}
void myDelete(int **pp, int row) {
	int i;
	for (i = 0; i < row; ++i) {
		free(pp[i]);
	}
	free(pp);
}
