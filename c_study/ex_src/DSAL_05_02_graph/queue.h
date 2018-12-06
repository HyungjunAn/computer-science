#ifndef QUEUE_H_
#define QUEUE_H_
#include<stdbool.h>
typedef struct _queue { 
	int *queue;
	int qSize; 
	int front, rear; 
}Queue; 

void initQueue(Queue * qPtr, int size); // ť ���� �� �ʱ�ȭ �Լ�
bool enqueue(Queue * qPtr, int inData);   // ť�� ������ �ϳ��� ������
bool dequeue(Queue * qPtr, int * getData);  // ť���� ������ �ϳ��� ����
void printQueue(const Queue * qPtr );  // ť ���� ��� �����͸� ���(dequeue�ϴ� ���� �ƴ�)
void destroyQueue(Queue * qPtr);  // ť �Ҹ� �Լ�
bool isQueueEmpty(const Queue *qPtr); // ť�� ����ִ°� �˻�

#endif /* QUEUE_H_ */
