#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	long int size = 1024;
	char *m;
	long int i;
	sscanf(argv[1],"%ld",&size);
	printf("size: %ld",size);
	if( (m = malloc(sizeof(char) * size +1)) == NULL ){
		perror("failed");
		exit(1);
	}
	for(i=0;i<size;i++){
		m[i] = '\1';
	}
	return(0);
}
