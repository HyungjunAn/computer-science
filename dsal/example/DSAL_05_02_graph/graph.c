#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include "graph.h"
#include "stack.h"
#include "queue.h"

int check[MAX_VERTEX];  /* 방문된 정점은 1로 미방문 정점은 0으로 저장 */
/*--------------------------------------------------------------------------------------
함수명 및 기능: initGraph() - 데이터파일에서 그래프의 정점과 간선 정보를 입력 받아 '
그래프를 인접 행렬법으로 초기화하는 함수
전달인자:  gm - 그래프 정보 구조체의 주소
         fileName - 그래프의 정점 및 간선 정보가 저장된 데이터 파일명
리턴값: 없음
--------------------------------------------------------------------------------------*/
void initGraph(GraphMatrix *gm, const char *fileName)
{
	char vertex[3];  /* 간선정보 입력을 위한 공간 "AB" 형태의 데이터 저장 char 배열 */
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
함수명 및 기능: outputGraph() - 그래프내의 정점과 간선의 관계를 인접 행렬 형태로 출력
전달인자:  gm : 그래프 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void outputGraph(GraphMatrix *gm)
{
	int i,j;         /* iterator */

	/* 정점명 가로방향 출력 */
	printf("   ");
	for(i=0; i<gm->vertexCnt; ++i)
		printf("%3c", 'A' + i);

	NEWL;  // 개행 매크로

	for(i=0; i<gm->vertexCnt; ++i)
	{
		printf("%3c", 'A' + i);
		for(j=0; j<gm->vertexCnt; j++)
			printf("%3d", gm->graph[i][j]);
		NEWL;
	}
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: DFS_Matrix() - 여러 개의 연결 요소로 구성된 그래프를 깊이 우선 탐색
하기 위한 함수(재귀판)
전달인자:  gm : 그래프 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void DFS_Matrix(GraphMatrix *gm)
{
	int i;
	for(i=0; i<gm->vertexCnt; ++i)  /* 정점의 방문상태 정보를 저장할 check배열 초기화 */
		check[i] = 0;
	for(i=0; i<gm->vertexCnt; ++i)
		if(check[i] == 0)
			DFS_recursive(gm, i);
	return;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: DFS_recursive() - 연결되어있는 하나의 그래프 내의 모든 정점을
재귀호출기법으로 방문하는 함수
전달인자:  gm : 그래프 정보 구조체의 주소
vNum : 방문하고자 하는 정점 번호
리턴값: 없음
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
함수명 및 기능: nrDFS_Matrix() - 여러 개의 연결 요소로 구성된 그래프를 깊이 우선 탐색
하기 위한 함수(비 재귀판)
전달인자:  gm : 그래프 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void nrDFS_Matrix(GraphMatrix *gm)
{
	int i;

	for(i=0; i<gm->vertexCnt; ++i)  /* 정점의 방문상태 정보를 저장할 check배열 초기화 */
		check[i] = 0;

	for(i=0; i<gm->vertexCnt; ++i){  /* 순차적으로 정점을 방문함 */
		if(check[i] == 0){           /* 방문하지 않은 정점을 발견 하면 */
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
함수명 및 기능: nrBFS_Matrix() - 여러 개의 연결 요소로 구성된 그래프를 너비 우선 탐색
하기 위한 함수(비 재귀판)
전달인자:  gm : 그래프 정보 구조체의 주소
리턴값: 없음
--------------------------------------------------------------------------------------*/
void BFS_Matrix(GraphMatrix *gm)
{
	int i;

	for(i=0; i<gm->vertexCnt; ++i)  /* 정점의 방문상태 정보를 저장할 check배열 초기화 */
		check[i] = 0;

	for(i=0; i<gm->vertexCnt; ++i){  /* 순차적으로 정점을 방문함 */
		if(check[i] == 0){           /* 방문하지 않은 정점을 발견 하면 */
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
함수명 및 기능: initGraph_L() - 데이터파일에서 그래프의 정점과 간선 정보를 입력 받아 '
그래프를 인접 리스트법으로 초기화하는 함수
전달인자:  g : 그래프 정보 구조체의 주소
fileName : 그래프의 정점 및 간선 정보가 저장된 데이터 파일명
리턴값: 없음
--------------------------------------------------------------------------------------*/
void initGraph_List(GraphList *g, const char *fileName)
{
	char vertex[3];  /* 간선정보 입력을 위한 공간 "AB" 형태의 데이터 저장 char 배열 */
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
함수명 및 기능: addNode() - 두 정점의 관계를 리스트에 등록함
전달인자:  g - 그래프 정보 구조체의 주소
vNum1 - 첫번째 정점의 번호
vNum2 - 두번째 정점이 번호
리턴값: 정점 등록이 성공하면 TRUE 리턴, 실패하면 false 리턴
--------------------------------------------------------------------------------------*/
bool addNode(GraphList *g, int vNum1, int vNum2)
{
	// TODO
	return true;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: outputGraph_L() - 그래프내의 정점과 간선의 관계를 인접 리스트 형태로 출력
전달인자:  g : 그래프 정보 구조체의 주소
리턴값: 없음
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
함수명 및 기능: destroyGraph_L() - 그래프내의 정점 노드 모두 삭제
전달인자:  g : 그래프 정보 구조체의 주소
리턴값: 없음
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
