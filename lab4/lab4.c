//gcc lab4.c -o lab4 -lpthread -lrt

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SEMAPHORE_NAME "/semaphore"
#define FILE_NAME "log.txt"

FILE *file;
sem_t *sem;


void* thrd_first(void *_data){
	//output random numbers
	int r;
	int data = *(int*)_data;
	srand(time(NULL));

	for (int i = 0; i < data; i++){
		sem_wait(sem);

		r = rand() % 100; // 0 - 100

		fprintf(file, "thrd_first[%d] - random number: %d\n", i,r);

		printf("thrd_first[%d] - random number: %d\n", i,r);

		sem_post(sem);
	}

	pthread_exit(0);
}


void* thrd_second(void *_data){
	//output random numbers
	int r;
	int data = *(int*)_data;
	srand(time(NULL));

	for (int i = 0; i < data; i++){
		sem_wait(sem);

		r = 100 + rand() % 200; // 100 - 200

		fprintf(file, "thrd_second[%d] - random number: %d\n", i,r);

		printf("thrd_second[%d] - random number: %d\n", i,r);

		sem_post(sem);
	}

	pthread_exit(0);
}


int main(){
	sem = sem_open(SEMAPHORE_NAME, O_CREAT, 0777, 0);

	if((file = fopen(FILE_NAME, "w")) == NULL){
		printf("Cannot open file.\n");
		exit(1);
	}
	
	int data_first = 20;
	int data_second = 10;

	pthread_t thrd_frst;
	pthread_t thrd_sec;

	pthread_create(&thrd_frst, NULL, thrd_first, &data_first);
	pthread_create(&thrd_sec, NULL, thrd_second, &data_second);

	pthread_join(thrd_frst, NULL);
	pthread_join(thrd_sec, NULL);

	sem_close(sem);
	fclose(file);
	
	return 0;
}