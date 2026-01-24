/*
 * Prova socket
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <string.h>

int main(){

	int fd1, fd2;
	struct sockaddr_un mio_indirizzo;

	mio_indirizzo.sun_family = AF_LOCAL;
	strcpy(mio_indirizzo.sun_path, "/tmp/server_socket");

	//creazione socket
	if((fd1 = socket(PF_LOCAL, SOCK_STREAM, 0)) < 0){
		perror("\nErrore creazione socket.\n");
		exit(-1);
	}

	//bind del socket
	if(bind(fd1, (struct sockaddr *)&mio_indirizzo, sizeof(mio_indirizzo)) < 0){
		perror("\nErrore bind.\n");
		exit(-1);
	}

	//listen
	if(listen(fd1, 5) < 0){
		perror("\nErrore listen.\n");
		exit(-1);
	}

	printf("\n[SERVER]: Connessione stabilita. In attesa...\n");

	socklen_t addrlen = sizeof(mio_indirizzo);
	if((fd2 = accept(fd1, (struct sockaddr *)&mio_indirizzo, &addrlen)) < 0){
		perror("\nErrore accept.\n");
		exit(-1);
	}

	printf("\n[SERVER]: Rilevata connessione da parte di un client.\n");

	close(fd1);
	close(fd2);
	unlink(mio_indirizzo.sun_path);
	return 0;
}
