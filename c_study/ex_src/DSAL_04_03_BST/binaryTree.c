#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
/* --------------------------------------------------------------------------------------
함수명 : initTree - 노드를 삽입하는 함수
전달인자 : t - tree_t 구조체의 주소
리턴 값 : 성공 시 true / 실패 시 false
---------------------------------------------------------------------------------------*/

void initTree(tree_t *t) {
	t->root = NULL;
	t->count = 0;
}
/* --------------------------------------------------------------------------------------
함수명 : addNode - 노드를 삽입하는 함수
전달인자 : t - tree_t 구조체의 주소
         data - 새 노드에 저장될 데이터
리턴 값 : 성공 시 true / 실패 시 false
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
함수명 : inOrderTraverse - 중위순회(정렬 순서로 출력)
전달인자 : np - 방문할 노드의 주소
리턴 값 : 없음
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
함수명 : preOrderTraverse - 전위순회
전달인자 : np - 방문할 노드의 주소
리턴 값 : 없음
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
함수명 : postOrderTraverse - 후위순회
전달인자 : np - 방문할 노드의 주소
리턴 값 : 없음
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
함수명 : searchNode - data에 해당하는 노드 검색
전달인자 : t - tree_t 구조체의 주소
         data - 검색할 데이터
리턴 값 : 찾은 노드의 주소 / 못찾으면 NULL pointer
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
함수명 : deleteNode - data에 해당하는 노드 삭제
전달인자 : t - tree_t 구조체의 주소
         data - 삭제할 데이터
성공 시 true / 실패 시 false
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
함수명 : destroyTree - tree 내의 모든 노드 삭제(tree 소멸)
전달인자 : t - Tree 구조체의 주소
리턴 값 : 없음
---------------------------------------------------------------------------------------*/
void destroyTree(tree_t *t) {
	postorderDelete(t->root);
	printf("삭제 완료\n");
	t->root = NULL;
	t->count = 0;
}
/* --------------------------------------------------------------------------------------
함수명 : postorderDelete - postorder(후위 순회)방식의 노드 삭제(재귀호출 함수)
전달인자 : np - 방문할 노드의 주소
리턴 값 : 없음
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
