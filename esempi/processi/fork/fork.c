#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int glob = 6;

int main(){

	int var;
	pid_t pid;
	
	var = 88;
	
	printf("\nBefore vfork.\n");
	if((pid = vfork()) < 0)
		perror("\nErrore vfork.\n");
	else if (pid == 0){
		glob++;
		var++;
		_exit(0);
	}
	
	printf("\npid: %d\nglob: %d\nvar: %d\n", getpid(), glob, var);
	exit(0);

	return 0;
}
