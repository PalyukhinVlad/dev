//gcc lab4.c -o lab4 -lpthread

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SEMAPHORE_NAME "/semaphore"

void* thrd_first(sem_t *sem){
	//output random numbers
	int r;
	srand(time(NULL));
	for (int i = 0; i < 10; i++){
		r = rand() % 100; // 0 - 100
		sem_wait(sem);
		printf("thrd_first[%d] - random number: %d\n", i,r);
		sem_post(sem);
	}

	pthread_exit(0);
}

void* thrd_second(sem_t *sem){
	//output random numbers
	int r;
	srand(time(NULL));
	for (int i = 0; i < 10; i++){
		r = 100 + rand() % 200; // 100 - 200
		sem_wait(sem);
		printf("thrd_second[%d] - random number: %d\n", i,r);
		sem_post(sem);
	}

	pthread_exit(0);
}

int main(){
	sem_t *sem;

	sem = sem_open(SEMAPHORE_NAME, O_CREAT, 0777, 0);

	void* data_first = NULL;
	void* data_second = NULL;

	pthread_t thrd_frst;
	pthread_t thrd_sec;

	pthread_create(&thrd_frst, NULL, thrd_first, data_first);
	pthread_create(&thrd_sec, NULL, thrd_second, data_second);

	pthread_join(thrd_frst, NULL);
	pthread_join(thrd_sec, NULL);

	sem_close(sem);
	
	return 0;
}