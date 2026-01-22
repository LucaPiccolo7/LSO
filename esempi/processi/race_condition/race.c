/*
Esempio di race condition o condizione di tempificazione
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

static void char_char(char *);

int main(){

	pid_t pid;
	
	if((pid = fork()) < 0){
		perror("\nErrore nella fork.\n");
		exit(-1);
	} else if (pid == 0){

		char_char("\nIo sono il figlio ed intendo scrivere prima del padre.\n");
		_exit(0);
			
	} else {
		char_char("\nIo sono il padre, e non ci sto.\n");
	}

	return 0;
}

static void char_char(char *str){

	char *ptr;
	int c;
	
	setbuf(stdout, NULL);
	
	for(ptr = str; c=*ptr++;)
		putc(c, stdout);
}
