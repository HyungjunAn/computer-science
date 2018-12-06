#include<stdio.h>
#include<stdlib.h>
#include "graph.h"
void displayTitle(const char *message);
void dijkstra(GraphMatrix *g, int vNum);
void printWeightArray(int vNum, int vCnt);
void printParent(int vCnt);
void pathPrint(int startVNum, int endVNum);
int indexOfMinWeight(GraphMatrix *g);

int weightArray[MAX_VERTEX];  /* 가중치를 순차적으로 저장하는 배열 */
int parent[MAX_VERTEX];      /* 부모 정점 저장 배열*/
int check[MAX_VERTEX];        /* 검사된 정점은 1로 미검사 정점은 0으로 저장 */

/*----------------------------------------------------------------------------------
함수명 : main() 
----------------------------------------------------------------------------------*/
int main()
{
	GraphMatrix g;
	int i;
	initGraph(&g, "..//graphData2.txt");/* 그래프 초기화 */

	displayTitle("[가중 그래프의 인접 행렬 출력]");
	outputGraph(&g);   /* 그래프 연결 및 가중치 상태 출력*/        
	NEWL; NEWL;

	/* 다익스트라 알고리즘 수행 */
	displayTitle("[가중치 변화 상태 출력]");
	dijkstra(&g, 5);  /* 5번에 해당하는 정점을 기준으로 다익스트라 알고리즘 실행 */

	displayTitle("[정점간의 부모, 자식관계 출력]");
	printParent(g.vertexCnt);  /* parent 배열 출력 */

	/* 기준 정점(F-5번 정점)로 부터 그래프태의 모든 정점(A~K)가지의 경로 및 가중치 출력 */
	displayTitle("[F(5번 정점)기준으로 각 정점으로의 path 출력하기]");
	for(i=0; i<g.vertexCnt; ++i)
		pathPrint(5, i);

	getchar();
	return 0;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: displayTitle() - 전달된 메시지를 출력 함 
전달인자:  message - 출력할 메시지
리턴값: 없음
--------------------------------------------------------------------------------------*/
void displayTitle(const char *message)
{
	printf("\n----------------------------------------\n");
	printf(" %s\n", message);
	printf("----------------------------------------\n");
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: dijkstra() - 전달된 그래프내에 선택된 정점으로 부터 나머지 정점까지의 
			최소 가중치를 계산하고 부모자식 관계를 연산함
전달인자:  g - 그래프 정보 구조체의 주소
			vNum - 선택된 정점 번호
리턴값: 없음
--------------------------------------------------------------------------------------*/
void dijkstra(GraphMatrix *g, int vNum)
{
	int i; /*iterator */
	int minIndex;  /* 체크되지 않은 정점 중 가장 작은 가중치를 저장하고 있는 정점의 인덱스 저장 */
	int target; /* 가중치 계산시 대상이 되는 정점의 인덱스 저장 */
	int dist;  /* 우회 가중치 저장 변수*/

	/* 기준 정점 vNum 기준으로 weightArray, parent, check 배열 초기화 */
	for(i=0; i<g->vertexCnt; ++i){
		weightArray[i] = g->graph[vNum][i]; /* 기준 정점 vNum으로 부터 각 정점에 이르는 가중치 저장 */
		if(g->graph[vNum][i]!=WEIGHT_MAX){
			parent[i] = vNum;  /* vNum 정점과 인접한 정점의 부모는 vNum */
		}
		else{
			parent[i] = -1;  /* vNum과 인접하지 않은 정점의 부모는 -1으로 초기화 */
		}
		check[i] = 0;  /* 체크 여부를 모두 0(체크안됨)으로 초기화 */
	}
	parent[vNum] = -1;  /* 기준 정점의 부모는 없으므로 -1(존재할 수 없는 인덱스번호)로 초기화 */
	check[vNum] = 1;  /* 시작 정점을 vNum 체크 */

	printWeightArray(vNum, g->vertexCnt);  /* 시작 정점 기준으로 가중치 배열 출력 */

	/* Dijkstra Algorithm : 기준 정점을 기준으로 가중치 배열을 갱신하며 부모 자식 관계를 생성 */
	for(i=0; i< g->vertexCnt-1; ++i){  /* 모든 정점에 대해서 가중치을 갱신하기 위해 반복 */

		minIndex = indexOfMinWeight(g); /* 가중치 갱신을 위한 기준 정점(기준으로 사용하지 않은 정점 중 가중치가 가장 작은 정점)을 구해 옴 */

		for(target=0; target<g->vertexCnt; target++){ /* 타겟 정점이 포함된 가중치로 갱신 */
			if( (g->graph[minIndex][target]!=WEIGHT_MAX) && (weightArray[minIndex]!=WEIGHT_MAX)){
				dist = weightArray[minIndex] + g->graph[minIndex][target]; /* 우회 경로의 가중치 계산 */
				if(dist < weightArray[target]){ /* 우회 경로의 가중치가 직접경로의 가중치 보다 작으면 갱신 */
					weightArray[target] = dist; /* 우회 경로 가중치로 갱신 */
					parent[target] = minIndex;  /* target의 부모노드로 minIndex노드 저장 */
				}
			}
		}
		printWeightArray(minIndex, g->vertexCnt);  /* minINdex 기준으로 갱신된 가중치 배열 출력 */
	}
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: indexOfMinWeight() - 가중치 갱신을 위한 기준 정점(기준으로 사용하지 않은 정점 중 가중치가 가장 작은 정점)
전달인자: g - 그래프 정보 구조체의 주소
리턴값: 기준 정점 인덱스
--------------------------------------------------------------------------------------*/
int indexOfMinWeight(GraphMatrix *g)
{
	int tmpWeight;  /* minIndex를 찾기 위한 가중치 저장 임시 변수 */
	int i;
	int minIndex;

	minIndex = 0;  /* 가중치가 가장 작은 정점을 0이라고 가정 */
	tmpWeight = WEIGHT_MAX;

	for(i=0; i<g->vertexCnt; i++){
		if(check[i]==0 && weightArray[i] <= tmpWeight){ /* 체크되지 않은 정점 중 가장 작은 정점의 인덱스를 찾음*/
			minIndex = i;
			tmpWeight = weightArray[minIndex];
		}

	}
	check[minIndex] = 1;  /* 찾아낸 가장 작은 가중치 정점을 체크 함 */
	return minIndex;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: printWeightArray() - weight배열을 출력 함
전달인자: vNum - 기준 정점 번호
        vCnt - 출력할 정점의 개수
리턴값: 없음
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
			printf("%5s", "∞");
		}

	NEWL;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능: printParent() - 부모, 자식 노드를 표시하는 배열 출력
전달인자: vCnt - 출력할 정점의 개수
리턴값: 없음
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
함수명 및 기능: pathPrint() - 시작 정점->끝 정점까지의 path 및 가중치 출력
전달인자:	startVNum - 시작 정점 번호
		endVNum - 도착 정점 번호
리턴값: 없음
--------------------------------------------------------------------------------------*/
void pathPrint(int startVNum, int endVNum)
{
	int i,j=0;
	int vNum;  /* 경로로 선택된 정점 번호 */
	char path[MAX_VERTEX];

	path[j] = endVNum;
	vNum = endVNum;   /* 도착지 정점 번호부터 검사 */

	if(weightArray[endVNum]!=WEIGHT_MAX){  // 연결되어있는 정점의 path 출력
		while(vNum!=startVNum){
			vNum = path[++j] = parent[vNum];
		}
		for(i=j; i>=0; --i)  /* path 배열을 뒤집어 출력해야 startVNum -> endVNum의 경로가 출력 됨 */
			printf("%c -> ", 'A'+path[i]);
		printf("\b\b\b (weight: %d)\n", weightArray[endVNum]);
	}
	else{
		printf("%c -> %c : No path (weight: %d)\n", startVNum+'A',endVNum+'A', weightArray[endVNum]);
	}
}

/*======================================================================================================
[ 출력 결과 ]
----------------------------------------
[가중 그래프의 인접 행렬 출력]
----------------------------------------
A  B  C  D  E  F  G  H  I  J  K
A  0  4  1  2  3 ∞ ∞ ∞ ∞ ∞ ∞
B  4  0 ∞ ∞ ∞  4 ∞ ∞ ∞ ∞ ∞
C  1 ∞  0  2 ∞ ∞ ∞ ∞ ∞ ∞ ∞
D  2 ∞  2  0 ∞  4  4 ∞ ∞ ∞ ∞
E  3 ∞ ∞ ∞  0  4 ∞ ∞ ∞ ∞ ∞
F ∞  4 ∞  4  4  0 ∞ ∞ ∞  2  4
G ∞ ∞ ∞  4 ∞ ∞  0  3  3  4 ∞
H ∞ ∞ ∞ ∞ ∞ ∞  3  0  2 ∞ ∞
I ∞ ∞ ∞ ∞ ∞ ∞  3  2  0  2 ∞
J ∞ ∞ ∞ ∞ ∞  2  4 ∞  2  0  1
K ∞ ∞ ∞ ∞ ∞  4 ∞ ∞ ∞  1  0

∞ : 1000값으로 계산됨

----------------------------------------
[가중치 변화 상태 출력]
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
[정점간의 부모, 자식관계 출력]
----------------------------------------
child :    A  B  C  D  E  F  G  H  I  J  K
Parent :   D  F  D  F  F  *  J  I  J  F  J

----------------------------------------
[F기준 각 정점으로의 path 출력]
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
