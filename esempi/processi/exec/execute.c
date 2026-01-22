#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

	printf("\nEsecuzione di ls\n");
	execl("/bin/ls", "ls", "-l", (char *)0);
	printf("\nciao.\n");
	perror("\nLa chiamata di execl ha generato un errore.\n");
	exit(-1);
	return 0;
}
