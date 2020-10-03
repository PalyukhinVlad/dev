#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void create(char* program, char** arg_list, int argc){
    pid_t cldPid;
    int status;
    
    for(int i = 0; i < argc; i++){
        arg_list[i] = arg_list[i+1];
    }
    
    if((cldPid = fork()) < 0){
        printf("Failed to fork\n");
        exit(1);
    } else if (cldPid == 0) {
        if(execvp(program, arg_list) < 0){
            printf("Failed to exec\n");
            exit(1);
        }    
    } else {
        wait(&status);
        if (WIFEXITED(status)) {
            printf("child exited with code %d\n", WEXITSTATUS(status));
        }
    }   
}

int main(int argc,char *argv[]){
    create(argv[1], argv, argc);
    return 0;
}

