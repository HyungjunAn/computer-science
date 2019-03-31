#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include <stdio.h>

int main(void)
{
	struct dirent* p;
	struct stat buf;
	long ttl_size = 0;
	DIR* dp = opendir(".");
	if (dp == NULL) {
		perror("opendir");
		return 1;
	}
	while ((p = readdir(dp)) != NULL) {
		lstat(p->d_name, &buf);
		printf("%-20s ", p->d_name);

		if (S_ISREG(buf.st_mode)) {
			ttl_size += buf.st_size;
			printf("%6ld\n", buf.st_size);
		}
		else {
			printf("%6s\n", "-");
		}
	}
	closedir(dp);
	printf("\nSum:%6ld\n", ttl_size);
	return 0;
}
