#include <stdio.h>

#define N_MAX 10
#define W_MAX 1000

typedef struct {
	int w; // weight
	int c; // cost
} PROD;

int N;
int W;
int cost[N_MAX][W_MAX+1];
PROD prod[N_MAX];


void getInput(void);
int findMaxCost(int i, int w);

int main()
{
	getInput();
	printf("%d\n", findMaxCost(N-1, W));
	getchar();
	getchar();
	return 0;
}

void getInput(void) {
	int i;
	scanf("%d %d", &N, &W);
	for (i = 0; i < N; ++i) {
		scanf("%d %d", &prod[i].w, &prod[i].c);
	}
}

int findMaxCost(int i, int w) {
	int prev_w;
	int with_i = 0;
	int without_i = 0;
	if (i < 0 || w < 0) {
		return 0;
	}
	else if (cost[i][w] != 0) {
		return cost[i][w];
	}
	prev_w = w - prod[i].w;
	if (prev_w >= 0) {
		with_i = findMaxCost(i-1, prev_w) + prod[i].c;
	}
	without_i = findMaxCost(i-1, w);
	return cost[i][w] = (with_i > without_i)? with_i: without_i;
}
