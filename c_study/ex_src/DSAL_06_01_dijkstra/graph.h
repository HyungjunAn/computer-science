#ifndef GRAPH_H_
#define GRAPH_H_
#include<limits.h>

#define MAX_VERTEX 100
#define WEIGHT_MAX INT_MAX /* ���� ���Ǵ� ����ġ���� ������ ���� å�� */
#define NEWL printf("\n")

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

#endif  /* GRAPH_H_ */
