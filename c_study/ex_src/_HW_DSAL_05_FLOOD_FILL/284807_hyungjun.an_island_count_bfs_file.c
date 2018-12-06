#include<stdio.h>
#include<assert.h>
#include "circularQueue.h"
#define MAX_SIZE 50
int a[MAX_SIZE][MAX_SIZE];
int d[MAX_SIZE][MAX_SIZE];
int dx[] = { 0, 0, 1,-1, 1, 1,-1,-1 };
int dy[] = { 1,-1, 0, 0, 1,-1, 1,-1 };
int w, h;  // 너비, 높이  저장변수
int dataLoad(FILE *);

void bfs(int x, int y, int cnt)
{
	size_t i;
	size_t num_way = sizeof(dx) / sizeof(dx[0]);
	int next_x;
	int next_y;
	Queue queue;
	RC enRC, deRC;
	createQueue(&queue, w*h);

	enRC.x = x;
	enRC.y = y;
	enqueue(&queue, enRC);
	while (!isQueueEmpty(&queue)) {
		dequeue(&queue, &deRC);
		x = deRC.x;
		y = deRC.y;
		d[x][y] = cnt;
		for (i = 0; i < num_way; ++i) {
			next_x = x + dx[i];
			next_y = y + dy[i];
			if (next_x < 0 || next_x >= h || next_y < 0 || next_y >= w) {
				;
			}
			else if (a[next_x][next_y] == 1 && d[next_x][next_y] == 0) {
				enRC.x = next_x;
				enRC.y = next_y;
				enqueue(&queue, enRC);
			}
		}
	}
	destroyQueue(&queue);
}
int main()
{
	int i;
	int j;
	int cnt;
	FILE * fp;
	fp = fopen("c:\\data\\land.txt", "rt");
	assert(fp != NULL);

	while (1) {
		cnt = 0;
		if (dataLoad(fp) == FALSE) return 0;
		for (i = 0; i<h; i++) {
			for (j = 0; j<w; j++) {
				if (a[i][j] == 1 && d[i][j] == 0) {
					bfs(i, j, ++cnt);
				}
			}
		}
		printf("섬의 개수 : %d개\n", cnt);
		getchar();
	}

	fclose(fp);

	return 0;
}
/*--------------------------------------------------------------------------------------
함수명 및 기능  dataLoad() : 데이터 파일에서 검사할 데이터를 입력 받아 map에 저장하는 함수
전달인자        char *fileName : 두더지 굴의 정보가 저장된 데이터 파일명
리턴값          파일 읽기가 성공하면 TRUE 리턴, 실패하면 FALSE 리턴
--------------------------------------------------------------------------------------*/
int dataLoad(FILE *fp)
{
	int i, j; /* iterator */
	fscanf(fp, "%d %d", &w, &h);
	if (w == 0 && h == 0) return FALSE;
	for (i = 0; i<h; i++) {
		for (j = 0; j<w; j++) {
			fscanf(fp, "%d", &a[i][j]);
			d[i][j] = 0;
		}
	}

	for (i = 0; i<h; i++) {
		for (j = 0; j<w; j++) {
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
	return TRUE;
}
