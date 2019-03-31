#include <stdio.h>
#include <stdlib.h>
#include "arrayStack.h"

BOOL createStack(Stack *sPtr, int size) {
	if (sPtr == NULL) {
		return FALSE;
	}
	sPtr->stack = (int*)malloc(sizeof(int)*size);
	if (sPtr->stack == NULL) {
		return FALSE;
	}
	sPtr->size = size;
	sPtr->top = 0;
	return TRUE;
}
BOOL isStackFull(Stack *sPtr) {
	if (sPtr == NULL || sPtr->stack == NULL) {
		return FALSE;
	}
	return (sPtr->size > sPtr->top)? FALSE: TRUE;
}
BOOL isStackEmpty(Stack *sPtr) {
	if (sPtr == NULL || sPtr->stack == NULL) {
		return FALSE;
	}
	return (sPtr->top == 0)? TRUE: FALSE;
}
BOOL push(Stack *sPtr, int data) {
	if (sPtr == NULL || sPtr->stack == NULL || isStackFull(sPtr) == TRUE) {
		return FALSE;
	}
	sPtr->stack[sPtr->top] = data;
	++(sPtr->top);
	return TRUE;
}
BOOL pop(Stack *sPtr, int *data) {
	if (sPtr == NULL || sPtr->stack == NULL || isStackEmpty(sPtr) == TRUE) {
		return FALSE;
	}
	*data = sPtr->stack[sPtr->top - 1];
	--(sPtr->top);
	return TRUE;
}
void printStack(const Stack *sPtr) {
	int i;
	for (i = 0; i < sPtr->top; ++i) {
		printf("|%3s%4d%3s|\n", "", sPtr->stack[sPtr->top - i - 1], "");
		printf("+----------+\n");
	}
}
void destroyStack(Stack *sPtr) {
	if (sPtr == NULL || sPtr->stack == NULL) {
		return;
	}
	free(sPtr->stack);
	sPtr->size = 0;
	sPtr->top = 0;
	sPtr->stack = NULL;
}
