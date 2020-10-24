#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv){
	char *date;
	int st;
	struct passwd *pwd;
	struct group *gr;
	struct stat buf;
	struct passwd pw;
	struct group grp;

	if((st = stat(argv[1], &buf)) != 0){
		printf("stat failure\n");
		exit(1);
	}

	if(S_ISDIR(buf.st_mode)) printf("d");

	if(S_ISREG(buf.st_mode)) printf("-");

	if(S_ISLNK(buf.st_mode) || S_ISCHR(buf.st_mode) ||
	   S_ISBLK(buf.st_mode) || S_ISFIFO(buf.st_mode) || 
	   S_ISSOCK(buf.st_mode))
		printf("?");


	if(buf.st_mode & S_IRUSR) printf("r"); else printf("-");
	if(buf.st_mode & S_IWUSR) printf("w"); else printf("-");
	if(buf.st_mode & S_IWUSR) printf("x"); else printf("-");

	if(buf.st_mode & S_IRGRP) printf("r"); else printf("-");
	if(buf.st_mode & S_IWGRP) printf("w"); else printf("-");
	if(buf.st_mode & S_IWGRP) printf("x"); else printf("-");

	if(buf.st_mode & S_IROTH) printf("r"); else printf("-");
	if(buf.st_mode & S_IWOTH) printf("w"); else printf("-");
	if(buf.st_mode & S_IWOTH) printf("x"); else printf("-");

	printf(" ");

	printf("%ld", buf.st_nlink);

	printf(" ");

	if((pwd = getpwuid(buf.st_uid)) != 0){
		printf("%-5.8s", pwd->pw_name);
	} else {
		printf("%-8d", buf.st_uid);
	}

	if((gr = getgrgid(buf.st_gid)) != 0){
		printf("%-5.8s", gr->gr_name);
	} else {
		printf("%-8d", buf.st_gid);
	}

	printf("%ld", buf.st_size);

	printf(" ");

	printf("%s", strtok(ctime(&buf.st_mtime), "\n"));

	printf(" ");

	printf("%s\n", strrchr(argv[1], '/'));


	return 0;
}