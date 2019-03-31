#ifndef CIRCULARQUEUE_H_
#define CIRCULARQUEUE_H_

typedef enum _BOOL { FALSE, TRUE } BOOL;

typedef struct _queue {
	int *queue;
	int size;
	int front, rear;  // rear: 입구, front: 출구
}Queue;

BOOL createQueue(Queue * qp, int size);		/* 큐 생성 및 초기화 함수 */
BOOL isQueueEmpty(const Queue *qp);			/* 큐가 완전히 비어있는가 */
BOOL isQueueFull(const Queue *qp);			/* 큐가 꽉차있는가 검사 */
BOOL enQueue(Queue * qp, int enqueData);	/* 큐에 데이터 하나를 저장 함 */
BOOL deQueue(Queue * qp, int * dequeData);	/* 큐에서 데이터 하나를 꺼냄 */
void printQueue(const Queue * qp);			/* 큐 내의 모든 데이터를 출력(dequeue하는 것은 아님) */
void destroyQueue(Queue * qp);				/* 큐 소멸 함수 */

#endif /* CIRCULARQUEUE_H_ */
