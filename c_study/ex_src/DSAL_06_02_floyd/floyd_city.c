#include<stdio.h>

int d[101][101];  // 그래프 연결 정보 저장(인접 행렬법)
int parent[101][101];
int n; // 정점의 개수

void _printGraph(int i, int j) {
	if (i == j) {
		printf("%d", i);
	}
	else if (parent[i][j] == 0) {
		printf("No Path!!");
	}
	else {
		_printGraph(i, parent[i][j]);
		printf(" > %d", j);
	}
}
void printGraph(void) {
	int i, j;

	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			if (i != j) {
				printf("%d -> %d: ", i, j);
				_printGraph(i, j);
				printf("\n");
			}
		}
	}
}
int fileLoad(FILE *fp)
{
	int i, j;
	fscanf(fp, "%d", &n);
	if(n==0)
		return 0;

	for(i=1; i<=n; i++)
		for(j=1; j<=n; j++)
			fscanf(fp, "%d", &d[i][j]);

	printf("vertex count : %d\n", n);
	for(i=1; i<=n; i++) {
		for(j=1; j<=n; j++) {
			printf("%3d", d[i][j]);
		}
		printf("\n");
	}
	printf("*------------------------*\n");
	return 1;
}

int main()
{
	FILE *fp;
	int i,j,k;
	if ((fp = fopen("..//floyd_city.txt", "rt")) == NULL)
		return 0;

	while(fileLoad(fp)){

		// floyd 알고리즘
		for (i = 1; i <= n; ++i) {
			for (j = 1; j <= n; ++j) {
				if (d[i][j] != 0) {
					parent[i][j] = i;
				}
				else {
					parent[i][j] = 0;
				}
			}
		}
		for (i = 1; i <= n; ++i) {
			for (j = 1; j <= n; ++j) {
				if (i == j) {
					continue;
				}
				for (k = 1; k <= n; ++k) {
					if (d[i][k] != 0 && d[k][j] != 0) {
						if (d[i][j] == 0 || d[i][j] > d[i][k] + d[k][j]) {
							d[i][j] = d[i][k] + d[k][j];
							parent[i][j] = k;
						}
					}
				}
			}
		}

		// floyed 알고리즘 수행 후 결과 출력
		for (i=1; i<=n; i++) {
			for (j=1; j<=n; j++) {
				printf("%3d", d[i][j]);
			}
			printf("\n");
		}
		printf("*------------------------*\n");
		printGraph();
		printf("*------------------------*\n");
	}
	fclose(fp);
	return 0;
}
