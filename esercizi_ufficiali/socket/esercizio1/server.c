/*
 * Scrivere due programmi server.c e client.c che comunicano tramite socket. Il server.c crea il socket locale,
 * ed ogni volta che instaura una connessione con un client, mediante fork crea un nuovo processo.
 * Tale processo dovrà leggere sul socket il messaggio scritto dal client e scrivere il messaggio che il server manda al client.
 * Il client.c dovrà connettersi al socket locale sul quale scriverà il messaggio da mandare al server.
 * (Lanciare l'esecuzione dei due programmi su due shell diverse della stessa macchina)
 * */

//server.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/signal.h>
#include <sys/un.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>

#define SIZE 4096

int main(){

	int server_socket, client_socket;
	pid_t pid;
	struct sockaddr_un server_address;
	socklen_t server_address_len = sizeof(server_address);

	server_address.sun_family = AF_LOCAL;
	strcpy(server_address.sun_path, "/tmp/server_socket");

	if((server_socket = socket(PF_LOCAL, SOCK_STREAM, 0)) < 0){
		perror("\n[SERVER] Errore creazione del socket.\n");
		exit(-1);
	}

	unlink(server_address.sun_path);

	if(bind(server_socket, (struct sockaddr *)&server_address, server_address_len) < 0){
		perror("\n[SERVER] Errore bind socket.\n");
		exit(-1);
	}
	
	if(listen(server_socket, 5) < 0){
		perror("\n[SERVER] Errore socket listen.\n");
		exit(-1);
	}

	while(1){
		
		if((client_socket = accept(server_socket, (struct sockaddr *)&server_address, &server_address_len)) < 0){
			perror("\n[SERVER] Errore accept socket.\n");
			exit(-1);
		}

		if ((pid = fork()) < 0){
			perror("\n[SERVER] Errore fork.\n");
			exit(-1);
		} else if (pid == 0){

			srand(getpid());

			close(server_socket);

			char received_message[SIZE];
			char mid_message[SIZE];
			char message_to_send[SIZE];
			
			ssize_t bytes_read;

			int random_number = 1 + rand() % 50; 

			if((bytes_read = read(client_socket, received_message, SIZE-1)) < 0){
				perror("\n[SERVER] Errore read.\n");
			}
			
			received_message[bytes_read] = '\0';

			printf("\n[SERVER] il messaggio inviato dal client è:\n\"%s\"\n", received_message);

			snprintf(mid_message, sizeof(mid_message), "%s con signature %d.", received_message, random_number);
			strcpy(message_to_send, mid_message);

			if(write(client_socket, message_to_send, strlen(message_to_send) + 1) < 0){
				perror("\n[SERVER] errore write.\n");
				exit(-1);
			}

			_exit(0);

		} else {

			close(client_socket);

			signal(SIGCHLD, SIG_IGN);
		}
	}

	close(server_socket);
	unlink(server_address.sun_path);
	return 0;
}
