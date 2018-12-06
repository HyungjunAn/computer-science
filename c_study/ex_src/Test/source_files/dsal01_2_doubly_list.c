#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct List List;
typedef struct Node Node;

struct List {
	Node *head;
	Node *tail;
	size_t size;
};
struct Node {
	int val;
	Node* next;
	Node* prev;
};

Node* mkNode(int val);
List* creatList(void);
void insertFirst(List* pList, int val);
void insertLast(List* pList, int val);
int erase(List* pList, int val);
int findNext(List* pList, int val);
int findPrev(List* pList, int val);
void deleteList(List* pList);
void printList(List* pList);

int main(void) {
	List* l = creatList();
	insertFirst(l, 4);
	insertFirst(l, 2);
	insertFirst(l, 6);
	insertFirst(l, 1);

	printList(l);

	erase(l, 1);
	erase(l, 4);
	printList(l);

	insertLast(l, 4);
	insertLast(l, 3);
	printList(l);
	return 0;
}

Node* mkNode(int val) {
	Node *pNode = (Node*)malloc(sizeof(Node));
	pNode->val = val;
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

void insertFirst(List* pList, int val) {
	Node* tmp = pList->head->next;
	Node* pNode = mkNode(val);
	pList->head->next = pNode;
	pNode->prev = pList->head;
	pNode->next = tmp;
	tmp->prev = pNode;
	pList->size++;
}
void insertLast(List* pList, int val) {
	Node* tmp = pList->tail->prev;
	Node* pNode = mkNode(val);
	pList->tail->prev = pNode;
	pNode->next = pList->tail;
	pNode->prev = tmp;
	tmp->next = pNode;
	pList->size++;
}

int findNext(List* pList, int val) {
	Node* p;
	for (p = pList->head->next; p != pList->tail; p = p->next) {
		if (p->val == val) {
			return 1;
		}
	}
	return 0;
}

int findPrev(List* pList, int val) {
	Node* p;
	for (p = pList->tail->prev; p != pList->head; p = p->prev) {
		if (p->val == val) {
			return 1;
		}
	}
	return 0;
}
int erase(List* pList, int val) {
	Node* p;
	Node* tmp;
	for (p = pList->head; p->next != pList->tail; p = p->next) {
		if (p->next->val == val) {
			tmp = p->next->next;
			free(p->next);
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
		printf("%d ", p->val);
	}
	printf("\n");
}
