#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include "queue.h" 

/*--------------------------------------------------------------------------------------
  함수명및기능 : initQueue() - 큐 초기화 함수
  전달인자 : qPtr - 큐 구조체의 주소
             size - 큐의 크기
  리턴값 : 없음
--------------------------------------------------------------------------------------*/
void initQueue(Queue * qPtr, int size) 
{ 
	qPtr->qSize = size; 
	qPtr->front = 0; 
	qPtr->rear = 0; 
	qPtr->queue = (int *)calloc(sizeof(int), qPtr->qSize); 
} 
/*--------------------------------------------------------------------------------------
  함수명및기능 : enqueue() - 큐에 데이터 하나를 저장함
  전달인자 : qPtr - 큐 구조체의 주소
             inData - 큐에 저장할 데이터
  리턴값 : 성공적으로 저장하면 true, 실패하면 false 리턴
--------------------------------------------------------------------------------------*/
bool enqueue(Queue * qPtr, int inData)
{ 
	if((qPtr->rear+1)%qPtr->qSize == qPtr->front) // rear가 완충지대에 있으면 put불가
	{ 

		printf("Queue Overflow !!\n"); 
		return false;
	} 

	qPtr->queue[qPtr->rear] = inData; 
	qPtr->rear++; 
	qPtr->rear = (qPtr->rear)%qPtr->qSize; 
	return true;

} 
/*--------------------------------------------------------------------------------------
  함수명 및 기능 : dequeue() - 큐에서 데이터 하나를 꺼냄
  전달인자 : qPtr - 큐 구조체의 주소
             getData - 꺼낸 데이터를 저장할 기억공간의 주소
  리턴값 : 성공적으로 꺼내면 true, 실패하면 false 리턴
--------------------------------------------------------------------------------------*/
bool dequeue(Queue * qPtr, int * getData)
{ 
	if( isQueueEmpty(qPtr) ) // 큐가 비어있으면 dequeue 불가
	{ 
		printf("Queue Underflow !!\n"); 
		return false;
	} 

	*getData = qPtr->queue[qPtr->front]; 
	qPtr->front++; 
	qPtr->front = (qPtr->front)%qPtr->qSize; 

	return true;
} 
/*--------------------------------------------------------------------------------------
  함수명및기능 : printQueue() - 큐 내의 모든 데이터를 출력 함
  전달인자 : qPtr - 큐 구조체의 주소
  리턴값 : 없음
--------------------------------------------------------------------------------------*/
void printQueue(const Queue * qPtr )
{ 
	int i;
	if(isQueueEmpty(qPtr)==true)
	{
		printf("Queue가 비어있습니다!!\n");
		return;
	}
	for(i = qPtr->front; i!=qPtr->rear; i=(i+1)%qPtr->qSize)
	{ 
		printf("%d", qPtr->queue[i]);
	} 
	printf("\n");
} 
/*--------------------------------------------------------------------------------------
  함수명및기능 : destroyQueue() - 큐 소멸 함수
  전달인자 : qPtr - 큐 구조체의 주소
  리턴값 : 없음
--------------------------------------------------------------------------------------*/
void destroyQueue(Queue * qPtr) 
{ 
	qPtr->qSize = 0; 
	free(qPtr->queue); 
	qPtr->queue = NULL; 
} 
/*--------------------------------------------------------------------------------------
  함수명 및 기능: isQueueEmpty() - 큐가 비어있는가 검사
  전달인자: qPtr - 큐 구조체의 주소
  리턴값: 비어있으면 TRUE 리턴, 비어있지 않으면 false 리턴
--------------------------------------------------------------------------------------*/
bool isQueueEmpty(const Queue *qPtr)
{
	if(qPtr-> front == qPtr->rear) 
		return true;
	else 
		return false;
}
