#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

	struct stat buf;
	
	/*
	Pone ad 1 il set-groupID ed a 0 il permesso di esecuzione per il gruppo
	*/
	
	if(stat("foo", &buf) < 0 )
		printf("\nErrore lettura stat file foo.\n");
	
	if (chmod("foo", (buf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
		perror("\nErrore di impostazione permessi set group id e togliere esecuzione al gruppo.\n");
		
	//protezione a rw-r--r--
	if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
		perror("\nErrore impostazione permessi rw-r--r--.\n");

	return 0;
}
