#include<stdio.h>

int getDistance(int i, int j, int sum) {
	if (i == j) {
		return sum;
	}
	else if (i > j) {
		return getDistance(i/2, j, sum + 1);
	}
	else {
		return getDistance(j, i, sum);
	}
}


int main()
{
	int from;
	int to;
	int sCnt;
	while (1) {
		printf("# 노드번호 2개를 입력하시오 : ");
		sCnt = scanf("%d %d", &from, &to);
		if (sCnt != 2 || from == 0 || to == 0) {
			break;
		}
		printf("%d와 %d사이의 거리 : %d\n\n", from, to, getDistance(from, to, 0));
	}
	getchar();
	getchar();
	return 0;
}
