#ifndef QUEUE_H_
#define QUEUE_H_
#include<stdbool.h>
typedef struct _queue { 
	int *queue;
	int qSize; 
	int front, rear; 
}Queue; 

void initQueue(Queue * qPtr, int size); // 큐 생성 및 초기화 함수
bool enqueue(Queue * qPtr, int inData);   // 큐에 데이터 하나를 저장함
bool dequeue(Queue * qPtr, int * getData);  // 큐에서 데이터 하나를 꺼냄
void printQueue(const Queue * qPtr );  // 큐 내의 모든 데이터를 출력(dequeue하는 것은 아님)
void destroyQueue(Queue * qPtr);  // 큐 소멸 함수
bool isQueueEmpty(const Queue *qPtr); // 큐가 비어있는가 검사

#endif /* QUEUE_H_ */
