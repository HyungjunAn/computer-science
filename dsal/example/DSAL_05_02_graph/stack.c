#include<stdlib.h>
#include<stdio.h>
#include "stack.h"

bool createStack(Stack *sPtr, int size)		/* ���� �޸� �Ҵ� �� ��� �ʱ�ȭ �Լ� */
{
	if (sPtr == NULL) {  /* sPtr������ NULL check*/
		return false;
	}
	sPtr->stack = (int *)calloc(size, sizeof(int));  /* stack �޸� �Ҵ� */
	if (sPtr->stack != NULL) {	/* stack �޸� �Ҵ� ���� ��*/
		sPtr->size = size;	/* ���� size �ʱ�ȭ */
		sPtr->top = 0;		/* top 0���� �ʱ�ȭ */
		return true;
	}
	else {	/* stack �޸� �Ҵ� ���� �� */
		return false;
	}
}
bool isStackFull(Stack *sPtr)		/* ������ �� ���ִ��� �˻� */
{
	if (sPtr == NULL) {  /* sPtr������ NULL check*/
		return false;
	}
	if (sPtr->top == sPtr->size)  /* stack�� �� �������� */
		return true;
	else
		return false;
}
bool isStackEmpty(Stack *sPtr)		/* ������ ������ ����ִ°� �˻� */
{
	if (sPtr == NULL) {  /* sPtr������ NULL check*/
		return false;
	}
	if (sPtr->top == 0)  /* stack�� �� ��� ������ */
		return true;
	else
		return false;
}
bool push(Stack *sPtr, int data)			/* ���ÿ� ������ �����ϴ� �Լ� */
{
	if (sPtr == NULL) {  /* sPtr������ NULL check*/
		return false;
	}
	if (isStackFull(sPtr)) {  /* stack�� �� �������� */
		return false;
	}
	else {					/* �����͸� top ��ġ�� ������ �� top�� ������Ŵ */
		sPtr->stack[sPtr->top] = data;
		sPtr->top++;
		return true;
	}
}
bool pop(Stack *sPtr, int *popData)			/* ���ÿ��� �����͸� ������ �Լ� */
{
	if (sPtr == NULL) {  /* sPtr������ NULL check*/
		return false;
	}

	if (isStackEmpty(sPtr)) {  /* stack�� ��������� */
		return false;
	}
	else {	/* �����͸� top-1�� ��ġ���� ���� popData�� ����Ű�� ���� ���� �� */
		--sPtr->top;
		*popData = sPtr->stack[sPtr->top];
		return true;
	}
}
void printStack(const Stack *sPtr)		/* ���� ���� ��� �����͸� ����ϴ� �Լ� */
{
	int i = sPtr->top;
	if (sPtr == NULL) {  /* sPtr������ NULL check*/
		return;
	}
	while (i != 0)
	{
		printf("%5d\n", sPtr->stack[--i]);
	}
	printf("\n");
}
void destroyStack(Stack *sPtr)			/* ���� �޸� ���� �Լ� */
{
	if (sPtr == NULL) {  /* sPtr������ NULL check*/
		return;
	}
	if(sPtr->stack!=NULL){
		free(sPtr->stack);
	}
	sPtr->stack = NULL;
	sPtr->size = 0;
	sPtr->top = 0;
	return;
}
