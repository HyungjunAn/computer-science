#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct List List;
typedef struct Node Node;
typedef int (*cmpFunc)(void *, void *);

struct List {
	Node *head;
	Node *tail;
	size_t size;
};
struct Node {
	void* pVal;
	Node* next;
	Node* prev;
};

Node* mkNode(int val);
List* creatList(void);
void insertFirst(List* pList, Node* pNode);
void insertLast(List* pList, Node* pNode);
int erase(List* pList, void* pVal, cmpFunc cmp);
int findNext(List* pList, void* pVal, cmpFunc cmp);
int findPrev(List* pList, void* pVal, cmpFunc cmp);
void deleteList(List* pList);
void printList(List* pList);
int cmp(void *pa, void *pb);
void freeNode(Node* pNode);

int main(void) {
	List* l = creatList();
	insertFirst(l, mkNode(4));
	insertFirst(l, mkNode(2));
	insertFirst(l, mkNode(6));
	insertFirst(l, mkNode(1));

	printList(l);

	int n;
	n = 1;
	erase(l, &n, cmp);
	n = 4;
	erase(l, &n, cmp);
	printList(l);

	insertLast(l, mkNode(4));
	insertLast(l, mkNode(3));
	printList(l);
	return 0;
}

Node* mkNode(int val) {
	Node *pNode = (Node*)malloc(sizeof(Node));
	pNode->pVal = (int*)malloc(sizeof(int));
	*(int*)(pNode->pVal) = val;
	pNode->next = NULL;
	pNode->prev = NULL;
	return pNode;
}

List* creatList(void) {
	List* p = (List*)malloc(sizeof(List));
	p->head = mkNode(0);
	p->tail = mkNode(0);

	p->head->next = p->tail;
	p->head->prev = p->head;
	p->tail->next = p->tail;
	p->tail->prev = p->head;

	p->size = 0;
	return p;
}

void insertFirst(List* pList, Node* pNode) {
	Node* tmp = pList->head->next;
	pList->head->next = pNode;
	pNode->prev = pList->head;
	pNode->next = tmp;
	tmp->prev = pNode;
	pList->size++;
}
void insertLast(List* pList, Node* pNode) {
	Node* tmp = pList->tail->prev;
	pList->tail->prev = pNode;
	pNode->next = pList->tail;
	pNode->prev = tmp;
	tmp->next = pNode;
	pList->size++;
}

int findNext(List* pList, void* pVal, cmpFunc cmp) {
	Node* p;
	for (p = pList->head->next; p != pList->tail; p = p->next) {
		if (cmp(p->pVal, pVal) == 0) {
			return 1;
		}
	}
	return 0;
}

int findPrev(List* pList, void* pVal, cmpFunc cmp) {
	Node* p;
	for (p = pList->tail->prev; p != pList->head; p = p->prev) {
		if (cmp(p->pVal, pVal) == 0) {
			return 1;
		}
	}
	return 0;
}
int erase(List* pList, void* pVal, cmpFunc cmp) {
	Node* p;
	Node* tmp;
	for (p = pList->head; p->next != pList->tail; p = p->next) {
		if (cmp(p->next->pVal, pVal) == 0) {
			tmp = p->next->next;
			freeNode(p->next);
			p->next = tmp;
			tmp->prev = p;
			pList->size--;
			return 1;
		}
	}
	return 0;
}
void deleteList(List* pList) {
	Node *tmp;
	Node *p = pList->head->next;
	while (p != pList->tail) {
		tmp = p->next;
		free(p);
		p = tmp;
	}
	free(pList->head);
	free(pList->tail);
	free(pList);
}
void printList(List* pList) {
	Node *p;
	for (p = pList->head->next; p != pList->tail; p = p->next) {
		printf("%d ", *(int*)(p->pVal));
	}
	printf("\n");
}
int cmp(void *pa, void *pb) {
	return *(int*)pa - *(int*)pb;

}
void freeNode(Node* pNode) {
	free(pNode->pVal);
	free(pNode);
}
