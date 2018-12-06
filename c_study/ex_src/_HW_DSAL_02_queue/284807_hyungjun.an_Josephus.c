#include<stdio.h>
#include "circularQueue.h"

BOOL initQueue(Queue* qp, int N);
BOOL printJosephus(Queue *qp, int M);

int main()
{
	int N;
	int M;
	printf("# N(인원수)와 M(간격수)를 입력하시오 (M<=N) : ");
	scanf("%d %d", &N, &M);

	Queue q;
	if (initQueue(&q, N) == FALSE) {
		return 1;
	}
	printf("(%d, %d) 요세푸스 순열: ", N, M);
	if (printJosephus(&q, M) == FALSE) {
		return 1;
	}
	destroyQueue(&q);
	return 0;
}

BOOL initQueue(Queue* qp, int N) {
	int i;
	if (createQueue(qp, N) == FALSE) {
		return FALSE;
	}
	for (i = 0; i < N; ++i) {
		if (enQueue(qp, i+1) == FALSE) {
			return FALSE;
		}
	}
	return TRUE;
}

BOOL printJosephus(Queue *qp, int M) {
	int i;
	int data;
	while (!isQueueEmpty(qp)) {
		for (i = 0; i < M-1; ++i) {
			if (deQueue(qp, &data) == FALSE) {
				return FALSE;
			}
			if (enQueue(qp, data) == FALSE) {
				return FALSE;
			}
		}
		if (deQueue(qp, &data) == FALSE) {
			return FALSE;
		}
		printf("%d ", data);
	}
	printf("\n");
	return TRUE;
}
