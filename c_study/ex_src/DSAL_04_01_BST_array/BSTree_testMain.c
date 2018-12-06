#include <stdio.h>


int V;
int E;
int ch1[12];
int ch2[12];
int p[12];
int cnt;

void find(int n);
//void findRoot(int n);


int main(void) {
	int i;
	scanf("%d", &E);
	V = E + 1;
	for (i = 0; i < E; ++i) {
		int p, c;
		scanf("%d %d", &p, &c);

		if (ch1[p] == 0) {
			ch1[p] = c;
		}
		else {
			ch2[p] = c;
		}
	}
	find(1);
	printf("방문한 노드 수 : %d\n", cnt);
	getchar();
	getchar();
	return 0;
}

void find(int n) {
	cnt++;
	if (ch1[n] != 0) {
		find(ch1[n]);
	}
	if (ch2[n] != 0) {
		find(ch2[n]);
	}
}
