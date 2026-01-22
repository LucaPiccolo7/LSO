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
	strcpy(string, "aaaaaaaaa\n");
	
	int fd;
	if((fd = open("testfile", O_RDWR|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR)) < 0)
		perror("\nErrore di apertura del file.\n");
	
	char input;
	do {
	
		if(write(STDOUT_FILENO, "Comando:", 8) < 8)
			perror("\nErrore di scrittura su STD_OUT");
		
		input=getchar();
		__fpurge(stdin);
		string[0]=input;
		
		write(fd, string, 10);
		lseek(fd, (off_t)3, SEEK_SET);
		if(write(STDOUT_FILENO, "Eseguito\n", 9) < 9)
			perror("\nErrore di scrittura 2.\n");
	
	} while (input!='f');
	
	close(fd);
	
	return 0;
}
