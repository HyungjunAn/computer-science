#pragma once 
typedef enum _BOOL { FALSE, TRUE } BOOL;

typedef struct rowcol { /* �࿭ ��ǥ 1 ��Ʈ�� �����ϴ� ����ü */
	int x;  // ��(column)
	int y;  // ��(row)
}RC;

typedef struct _queue { /* ����ť ���� ����ü */
	RC *queue;
	int size;
	int front, rear;
}Queue;

BOOL createQueue(Queue * qp, int size);		/* ť ���� �� �ʱ�ȭ �Լ� */
BOOL isQueueEmpty(const Queue *qp);			/* ť�� ������ ����ִ°� */
BOOL isQueueFull(const Queue *qp);			/* ť�� �����ִ°� �˻� */
BOOL enqueue(Queue * qp, RC enqueData);		/* ť�� ������ �ϳ��� ���� �� */
BOOL dequeue(Queue * qp, RC * dequeData);	/* ť���� ������ �ϳ��� ���� */
void printQueue(const Queue * qp);			/* ť ���� ��� �����͸� ���(dequeue�ϴ� ���� �ƴ�) */
void destroyQueue(Queue * qp);				/* ť �Ҹ� �Լ� */
