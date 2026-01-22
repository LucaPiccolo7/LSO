/*
Scrivere un programma "aspetta.c" che crea un processo figlio che scrive un messaggio su STDOUT
quando il padre invia segnali SIGINT e SIGUSR1

Il processo figlio non termina, entrando in un ciclo infinito

Il processo padre manda i due segnali, attende input da tastiera, poi termina il figlio e
si mette in attesa in un ciclo infinito
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define BUFFSIZE 100

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
void write_message(int signum);

int main(){
	
	pid_t pid;
	
	if((pid = fork()) < 0){
		perror("\nErrore fork.\n");
		exit(-1);
	} else if (pid == 0){
	
		printf("\n[FIGLIO]: pid %d\n", pid);
		
		signal(SIGINT, write_message);
		signal(SIGUSR1, write_message);
		
		for(;;) pause();
		
	} else {
	
		sleep(1);
	
		printf("\n[PADRE]: pid %d\n", pid);
	
		if (kill(pid, SIGINT) < 0){
			printf("\n[PADRE]: Errore nell'invio di SIGINT\n");
			exit(-1);
		}
		
		if(kill(pid, SIGUSR1) < 0){
			perror("\n[PADRE]: Errore nell'invio di SIGUSR1\n");
			exit(-1);
		}
		
		int input;
		printf("\nScrivi 1 per terminare il processo figlio: ");
		if (scanf("%d", &input) != 1){
			printf("\n[PADRE]: Errore input.\n");
			exit(-1);
		}
		
		printf("\n[PADRE]: Kill del processo...");
		
		if(kill(pid, SIGKILL) < 0){
			perror("\n[PADRE]: Errore nell'invio di SIGKILL.\n");
			exit(-1);
		}
		
		printf("\n[PADRE]: Fine kill.\n");
	}
}

void write_message(int signum){

	char sigint_message[BUFFSIZE] = "\n[FIGLIO]: Ricevuto un segnale SIGINT.\n";
	char sigusr1_message[BUFFSIZE] = "\n[FIGLIO]: Ricevuto un segnale SIGUSR1.\n";

	if(signum == SIGINT){
		if(write(STDOUT_FILENO, sigint_message, BUFFSIZE) < 0){
			perror("\n[FIGLIO]: Errore di scrittura.\n");
			exit(-1);
		}
	} else if (signum == SIGUSR1){
		if(write(STDOUT_FILENO, sigusr1_message, BUFFSIZE) < 0){
			perror("\n[FIGLIO]: Errore di scrittura.\n");
			exit(-1);
		}
	}
}
