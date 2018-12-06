#ifndef CIRCULARQUEUE_H_
#define CIRCULARQUEUE_H_

typedef enum _BOOL { FALSE, TRUE } BOOL;
typedef struct _queue Queue;
typedef struct _qnode Qnode;

struct _queue {
	Qnode *head;
	Qnode *tail;
	int cnt;
};

struct _qnode{
	int data;
	Qnode *next;
	Qnode *prev;
};

BOOL createQueue(Queue * qp);		/* ť ���� �� �ʱ�ȭ �Լ� */
BOOL isQueueEmpty(const Queue *qp);			/* ť�� ������ ����ִ°� */
BOOL enqueue(Queue * qp, int enqueData);	/* ť�� ������ �ϳ��� ���� �� */
BOOL dequeue(Queue * qp, int * dequeData);	/* ť���� ������ �ϳ��� ���� */
void printQueue(const Queue * qp);			/* ť ���� ��� �����͸� ���(dequeue�ϴ� ���� �ƴ�) */
void destroyQueue(Queue * qp);				/* ť �Ҹ� �Լ� */

#endif /* CIRCULARQUEUE_H_ */
