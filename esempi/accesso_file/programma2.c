#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	char *string;
	strcpy(string, "bbbbbbbbb\n");
	
	int fd;
	if((fd = open("testfile", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR)) < 0)
		perror("\nErrore di apertura del file.\n");
		
	lseek(fd, 0, SEEK_END);
	
	char input;
	do {
	
		if(write(STDOUT_FILENO, "Comando:", 8) < 8)
			perror("\nErrore di scrittura su STD_OUT");
		
		input=getchar();
		__fpurge(stdin);
		string[0]=input;
		
		if(write(fd, string, 10) < 10) perror("\nErrore di scrittura 2.\n");

		if(write(STDOUT_FILENO, "Eseguito\n", 9) < 9)
			perror("\nErrore di scrittura 3.\n");
	
	} while (input!='f');
	
	close(fd);
	
	return 0;
}
