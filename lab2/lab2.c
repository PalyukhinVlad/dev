#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_SIZE 101

int *lines = NULL;
int size = 1;
int counterLines = 0;
char *pmap;
struct stat sb;

void loop(char *pmap){
    int row = -1;
    
    while(row != 0){
        printf("Enter row num: ");
        scanf("%u", &row);
        
        if(row > counterLines){
            printf("row non exist\n");
        } else {
            if (row == 1){
                for(int i = 0; i < lines[row - 1] + 1; i++){
                    printf("%c", pmap[i]);
                }
            } else {     
                for(int i = lines[row - 2] + 1; i < lines[row - 1] + 1; i++){
                    printf("%c", pmap[i]);
                }    
            }
        }
    }
}



char* dataSet(int fd){

    if(fstat(fd, &sb) == -1){
        perror("couldn't get file size.\n");
    }

    printf("file size id %ld\n", sb.st_size);
    pmap = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(pmap == MAP_FAILED){
        perror("mmap");
        exit(1);
    }

    printf("%s", pmap);
    return pmap;
    
    //--------------------------------------------

    /*fseek(file, 0L, SEEK_END);
    unsigned int fSize = ftell(file);
    rewind(file);

    lines = (int*)calloc(size, sizeof(int));

    char ch;
    while((ch = fgetc(file)) != EOF){
        if (ch == '\n'){
            size += 2;
            lines = (int*)realloc(lines, (size)*sizeof(int));       
            lines[counterLines] = (ftell(file) +1);
            counterLines += 1;
        } else {
            continue;
        }
    }*/
}

int main(int argc, char **argv){
    //loader
    int fd = open(argv[1], O_RDONLY);
    
    
    loop(dataSet(fd));

    free(lines);
    close(fd);
    
    return 0;
}
