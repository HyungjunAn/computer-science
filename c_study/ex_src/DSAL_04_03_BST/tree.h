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
	node_t *root;  // 트리의 head node를 가리키는 포인터 멤버
	int count;     // 총 노드의 개수
};

void initTree(tree_t *t);   // 트리 관리 구조체를 초기화 하는 함수
void inOrderTraverse(node_t *node); // 중위순회(정렬 순서로 출력)
void preOrderTraverse(node_t *node); // 전위순회
void postOrderTraverse(node_t *node); // 후위순회
bool addNode(tree_t *t, int key);      // 노드를 삽입하는 함수
bool deleteNode(tree_t *t, int key);    // data에 해당하는 노드 삭제 / 삭제한 노드의 parent의 주소 리턴
node_t *searchNode(tree_t *t, int data); // data에 해당하는 노드 검색 / 찾은 노드의 주소 리턴, 못찾으면 NULL 리턴
void postorderDelete(node_t *n); //postorder(후위 순회)방식의 노드 삭제 재귀호출 함수
void destroyTree(tree_t *t); // tree 소멸 함수

#endif /* BSTREE_H_ */
