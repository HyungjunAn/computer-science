#include<stdio.h>
#include<time.h>

#define NUM 5

int fib_normal(int n);
int fib_tail(int n, int a0, int a1);

int strlen_rec(const char *str);
int strlen_nonRec(const char *str);

int check[NUM];
int arr[NUM];
int printBin(int n, int k);


int main()
{
	int N;
	scanf("%d", &N);

	time_t t_s;
	time_t t_e;
	time(&t_s);
	printf("%d\n", fib_normal(N));
	time(&t_e);
	printf("normal: %.2lf\n", (double)(t_e - t_s));

	time(&t_s);
	printf("%d\n", fib_tail(N, 0, 1));
	time(&t_e);
	printf("tail: %.2lf\n", (double)(t_e - t_s));


	const char *str = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	time(&t_s);
	printf("%d\n", strlen_rec(str));
	time(&t_e);
	printf("tail: %.2lf\n", (double)(t_e - t_s));

	time(&t_s);
	printf("%d\n", strlen_nonRec(str));
	time(&t_e);
	printf("tail: %.2lf\n", (double)(t_e - t_s));


	printf("# of permutation: %d\n", printBin(NUM, 0));


	return 0;
}


int fib_normal(int n) {
	switch (n) {
	case 0:		return 0;
	case 1: 	return 1;
	default:	return fib_normal(n-1) + fib_normal(n-2);
	}
}
int fib_tail(int n, int a0, int a1) {
	switch (n) {
	case 0:		return a0;
	case 1: 	return a1;
	default:	return fib_tail(n-1, a1, a0 + a1);
	}
}

int strlen_rec(const char *str) {
	if (*str == '\0') {
		return 0;
	}
	return 1 + strlen_rec(str + 1);
}
int strlen_nonRec(const char *str) {
	int n = 0;
	while (*(str++) != '\0') {
		n++;
	}
	return n;
}

int printBin(int n, int k) {
	int i;
	int sum = 0;
	if (k == n) {
		for (i = 0; i < n; ++i) {
			printf("%d ", arr[i]);
		}
		printf("\n");
		return 1;
	}
	for (i = 0; i < n; ++i) {
		if (check[i] == 0) {
			arr[k] = i+1;
			check[i] = 1;
			sum += printBin(n, k+1);
			check[i] = 0;
		}
	}
	return sum;
}

