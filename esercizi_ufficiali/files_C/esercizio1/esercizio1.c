/*
Scrivere un programma che mostra il contenuto di un file a byte alterni
(un carattere si ed uno no)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFSIZE 4096

int main(){

	int fd;
	char buffer[BUFFSIZE];
	
	if((fd = open("esercizio1.txt", O_RDONLY, S_IRUSR)) < 0)
		perror("\nErrore di apertura del file esercizio1.txt\n");

	ssize_t n;
	if((n = read(fd, buffer, BUFFSIZE)) >= 0){
	
		buffer[n - 1] = '\0';
		
		for(int i = 0; i < n; i++){
			if(i % 2 == 0)
				printf("%c ", buffer[i]);
		}		
	
	} else perror("\nErrore in lettura del file.\n");
	/*	
	while((read = read(fd, buffer, BUFFSIZE)) > 0){
	
		if(read < 0)
			perror("\nErrore nella lettura del file.\n");
		
		buffer[read - 1] = '\0';
	}
	*/

	if(close(fd) == -1)
		perror("\nErrore in chiusura del file.\n");
		
	return 0;
}
