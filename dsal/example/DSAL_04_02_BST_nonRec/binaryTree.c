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

bool deleteNode(tree_t *t, int key) {
	node_t *target;		/* 삭제 대상 노드 */
	node_t *parent;		/* 삭제 대상 노드의 부모 노드 */
	node_t *sub;		/* 대체 노드 */
	node_t *subParent;	/* 대체 노드의 부모 노드 */
	node_t *child;		/* 삭제 노드의 자식 노드 */


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
