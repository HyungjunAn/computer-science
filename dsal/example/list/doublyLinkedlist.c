#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "doublyLinkedlist.h"
#include "word.h"

Node* mkNode(const char *str) {
	Node *pNode = (Node*)malloc(sizeof(Node));

	if (pNode == NULL) {
		return NULL;
	}
	makeWord(&(pNode->data), str);
	pNode->next = NULL;
	pNode->prev = NULL;
	return pNode;
}

BOOL createList(List *pList) {
	if (pList == NULL) {
		return FALSE;
	}
	pList->head = mkNode("");
	if (pList->head == NULL) {
		return FALSE;
	}
	pList->tail = mkNode("");
	if (pList->tail == NULL) {
		return FALSE;
	}

	pList->head->next = pList->tail;
	pList->head->prev = pList->head;
	pList->tail->next = pList->tail;
	pList->tail->prev = pList->head;

	pList->size = 0;
	return TRUE;
}

BOOL addFirst(List* pList, const char *str) {
	if (pList == NULL) {
		return FALSE;
	}
	Node* tmp = pList->head->next;
	Node* pNode = mkNode(str);
	if (pNode == NULL) {
		return FALSE;
	}
	pList->head->next = pNode;
	pNode->prev = pList->head;
	pNode->next = tmp;
	tmp->prev = pNode;
	pList->size++;
	return TRUE;
}
BOOL addLast(List* pList, const char *str) {
	if (pList == NULL) {
		return FALSE;
	}
	Node* tmp = pList->tail->prev;
	Node* pNode = mkNode(str);
	if (pNode == NULL) {
		return FALSE;
	}
	pList->tail->prev = pNode;
	pNode->next = pList->tail;
	pNode->prev = tmp;
	tmp->next = pNode;
	pList->size++;
	return TRUE;
}

Node* findNext(List* pList, const char *str) {
	if (pList == NULL) {
		return NULL;
	}
	Node* p;
	for (p = pList->head->next; p != pList->tail; p = p->next) {
		if (strcmp(p->data.word, str) == 0) {
			return p;
		}
	}
	return NULL;
}

Node* findPrev(List* pList, const char *str) {
	if (pList == NULL) {
		return NULL;
	}
	Node* p;
	for (p = pList->tail->prev; p != pList->head; p = p->prev) {
		if (strcmp(p->data.word, str) == 0) {
			return p;
		}
	}
	return NULL;
}
BOOL erase(List* pList, const char *str) {
	if (pList == NULL) {
		return FALSE;
	}
	Node* p;
	Node* tmp;
	for (p = pList->head; p->next != pList->tail; p = p->next) {
		if (strcmp(p->next->data.word, str) == 0) {
			tmp = p->next->next;
			free(p->next);
			p->next = tmp;
			tmp->prev = p;
			pList->size--;
			return TRUE;
		}
	}
	return FALSE;
}
void destroyList(List* pList) {
	Node *tmp;
	Node *p = pList->head->next;
	while (p != pList->tail) {
		tmp = p->next;
		free(p);
		p = tmp;
	}
	free(pList->head);
	free(pList->tail);
}
void printList(List* pList) {
	printf("사용자 입력 단어 : ");
	Node *p;
	for (p = pList->head->next; p != pList->tail; p = p->next) {
		printf("%s(%d)/", p->data.word, p->data.len);
	}
	printf("\n");
	return;
}
