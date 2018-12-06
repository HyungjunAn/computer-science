#ifndef STACK_H_
#define STACK_H_
#include<stdbool.h>

typedef struct _stack {
	int *stack;		/* stack���� ���Ǵ� �����Ҵ� �迭�� ����Ű�� ������ ���� */
	int size;		/* ������ ũ��(size) */
	int top;		/* ������ ��,�ⱸ ��ġ���� ���� */
}Stack;

bool createStack(Stack *, int);		/* ���� �޸� �Ҵ� �� ��� �ʱ�ȭ �Լ� */
bool isStackFull(Stack *sPtr);		/* ������ �� ���ִ��� �˻� */
bool isStackEmpty(Stack *sPtr);		/* ������ ������ ����ִ°� �˻� */
bool push(Stack *, int);			/* ���ÿ� ������ �����ϴ� �Լ� */
bool pop(Stack *, int *);			/* ���ÿ��� �����͸� ������ �Լ� */
void printStack(const Stack*);		/* ���� ���� ��� �����͸� ����ϴ� �Լ� */
void destroyStack(Stack *);			/* ���� �޸� ���� �Լ� */

#endif /* STACK_H_ */
