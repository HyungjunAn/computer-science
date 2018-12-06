#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
void displayTitle(const char *message);
void dijkstra(GraphMatrix *g, int vNum);
void printWeightArray(int vNum, int vCnt);
void printParent(int vCnt);
void pathPrint(int startVNum, int endVNum);
int indexOfMinWeight(GraphMatrix *g);

int weightArray[MAX_VERTEX];  /* ����ġ�� ���������� �����ϴ� �迭 */
int parent[MAX_VERTEX];      /* �θ� ���� ���� �迭*/
int check[MAX_VERTEX];        /* �˻�� ������ 1�� �̰˻� ������ 0���� ���� */

/*----------------------------------------------------------------------------------
�Լ��� : main() 
----------------------------------------------------------------------------------*/
int main()
{
	GraphMatrix g;
	int i;
	initGraph(&g, "..//graphData2.txt");/* �׷��� �ʱ�ȭ */

	displayTitle("[���� �׷����� ���� ��� ���]");
	outputGraph(&g);   /* �׷��� ���� �� ����ġ ���� ���*/        
	NEWL; NEWL;

	/* ���ͽ�Ʈ�� �˰��� ���� */
	displayTitle("[����ġ ��ȭ ���� ���]");
	dijkstra(&g, 5);  /* 5���� �ش��ϴ� ������ �������� ���ͽ�Ʈ�� �˰��� ���� */

	displayTitle("[�������� �θ�, �ڽİ��� ���]");
	printParent(g.vertexCnt);  /* parent �迭 ��� */

	/* ���� ����(F-5�� ����)�� ���� �׷������� ��� ����(A~K)������ ��� �� ����ġ ��� */
	displayTitle("[F(5�� ����)�������� �� ���������� path ����ϱ�]");
	for(i=0; i<g.vertexCnt; ++i)
		pathPrint(5, i);

	getchar();
	return 0;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: displayTitle() - ���޵� �޽����� ��� �� 
��������:  message - ����� �޽���
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void displayTitle(const char *message)
{
	printf("\n----------------------------------------\n");
	printf(" %s\n", message);
	printf("----------------------------------------\n");
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: dijkstra() - ���޵� �׷������� ���õ� �������� ���� ������ ���������� 
			�ּ� ����ġ�� ����ϰ� �θ��ڽ� ���踦 ������
��������:  g - �׷��� ���� ����ü�� �ּ�
			vNum - ���õ� ���� ��ȣ
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void dijkstra(GraphMatrix *g, int vNum)
{
	int i; /*iterator */
	int minIndex;  /* üũ���� ���� ���� �� ���� ���� ����ġ�� �����ϰ� �ִ� ������ �ε��� ���� */
	int target; /* ����ġ ���� ����� �Ǵ� ������ �ε��� ���� */
	int dist;  /* ��ȸ ����ġ ���� ����*/

	/* ���� ���� vNum �������� weightArray, parent, check �迭 �ʱ�ȭ */
	for(i=0; i<g->vertexCnt; ++i){
		weightArray[i] = g->graph[vNum][i]; /* ���� ���� vNum���� ���� �� ������ �̸��� ����ġ ���� */
		if(g->graph[vNum][i]!=WEIGHT_MAX){
			parent[i] = vNum;  /* vNum ������ ������ ������ �θ�� vNum */
		}
		else{
			parent[i] = -1;  /* vNum�� �������� ���� ������ �θ�� -1���� �ʱ�ȭ */
		}
		check[i] = 0;  /* üũ ���θ� ��� 0(üũ�ȵ�)���� �ʱ�ȭ */
	}
	parent[vNum] = -1;  /* ���� ������ �θ�� �����Ƿ� -1(������ �� ���� �ε�����ȣ)�� �ʱ�ȭ */
	check[vNum] = 1;  /* ���� ������ vNum üũ */

	printWeightArray(vNum, g->vertexCnt);  /* ���� ���� �������� ����ġ �迭 ��� */

	/* Dijkstra Algorithm : ���� ������ �������� ����ġ �迭�� �����ϸ� �θ� �ڽ� ���踦 ���� */
	for(i=0; i< g->vertexCnt-1; ++i){  /* ��� ������ ���ؼ� ����ġ�� �����ϱ� ���� �ݺ� */

		minIndex = indexOfMinWeight(g); /* ����ġ ������ ���� ���� ����(�������� ������� ���� ���� �� ����ġ�� ���� ���� ����)�� ���� �� */

		for(target=0; target<g->vertexCnt; target++){ /* Ÿ�� ������ ���Ե� ����ġ�� ���� */
			if( (g->graph[minIndex][target]!=WEIGHT_MAX) && (weightArray[minIndex]!=WEIGHT_MAX)){
				dist = weightArray[minIndex] + g->graph[minIndex][target]; /* ��ȸ ����� ����ġ ��� */
				if(dist < weightArray[target]){ /* ��ȸ ����� ����ġ�� ��������� ����ġ ���� ������ ���� */
					weightArray[target] = dist; /* ��ȸ ��� ����ġ�� ���� */
					parent[target] = minIndex;  /* target�� �θ���� minIndex��� ���� */
				}
			}
		}
		printWeightArray(minIndex, g->vertexCnt);  /* minINdex �������� ���ŵ� ����ġ �迭 ��� */
	}
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: indexOfMinWeight() - ����ġ ������ ���� ���� ����(�������� ������� ���� ���� �� ����ġ�� ���� ���� ����)
��������: g - �׷��� ���� ����ü�� �ּ�
���ϰ�: ���� ���� �ε���
--------------------------------------------------------------------------------------*/
int indexOfMinWeight(GraphMatrix *g)
{
	int tmpWeight;  /* minIndex�� ã�� ���� ����ġ ���� �ӽ� ���� */
	int i;
	int minIndex;

	minIndex = 0;  /* ����ġ�� ���� ���� ������ 0�̶�� ���� */
	tmpWeight = WEIGHT_MAX;

	for(i=0; i<g->vertexCnt; i++){
		if(check[i]==0 && weightArray[i] <= tmpWeight){ /* üũ���� ���� ���� �� ���� ���� ������ �ε����� ã��*/
			minIndex = i;
			tmpWeight = weightArray[minIndex];
		}

	}
	check[minIndex] = 1;  /* ã�Ƴ� ���� ���� ����ġ ������ üũ �� */
	return minIndex;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: printWeightArray() - weight�迭�� ��� ��
��������: vNum - ���� ���� ��ȣ
        vCnt - ����� ������ ����
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void printWeightArray(int vNum, int vCnt)
{
	int i;
	printf("%3c : ", 'A'+vNum);
	for(i=0; i<vCnt; ++i)
		if(weightArray[i] != WEIGHT_MAX){
			printf("%5d", weightArray[i]);
		}
		else{
			printf("%5s", "��");
		}

	NEWL;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: printParent() - �θ�, �ڽ� ��带 ǥ���ϴ� �迭 ���
��������: vCnt - ����� ������ ����
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void printParent(int vCnt)
{
	int i;
	printf("\n---------------------------------------------------------\n");
	printf("child :  ");
	for(i=0; i<vCnt; ++i)
		printf("%3c", i+'A');
	NEWL;
	printf("Parent : ");
	for(i=0; i<vCnt; ++i){
		if(parent[i]==-1) printf("  *");
		else printf("%3c", parent[i]+'A');
	}
	printf("\n--------------------------------------------------------\n");
	NEWL;
}
/*--------------------------------------------------------------------------------------
�Լ��� �� ���: pathPrint() - ���� ����->�� ���������� path �� ����ġ ���
��������:	startVNum - ���� ���� ��ȣ
		endVNum - ���� ���� ��ȣ
���ϰ�: ����
--------------------------------------------------------------------------------------*/
void pathPrint(int startVNum, int endVNum)
{
	int i,j=0;
	int vNum;  /* ��η� ���õ� ���� ��ȣ */
	char path[MAX_VERTEX];

	path[j] = endVNum;
	vNum = endVNum;   /* ������ ���� ��ȣ���� �˻� */

	if(weightArray[endVNum]!=WEIGHT_MAX){  // ����Ǿ��ִ� ������ path ���
		while(vNum!=startVNum){
			vNum = path[++j] = parent[vNum];
		}
		for(i=j; i>=0; --i)  /* path �迭�� ������ ����ؾ� startVNum -> endVNum�� ��ΰ� ��� �� */
			printf("%c -> ", 'A'+path[i]);
		printf("\b\b\b (weight: %d)\n", weightArray[endVNum]);
	}
	else{
		printf("%c -> %c : No path (weight: %d)\n", startVNum+'A',endVNum+'A', weightArray[endVNum]);
	}
}

/*======================================================================================================
[ ��� ��� ]
----------------------------------------
[���� �׷����� ���� ��� ���]
----------------------------------------
A  B  C  D  E  F  G  H  I  J  K
A  0  4  1  2  3 �� �� �� �� �� ��
B  4  0 �� �� ��  4 �� �� �� �� ��
C  1 ��  0  2 �� �� �� �� �� �� ��
D  2 ��  2  0 ��  4  4 �� �� �� ��
E  3 �� �� ��  0  4 �� �� �� �� ��
F ��  4 ��  4  4  0 �� �� ��  2  4
G �� �� ��  4 �� ��  0  3  3  4 ��
H �� �� �� �� �� ��  3  0  2 �� ��
I �� �� �� �� �� ��  3  2  0  2 ��
J �� �� �� �� ��  2  4 ��  2  0  1
K �� �� �� �� ��  4 �� �� ��  1  0

�� : 1000������ ����

----------------------------------------
[����ġ ��ȭ ���� ���]
----------------------------------------
F :  1000    4 1000    4    4    0 1000 1000 1000    2    4
J :  1000    4 1000    4    4    0    6 1000    4    2    3
K :  1000    4 1000    4    4    0    6 1000    4    2    3
B :     8    4 1000    4    4    0    6 1000    4    2    3
D :     6    4    6    4    4    0    6 1000    4    2    3
E :     6    4    6    4    4    0    6 1000    4    2    3
I :     6    4    6    4    4    0    6    6    4    2    3
A :     6    4    6    4    4    0    6    6    4    2    3
C :     6    4    6    4    4    0    6    6    4    2    3
G :     6    4    6    4    4    0    6    6    4    2    3
H :     6    4    6    4    4    0    6    6    4    2    3

----------------------------------------
[�������� �θ�, �ڽİ��� ���]
----------------------------------------
child :    A  B  C  D  E  F  G  H  I  J  K
Parent :   D  F  D  F  F  *  J  I  J  F  J

----------------------------------------
[F���� �� ���������� path ���]
----------------------------------------
F ->   D ->   A  (weight: 6)
F ->   B  (weight: 4)
F ->   D ->   C  (weight: 6)
F ->   D  (weight: 4)
F ->   E  (weight: 4)
F  (weight: 0)
F ->   J ->   G  (weight: 6)
F ->   J ->   I ->   H  (weight: 6)
F ->   J ->   I  (weight: 4)
F ->   J  (weight: 2)
F ->   J ->   K  (weight: 3)

 */
