/*
Scrivere un programma "aspetta.c" che scrive un messaggio su stdout ogni volta che riceve i segnali SIGINT e SIGUSR1
Il programma non deve mai terminare spontaneamente
Lanciare il programma. Usando il comando kill della shell, provare ad inviare questi due segnali, e alla fine terminarlo.
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
	
	signal(SIGINT, write_message);
	signal(SIGUSR1, write_message);
	
	for(;;)	pause();
	
	return 0;
}

void write_message(int signum){

	char sigint_message[BUFFSIZE] = "\nÈ stato rilevato un signal SIGINT.\n";
	char sigusr1_message[BUFFSIZE] = "\nÈ stato rilevato un signal SIGUSR1.\n";
	char other_message[BUFFSIZE] = "\nIl segnale rilevato non è riconosciuto.\n";

	if(signum == SIGINT){
		if(write(STDOUT_FILENO, sigint_message, BUFFSIZE) < 0){
			perror("\nErrore di scrittura SIGINT message su STDOUT.\n");
			exit(-1);
		}
	} else if (signum == SIGUSR1){
		if(write(STDOUT_FILENO, sigusr1_message, BUFFSIZE) < 0){
			perror("\nErrore di scrittura SIGUSR1 message su STDOUT.\n");
			exit(-1);
		}
	} else {
		if(write(STDOUT_FILENO, other_message, BUFFSIZE) < 0){
			perror("\nErrore di scrittura OTHER message su STDOUT.\n");
			exit(-1);
		}
	} 
}
