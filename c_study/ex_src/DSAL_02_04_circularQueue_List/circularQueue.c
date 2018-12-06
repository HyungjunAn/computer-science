#include <stdio.h>
#include <stdlib.h>
#include "circularQueue.h"

BOOL createQueue(Queue * qp) {
	if (qp == NULL) {
		return FALSE;
	}
	qp->head = (Qnode*)malloc(sizeof(Qnode));
	if (qp->head == NULL) {
		return FALSE;
	}
	qp->tail = (Qnode*)malloc(sizeof(Qnode));
	if (qp->tail == NULL) {
		free(qp->head);
		return FALSE;
	}
	qp->head->next = qp->tail;
	qp->head->prev = qp->head;
	qp->tail->prev = qp->head;
	qp->tail->next = qp->tail;
	qp->cnt = 0;
	return TRUE;
}
BOOL isQueueEmpty(const Queue *qp) {
	if (qp == NULL) {
		return FALSE;
	}
	return (qp->cnt == 0)? TRUE: FALSE;
}
BOOL enqueue(Queue * qp, int enqueData) {
	if (qp == NULL) {
		return FALSE;
	}
	Qnode* qNode = (Qnode*)malloc(sizeof(Qnode) * 1);
	if (qNode == NULL) {
		return FALSE;
	}
	qNode->data = enqueData;
	Qnode* p = qp->tail->prev;
	p->next = qNode;
	qNode->prev = p;
	qNode->next = qp->tail;
	qp->tail->prev = qNode;
	qp->cnt++;
	return TRUE;
}
BOOL dequeue(Queue * qp, int * dequeData) {
	if (qp == NULL || isQueueEmpty(qp) == TRUE) {
		return FALSE;
	}
	Qnode *p = qp->head->next;
	*dequeData = p->data;
	qp->head->next = p->next;
	p->next->prev = qp->head;
	free(p);
	qp->cnt--;
	return TRUE;
}
void printQueue(const Queue * qp) {
	if (qp == NULL || isQueueEmpty(qp) == TRUE) {
		return;
	}
	Qnode *pQnode;
	for (pQnode = qp->head->next; pQnode != qp->tail; pQnode = pQnode->next) {
		printf("%d < ", pQnode->data);
	}
	printf("\n");
}
void destroyQueue(Queue * qp) {
	if (qp == NULL) {
		return;
	}
	Qnode *tmp;
	Qnode *pQnode = qp->head->next;
	while (pQnode != qp->tail) {
		tmp = pQnode;
		pQnode = pQnode->next;
		free(tmp);
	}
	free(qp->head);
	free(qp->tail);
}
