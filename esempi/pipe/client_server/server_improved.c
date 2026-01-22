/*
Esempio preso dalla slide delle pipe, ma il processo server non termina
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>

#define BUFFSIZE 100

int main(int argc, char *argv[]){

	int fd, ret_val, count, numread;
	char buff[BUFFSIZE];
	
	/*create the named pipe*/
	ret_val = mkfifo("miafifo", S_IRUSR | S_IWUSR);		
	if(ret_val == -1 && errno == EEXIST){
		perror("\nError creating the named pipe.\n");
		exit(1);
	}
	
	while(1){
	
		//open the pipe for reading
		fd = open("miafifo", O_RDONLY);
	
		while((numread = read(fd, buff, BUFFSIZE)) > 0){
		
			buff[numread] = '\0';
	
			printf("\n[SERVER]: Read from the pipe: %s\n", buff);

			//convert the string to uppercase
			count = 0;
			while (count < numread){
				buff[count] = toupper(buff[count]);
				count++;
			}
	
			printf("\n[SERVER]: converted string -> %s\n", buff);
		}
		
		printf("\n[SERVER]: Fine dati.\n");
		close(fd);
	}
	
	return 0;
}
