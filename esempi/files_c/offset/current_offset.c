#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){

	int current_offset;
	
	if((current_offset = lseek(STDIN_FILENO, 0, SEEK_CUR)) == -1){
		printf("\nCannot seek file\n");
		exit(-1);
	} else {
		printf("\nSeek ok, current offset %d\n", current_offset);
		exit(0);
	}
}
