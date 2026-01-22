#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

	int i;
	struct stat buf;
	char *ptr;
	
	for(i=1; i<argc; i++){
		printf("%s: ", argv[i]);
		if(lstat(argv[i], &buf) < 0){
			perror("\nlstat error.\n");
			continue;
		}
		
		if(S_ISREG(buf.st_mode)) ptr = "Regular file";
		else if (S_ISDIR(buf.st_mode)) ptr = "Directory file";
		else if (S_ISBLK(buf.st_mode)) ptr = "Block file";
		else if (S_ISCHR(buf.st_mode)) ptr = "Character file";
		else if (S_ISFIFO(buf.st_mode)) ptr = "FIFO file";
		else if (S_ISSOCK(buf.st_mode)) ptr = "Socket file";
		else if (S_ISLNK(buf.st_mode)) ptr = "Soft link file";
		
		printf("%s.\n", ptr);
	}

	return 0;
}
