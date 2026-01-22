#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){

	if(argc != 2){
		perror("\n[CLIENT]: È necessario scrivere il nome da mandare in FIFO.\n");
		exit(-1);
	}

	int fd;
	
	if((fd = open("miafifo", O_WRONLY)) < 0){
		perror("\n[CLIENT]: Errore open FIFO.\n");
		exit(-1);
	}
	
	if(write(fd, argv[1], strlen(argv[1])) < 0){
		perror("\n[CLIENT]: Errore scrittura FIFO.\n");
		exit(-1);
	}

	return 0;
}
