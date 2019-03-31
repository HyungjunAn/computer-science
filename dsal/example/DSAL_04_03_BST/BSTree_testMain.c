#include <stdio.h>
#include "tree.h"

int main(void) {
	int ary[] = { 50, 30, 80, 20, 40, 10, 70, 90, 60 ,100};
	int size = (int)(sizeof(ary)/sizeof(ary[0]));
	int i;
	tree_t t;
	node_t *n;
	int data;

	initTree(&t);
	for (i=0 ; i<size ; i++) {
		addNode(&t, ary[i]);
	}
	n = t.root;
	inOrderTraverse(t.root);
	printf("\n");

	for (i=0 ; i<size ; i++) {
		printf("[%d delete : ]", ary[i]);
		deleteNode(&t, ary[i]);
		inOrderTraverse(t.root);
		printf("\n");
	}

	for (i=0 ; i<size ; i++) {
		addNode(&t, ary[i]);
	}
	inOrderTraverse(t.root);
	printf("\n");

	data = 80;
	n = searchNode(&t, data);
	if (n == NULL) {
		printf("%d : Not found!\n", data);
	}
	else {
		printf("%d : found!\n", n->data);
	}

	data = 100;
	n = searchNode(&t, data);
	if (n == NULL) {
		printf("%d : Not found!\n", data);
	}
	else {
		printf("%d : found!\n", n->data);
	}

	destroyTree(&t);
	return 0;
}
