#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char buf1[] = "abcdefghij\n";
char buf2[] = "ABCDEFGHIJ\n";

int main(){

	int file_descriptor;

	if((file_descriptor = open("esempio_scrittura_con_buco.txt", O_RDWR | O_CREAT, S_IRWXU)) < 0)
		perror("\nErrore apertura del file in lettura scrittura nomi.txt\n");

	if(write(file_descriptor, buf1, 10) != 10)
		perror("\nErrore di scrittura di buf1 su file nomi.txt\n");

	//creazione di un buco con offset
	if(lseek(file_descriptor, 20, SEEK_SET) == -1)
		perror("\nErrore cerazione buco con offset lseek\n");


	if(write(file_descriptor, buf2, 10) != 10)
		perror("\nErrore di scrittura di buf2 su file nomi.txt\n");

	//impostando l'offset all'inizio per una lettura di tutto il file
	if(lseek(file_descriptor, 0, SEEK_SET) == -1)
		perror("\nErrore di impostazione offset inizio.\n");

	char all[500];
	ssize_t bytes_read;
	while((bytes_read = read(file_descriptor, all, sizeof(all) - 1)) > 0){

		all[bytes_read] = '\0';
		printf("%s", all);
	}

	if(close(file_descriptor) < 0)
		perror("\nErrore nella chiusura del file\n");

	return 0;
}
