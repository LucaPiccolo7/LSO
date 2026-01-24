/*
 * - Realizzare un programma che accetta da riga di comando due numeri interi n ed m,
 *   creando n produttori ed m consumatori
 *
 * - Produttori e consumatori condividono un array di 100 interi
 *
 * - Ogni produttore aspetta un numero casuale di secondi tra 1 e 10, e poi produce (ovvero inserisce nell'array) da 1 a 5 numeri casuali.
 *   Se il produttore trova l'array pieno, salta il turno.
 *
 * - Ogni consumatore aspetta che ci sia un numero da consumare, e poi stampa a video il proprio TID e il numero consumato.
 * */
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define SIZE 6

typedef struct shared_data {

	int data[SIZE];
	int dim;
	int in;
	int out;
	pthread_mutex_t mutex;

} shared_data;

shared_data* common_data;
pthread_cond_t non_vuoto_cv;

shared_data* init_common_data(){

	shared_data *fp = (shared_data *) malloc(sizeof(shared_data));
	if(fp == NULL){
		perror("\nErrore allocazione dati.\n");
		exit(-1);
	}
	fp->dim = 0;
	fp->in = 0;
	fp->out = 0;

	if(pthread_mutex_init(&fp->mutex, NULL) != 0){
		perror("\nErrore inizializzazione mutex.\n");
		exit(-1);
	}

	return fp;
}

void init_common_cv(){

	if(pthread_cond_init(&non_vuoto_cv, NULL) != 0){
		perror("\nErrore inizializzazione condizione non vuoto.\n");
		exit(-1);
	}
}

void stamp(int consumed_number){

	printf("\nThread %d, consumed=%d.\n", (int)pthread_self(), consumed_number);
}

void* producer(void *arg){

	/*
	if(common_data->dim == SIZE){
		printf("\nThread %d. Array pieno salto il turno.\n", (int)pthread_self());
		return NULL;
	}
	*/

	int second_to_wait = 1 + rand() % 10;
	sleep(second_to_wait);

	pthread_mutex_lock(&common_data->mutex);

	if(common_data->dim == SIZE){
		printf("\nThread %d. Array pieno salto il turno.\n", (int)pthread_self());
		pthread_mutex_unlock(&common_data->mutex);
		pthread_exit(NULL);
	}

	int quantity_of_number_to_insert = 1 + rand() % 5;
	int i;
	int rand_number;
	for(i = 0; i < quantity_of_number_to_insert; i++){

		rand_number = 1 + rand() % 100; //numero random da 1 a 100
		common_data->data[common_data->in] = rand_number;
		common_data->in = (common_data->in + 1) % SIZE;
		common_data->dim = common_data->dim + quantity_of_number_to_insert;
	
	}

	if(pthread_cond_broadcast(&non_vuoto_cv) != 0){
		perror("\nErrore broadcast.\n");
		exit(-1);
	}

	pthread_mutex_unlock(&common_data->mutex);
	
	pthread_exit(NULL);
}

void* consumer(void *arg){

	pthread_mutex_lock(&common_data->mutex);

	while(common_data->dim == 0)
		pthread_cond_wait(&non_vuoto_cv, &common_data->mutex);

	//prende dall'array
	int number = common_data->data[common_data->out];
	common_data->out = (common_data->out + 1) % SIZE;
	common_data->dim--;
	
	stamp(number);

	pthread_mutex_unlock(&common_data->mutex);

	pthread_exit(NULL);
}

int main(int argc, char *argv[]){

	if(argc != 3){
		printf("\nSpecificare numero producer e consumer in ordine.\n");
		exit(-1);
	}

	int n_producer = atoi(argv[1]);
	int n_consumer = atoi(argv[2]);

	pthread_t producers[n_producer];
	pthread_t consumers[n_consumer];

	common_data = init_common_data();
	init_common_cv();

	//creazione produttori
	int i;
	for(i = 0; i < n_producer; i++){
		if(pthread_create(&producers[i], NULL, producer, NULL) != 0){
			printf("\nErrore creazione producer numero %d.\n", i);
			exit(-1);
		}
	}
	
	//creazione consumatori	
	for(i = 0; i < n_consumer; i++){
		if(pthread_create(&consumers[i], NULL, consumer, NULL) != 0){
			printf("\nErrore creazione consumer numero %d.\n", i);
			exit(-1);
		}
	}

	//attesa produttori
	
	for(i = 0; i < n_producer; i++){
		if(pthread_join(producers[i], NULL) != 0){
			printf("\nErrore terminazione thread producer %ld.\n", producers[i]);
			exit(-1);
		}
	}

	//attesa consumatori
	for(i = 0; i < n_consumer; i++){
		if(pthread_join(consumers[i], NULL) != 0){
			printf("\nErrore terminazione thread consumer %ld.\n", consumers[i]);
			exit(-1);
		}
	}

	pthread_mutex_destroy(&common_data->mutex);
	pthread_cond_destroy(&non_vuoto_cv);
	return 0;
}
