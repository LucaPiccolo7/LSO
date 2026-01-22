/*
Programma che genera due processi, il primo scrive una stringa
su un file, il secondo la legge
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFSIZE 4096

int main(){

        int file_des;
        int pid;
        char message[BUFFSIZE] = "Questo è il messaggio del processo figlio che scrive dentro testfile.\n";

        if ((file_des = open("testfile", O_RDWR | O_CREAT | O_APPEND, S_IRWXU)) < 0){
                perror("\nErrore apertura file.\n");
                exit(-1);
        }

        if((pid = vfork()) < 0){
                perror("\nErrore nella fork.\n");
                exit(-1);
        } else if (pid == 0){

                if(write(file_des, message, BUFFSIZE) < 0){
                        perror("\nErrore scrittura file processo figlio.\n");
                        exit(-1);
                }

                _exit(0);

        } else {

                char output_message[BUFFSIZE];

                lseek(file_des, 0, SEEK_SET);

                if(read(file_des, output_message, BUFFSIZE) < 0){
                        perror("\nErrore nella lettura del file nel processo padre.\n");
                        exit(-1);
                }

                printf("\nLa stringa letta dal file è la seguente: %s\n", output_message);

        }

        if(close(file_des) < 0){
                perror("\nErrore chiusura file.\n");
                exit(-1);
        }

        return 0;
}
