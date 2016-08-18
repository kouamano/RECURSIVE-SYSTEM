#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	long int size = 1024;
	char *m;
	sscanf(argv[1],"%ld",&size);
	if( (m = malloc(sizeof(char) * size)) == NULL ){
		perror("failed");
		exit(1);
	}
	return(0);
}
