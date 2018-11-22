#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = "hello\\ wo\\rld show me the money";
	char *argv[20];
	char *p;

	// strtok
	p = strtok(s, "\\ ");
	printf("%s\n", p);
	while (p != NULL) {
		p = strtok(NULL, " \\");
		printf("%s\n", p);
	}
	//printf("%s\n", s);
	return 0;
}
