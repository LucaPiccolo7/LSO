/*
 * Esempio di mutex tra thread differenti
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct foo {

	int a;
	int b;
} myfoo;

myfoo test;

pthread_mutex_t mutexid;

void* init(void* arg){

	pthread_mutex_lock(&mutexid);
	test.a++;
	test.b++;
	printf("\nThread id: %d, a=%d, b=%d.\n", (int)pthread_self(), test.a, test.b);
	pthread_mutex_unlock(&mutexid);
	pthread_exit((void *) &test);
}

int main(){

	pthread_mutex_init(&mutexid, NULL);

	char str[100];
	pthread_t tid;
	int i = 0;
	myfoo *b;

	while(i++<10){
		pthread_create(&tid, NULL, init, NULL);
	}

	pthread_mutex_destroy(&mutexid);

	return 0;
}
