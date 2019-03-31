#ifndef CIRCULARQUEUE_H_
#define CIRCULARQUEUE_H_

typedef enum _BOOL { FALSE, TRUE } BOOL;

typedef struct _queue {
	int *queue;
	int size;
	int front, rear;  // rear: �Ա�, front: �ⱸ
}Queue;

BOOL createQueue(Queue * qp, int size);		/* ť ���� �� �ʱ�ȭ �Լ� */
BOOL isQueueEmpty(const Queue *qp);			/* ť�� ������ ����ִ°� */
BOOL isQueueFull(const Queue *qp);			/* ť�� �����ִ°� �˻� */
BOOL enQueue(Queue * qp, int enqueData);	/* ť�� ������ �ϳ��� ���� �� */
BOOL deQueue(Queue * qp, int * dequeData);	/* ť���� ������ �ϳ��� ���� */
void printQueue(const Queue * qp);			/* ť ���� ��� �����͸� ���(dequeue�ϴ� ���� �ƴ�) */
void destroyQueue(Queue * qp);				/* ť �Ҹ� �Լ� */

#endif /* CIRCULARQUEUE_H_ */
