/*
Scrivere due processi parten e child, dove il processo parent comunica al figlio
una stringa e questo provvede a stamparla.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFSIZE 100

int main(){

	int fd[2];
	pid_t pid;
	
	if(pipe(fd) < 0){
		perror("\n[PADRE]: Errore creazione pipe.\n");
		exit(-1);
	}
	
	if((pid = fork()) < 0){
		perror("\nErrore nella fork.\n");
		exit(-1);
	} else if (pid == 0){
	
		char father_message[BUFFSIZE];
		
		close(fd[1]);
		
		if(read(fd[0], father_message, BUFFSIZE) < 0){
			perror("\n[FIGLIO]: Errore read.\n");
			exit(-1);
		}
	
		printf("\n[FIGLIO] %s", father_message);
	
		close(fd[0]);
		
	} else {
		
		close(fd[0]);
		
		char message_to_send[BUFFSIZE] = "\n[FROM-PADRE]: Ciao.\n";
		
		if(write(fd[1], message_to_send, BUFFSIZE) < 0){
			perror("\n[PADRE]: Errore write.\n");
			exit(-1);
		}
		
		close(fd[1]);	
	}

	return 0;
}
