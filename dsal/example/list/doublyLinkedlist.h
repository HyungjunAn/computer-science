#ifndef _DOUBLELYLINKEDLIST_
#define _DOUBLELYLINKEDLIST_

#include "word.h"

typedef enum _BOOL { FALSE, TRUE } BOOL;

typedef struct List List;
typedef struct Node Node;

struct List {
	Node *head;
	Node *tail;
	size_t size;
};
struct Node {
	Word data;
	Node* next;
	Node* prev;
};

Node* mkNode(const char *str);
BOOL createList(List *pList);
BOOL addFirst(List* pList, const char *str);
BOOL addLast(List* pList, const char *str);
BOOL erase(List* pList, const char *str);
Node* findNext(List* pList, const char *str);
Node* findPrev(List* pList, const char *str);
void destroyList(List* pList);
void printList(List* pList);

#endif
