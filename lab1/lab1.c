#include <stdio.h>
#include <stdlib.h>

char *buffer = NULL;
int *lines = NULL;
int size = 1;
int counterLines = 0;

void loop(){
    int row = -1;
    
    while(row != 0){
        printf("Enter row num: ");
        scanf("%u", &row);
        printf("\n");
        
        if(row > counterLines){
            printf("row non exist\n");
        } else {
            if (row == 1){
                for (int i = 0; i < lines[row - 1]; i++){
                    printf("%c", buffer[i]);
                }
            } else {             
                for(int i = lines[row - 2] + 1; i < lines[row - 1]; i++){
                    printf("%c", buffer[i]);
                }
            }
         printf("\n");
        }
    }
}

void dataSet(FILE *file){
    fseek(file, 0L, SEEK_END);
    unsigned int fSize = ftell(file);
    rewind(file);
    
    buffer = (char*)malloc(sizeof(char) * fSize);
    
    if (buffer == NULL){
        printf("malloc() error.\n");
        exit(2);
    }
    
    size_t readResult = fread(buffer, sizeof(char), fSize, file);
    if(readResult != fSize){
        printf("Read error.\n");
        exit(3);
    }
    
    lines = (int*)calloc(size, sizeof(int));
    
    for(int i = 0; i < fSize; i++){
        if(buffer[i] == '\n'){
            size += 2;
            lines = (int*)realloc(lines, (size)*sizeof(int));       
            lines[counterLines] = i;
            counterLines += 1;
            printf("\n");
        } else {
            continue;
        }
    }
}


void loader(char *path){
    FILE *file = fopen(path, "r");
    
    if(file == NULL){
        printf("Error. Can't open file %s\n", path);
        exit(1);
    } else {
        dataSet(file);
    }
    fclose(file);
}

int main(int argc, char **argv){
    loader(argv[1]);
    
    loop();
    
    free(buffer);
    free(lines);
    
    return 0;
}
