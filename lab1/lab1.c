#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 101

int *lines = NULL;
int size = 1;
int counterLines = 0;
FILE *file;

void loop(){
    int row = -1;
    char _string[MAX_SIZE];
    
    while(row != 0){
        printf("Enter row num: ");
        scanf("%u", &row);
        
        if(row > counterLines){
            printf("row non exist\n");
        } else {
            if (row == 1){
                fseek(file, 0, SEEK_SET);
                fgets(_string, MAX_SIZE, file);
                printf("%s\n", _string);
            } else {     
                fseek(file, lines[row - 2], SEEK_SET);
                fgets(_string, MAX_SIZE, file);
                printf("%s\n", _string);      
            }
        *_string = '\0'; 
        }
    }
}

void dataSet(FILE *file){
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
    }
}


void loader(char *path){
    file = fopen(path, "r");
    
    if(file == NULL){
        printf("Error. Can't open file %s\n", path);
        exit(1);
    } else {
        dataSet(file);
    }
}

int main(int argc, char **argv){
    loader(argv[1]);
    
    loop();

    free(lines);
    pclose(file);
    
    return 0;
}
