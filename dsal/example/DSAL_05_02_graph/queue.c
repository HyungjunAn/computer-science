#include <stdio.h> 
#include <stdlib.h>
#include <assert.h> 
#include "queue.h" 

/*--------------------------------------------------------------------------------------
  �Լ���ױ�� : initQueue() - ť �ʱ�ȭ �Լ�
  �������� : qPtr - ť ����ü�� �ּ�
             size - ť�� ũ��
  ���ϰ� : ����
--------------------------------------------------------------------------------------*/
void initQueue(Queue * qPtr, int size) 
{ 
	qPtr->qSize = size; 
	qPtr->front = 0; 
	qPtr->rear = 0; 
	qPtr->queue = (int *)calloc(sizeof(int), qPtr->qSize); 
} 
/*--------------------------------------------------------------------------------------
  �Լ���ױ�� : enqueue() - ť�� ������ �ϳ��� ������
  �������� : qPtr - ť ����ü�� �ּ�
             inData - ť�� ������ ������
  ���ϰ� : ���������� �����ϸ� true, �����ϸ� false ����
--------------------------------------------------------------------------------------*/
bool enqueue(Queue * qPtr, int inData)
{ 
	if((qPtr->rear+1)%qPtr->qSize == qPtr->front) // rear�� �������뿡 ������ put�Ұ�
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
  �Լ��� �� ��� : dequeue() - ť���� ������ �ϳ��� ����
  �������� : qPtr - ť ����ü�� �ּ�
             getData - ���� �����͸� ������ �������� �ּ�
  ���ϰ� : ���������� ������ true, �����ϸ� false ����
--------------------------------------------------------------------------------------*/
bool dequeue(Queue * qPtr, int * getData)
{ 
	if( isQueueEmpty(qPtr) ) // ť�� ��������� dequeue �Ұ�
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
  �Լ���ױ�� : printQueue() - ť ���� ��� �����͸� ��� ��
  �������� : qPtr - ť ����ü�� �ּ�
  ���ϰ� : ����
--------------------------------------------------------------------------------------*/
void printQueue(const Queue * qPtr )
{ 
	int i;
	if(isQueueEmpty(qPtr)==true)
	{
		printf("Queue�� ����ֽ��ϴ�!!\n");
		return;
	}
	for(i = qPtr->front; i!=qPtr->rear; i=(i+1)%qPtr->qSize)
	{ 
		printf("%d", qPtr->queue[i]);
	} 
	printf("\n");
} 
/*--------------------------------------------------------------------------------------
  �Լ���ױ�� : destroyQueue() - ť �Ҹ� �Լ�
  �������� : qPtr - ť ����ü�� �ּ�
  ���ϰ� : ����
--------------------------------------------------------------------------------------*/
void destroyQueue(Queue * qPtr) 
{ 
	qPtr->qSize = 0; 
	free(qPtr->queue); 
	qPtr->queue = NULL; 
} 
/*--------------------------------------------------------------------------------------
  �Լ��� �� ���: isQueueEmpty() - ť�� ����ִ°� �˻�
  ��������: qPtr - ť ����ü�� �ּ�
  ���ϰ�: ��������� TRUE ����, ������� ������ false ����
--------------------------------------------------------------------------------------*/
bool isQueueEmpty(const Queue *qPtr)
{
	if(qPtr-> front == qPtr->rear) 
		return true;
	else 
		return false;
}
