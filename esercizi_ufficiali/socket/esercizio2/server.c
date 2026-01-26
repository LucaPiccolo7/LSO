/*
 * Ad ogni nuova connessione, il server scrive sul socket l'ora corrente. Poi chiude la connessione e
 * si rimette in attesa di nuove connessioni.
 *
 * Implementare anche un client che riceve l'ora dal server e la stampa sul terminale
 *
 * Provare a lanciare diversi client in rapida successione.
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>

int main(){

	int server_socket;
	struct sockaddr_un server_address;
	
	server_address.sun_family = AF_LOCAL;
	strcpy(server_address.sun_path, "/tmp/server_socket");

	if((server_socket = socket(PF_LOCAL, SOCK_STREAM, 0)) < 0){
		perror("");
	}

	return 0;
}
