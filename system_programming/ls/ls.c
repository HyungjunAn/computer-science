#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#include <stdio.h>


int main()
{
	struct dirent* p;
	DIR* dp;
	dp = opendir(".");

	while ((p = readdir(dp)) != NULL) {
		printf("A: %s\n", p->d_name);
	}

	rewinddir(dp);

	while ((p = readdir(dp)) != NULL) {
		printf("B: %s\n", p->d_name);
	}

	closedir(dp);
}



// File
// open : int, 
//  -> fopen : FILE* 

// Directory
// open : int
//  -> opendir : DIR*

/*
int main()
{
	int fd = open(".", O_RDONLY);
	printf("fd: %d\n", fd);
}
*/
