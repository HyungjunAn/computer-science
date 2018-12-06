#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

static void downHeap(Heap *hPtr, int position) {
	int left;
	int right;
	int min;
	int tmp;

	while (position < hPtr->count) {
		left = position * 2;
		right = position * 2 + 1;
		if (hPtr->count < left) {
			break;
		}

		if (hPtr->count == left) {
			min = left;
		}
		else {
			min = (hPtr->heap[left] < hPtr->heap[right])? left: right;
		}
		if (hPtr->heap[position] < hPtr->heap[min]) {
			break;
		}
		tmp = hPtr->heap[position];
		hPtr->heap[position] = hPtr->heap[min];
		hPtr->heap[min] = tmp;
		position = min;
	}
}

static void upHeap(Heap *hPtr, int position) {
	int parent;
	int tmp;

	while (position > 1) {
		parent = position / 2;
		if (hPtr->heap[position] > hPtr->heap[parent]) {
			break;
		}
		tmp = hPtr->heap[parent];
		hPtr->heap[parent] = hPtr->heap[position];
		hPtr->heap[position] = tmp;
		position = parent;
	}
}

bool createHeap(Heap *hPtr, int size) {
	if (hPtr == NULL) {
		return false;
	}
	hPtr->heap = (int*)malloc(sizeof(int) * (size+1));
	if (hPtr->heap == NULL) {
		return false;
	}
	hPtr->hSize = size;
	hPtr->count = 0;
	return true;
}

void destroyHeap(Heap *hPtr) {
	if (hPtr == NULL) {
		return;
	}
	free(hPtr->heap);
	hPtr->hSize = 0;
	hPtr->count = 0;
	return;
}

bool insertUpHeap(Heap *hPtr, int inData) {
	if (isHeapFull(hPtr)) {
		return false;
	}
	hPtr->heap[hPtr->count + 1] = inData;
	hPtr->count++;
	upHeap(hPtr, hPtr->count);
	return true;
}

bool deleteDownHeap(Heap *hPtr, int *getData) {
	if (isHeapEmpty(hPtr)) {
		return false;
	}
	*getData = hPtr->heap[1];
	hPtr->heap[1] = hPtr->heap[hPtr->count];
	hPtr->count--;
	downHeap(hPtr, 1);
	return true;
}

void printHeap(Heap *hPtr) {
	int i;
	if (!isHeapEmpty(hPtr)) {
		for (i=1 ; i<=hPtr->count ; i++) {
			printf("%d ", hPtr->heap[i]);
		}
		printf("\n");
	}
}

bool isHeapEmpty(Heap *hPtr) {
	return (hPtr->count == 0);
}

bool isHeapFull(Heap *hPtr) {
	return (hPtr->count >= hPtr->hSize);
}
