#ifndef HEAP_H_
#define HEAP_H_
#include <stdbool.h>

typedef struct _heap Heap;
struct _heap {
	int *heap;
	int hSize;
	int count;
};

bool createHeap(Heap *hPtr, int size);
void destroyHeap(Heap *hPtr);
bool insertUpHeap(Heap *hPtr, int inData);
bool deleteDownHeap(Heap *hPtr, int *getData);
void printHeap(Heap *hPtr);
bool isHeapEmpty(Heap *hPtr);
bool isHeapFull(Heap *hPtr);

#endif /* HEAP_H_ */
