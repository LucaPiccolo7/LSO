/*
Scrivere un programma in C che apre un file, effettua una fork e
scrive messaggi diversi sul file a seconda che sia padre o figlio.
Come si alternano i messaggi nel file?
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFSIZE 100

int main(){

	int fd;	
	int pid;
	
	if ((fd = open("testfile", O_WRONLY | O_APPEND | O_CREAT, S_IRWXU)) < 0){
		perror("\nErrore in apertura del file.\n");
		exit(-1);
	}
	
	if((pid = fork()) < 0){
		perror("\nErrore creazione processo.\n");
		exit(-1);
	} else {
	
		if(pid != 0){
			char message[BUFFSIZE] = "Sono il processo padre.\n";
			if(write(fd, message, BUFFSIZE) < 0){
				perror("\nErrore scrittura sul file nel padre.\n");
				exit(-1);
			}
		} else {
			char message[BUFFSIZE] = "Sono il processo figlio.\n";	
			if(write(fd, message, BUFFSIZE) < 0){
				perror("\nErrore scrittura sul file nel figlio.\n");
				exit(-1);
			}
		}
	}

	if(close(fd) < 0){
		perror("\nErrore chiusura del file.\n");
		exit(-1);
	}
	
	return 0;
}
