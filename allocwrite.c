#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int size = 1024;
	char *m;
	int i;
	sscanf(argv[1],"%d",&size);
	printf("size: %d",size);
	if( (m = malloc(sizeof(char) * size +1)) == NULL ){
		perror("failed");
		exit(1);
	}
	for(i=0;i<size;i++){
		m[i] = '\1';
	}
	return(0);
}
