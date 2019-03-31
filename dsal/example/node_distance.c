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
		printf("# ����ȣ 2���� �Է��Ͻÿ� : ");
		sCnt = scanf("%d %d", &from, &to);
		if (sCnt != 2 || from == 0 || to == 0) {
			break;
		}
		printf("%d�� %d������ �Ÿ� : %d\n\n", from, to, getDistance(from, to, 0));
	}
	getchar();
	getchar();
	return 0;
}
