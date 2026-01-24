/*
 *Questo programma mostra come utilizzare producer e consumer per quanto riguarda accesso a risorse condivise
 * */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>
#include <time.h>

#define BUFFISIZE 100

int buffer[BUFFSIZE];
int count = 0;
int inserisci_idx = 0;
int preleva_idx = 0;

pthread_mutex_t mutex;
pthread_cond_t cond_pieno;
pthread_cont_t cond_vuoto;

void* consumer(void *arg){

}

void* producer(void *arg){

}

int main(){




	return 0;
}
