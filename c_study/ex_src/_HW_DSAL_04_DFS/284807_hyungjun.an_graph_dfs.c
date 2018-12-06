#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#define MAX_VERTEX 10
int graph[MAX_VERTEX + 1][MAX_VERTEX + 1]; /* �������� ���� ���� ���� ���� ��� �迭 */
int vertexCnt, edgeCnt; /* ���� ������ ���� ���� ���� ���� */
int check[MAX_VERTEX + 1]; /* ������� �湮�� ���� üũ �迭 */
int start, goal; /* ��߳��̱ⱸ ��ȣ�� ���� ���̱ⱸ ��ȣ */
int minDistance;  /* �ִܰŸ� */

bool initGraph(FILE *fp); /* ���������Ͽ��� �׷����� ������ ���� ������ �Է� �޾� ������Ĺ����� �ʱ�ȭ �ϴ� �Լ� */
void solve(int vertex, int sumDistance);  /* ���̵��� �̵� �� �ִ� �Ÿ��� ����ϴ� ����Լ� */

/*----------------------------------------------------------------------------------------
 �Լ��� : main()
----------------------------------------------------------------------------------------*/
int main() {
	int i;

	FILE *fp; /* �׷��� ���� ���� ������ ���������� */

	fp = fopen("c:\\data\\park.txt", "rt");
	if (fp == NULL) {
		printf("File open error!\n");
		return 1;
	}

	initGraph(fp);
	fclose(fp);

	while (1) {
		printf("# ������� �������� �Է�(1~%d) : ", vertexCnt);
		scanf("%d %d", &start, &goal);
		if (start == 0 || goal == 0)
			break;

		for (i = 1; i <= vertexCnt; ++i)
			check[i] = 0;

		minDistance = INT_MAX;	/* �ּ� �̵��Ÿ��� INT_MAX ������ ���� */

		solve(start, 0); /* ������� ������ ������ȣ, ������� �̵� ���� �Ÿ��� ����Լ� ȣ��*/

		if (minDistance == INT_MAX)
			printf("�ִܰŸ� : -1(���� �Ұ���)\n");
		else
			printf("�ִܰŸ� : %d\n", minDistance);
	}

	getchar(); getchar();
	return 0;
}
/*--------------------------------------------------------------------------------------
Function name 	: initGraph() - ���������Ͽ��� �׷����� ������ ���� ������ �Է� �޾� ������Ĺ����� �ʱ�ȭ �ϴ� �Լ�
Parameters		: fp - �׷��� ������ �����ϰ� �ִ� ������ ���� ������
Returns		: �׷����� ���������� �ʱ�ȭ �ϸ� false ����, �����ϸ� false ����
--------------------------------------------------------------------------------------*/
bool initGraph(FILE *fp) {
	int vertex1, vertex2; /* ������ȣ �Է� ���� */
	int weight; /* ����ó �Է� ���� */
	int i; /* iterator */

	if (fscanf(fp, "%d %d\n", &vertexCnt, &edgeCnt) != 2) /* ������ ������ ������ �б� */
		return false; /* �׷��� ������ �б⸦ �����ϸ� false ���� */

	/* ������ �׷��������� ��Ī��(Symmetry) ������ �ʱ�ȭ ǥ�� */
	for (i = 0; i < edgeCnt; ++i) {
		fscanf(fp, "%d %d %d\n", &vertex1, &vertex2, &weight);
		graph[vertex1][vertex2] = graph[vertex2][vertex1] = weight;
	}
	return true; /* ���������� �׷��� �����͸� �о����� true ���� */
}
/*--------------------------------------------------------------------------------------
Function name	: solve() - �̵� �� �ִ� �Ÿ��� ����ϴ� ����Լ�(���� �켱 Ž��������� �˻�)
Parameters		: vertex - ������� ������ ���� ��ȣ
sumDistance - ������� �̵� ���� �Ÿ�
Returns		: ����
--------------------------------------------------------------------------------------*/
void solve(int vertex, int sumDistance)
{
	int i;
	check[vertex] = 1;
	if (vertex == goal) {
		if (minDistance > sumDistance) {
			minDistance = sumDistance;
		}
	}
	else if (sumDistance > minDistance) {
		;
	}
	else {
		for (i = 1; i <= vertexCnt; ++i) {
			if (check[i] == 0 && graph[vertex][i] != 0) {
				solve(i, sumDistance + graph[vertex][i]);
			}
		}
	}
	check[vertex] = 0;
}