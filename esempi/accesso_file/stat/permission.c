#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

	if (argc != 2){
		perror("\nErrore argomenti programma, passane 2.\n");
		exit(-1);
	}
	
	if (access(argv[1], F_OK) == 0)
		printf("\nIl file %s esiste.\n", argv[1]);
	else printf("\nIl file %s non esiste.\n", argv[1]);
	
	if (access(argv[1], R_OK) == 0)
		printf("lettura: SI\n");
	else printf("lettura: NO\n");
	
	if (access(argv[1], W_OK) == 0)
		printf("scrittura: SI.\n");
	else printf("scrittura: NO.\n");
	
	if (access(argv[1], X_OK) == 0)
		printf("esecuzione: SI.\n");
	else printf("esecuzione: NO.\n");
	
	return 0;
}
