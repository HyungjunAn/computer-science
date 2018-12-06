#include <stdio.h>
typedef enum _BOOL { FALSE, TRUE } BOOL;

void swap(int* pa, int* pb);
void selectionSort(int *arr, int size);
void bubbleSort(int *arr, int size);
void quickSort(int *arr, int size);
void quickSort_nonRec(int *arr, int size);
void printArr(int *arr, int size);
BOOL binarySearch(int *arr, int size, int data);
BOOL binarySearch_nonRec(int *arr, int size, int data);



int main(void) {
	int i;
	int arr[][10] = {
			{1,4,3,6,0,1,2,9,10,5},
			{1,4,3,6,0,1,2,9,10,5},
			{1,4,3,6,0,1,2,9,10,5},
			{1,4,3,6,0,1,2,9,10,5},
			{1,4,3,6,0,1,2,9,10,5},
		};
	int size = sizeof(arr[0]) / sizeof(arr[0][0]);
	void (*sortf[])(int *, int) = {selectionSort, bubbleSort, quickSort, quickSort_nonRec};
	int numFunc = sizeof(sortf) / sizeof(sortf[0]);

	for (i = 0; i < numFunc; ++i) {
		printArr(arr[i], size);
		sortf[i](arr[i], size);
		printArr(arr[i], size);
		printf("\n");
	}

	int n = 1;
	printf("%d: %s\n", n, binarySearch(arr[0], size, n)? "O": "X");
	printf("%d: %s\n", n, binarySearch_nonRec(arr[0], size, n)? "O": "X");
	n = 13;
	printf("%d: %s\n", n, binarySearch(arr[0], size, n)? "O": "X");
	printf("%d: %s\n", n, binarySearch_nonRec(arr[0], size, n)? "O": "X");

	//int arrr[10] = {3, 0, 5, 0, 4, 0, 1, 0, 2, 0};
	int arrr[10];
	printArr(arrr, 10);
	quickSort(arrr, 10);
	printArr(arrr, 10);

	return 0;
}

void swap(int* pa, int* pb) {
	int tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}
void selectionSort(int *arr, int size) {
	int i, j, min_i;
	for (i = 0; i < size - 1; ++i) {
		min_i = i;
		for (j = i+1; j < size; ++j) {
			if (arr[j] < arr[min_i]) {
				min_i = j;
			}
		}
		swap(&arr[i], &arr[min_i]);
	}
}
void bubbleSort(int *arr, int size) {
	int i;
	while (size != 1) {
		for (i = 0; i < size - 1; ++i) {
			if (arr[i] > arr[i+1]) {
				swap(&arr[i], &arr[i+1]);
			}
		}
		size--;
	}
}
void quickSort(int *arr, int size) {
	if (size == 1 || size == 0) {
		return;
	}
	int pivot_i = size - 1;
	int i = -1;
	int j = size - 1;
	while (1) {
		while (arr[pivot_i] > arr[++i]);
		while (j >= 0 && arr[pivot_i] < arr[--j]);
		if (i>=j) {
			break;
		}
		swap(&arr[i], &arr[j]);
	}
	swap(&arr[i], &arr[pivot_i]);

	quickSort(arr, i);
	quickSort(arr+i+1, size-i-1);
}
void quickSort_nonRec(int *arr, int size) {
	if (size == 0) {
		return;
	}
	int pivot_i = size - 1;
	int i;
	int j;
	while (size > 1) {
		i = -1;
		j = pivot_i;
		while (1) {
			while (i <= pivot_i - 1 && arr[pivot_i] > arr[++i]);
			while (j >= 0 && arr[pivot_i] < arr[--j]);
			if (i>=j) {
				break;
			}
			swap(&arr[i], &arr[j]);
		}
		if (pivot_i == i) {
			pivot_i--;
		}
		else {
			swap(&arr[i], &arr[pivot_i]);
			size--;
		}
	}
}
void printArr(int *arr, int size) {
	while (size != 0) {
		printf("%d ", *arr);
		arr++;
		size--;
	}
	printf("\n");
}
BOOL binarySearch(int *arr, int size, int data) {
	if (size == 0) {
		return FALSE;
	}
	int mid_i = size / 2;

	if (arr[mid_i] == data) {
		return TRUE;
	}
	else if (arr[mid_i] > data) {
		return binarySearch(arr, mid_i, data);
	}
	else {
		return binarySearch(arr + mid_i + 1, size - mid_i - 1, data);
	}
}
BOOL binarySearch_nonRec(int *arr, int size, int data) {
	if (size == 0) {
		return FALSE;
	}
	int start_i = 0;
	int mid_i;

	while (size != 0) {
		mid_i = start_i + size / 2;
		if (arr[mid_i] == data) {
			return TRUE;
		}
		else if (arr[mid_i] > data) {
			size = mid_i - start_i;
		}
		else {
			size = size - (mid_i - start_i) - 1;
			start_i = mid_i + 1;
		}
	}
	return FALSE;
}

