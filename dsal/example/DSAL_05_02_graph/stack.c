#include<stdlib.h>
#include<stdio.h>
#include "stack.h"

bool createStack(Stack *sPtr, int size)		/* 스택 메모리 할당 및 멤버 초기화 함수 */
{
	if (sPtr == NULL) {  /* sPtr포인터 NULL check*/
		return false;
	}
	sPtr->stack = (int *)calloc(size, sizeof(int));  /* stack 메모리 할당 */
	if (sPtr->stack != NULL) {	/* stack 메모리 할당 설공 시*/
		sPtr->size = size;	/* 스택 size 초기화 */
		sPtr->top = 0;		/* top 0으로 초기화 */
		return true;
	}
	else {	/* stack 메모리 할당 실패 시 */
		return false;
	}
}
bool isStackFull(Stack *sPtr)		/* 스택이 꽉 차있는지 검사 */
{
	if (sPtr == NULL) {  /* sPtr포인터 NULL check*/
		return false;
	}
	if (sPtr->top == sPtr->size)  /* stack이 꽉 차있으면 */
		return true;
	else
		return false;
}
bool isStackEmpty(Stack *sPtr)		/* 스택이 완전히 비어있는가 검사 */
{
	if (sPtr == NULL) {  /* sPtr포인터 NULL check*/
		return false;
	}
	if (sPtr->top == 0)  /* stack이 텅 비어 있으면 */
		return true;
	else
		return false;
}
bool push(Stack *sPtr, int data)			/* 스택에 데이터 저장하는 함수 */
{
	if (sPtr == NULL) {  /* sPtr포인터 NULL check*/
		return false;
	}
	if (isStackFull(sPtr)) {  /* stack이 꽉 차있으면 */
		return false;
	}
	else {					/* 데이터를 top 위치에 저장한 후 top을 증가시킴 */
		sPtr->stack[sPtr->top] = data;
		sPtr->top++;
		return true;
	}
}
bool pop(Stack *sPtr, int *popData)			/* 스택에서 데이터를 꺼내는 함수 */
{
	if (sPtr == NULL) {  /* sPtr포인터 NULL check*/
		return false;
	}

	if (isStackEmpty(sPtr)) {  /* stack이 비어있으면 */
		return false;
	}
	else {	/* 데이터를 top-1번 위치에서 꺼내 popData가 가리키는 곳에 저장 함 */
		--sPtr->top;
		*popData = sPtr->stack[sPtr->top];
		return true;
	}
}
void printStack(const Stack *sPtr)		/* 스택 내의 모든 데이터를 출력하는 함수 */
{
	int i = sPtr->top;
	if (sPtr == NULL) {  /* sPtr포인터 NULL check*/
		return;
	}
	while (i != 0)
	{
		printf("%5d\n", sPtr->stack[--i]);
	}
	printf("\n");
}
void destroyStack(Stack *sPtr)			/* 스택 메모리 해제 함수 */
{
	if (sPtr == NULL) {  /* sPtr포인터 NULL check*/
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
