/*
 * Scrivere due programmi server.c e client.c che comunicano tramite socket. Il server.c crea il socket locale,
 * ed ogni volta che instaura una connessione con un client, mediante fork crea un nuovo processo.
 * Tale processo dovrà leggere sul socket il messaggio scritto dal client e scrivere il messaggio che il server manda al client.
 * Il client.c dovrà connettersi al socket locale sul quale scriverà il messaggio da mandare al server.
 * (Lanciare l'esecuzione dei due programmi su due shell diverse della stessa macchina)
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <string.h>

#define SIZE 4096

int main(){
	
	int client_socket;
	struct sockaddr_un server_address;
	socklen_t server_address_len = sizeof(server_address);

	server_address.sun_family = AF_LOCAL;
	strcpy(server_address.sun_path, "/tmp/server_socket");

	if((client_socket = socket(PF_LOCAL, SOCK_STREAM, 0)) < 0){
		perror("\n[CLIENT] Errore socket.\n");
		exit(-1);
	}

	if(connect(client_socket, (struct sockaddr *)&server_address, server_address_len) < 0){
		perror("\n[CLIENT] Errore connect.\n");
		exit(-1);
	}

	char message_to_send[SIZE] = "Questo è un messaggio da parte del client.";
	char message_received[SIZE];

	if(write(client_socket, message_to_send, SIZE) < 0){
		perror("\n[CLIENT] Errore write.\n");
		exit(-1);
	}

	if(read(client_socket, message_received, SIZE) < 0){
		perror("\n[CLIENT] Errore read.\n");
		exit(-1);
	}

	printf("[CLIENT] messaggio ricevuto dal server: %s\n", message_received);

	close(client_socket);

	return 0;
}
