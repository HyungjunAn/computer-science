#include <stdio.h>
#include <stdlib.h>
#include "circularQueue.h"

BOOL createQueue(Queue * qp, int size) {
	if (qp == NULL) {
		return FALSE;
	}
	qp->queue = (int*)malloc(sizeof(int) * (size+1));
	if (qp->queue == NULL) {
		return FALSE;
	}
	qp->size = size;
	qp->front = 0;
	qp->rear = 0;
	return TRUE;
}
BOOL isQueueEmpty(const Queue *qp) {
	if (qp == NULL) {
		return FALSE;
	}
	else if (qp->front == qp->rear) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}
BOOL isQueueFull(const Queue *qp) {
	if (qp == NULL) {
		return FALSE;
	}
	else if (qp->front == (qp->rear + 1) % (qp->size+1)) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}
BOOL enQueue(Queue * qp, int enqueData) {
	if (qp == NULL || isQueueFull(qp) == TRUE) {
		return FALSE;
	}
	qp->queue[qp->rear] = enqueData;
	qp->rear = (qp->rear + 1) % (qp->size+1);
	return TRUE;
}
BOOL deQueue(Queue * qp, int * dequeData) {
	if (qp == NULL || isQueueEmpty(qp) == TRUE) {
		return FALSE;
	}
	*dequeData = qp->queue[qp->front];
	qp->front = (qp->front + 1) % (qp->size+1);
	return TRUE;
}
void printQueue(const Queue * qp) {
	if (qp == NULL || isQueueEmpty(qp) == TRUE) {
		return;
	}
	int i = qp->front;
	for (i = qp->front; i != qp->rear; i = (i+1) % (qp->size+1)) {
		printf("%d < ", qp->queue[i]);
	}
	printf("\n");
}
void destroyQueue(Queue * qp) {
	if (qp == NULL) {
		return;
	}
	free(qp->queue);
}
