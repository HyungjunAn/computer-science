#include <stdio.h>
#include "list.h"
#include <math.h>
#include <float.h>

void printList(List* head) {
	if (!head) {
		printf("[]\n");
		return;
	}
	printf("%d -> ", head->val);
	printList(head->next);
}
int main(void) {
	List* l = mkElement(3);
	l = insert(l, 4);
	l = insert(l, 2);
	l = insert(l, 6);
	l = insert(l, 1);
	l = insert(l, 4);

	printList(l);

	l = erase(l, 1);
	l = erase(l, 4);

	printList(l);

	float x = 100000000.0f;
	printf("1. x = %f\n", x);
	x += 1.0f;
	printf("2. x = %f\n", x);

	int count = 1;
	for (x = 0; x <= 1.0f; x += 0.1f)
	{
		printf("%d. x = %.10f\n", count++, x);
	}

	double a, b;
	printf("a=");
	scanf("%lf", &a);

	printf("b=");
	scanf("%lf", &b);

	printf("DBL_EPSILON = %.30lf\n", DBL_EPSILON);

	unsigned int aa=200;

	int bb=-1;

	if(aa>bb) printf("true");

	else printf("false");


	return 0;
}
