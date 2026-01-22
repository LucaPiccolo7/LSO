#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define TRUE 1
#define FALSE 0
#define BELLS "\007\007\007"

int alarm_flag = FALSE;

//handler per SIGALARM
//quando si verifica l'allarme si setta la variabile
void setflag(){
	alarm_flag = TRUE;
	
}

int main(int argc, char *argv[]){

	int nsec;
	
	if(argc != 2){
		perror("\nErrore numero argomenti.\n");
		exit(-1);
	}
	
	nsec = atoi(argv[1]);
	
	signal(SIGALRM, setflag);
	
	alarm(nsec);
	pause();
	
	if(alarm_flag == TRUE){
		printf(BELLS);
		printf("\n");
	}

	return 0;
}
