#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

typedef struct foo {

	int a;
	int b;
} myfoo;

myfoo test;

void stampa(char *str, struct foo *test){
	printf("%s: tid=%d a=%d b=%d\n", str, (int)pthread_self(), test->a, test->b);
}

void* fun1(void *arg){

	myfoo test2 = {1,2};
	printf("%s %d\n", (char *)arg, (int)pthread_self());
	stampa(arg, &test2);
	pthread_exit((void *) &test2);
}

void* fun2(void *arg){

	test.a = 3;
	test.b = 4;
	printf("%s %d\n", (char *)arg, (int)pthread_self());
	stampa(arg, &test);
	pthread_exit((void *) &test);
}

void* fun3(void *arg){
	myfoo *test3;
	test3 = malloc(sizeof(struct foo));
	test3->a = 5;
	test3->b = 6;
	printf("%s %d.\n", (char *)arg, (int)pthread_self());
	stampa(arg, test3);
	pthread_exit((void *) test3);
}

int main(){

	char str[100];
	pthread_t tid1, tid2, tid3;

	myfoo *b;

	//THREAD1
	if(pthread_create(&tid1, NULL, fun1, "Thread 1") != 0){
		perror("\nErrore pthread_create thread 1.\n");
		exit(-1);
	}
	if(pthread_join(tid1, (void*)&b) != 0){
		perror("\nErrore join thread 1.\n");
		exit(-1);
	}
	stampa("Master ", b);

	//THREAD2
	if(pthread_create(&tid2, NULL, fun2, "Thread 2") != 0){
		perror("\nErrore creazione thread 2.\n");
		exit(-1);
	}
	if(pthread_join(tid2, (void*) &b) != 0){
		perror("\nErrore join thread 2.\n");
		exit(-1);
	}
	stampa("Master ", b);

	//THREAD3
	if(pthread_create(&tid3, NULL, fun3, "Thread 3") != 0){
		perror("\nErrore creazione thread 3.\n");
		exit(-1);
	}
	if(pthread_join(tid3, (void *)&b) != 0){
		perror("\nErrore join thread 3.\n");
		exit(-1);
	}
	stampa("Master ", b);

	return 0;
}
