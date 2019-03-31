#include<stdio.h>
#include<stdbool.h>
#include<limits.h>
#define MAX_VERTEX 10
int graph[MAX_VERTEX + 1][MAX_VERTEX + 1]; /* 정점간의 연결 상태 저장 인접 행렬 배열 */
int vertexCnt, edgeCnt; /* 정점 개수와 간선 개수 저장 공간 */
int check[MAX_VERTEX + 1]; /* 현재까지 방문한 정점 체크 배열 */
int start, goal; /* 출발놀이기구 번호와 도착 놀이기구 번호 */
int minDistance;  /* 최단거리 */

bool initGraph(FILE *fp); /* 데이터파일에서 그래프의 정점과 간선 정보를 입력 받아 인접행렬법으로 초기화 하는 함수 */
void solve(int vertex, int sumDistance);  /* 놀이동산 이동 시 최단 거리를 계산하는 재귀함수 */

/*----------------------------------------------------------------------------------------
 함수명 : main()
----------------------------------------------------------------------------------------*/
int main() {
	int i;

	FILE *fp; /* 그래프 정보 저장 파일의 파일포인터 */

	fp = fopen("c:\\data\\park.txt", "rt");
	if (fp == NULL) {
		printf("File open error!\n");
		return 1;
	}

	initGraph(fp);
	fclose(fp);

	while (1) {
		printf("# 출발지점 도착지점 입력(1~%d) : ", vertexCnt);
		scanf("%d %d", &start, &goal);
		if (start == 0 || goal == 0)
			break;

		for (i = 1; i <= vertexCnt; ++i)
			check[i] = 0;

		minDistance = INT_MAX;	/* 최소 이동거리를 INT_MAX 값으로 지정 */

		solve(start, 0); /* 현재까지 도착한 정점번호, 현재까지 이동 누적 거리로 재귀함수 호출*/

		if (minDistance == INT_MAX)
			printf("최단거리 : -1(도착 불가능)\n");
		else
			printf("최단거리 : %d\n", minDistance);
	}

	getchar(); getchar();
	return 0;
}
/*--------------------------------------------------------------------------------------
Function name 	: initGraph() - 데이터파일에서 그래프의 정점과 간선 정보를 입력 받아 인접행렬법으로 초기화 하는 함수
Parameters		: fp - 그래프 정보를 저장하고 있는 파일의 파일 포인터
Returns		: 그래프를 정상적으로 초기화 하면 false 리턴, 실패하면 false 리턴
--------------------------------------------------------------------------------------*/
bool initGraph(FILE *fp) {
	int vertex1, vertex2; /* 간선번호 입력 변수 */
	int weight; /* 가중처 입력 번수 */
	int i; /* iterator */

	if (fscanf(fp, "%d %d\n", &vertexCnt, &edgeCnt) != 2) /* 정점과 간선의 개수를 읽기 */
		return false; /* 그래프 데이터 읽기를 실패하면 false 리턴 */

	/* 무방향 그래프에서의 대칭성(Symmetry) 고려한 초기화 표기 */
	for (i = 0; i < edgeCnt; ++i) {
		fscanf(fp, "%d %d %d\n", &vertex1, &vertex2, &weight);
		graph[vertex1][vertex2] = graph[vertex2][vertex1] = weight;
	}
	return true; /* 성공적으로 그래프 데이터를 읽었으면 true 리턴 */
}
/*--------------------------------------------------------------------------------------
Function name	: solve() - 이동 시 최단 거리를 계산하는 재귀함수(깊이 우선 탐색기법으로 검색)
Parameters		: vertex - 현재까지 도착한 정점 번호
sumDistance - 현재까지 이동 누적 거리
Returns		: 없음
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
