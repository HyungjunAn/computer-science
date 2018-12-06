#ifndef GRAPH_H_
#define GRAPH_H_
#include "stack.h"
#define MAX_VERTEX 100
#define NEWL printf("\n")

extern int check[];
/*----------------------------------------------
       GraphMatrix ó�� ����ü �� Ȱ�� �Լ�
-----------------------------------------------*/
typedef struct 
{
	int graph[MAX_VERTEX][MAX_VERTEX]; /* ���� ��Ĺ� ǥ�� �迭 - 2���� �迭 */
	int vertexCnt;    /* ���� ���� */
	int edgeCnt;      /* ���� ���� */
}GraphMatrix;

void initGraph(GraphMatrix *gm, const char *fileName); /*���������Ͽ��� �׷����� ������ ���� ������ �Է� �޾� �׷����� �ʱ�ȭ�ϴ� �Լ� */
void outputGraph(GraphMatrix *gm); /* �׷������� ������ ������ ���踦 ���� ��� ���·� ��� �� */
void DFS_Matrix(GraphMatrix *gm); /* ���� ���� ���� ��ҷ� ������ �׷����� ���� �켱 Ž���ϱ� ���� �Լ�(�����) - DFS_recursive()�Լ��� ȣ���Ͽ� ó��(�� �Լ� ��ü�� ������� ����) */
void dfs(GraphMatrix *gm, int vNum);
void DFS_recursive(GraphMatrix *gm, int vNum); /* ����Ǿ��ִ� �ϳ��� �׷�Ʈ���� ��� ������ ���ȣ�������� �湮�ϴ� �Լ� */
void nrDFS_Matrix(GraphMatrix *gm); /* ���� ���� ���� ��ҷ� ������ �׷����� ���� �켱 Ž���ϱ� ���� �Լ�(�� �����) */
void BFS_Matrix(GraphMatrix *gm); /* ���� ���� ���� ��ҷ� ������ �׷����� �ʺ� �켱 Ž���ϱ� ���� �Լ�(�� �����) */
void bfs(GraphMatrix *gm, int vNum);
/*---------------------------------------------
        GraphList ó�� ����ü �� Ȱ�� �Լ�
----------------------------------------------*/
typedef struct _node
{
	int vertex;
	struct _node *next;
}Node;

typedef struct 
{
	Node *graph[MAX_VERTEX];  /* ���� ����Ʈ ǥ�� �迭 - Node ������ �迭 */
	int vertexCnt;    /* ���� ���� */
	int edgeCnt;      /* ���� ���� */
}GraphList;

void initGraph_List(GraphList *g, const char *fileName); /* ���������Ͽ��� �׷����� ������ ���� ������ �Է� �޾� �׷����� ���� ����Ʈ������ �ʱ�ȭ�ϴ� �Լ� */
void outputGraph_List(GraphList *g); /* �׷������� ������ ������ ���踦 ���� ����Ʈ ���·� ��� */
bool addNode(GraphList *g, int vNum1, int vNum2); /* �� ������ ���踦 ����Ʈ�� ����� */
void destroyGraph_List(GraphList *g); /* �׷������� ���� ��� ��� ���� */

#endif /* GRAPH_H_ */
