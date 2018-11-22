#include <stdio.h>
#include <string.h>

int main(void) {
	char buff[100];
	int ret;

	while (ret = fread(buff, 1, sizeof(buff), stdin)) {
		printf("ret: %d\n", ret);
		fwrite(buff, 1, ret, stdout);
	}
	return 0;
}


