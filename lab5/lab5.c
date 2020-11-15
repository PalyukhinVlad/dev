#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

//65 - 90; 97 - 122 [A - Z; a - z]
char chars[52];
char str[10];

void generator(){
	int r;

	for (int i = 65, n = 0; i <= 90; ++i, ++n) 
		chars[n] = (char) i;

	for (int i = 97, n = 26; i <= 122; ++i, ++n) 
		chars[n] = (char) i;

	srand(time(NULL));
	
	for (int i = 0; i < 10; i++){
		r = rand() % 52;
		str[i] = chars[r];
	}

	fprintf(stdout, "%s\n", chars);
	fprintf(stdout, "%s\n", str);

}

int main(){
	pid_t pid;
	int status;

	switch(pid = fork()){
	case -1:{
		perror("fork");
		exit(1);
	}
	case 0:{
		//child
		exit(0);
	}
	default:{
		//parent
		generator();
		wait(&status);
	}
	}

	
	return 0;
}