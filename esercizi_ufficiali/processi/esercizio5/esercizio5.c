/*
(esercizio 4)
Scrivere un programma che manda in esecuzione un eseguibile il cui filename è
inserito come argomento sulla linea di comando e ne aspetta la terminazione.

Aggiungere al programma di sopra la capacità di eseguire nella directory di ambiente PATH
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void errore(char *error){
        printf("%s", error);
        exit(-1);
}

int main(int argv, char *argc[]){

        printf("\nargv: %d\n", argv);
        printf("argc[0]=%s\n", argc[0]);
        printf("argc[1]=%s\n", argc[1]);
        printf("argc[2]=%s\n", argc[2]);

        if(argv != 3)
                errore("\nInserire esattamente il nome di 1 eseguibile.\n");

        pid_t pid;
        int status;

        if((pid = fork()) < 0)
                errore("\nErrore nell'esecuzione di fork.\n");
        else if (pid == 0){

                printf("\nControllo passato al processo figlio.\nViene eseguita la execvp di seguito.\n");
                execlp(argc[1], argc[1], argc[2], (char *)0);
                errore("\nErrore nell'esecuzione del comando.\n");

        } else {

                if((pid = waitpid(pid, &status, 0)) < 0)
                        errore("\nErrore nell'esecuzione di wait.\n");

                printf("\nControllo passato al processo padre, esecuzione execlp terminata.\n");
                exit(0);
        }

        return 0;
}

