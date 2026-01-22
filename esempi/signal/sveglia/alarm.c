#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
void foo(int signum);

int main(){

	int n = 0;
	int buff[100];
	alarm(5);
	signal(SIGALRM, foo);
	
	while(n <= 0){
	
		printf("\nDigitare qualcosa:\n");
		alarm(1);
		if((n=read(STDIN_FILENO, buff, 10)) < 0)
			perror("\nRead error.\n");
		alarm(0);
	}	

	return 0;
}

void foo(int signum){

	alarm(1);
	printf("\nVuoi muoverti a digitare qualcosa???\n");
}
