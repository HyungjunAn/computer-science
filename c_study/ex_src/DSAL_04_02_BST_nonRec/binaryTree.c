#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
/* --------------------------------------------------------------------------------------
�Լ��� : initTree - ��带 �����ϴ� �Լ�
�������� : t - tree_t ����ü�� �ּ�
���� �� : ���� �� true / ���� �� false
---------------------------------------------------------------------------------------*/

void initTree(tree_t *t) {
	t->root = NULL;
	t->count = 0;
}
/* --------------------------------------------------------------------------------------
�Լ��� : addNode - ��带 �����ϴ� �Լ�
�������� : t - tree_t ����ü�� �ּ�
         data - �� ��忡 ����� ������
���� �� : ���� �� true / ���� �� false
---------------------------------------------------------------------------------------*/

static node_t* _mkNode(int key) {
	node_t* pNode = (node_t*)malloc(sizeof(node_t) * 1);
	pNode->data = key;
	pNode->left = NULL;
	pNode->right = NULL;
	return pNode;
}

bool addNode(tree_t *t, int key)
{
	if (t == NULL) {
		return false;
	}
	else if (t->root == NULL) {
		t->root = _mkNode(key);
	}
	else {
		node_t *cur = t->root;
		node_t *parent;
		while (cur != NULL) {
			parent = cur;
			if (cur->data == key) {
				return false;
			}
			else if (cur->data > key) {
				cur = cur->left;
			}
			else if (cur->data < key) {
				cur = cur->right;
			}
			else {
				;
			}
		}
		if (parent->data > key) {
			parent->left = _mkNode(key);
		}
		else {
			parent->right = _mkNode(key);
		}
	}
	t->count++;
	return true;
}
/* --------------------------------------------------------------------------------------
�Լ��� : inOrderTraverse - ������ȸ(���� ������ ���)
�������� : np - �湮�� ����� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void inOrderTraverse(node_t *np)
{
	if (np == NULL) {
		return;
	}
	inOrderTraverse(np->left);
	printf("%d ", np->data);
	inOrderTraverse(np->right);
}

/* --------------------------------------------------------------------------------------
�Լ��� : preOrderTraverse - ������ȸ
�������� : np - �湮�� ����� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void preOrderTraverse(node_t *np)
{
	if (np == NULL) {
		return;
	}
	printf("%d ", np->data);
	preOrderTraverse(np->left);
	preOrderTraverse(np->right);
}
/* --------------------------------------------------------------------------------------
�Լ��� : postOrderTraverse - ������ȸ
�������� : np - �湮�� ����� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void postOrderTraverse(node_t *np)
{
	if (np == NULL) {
		return;
	}
	postOrderTraverse(np->left);
	postOrderTraverse(np->right);
	printf("%d ", np->data);
}
/* --------------------------------------------------------------------------------------
�Լ��� : searchNode - data�� �ش��ϴ� ��� �˻�
�������� : t - tree_t ����ü�� �ּ�
         data - �˻��� ������
���� �� : ã�� ����� �ּ� / ��ã���� NULL pointer
---------------------------------------------------------------------------------------*/
static node_t * _searchNode(node_t *pNode, int data) {
	if (pNode == NULL) {
		return NULL;
	}
	else if (pNode->data == data) {
		return pNode;
	}
	else if (pNode->data > data) {
		return _searchNode(pNode->left, data);
	}
	else if (pNode->data < data) {
		return _searchNode(pNode->right, data);
	}
	else {
		return NULL;
	}
}
node_t * searchNode(tree_t *t, int  data)
{
	if (t == NULL) {
		return NULL;
	}
	return _searchNode(t->root, data);
}
/* --------------------------------------------------------------------------------------
�Լ��� : deleteNode - data�� �ش��ϴ� ��� ����
�������� : t - tree_t ����ü�� �ּ�
         data - ������ ������
���� �� true / ���� �� false
---------------------------------------------------------------------------------------*/

bool deleteNode(tree_t *t, int key) {
	node_t *target;		/* ���� ��� ��� */
	node_t *parent;		/* ���� ��� ����� �θ� ��� */
	node_t *sub;		/* ��ü ��� */
	node_t *subParent;	/* ��ü ����� �θ� ��� */
	node_t *child;		/* ���� ����� �ڽ� ��� */


	if (t == NULL) {
		return false;
	}
	else {
		parent = t->root;
		target = t->root;
		while (target != NULL && target->data != key) {
			parent = target;
			if (target->data > key) {
				target = target->left;
			}
			else if (target->data < key) {
				target = target->right;
			}
			else {
				;
			}
		}
		if (target == NULL) {
			return false;
		}

		if (target->left == NULL || target->right == NULL) {
			node_t *nonNull = (target->left != NULL)? target->left: target->right;
			if (parent == target) {
				t->root = nonNull;
			}
			if (parent->left == target) {
				parent->left = nonNull;
			}
			else if (parent->right == target) {
				parent->right = nonNull;
			}
			free(target);
		}
		else {
			subParent = target;
			sub = subParent->left;
			while (sub->right != NULL) {
				subParent = sub;
				sub = sub->right;
			}
			if (subParent->left == sub) {
				subParent->left = sub->left;
			}
			else {
				subParent->right = sub->left;
			}
			target->data = sub->data;
			free(sub);
		}
		t->count--;
		return true;
	}
}
/* --------------------------------------------------------------------------------------
�Լ��� : destroyTree - tree ���� ��� ��� ����(tree �Ҹ�)
�������� : t - Tree ����ü�� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void destroyTree(tree_t *t) {
	postorderDelete(t->root);
	printf("���� �Ϸ�\n");
	t->root = NULL;
	t->count = 0;
}
/* --------------------------------------------------------------------------------------
�Լ��� : postorderDelete - postorder(���� ��ȸ)����� ��� ����(���ȣ�� �Լ�)
�������� : np - �湮�� ����� �ּ�
���� �� : ����
---------------------------------------------------------------------------------------*/
void postorderDelete(node_t *n)
{
	if (n == NULL) {
		return;
	}
	postorderDelete(n->left);
	postorderDelete(n->right);
	free(n);
	return;
}
