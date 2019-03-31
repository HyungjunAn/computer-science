#include<stdio.h>
#include "graph.h"
void displayTitle(const char *message);

int main()
{
	GraphMatrix gm;

	GraphList gl;
	initGraph(&gm, "C://C_Study//DSAL_05_02_graph//data.txt");/* 그래프 초기화 */
	outputGraph(&gm);   /* 그래프 상태 출력*/

	displayTitle("DFS 방문(비재귀판)");
	nrDFS_Matrix(&gm);

	displayTitle("DFS 방문(재귀판)");
	DFS_Matrix(&gm);

	displayTitle("BFS 방문");
	BFS_Matrix(&gm);

	printf("\n\n");

	initGraph_List(&gl, "C://C_Study//DSAL_05_02_graph//data.txt");/* 그래프 초기화 */
	outputGraph_List(&gl);
	//destroyGraph_List(&gl);

	return 0;
}

void displayTitle(const char *message)
{
	printf("\n----------------------------------------\n");
	printf("\t %s\n", message);
	printf("----------------------------------------\n");
}


/*=========================================================================================
[ 실행결과 ]
     A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q
  A  0  1  1  1  0  0  0  0  0  0  0  0  0  0  0  0  0
  B  1  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0
  C  1  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0  0
  D  1  0  0  0  0  0  0  1  0  0  0  0  0  0  0  0  0
  E  0  1  0  0  0  1  1  0  0  0  0  0  0  0  0  0  0
  F  0  0  1  0  1  0  0  1  0  0  0  0  0  0  0  0  0
  G  0  0  0  0  1  0  0  0  1  0  0  0  0  0  0  0  0
  H  0  0  0  1  0  1  0  0  1  0  0  0  0  0  0  0  0
  I  0  0  0  0  0  0  1  1  0  0  0  0  0  0  0  0  0
  J  0  0  0  0  0  0  0  0  0  0  1  1  0  0  0  0  0
  K  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0
  L  0  0  0  0  0  0  0  0  0  1  0  0  0  0  0  0  0
  M  0  0  0  0  0  0  0  0  0  0  0  0  0  1  1  0  0
  N  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  1  1
  O  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0  1
  P  0  0  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0
  Q  0  0  0  0  0  0  0  0  0  0  0  0  0  1  1  0  0

----------------------------------------
         DFS 방문(비재귀판)
----------------------------------------
  A  D  H  I  G  E  F  C  B  J  L  K  M  O  Q  N  P
----------------------------------------
         DFS 방문(재귀판)
----------------------------------------
  A  B  E  F  C  H  D  I  G  J  K  L  M  N  P  Q  O
----------------------------------------
         BFS 방문
----------------------------------------
  A  B  C  D  E  F  H  G  I  J  K  L  M  N  O  P  Q


  A :   D ->   C ->   B
  B :   E ->   A
  C :   F ->   A
  D :   H ->   A
  E :   G ->   F ->   B
  F :   H ->   E ->   C
  G :   I ->   E
  H :   I ->   F ->   D
  I :   H ->   G
  J :   L ->   K
  K :   J
  L :   J
  M :   O ->   N
  N :   Q ->   P ->   M
  O :   Q ->   M
  P :   N
  Q :   O ->   N
=========================================================================================*/
