#include <stdio.h>
#include <stdlib.h>
#include "listStack.h"

BOOL createStack(Stack *sp) {
	if (sp == NULL) {
		return FALSE;
	}
	sp->head = (Snode*)malloc(sizeof(Snode) * 1);
	if (sp->head == NULL) {
		return FALSE;
	}
	sp->tail = (Snode*)malloc(sizeof(Snode) * 1);
	if (sp->tail == NULL) {
		free(sp->head);
		return FALSE;
	}
	sp->head->next = sp->tail;
	sp->tail->next = sp->tail;
	return TRUE;
}
BOOL isStackEmpty(const Stack *sp) {
	if (sp == NULL) {
		return FALSE;
	}
	if (sp->head->next == sp->tail) {
		return TRUE;
	}
	return FALSE;
}
BOOL push(Stack *sp, int pushData) {
	if (sp == NULL) {
		return FALSE;
	}
	Snode *pSnode = (Snode*)malloc(sizeof(Snode) * 1);
	if (sp == NULL || pSnode == NULL) {
		return FALSE;
	}
	pSnode->data = pushData;
	pSnode->next = sp->head->next;
	sp->head->next = pSnode;
	return TRUE;
}
BOOL pop(Stack *sp, int *popData) {
	if (sp == NULL) {
		return FALSE;
	}
	Snode *pSnode = sp->head->next;
	if (pSnode == sp->tail) {
		return FALSE;
	}
	*popData = pSnode->data;
	sp->head->next = pSnode->next;
	free(pSnode);
	return TRUE;
}
void printStack(const Stack*sp) {
	if (sp == NULL) {
		return;
	}
	Snode *pSnode;
	for (pSnode = sp->head->next; pSnode != sp->tail; pSnode = pSnode->next) {
		printf("|%3s%4d%3s|\n", "", pSnode->data, "");
		printf("+----------+\n");
	}
}
void destroyStack(Stack *sp) {			/* 스택 메모리 해제 함수 */
	if (sp == NULL) {
		return;
	}
	Snode *tmp;
	Snode *pSnode = sp->head->next;
	while (pSnode->next != sp->tail) {
		tmp = pSnode;
		pSnode = pSnode->next;
		free(tmp);
	}
	free(sp->head);
	free(sp->tail);
}
