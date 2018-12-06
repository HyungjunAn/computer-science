#ifndef BSTREE_H_
#define BSTREE_H_
#include <stdbool.h>

typedef struct _node node_t;
typedef struct _tree tree_t;

struct _node {
	int data;
	struct _node *left;
	struct _node *right;
};

struct _tree {
	node_t *root;  // Ʈ���� head node�� ����Ű�� ������ ���
	int count;     // �� ����� ����
};

void initTree(tree_t *t);   // Ʈ�� ���� ����ü�� �ʱ�ȭ �ϴ� �Լ�
void inOrderTraverse(node_t *node); // ������ȸ(���� ������ ���)
void preOrderTraverse(node_t *node); // ������ȸ
void postOrderTraverse(node_t *node); // ������ȸ
bool addNode(tree_t *t, int key);      // ��带 �����ϴ� �Լ�
bool deleteNode(tree_t *t, int key);    // data�� �ش��ϴ� ��� ���� / ������ ����� parent�� �ּ� ����
node_t *searchNode(tree_t *t, int data); // data�� �ش��ϴ� ��� �˻� / ã�� ����� �ּ� ����, ��ã���� NULL ����
void postorderDelete(node_t *n); //postorder(���� ��ȸ)����� ��� ���� ���ȣ�� �Լ�
void destroyTree(tree_t *t); // tree �Ҹ� �Լ�

#endif /* BSTREE_H_ */
