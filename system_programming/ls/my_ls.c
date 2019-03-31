#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include <stdio.h>
#include <string.h>

#define LIST  0x01
#define INODE 0x02
#define RECUR 0x04
#define ALL   0x08

int getPermit(struct stat *pBuf, char *szPerm);
char get_f_category(mode_t mode);
int print_result(const char *dname);
int print_LineInfo(struct stat *buf, const char *d_name);
void rec_print_result(DIR* dp, const char* d_name);

int flags = 0;
int main(int argc, char** argv)
{
	int ch;
	while ((ch = getopt(argc, argv, "liRa")) !=  -1) {
		switch (ch) {
			case 'l':
				flags |= LIST;
				break;
			case 'i':
				flags |= INODE;
				break;
			case 'R':
				flags |= RECUR;
				break;
			case 'a':
				flags |= ALL;
				break;
		}
	}
	if (argc >= 2 && argv[argc-1][0] != '-') {
		chdir(argv[argc-1]);
	}
	else {
		chdir(".");
	}
	print_result(".");
	return 0;
}

int print_LineInfo(struct stat *buf, const char* d_name) {
	char szLink[128];
	struct tm* tm;
	char szTime[128];
	char szPermit[128];
	int tmp;
	char category = get_f_category(buf->st_mode);

	tm = localtime(&buf->st_mtime);
	
	sprintf(szTime, "%2d월 %2d %02d:%02d", 
		tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min);
	
	getPermit(buf, szPermit);
	
	printf("%c%s %4ld %5s %5s %7ld %s ", 
		category,
		szPermit,
		buf->st_nlink,
		getpwuid(buf->st_uid)->pw_name, 
		getgrgid(buf->st_gid)->gr_name,
		buf->st_size,
		szTime);
	printf("%s", d_name);

	if (category == 'l') {
		tmp = readlink(d_name, szLink, sizeof(szLink));
		szLink[tmp] = '\0';
		printf(" -> %s", szLink); 
	}
	putchar('\n');
	return 1;
}

int print_result(const char *d_name)
{
	struct dirent* p;
	DIR* dp;
	struct stat buf;
	char szNewDirName[256];

	dp = opendir(d_name);

	if (flags & RECUR) {
		printf("%s:\n", d_name);
	}
	while ((p = readdir(dp)) != NULL) {
		if (!(flags & ALL) && (p->d_name[0] ==  '.')) {
			continue;
		}

		sprintf(szNewDirName, "%s/%s", d_name, p->d_name);
		lstat(szNewDirName, &buf);
		if (flags & INODE) {
			printf("%6ld ", p->d_ino);
		}

		if (flags & LIST)  {
			print_LineInfo(&buf, p->d_name);
		}
		else {
			printf("%s  ", p->d_name);
		}
	}
	if (!(flags & LIST))  {
		printf("\n");
	}
	if (flags & RECUR) {
		rewinddir(dp);
		rec_print_result(dp, d_name);
	}
	closedir(dp);
}
void rec_print_result(DIR* dp, const char* d_name)
{
	struct dirent* p;
	char szNewDirName[256];
	struct stat buf;

	while ((p = readdir(dp)) != NULL)  {
		sprintf(szNewDirName, "%s/%s", d_name, p->d_name);
		lstat(szNewDirName, &buf);
		if (S_ISDIR(buf.st_mode)) {
			if (!(flags & ALL) && p->d_name[0] == '.') {
				;
			}
			else if (strcmp(p->d_name, ".") && strcmp(p->d_name, "..")) {
				printf("\n");
				print_result(szNewDirName);
			}
		}
	}
}
	

char get_f_category(mode_t mode)
{
	if (S_ISREG(mode)) {
		return '-';
	} else if (S_ISDIR(mode)) {
		return 'd';
	} else if (S_ISCHR(mode)) {
		return 'c';
	} else if (S_ISBLK(mode)) {
		return 'b';
	} else if (S_ISFIFO(mode)) {
		return 'p';
	} else if (S_ISLNK(mode)) {
		return 'l';
	} else if (S_ISSOCK(mode)) {
		return 's';
	}
	return '?';
}

int getPermit(struct stat *pBuf, char *szPerm)
{
	char rwx[] = "rwx";
	int i;
	for( i = 0; i < 9; i++ ) {
		szPerm[i] = ((pBuf->st_mode >> (8-i)) & 0x1)? rwx[i%3]: '-';
	}
	szPerm[i] = '\0';
	return 1;
}

















