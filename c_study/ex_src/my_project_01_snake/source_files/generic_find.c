#include <stdio.h>
int* find(int* begin, int* end, int value);
void* generic_find(void* begin, void* end, size_t size, void* pValue);

int main()
{
	int x[10] = { 1,2,3,4,5,6,7,8,9,10 };

	size_t size = sizeof(x) / sizeof(x[0]);

	int* p = find(x, x + size, 5);
	int n = 5;
	void *vp = generic_find(x, x + size, sizeof(int), &n);

	if (vp == x + size) {
		printf("not find\n");
	}
	else {
		printf("find data = %d\n", *(int*)vp);
	}

	p = find(x, x + size, 15);
	n = 15;
	vp = generic_find(x, x + size, sizeof(int), &n);
	if (vp == x + size)
	{
		printf("not find\n");
	}
	else
	{
		printf("find data = %d\n", *(int*)vp);
	}

	return 0;
}

int* find(int* begin, int* end, int value)
{
	while (begin != end && *begin != value) {
		++begin;
	}

	return begin;
}
void* generic_find(void* begin, void* end, size_t size, void* pValue) {
	int check = 0;
	int i;
	while (begin != end) {
		for (i = 0; i < size; ++i) {
			if (((char*)begin)[i] != ((char*)pValue)[i]) {
				break;
			}
		}
		if (i != size) {
			begin = (char*)begin + size;
		}
		else {
			break;
		}
	}
	return begin;
}
