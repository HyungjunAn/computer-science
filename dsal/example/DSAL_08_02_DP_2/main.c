#include <stdio.h>

#define N_MAX 100

int N;
int arr[N_MAX];
int sum[N_MAX][N_MAX];

int findMax();

int main()
{
	int i;
	int j;
	int k;
	getInput();


	for (j = 1; j < N; ++j) {
		if (arr[0] < arr[j]) {
			sum[0][j] = arr[0] + arr[j];
		}
		sum[0][j] = arr[0];
	}

	for (i = 0; i < N; ++i) {
		for (j = i+1; j < N; ++j) {
			int max = 0;
			for (k = i+1; k < j-1; ++k) {
				if (max < sum[i-1][j]

			}



		}

	}




	printf("%d\n", findMaxCost(N-1, W));
	getchar();
	getchar();
	return 0;
}

void getInput(void) {
	int i;
	scanf("%d", &N);
	for (i = 0; i < N; ++i) {
		scanf("%d", arr + i);
	}
}


