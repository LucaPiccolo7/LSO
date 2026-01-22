#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	pid_t pid;
	
	if((pid = fork()) < 0){
		perror("\nErrore creazione processo.\n");
		exit(-1);
	} else {
		if(pid != 0){
			printf("\nProcesso padre, pid figlio: %d\n", pid);
		} else {
			printf("\nProcesso figlio con pid: %d\n", pid);
		}
	}

	return 0;
}
