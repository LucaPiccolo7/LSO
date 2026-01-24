/*
 * Client di prova
 * */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

int main(){

	int fd;
	struct sockaddr_un server_address;

	server_address.sun_family = AF_LOCAL;
	strcpy(server_address.sun_path, "/tmp/server_socket");

	if((fd = socket(PF_LOCAL, SOCK_STREAM, 0)) < 0){
		perror("\n[CLIENT]: errore creazione socket.\n");
		exit(-1);
	}

	if(connect(fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
		perror("\n[CLIENT]: errore connect.\n");
		exit(-1);
	}

	close(fd);
	return 0;
}
