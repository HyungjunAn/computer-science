#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 

char *print_file_category(mode_t mode) {
	if (S_ISREG(mode)) {

	}
}
int main(int argc, char** argv) {
	struct dirent* p;
	int fd;

	char buff[128];


	struct stat buff;

	while ((ret = read(fd, buff, sizeof(buff))) > 0) {
			write(1, buff, ret);
			lstat(p->argv[1], &buff);
	}
	lseek(
	close(fd);
	return 0;
}
