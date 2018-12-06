#ifndef LISTSTACK_H_
#define LISTSTACK_H_

typedef enum _BOOL{ FALSE, TRUE } BOOL;

typedef struct _stacknode Snode;

struct _stacknode
{
	int data;		/* int ������ ���� */
	Snode *next;	/* ���� ��带 ����Ű�� ������ ���� */
};

typedef struct _stack	/* stack ���� ����ü */
{
	Snode *head;	/* head pointer (head node ����Ŵ) */
	Snode *tail;	/* tail pointer (tail node ����Ŵ) */
}Stack;

BOOL createStack(Stack *sp);		/* ��ũ�帮��Ʈ�� �����Ǵ� ���� ���� �Լ� */
BOOL isStackEmpty(const Stack *sp);		/* ������ ������ ����ִ°� �˻� */
BOOL push(Stack *sp, int pushData);	/* ���ÿ� ������ �����ϴ� �Լ� */
BOOL pop(Stack *sp, int *popData);	/* ���ÿ��� �����͸� ������ �Լ� */
void printStack(const Stack*sp);		/* ���� ���� ��� �����͸� ����ϴ� �Լ� */
void destroyStack(Stack *sp);			/* ���� �޸� ���� �Լ� */

#endif /* LISTSTACK_H_  */
