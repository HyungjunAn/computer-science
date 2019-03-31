#include <stdio.h>

#define bee 4
#define STR(x) #x
#define XSTR(x) STR(x)

#define MAKE_NAME(VAL, NUM) VAL ## NUM
#define PRINT_WITH_NAME(X) printf(#X ": %d\n", X);

int main(void) {
	int MAKE_NAME(a, 0) = 3;
	int MAKE_NAME(a, 1) = 3;

	PRINT_WITH_NAME(a0);
	PRINT_WITH_NAME(a1);
	PRINT_WITH_NAME(1 + 3);
	return 0;
}
