#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include "graph.h"
#include "stack.h"
#include "queue.h"

int check[MAX_VERTEX];  /* �湮�� ������ 1�� �̹湮 ������ 0���� ���� */
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: initGraph() - ���������Ͽ��� �׷����� ������ ���� ������ �Է� �޾� '
�׷����� ���� ��Ĺ����� �ʱ�ȭ�ϴ� �Լ�
��������:  gm - �׷��� ���� ����ü�� �ּ�
         fileName - �׷����� ���� �� ���� ������ ����� ������ ���ϸ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void initGraph(GraphMatrix *gm, const char *fileName)
{
	char vertex[3];  /* �������� �Է��� ���� ���� "AB" ������ ������ ���� char �迭 */
	int i,j;       /* iterator */
	int from, to;

	freopen(fileName, "rt", stdin);
	scanf("%d %d", &gm->vertexCnt, &gm->edgeCnt);

	for (i = 0; i < gm->vertexCnt; ++i) {
		for (j = 0; j < gm->vertexCnt; j++) {
			gm->graph[i][j] = 0;
		}
	}

	for (i = 0; i < gm->edgeCnt; ++i) {
		scanf("%s", vertex);
		from = vertex[0] - 'A';
		to = vertex[1] - 'A';
		gm->graph[from][to] = 1;
		gm->graph[to][from] = 1;
	}
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: outputGraph() - �׷������� ������ ������ ���踦 ���� ��� ���·� ���
��������:  gm : �׷��� ���� ����ü�� �ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void outputGraph(GraphMatrix *gm)
{
	int i,j;         /* iterator */

	/* ������ ���ι��� ��� */
	printf("   ");
	for(i=0; i<gm->vertexCnt; ++i)
		printf("%3c", 'A' + i);

	NEWL;  // ���� ��ũ��

	for(i=0; i<gm->vertexCnt; ++i)
	{
		printf("%3c", 'A' + i);
		for(j=0; j<gm->vertexCnt; j++)
			printf("%3d", gm->graph[i][j]);
		NEWL;
	}
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: DFS_Matrix() - ���� ���� ���� ��ҷ� ������ �׷����� ���� �켱 Ž��
�ϱ� ���� �Լ�(�����)
��������:  gm : �׷��� ���� ����ü�� �ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void DFS_Matrix(GraphMatrix *gm)
{
	int i;
	for(i=0; i<gm->vertexCnt; ++i)  /* ������ �湮���� ������ ������ check�迭 �ʱ�ȭ */
		check[i] = 0;
	for(i=0; i<gm->vertexCnt; ++i)
		if(check[i] == 0)
			DFS_recursive(gm, i);
	return;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: DFS_recursive() - ����Ǿ��ִ� �ϳ��� �׷��� ���� ��� ������
���ȣ�������� �湮�ϴ� �Լ�
��������:  gm : �׷��� ���� ����ü�� �ּ�
vNum : �湮�ϰ��� �ϴ� ���� ��ȣ
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void DFS_recursive(GraphMatrix *gm, int vNum)
{
	int i;
	check[vNum] = 1;
	for (i = 0; i < gm->vertexCnt; ++i) {
		if (i != vNum && check[i] == 0 && gm->graph[vNum][i] != 0) {
			printf("%c -> %c\n", vNum + 'A', i + 'A');
			DFS_recursive(gm, i);
		}
	}
	check[vNum] = 0;
}

/*--------------------------------------------------------------------------------------
�Լ��� �� ���: nrDFS_Matrix() - ���� ���� ���� ��ҷ� ������ �׷����� ���� �켱 Ž��
�ϱ� ���� �Լ�(�� �����)
��������:  gm : �׷��� ���� ����ü�� �ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void nrDFS_Matrix(GraphMatrix *gm)
{
	int i;

	for(i=0; i<gm->vertexCnt; ++i)  /* ������ �湮���� ������ ������ check�迭 �ʱ�ȭ */
		check[i] = 0;

	for(i=0; i<gm->vertexCnt; ++i){  /* ���������� ������ �湮�� */
		if(check[i] == 0){           /* �湮���� ���� ������ �߰� �ϸ� */
			dfs(gm, i);
		}
	}
	return;
}
void dfs(GraphMatrix *gm, int vNum)
{
	int i, j;
	Stack s;
	createStack(&s, gm->vertexCnt);
	push(&s, vNum);
	check[vNum] = 1;
	while (!isStackEmpty(&s)) {
		pop(&s, &i);
		printf("%c ->\n", i + 'A');
		for (j = gm->vertexCnt - 1; j >= 0; --j) {
			if (check[j] == 0 && gm->graph[i][j] != 0) {
				push(&s, j);
				check[j] = 1;
			}
		}
	}
	printf("\n");
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: nrBFS_Matrix() - ���� ���� ���� ��ҷ� ������ �׷����� �ʺ� �켱 Ž��
�ϱ� ���� �Լ�(�� �����)
��������:  gm : �׷��� ���� ����ü�� �ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void BFS_Matrix(GraphMatrix *gm)
{
	int i;

	for(i=0; i<gm->vertexCnt; ++i)  /* ������ �湮���� ������ ������ check�迭 �ʱ�ȭ */
		check[i] = 0;

	for(i=0; i<gm->vertexCnt; ++i){  /* ���������� ������ �湮�� */
		if(check[i] == 0){           /* �湮���� ���� ������ �߰� �ϸ� */
			bfs(gm, i);
		}
	}
	return;
}

void bfs(GraphMatrix *gm, int vNum)
{
	int i, j;
	Queue q;
	initQueue(&q, gm->vertexCnt);
	enqueue(&q, vNum);
	check[vNum] = 1;
	while (!isQueueEmpty(&q)) {
		dequeue(&q, &i);
		for (j = 0; j < gm->vertexCnt; ++j) {
			if (check[j] == 0 && gm->graph[i][j] != 0) {
				printf("%c -> %c\n", i + 'A', j + 'A');
				enqueue(&q, j);
				check[j] = 1;
			}
		}
	}
	printf("\n");
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: initGraph_L() - ���������Ͽ��� �׷����� ������ ���� ������ �Է� �޾� '
�׷����� ���� ����Ʈ������ �ʱ�ȭ�ϴ� �Լ�
��������:  g : �׷��� ���� ����ü�� �ּ�
fileName : �׷����� ���� �� ���� ������ ����� ������ ���ϸ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void initGraph_List(GraphList *g, const char *fileName)
{
	char vertex[3];  /* �������� �Է��� ���� ���� "AB" ������ ������ ���� char �迭 */
	int i;       /* iterator */
	int from, to;

	freopen(fileName, "rt", stdin);
	scanf("%d %d", &g->vertexCnt, &g->edgeCnt);

	for (i = 0; i < g->edgeCnt; ++i) {
		g->graph[i] = NULL;
	}
	for (i = 0; i < g->edgeCnt; ++i) {
		check[i] = 0;
	}

	for (i = 0; i < g->edgeCnt; ++i) {
		scanf("%s", vertex);
		from = vertex[0] - 'A';
		to = vertex[1] - 'A';

		Node* pNode = (Node*)malloc(sizeof(Node) * 1);
		pNode->vertex = to;
		pNode->next = NULL;
		if (g->graph[from] == NULL) {
			g->graph[from] = pNode;
		}
		else {
			pNode->next = g->graph[from]->next;
			g->graph[from]->next = pNode;
		}
	}
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: addNode() - �� ������ ���踦 ����Ʈ�� �����
��������:  g - �׷��� ���� ����ü�� �ּ�
vNum1 - ù��° ������ ��ȣ
vNum2 - �ι�° ������ ��ȣ
���ϰ�: ���� ����� �����ϸ� TRUE ����, �����ϸ� false ����
--------------------------------------------------------------------------------------*/
bool addNode(GraphList *g, int vNum1, int vNum2)
{
	// TODO
	return true;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: outputGraph_L() - �׷������� ������ ������ ���踦 ���� ����Ʈ ���·� ���
��������:  g : �׷��� ���� ����ü�� �ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void outputGraph_List(GraphList *g)
{
	int i;         /* iterator */
	Node *now;
	for(i=0; i<g->vertexCnt; ++i)
	{
		printf("%3c : ", 'A' + i);
		for(now = g->graph[i]; now != NULL; now = now->next)
			printf("%3c -> ", 'A' + now->vertex);
		printf("\b\b\b    ");
		NEWL;
	}
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: destroyGraph_L() - �׷������� ���� ��� ��� ����
��������:  g : �׷��� ���� ����ü�� �ּ�
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void destroyGraph_List(GraphList *g)
{
	int i;         /* iterator */
	Node *now, *next;
	for(i=0; i<g->vertexCnt; ++i)
	{
		now = g->graph[i];
		while(now != NULL)
		{
			next = now->next;
			free(now);
			now=next;
		}
	}
}
