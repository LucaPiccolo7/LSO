#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){

	pid_t pid;
	int status;
	
	if((pid = fork()) < 0){
		printf("\nErrore fork.\n");
		exit(-1);
	} else if (pid == 0){
		printf("\nSono il processo figlio.\n");
		_exit(0);
	} else {
		if(wait(&status) < 0){
			perror("\nErrore in wait");
			exit(-1);
		}
		
		printf("\nProcesso padre:\n");
		
		if(WIFEXITED(status))
			printf("\nvalore di uscira: %d\n", WEXITSTATUS(status));
		else printf("\nTerminazione anomala.\n");
	}
	
	return 0;
}
