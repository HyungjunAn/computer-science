#ifndef ARRAYSTACK_H_
#define ARRAYSTACK_H_
typedef enum _BOOL { FALSE, TRUE } BOOL;

typedef struct _stack {
	int *stack;		/* stack���� ���Ǵ� �����Ҵ� �迭�� ����Ű�� ������ ���� */
	int size;		/* ������ ũ��(size) */
	int top;		/* ������ ��,�ⱸ ��ġ���� ���� */
}Stack;

BOOL createStack(Stack *sPtr, int size);		/* ���� �޸� �Ҵ� �� ��� �ʱ�ȭ �Լ� */
BOOL isStackFull(Stack *sPtr);		/* ������ �� ���ִ��� �˻� */
BOOL isStackEmpty(Stack *sPtr);		/* ������ ������ ����ִ°� �˻� */
BOOL push(Stack *sPtr, int data);			/* ���ÿ� ������ �����ϴ� �Լ� */
BOOL pop(Stack *sPtr, int *dataPtr);			/* ���ÿ��� �����͸� ������ �Լ� */
void printStack(const Stack*sPtr);		/* ���� ���� ��� �����͸� ����ϴ� �Լ� */
void destroyStack(Stack *sPtr);			/* ���� �޸� ���� �Լ� */

#endif /* ARRAYSTACK_H_ */
