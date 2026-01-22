/*
- Il padre invia al figlio 10 numeri interi casuali al
ritmo di uno al secondo, poi termina

- Il figlio riceve i numeri del padre e li stampa sul terminale

- Il figlio termina dopo aver ricevuto il decimo numero.

- I due processi comunicano tramite una pipe

- Opzionale: modificare il figlio in modo che termini dopo aver ricevuto 5 interi NO
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

#define BUFFSIZE 100

int main(){

	srand(time(NULL));
	
	int fd[2];
	pid_t pid;
	
	if(pipe(fd) < 0){
		perror("\nErrore creazione pipe.\n");
		exit(-1);
	}
	
	if((pid = fork()) < 0){
		perror("\nErrore fork.\n");
		exit(-1);
	} else if (pid == 0){
	
		int numread;
		int num;
		
		close(fd[1]);
		
		printf("\n[FIGLIO]: inizio lettura.\n");
		
		while((numread = read(fd[0], &num, sizeof(int))) > 0){
			printf("\n[FIGLIO]: letto da pipe il numero -> %d.\n", num);
		}
		
		printf("\n[FIGLIO]: fine lettura.\n");
		
		close(fd[0]);
	
	} else {
	
		int i;
		int num;
		int numwrite;
		
		close(fd[0]);
		
		for(i = 0; i < 10; i++){
			num = -10 + rand() % (10 + 10 + 1);
			
			if ((numwrite = write(fd[1], &num, sizeof(int))) < 0){
				perror("\n[PADRE]: Errore scrittura in pipe.\n");
				exit(-1);
			}
			
			//printf("\n[PADRE]: quantità scritta -> %d.\n", numwrite);
			
			sleep(1);
		}
		
		close(fd[1]);
		
		exit(0);
	}
}

