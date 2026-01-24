/*
 * Esempio di mutex con sincronizzazione per struttura al posto di sezione critica
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 100

typedef struct foo {
	
	int a;
	int b;
	pthread_mutex_t mutex;
} myfoo;

myfoo *test;

myfoo* init(){

	myfoo *fp = (myfoo*) malloc(sizeof(myfoo));
	if(fp == NULL){
		perror("\nErrore allocazione dinamica struttura.\n");
		exit(-1);
	}
	fp->a = 0;
	fp->b = 0;

	pthread_mutex_init(&fp->mutex, NULL);
	
	return fp;
}

void* incr(void* arg){

	pthread_mutex_lock(&test->mutex);
	test->a++;
	test->b++;
	printf("\nThreadID: %d, a=%d, b=%d.\n", (int)pthread_self(), test->a, test->b);
	pthread_mutex_unlock(&test->mutex);
	pthread_exit((void *) &test);
}

int main(){

	char str[SIZE];
	int i;
	pthread_t tid;

	test = init();

	while(i++<10){
		pthread_create(&tid, NULL, incr, NULL);
	}

	sleep(3);

	printf("\nMASTER-ID: %d, a=%d, b=%d.\n", (int)pthread_self(), test->a, test->b);
	return 0;
}
