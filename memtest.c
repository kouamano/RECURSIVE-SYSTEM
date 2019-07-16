#include <stdio.h>
#include <stdlib.h>
#include "../include/alloc.c"

int main(int argc, char *argv[]){
	int i;
	int j;
	int x;
	int y;
	int **m;
	sscanf(argv[1],"%d",&y);
	sscanf(argv[2],"%d",&x);
	m = i_alloc_mat(y,x);
	/*
	if((m = malloc(sizeof(int *)*y)) == NULL){
		printf("failed : malloc() -- exit.\n");
	}
	for(i=0;i<y;i++){
		if((m[i] = malloc(sizeof(int)*x)) == NULL){
			printf("failed : malloc() -- exit.\n");
		}
	}
	*/
	m[y-1][x-1] = 12;
	printf("%d\n",m[y-1][x-1]);
	return(0);
}
