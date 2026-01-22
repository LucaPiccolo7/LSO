/*
Scrivere un programma in cui processo padre e processo figlio si scambiano
il controllo a vicenda attraverso l'utilizzo di kill e pause
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFSIZE 100

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
void son_message(int signum);
void father_message(int signum);

int main(){

	pid_t pid;
	
	if((pid = fork()) < 0){
		perror("\nErrore nella fork.\n");
		exit(-1);
	} else if (pid == 0){
	
		pid_t ppid = getppid();
	
		signal(SIGINT, son_message);
		signal(SIGUSR1, son_message);
		
		if (kill(ppid, SIGINT) < 0){
			printf("\n[FIGLIO]: Errore kill SIGINT.\n");
			exit(-1);
		}
		printf("\n[FIGLIO]: Mandato segnale SIGINT.\n");
		
		pause();
		
		if (kill(ppid, SIGUSR1) < 0){
			printf("\n[FIGLIO]: Errore kill SIGUSR1.\n");
			exit(-1);
		}
		printf("\n[FIGLIO]: Mandato segnale SIGUSR1.\n");
		
		pause();
		
	} else {
	
		signal(SIGINT, father_message);
		signal(SIGUSR1, father_message);
		
		sleep(1);
		
		if (kill(pid, SIGINT) < 0){
			printf("\n[PADRE]: Errore kill SIGINT.\n");
			exit(-1);
		}
		printf("\n[PADRE]: Mandato segnaSle SIGINT.\n");
		
		pause();
		
		if (kill(pid, SIGUSR1) < 0){
			printf("\n[PADRE]: Errore kill SIGUSR1.\n");
			exit(-1);
		}
		printf("\n[PADRE]: Mandato segnale SIGUSR1.\n");
		
		pause();
	}

	return 0;
}

void son_message(int signum){

	char sigint_message[BUFFSIZE] = "\n[FIGLIO]: Ricevuto messaggio SIGINT.\n";
	char sigusr1_message[BUFFSIZE] = "\n[FIGLIO]: Ricevuto messaggio SIGUSR1.\n";

	if (signum == SIGINT){
		if (write(STDOUT_FILENO, sigint_message, BUFFSIZE) < 0){
			perror("\n[FIGLIO]: Errore SIGINT.\n");
			exit(-1);
		}
	} else if (signum == SIGUSR1){
		if (write(STDOUT_FILENO, sigusr1_message, BUFFSIZE) < 0){
			perror("\n[FIGLIO]: Errore SIGUSR1.\n");
			exit(-1);
		}
	}
}

void father_message(int signum){

	char sigint_message[BUFFSIZE] = "\n[PADRE]: Ricevuto messaggio SIGINT.\n";
	char sigusr1_message[BUFFSIZE] = "\n[PADRE]: Ricevuto messaggio SIGUSR1.\n";

	if (signum == SIGINT){
		if (write(STDOUT_FILENO, sigint_message, BUFFSIZE) < 0){
			perror("\n[PADRE]: Errore SIGINT.\n");
			exit(-1);
		}
	} else if (signum == SIGUSR1){
		if (write(STDOUT_FILENO, sigusr1_message, BUFFSIZE) < 0){
			perror("\n[PADRE]: Errore SIGUSR1.\n");
			exit(-1);
		}
	}
}
