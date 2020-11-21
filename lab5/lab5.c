#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

//65 - 90; 97 - 122 [A - Z; a - z]

char str[10];

char* generator(){
	int r;
	int i = 0; 
	char chars[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
					'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','\0'};

	srand(time(NULL));

	for (;i < 10; i++){
		r = rand() % 52;
		str[i] = chars[r];
	}
	str[i] = '\n';

	return str;
}

void upperer(char *str){
	int i = 0;
	char strUp[10];

	while(str[i] != '\n'){
		strUp[i] = toupper(str[i]);
		i++;
	}
	strUp[i] = '\0';
	
	fprintf(stdout, "%s\n", strUp);
}

int main(){
	pid_t pid;
	int fd[2];
	size_t size;

	if(pipe(fd) == -1){
		perror("pipe");
		exit(-1);
	}

	switch(pid = fork()){
		case -1:{
			perror("fork");
			exit(1);
		}
		case 0:{
			//child
			close(fd[1]);
			char buf;
			char input[10];
			int  i = 0;

			while(read(fd[0], &buf, 1) > 0){
				input[i] = buf;
				i++;
			}

			upperer(input);

			close(fd[0]);
			exit(0);
		}
		default:{
			//parent
			close(fd[0]);

			char* res = generator();

			write(fd[1], res, strlen(res));

			printf("%s\n", res);

			close(fd[1]);
			wait(NULL);
		}
	} 
	return 0;
}