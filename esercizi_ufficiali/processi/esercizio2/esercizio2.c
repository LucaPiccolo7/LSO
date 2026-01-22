#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	int i;
	
	for (i = 0; i < 2; i++){
	
		if (fork() > 0){
			printf("\nPadre! %d.\n", i);
		} else {
			printf("\nFiglio! %d.\n", i);
		}
	}

	sleep(10);
	return 0;
}
