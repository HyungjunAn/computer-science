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

static node_t* _addNode(node_t *pNode, int key) {
	if (pNode == NULL) {
		return pNode = _mkNode(key);
	}
	else if (pNode->data == key) {
		return pNode;
	}
	else if (pNode->data > key) {
		pNode->left = _addNode(pNode->left, key);
	}
	else if (pNode->data < key) {
		pNode->right = _addNode(pNode->right, key);
	}
	else {
		;
	}
	return pNode;
}
bool addNode(tree_t *t, int key)
{
	if (t == NULL) {
		return false;
	}
	t->root = _addNode(t->root, key);
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
static node_t* _findMax(node_t *pNode) {
	if (pNode == NULL) {
		return NULL;
	}
	else if (pNode->right == NULL) {
		return pNode;
	}
	else {
		return _findMax(pNode->right);
	}
}
static node_t* _findMin(node_t *pNode) {
	if (pNode == NULL) {
		return NULL;
	}
	else if (pNode->left == NULL) {
		return pNode;
	}
	else {
		return _findMin(pNode->left);
	}

}
static node_t* _deleteNode(node_t *pNode, int key, int *pCount) {
	node_t *lMax;
	node_t *rMin;
	if (pNode == NULL) {
		return NULL;
	}
	else if (pNode->data == key) {
		lMax = _findMax(pNode->left);
		rMin = _findMin(pNode->right);
		if (lMax != NULL) {
			pNode->data = lMax->data;
			pNode->left = _deleteNode(pNode->left, lMax->data, pCount);
		}
		else if (rMin != NULL) {
			pNode->data = rMin->data;
			pNode->right = _deleteNode(pNode->right, rMin->data, pCount);
		}
		else {
			(*pCount)--;
			free(pNode);
			pNode = NULL;
		}
	}
	else if (pNode->data > key) {
		pNode->left = _deleteNode(pNode->left, key, pCount);
	}
	else if (pNode->data < key) {
		pNode->right = _deleteNode(pNode->right, key, pCount);
	}
	else {
		;
	}
	return pNode;
}

bool deleteNode(tree_t *t, int key) {
	int oldCnt;
	if (t == NULL) {
		return false;
	}
	oldCnt = t->count;
	t->root = _deleteNode(t->root, key, &(t->count));
	return (oldCnt == t->count)? false: true;
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
