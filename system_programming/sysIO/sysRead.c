#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 

int main(int argc, char** argv) {
	char buff[100];
	mode_t *st_mode;
	int ret;
	int fd = open(argv[1], O_RDONLY);
	while ((ret = read(fd, buff, sizeof(buff))) > 0) {
		write(1, buff, ret);
	}
	lseek(
	close(fd);
	return 0;
}

