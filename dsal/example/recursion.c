#include <stdio.h>
#include <limits.h>

#define MAX_N 30
#define MAX_K 9

int check[MAX_N];
int K[MAX_N][MAX_N];
int min = INT_MAX;

void calcMinTime(int n, int k);
int main()
{
	int i, j;
	int N;
	scanf("%d", &N);

	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			scanf("%d", &K[i][j]);
		}
	}
	calcMinTime(N, 0);
	printf("%d\n", min);
	return 0;
}

void calcMinTime(int n, int row) {
	static int cur_timeSum = 0;
	int col;
	if (row == n) {
		if (cur_timeSum < min) {
			min = cur_timeSum;
		}
		return;
	}
	for (col = 0; col < n; ++col) {
		if (check[col] == 0) {
			cur_timeSum += K[row][col];
			if (cur_timeSum < min) {
				check[col] = 1;
				calcMinTime(n, row+1);
				check[col] = 0;
			}
			cur_timeSum -= K[row][col];
		}
	}
	return;
}
