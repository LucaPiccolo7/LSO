/*
Scrivere un programma "aspetta.c" che scrive un messaggio su stdout ogni volta che riceve i segnali SIGINT e SIGUSR1
Il programma non deve mai terminare spontaneamente
Lanciare il programma. Usando il comando kill della shell, provare ad inviare questi due segnali, e alla fine terminarlo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

int main(){

	
}
