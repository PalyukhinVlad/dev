//gcc lab4.c -o lab4 -lpthread -lrt

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

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
		if(sem_wait(sem) == -1){
			fprintf(file, "sem_wait error: %d", errno);
			exit(5);
		}
		
		r = rand() % 100; // 0 - 100

		fprintf(file, "thrd_first - iteration[%d] - random number: %d\n", i,r);

		printf("thrd_first - iteration[%d] - random number: %d\n", i,r);
		
		if(sem_post(sem) == -1){
			fprintf(file, "sem_post error: %d", errno);
			exit(6);
		}
		//usleep(1000);
	}

	pthread_exit(0);
}


void* thrd_second(void *_data){
	//output random numbers
	int r;
	int data = *(int*)_data;
	srand(time(NULL));

	for (int i = 0; i < data; i++){
		if(sem_wait(sem) == -1){
			fprintf(file, "sem_wait error: %d", errno);
			exit(5);
		}
		
		r = 100 + rand() % 200; // 100 - 200

		fprintf(file, "thrd_second - iteration[%d] - random number: %d\n", i,r);

		printf("thrd_second - iteration[%d] - random number: %d\n", i,r);
		
		if(sem_post(sem) == -1){
			fprintf(file, "sem_post error: %d", errno);
			exit(6);
		}
		//usleep(1000);
	}

	pthread_exit(0);
}


int main(){
	int status;
	if((file = fopen(FILE_NAME, "w")) == NULL){
		printf("Cannot open file.\n");
		exit(1);
	}

	sem = sem_open(SEMAPHORE_NAME, O_CREAT, 0777, 1);
	if(sem == SEM_FAILED){
		fprintf(file, "sem_open error: cant create semophore errno: %d", errno);
		exit(2);
	}
	
	int data_first = 10;
	int data_second = 10;

	pthread_t thrd_frst;
	pthread_t thrd_sec;

	status = pthread_create(&thrd_frst, NULL, thrd_first, &data_first);
	if (status != 0){
		fprintf(file, "thrd_frst error: cant create thread, status = %d\n", status);
		exit(3);
	}

	status = pthread_create(&thrd_sec, NULL, thrd_second, &data_second);
	if (status != 0){
		fprintf(file, "thrd_sec error: cant create thread, status = %d\n", status);
		exit(3);
	}

	pthread_join(thrd_frst, NULL);
	if (status != 0){
		fprintf(file, "thrd_sec error: cant join thread, status = %d\n", status);
		exit(4);
	}
	pthread_join(thrd_sec, NULL);
	if (status != 0){
		fprintf(file, "thrd_sec error: cant join thread, status = %d\n", status);
		exit(4);
	}
	
	if(sem_close(sem) == -1){
		fprintf(file, "sem_close error: %d", errno);
		exit(7);
	}
	
	fclose(file);
	
	return 0;
}