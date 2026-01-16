/*
Scrivete un programma che mostra il contenuto di un file alla rovescia.
(cioè a partire dall'ultimo carattere per arrivare al primo)
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
	
	if((fd = open("esercizio2.txt", O_RDONLY, S_IRUSR)) < 0)
		perror("\nErrore in apertura del file \"esercizio2.txt\"\n");

	ssize_t n;
	if((n = read(fd, buffer, BUFFSIZE)) >= 0){
	
		buffer[n - 1] = '\0';
		
		printf("\n");
		
		for(int i = n - 1; i >= 0; i--){
			printf("%c", buffer[i]);
		}
		
		printf("\n");
		
	} else perror("\nErrore nella lettura del file.\n");

	if(close(fd) < 0)
		perror("\nErrore chiusura file.\n");

	return 0;
}
