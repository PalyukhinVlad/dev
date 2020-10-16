#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int *lines = NULL;
int size = 1;
int counterLines = 0;
char *file_mem;

struct stat statbuf;
int fd;

void loop(){

    int row = -1;
    
    while(row != 0){
        printf("Enter row num: ");
        scanf("%u", &row);
        
        if(row > counterLines){
            printf("row non exist.\n");
        } else {
            if (row == 1){
                for(int i = 0; i < lines[row - 1]; i++)
                    printf("%c", file_mem[i]);
                printf("\n");
            } else {     
                for(int i = lines[row - 2]; i < lines[row - 1]; i++)
                    printf("%c", file_mem[i]);
                printf("\n");     
            }
        }
    }

    if(munmap(file_mem, statbuf.st_size) == -1){
        printf("unmap failed");
        close(fd);
    }
    close(fd);   
}

void dataSet(char* path){

    if((fd = open(path, O_RDONLY)) == -1) {
        printf("Cannot open file <%s>.\n", path);
        exit(1);
    } else {
        int status = fstat(fd, &statbuf);

        file_mem = mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if(file_mem == MAP_FAILED){
            printf("Mapping failed\n");
            close(fd);
            exit(1);
        }

        lines = (int*)calloc(size, sizeof(int));

        for(int i = 0; i < statbuf.st_size; i++){
            if (file_mem[i] == '\n'){
                size += 2;
                lines = (int*)realloc(lines, (size)*sizeof(int));       
                lines[counterLines] = i;
                counterLines += 1;
            } else {
                continue;
            }
        }
    }
}

int main(int argc, char **argv){
    dataSet(argv[1]);
    loop();

    free(lines);
    
    return 0;
}
