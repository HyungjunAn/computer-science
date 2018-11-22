#include <stdio.h>


#define Row 16
#define Col 8

int map[Row][Row];
int tmp_map[Row][Row];
int hexArr[Row];


void input(void)
{
	char ch;
	int i;
	int j;
	for (i = 0; i < Row; ++i) {
		for (j = 0; j < Col; ++j) {
			scanf(" %c", &ch);
			map[i][j] = ch - '0';
		}
	}
}

void printMap(int row, int col)
{
	int i;
	int j;
	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j) {
			printf("%d", map[i][j]);
		}
		printf("\n");
	}
}

int main(void)
{
	int i;
	int j;

	input();

	//printf("\n");
	//printMap(16, 8);

	for (i = 0; i < Row; ++i) {
		for (j = 0; j < Col; ++j) {
			tmp_map[i][j] = map[Row - i - 1][j];
		}
	}
	for (i = 0; i < Row; ++i) {
		for (j = 0; j < Col; ++j) {
			map[j][i] = tmp_map[i][j];
		}
	}

	//printf("\n");
	//printMap(8, 16);

	for (i = 0; i < Col; ++i) {
		for (j = 0; j < Col; ++j) {
			tmp_map[i+Col][j] = map[i][j];
		}
	}
	for (i = 0; i < Col; ++i) {
		for (j = 0; j < Col; ++j) {
			tmp_map[i][j] = map[i][Col+j];
		}
	}
	for (i = 0; i < Row; ++i) {
		for (j = 0; j < Col; ++j) {
			map[i][j] = tmp_map[i][j];
		}
	}

	//printf("\n");
	//printMap(16, 8);

	for (i = 0; i < Row; ++i) {
		hexArr[i] = 0;
		for (j = 0; j < Col; ++j) {
			hexArr[i] |= map[i][j] * (1 << (Col - j - 1));
		}
	}

	printf("{");
	for (i = 0; i < Row; ++i) {
		printf("0x%02X,", hexArr[i]);
	}
	printf("},");



	return 0;
}


