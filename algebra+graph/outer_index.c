#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define TMP_STR_LEN 512
#include "../../include/alloc.c"
#include "../../include/list_operations.c"

int main(int argc, char **argv){
	int i;
	int j;
	int *dim;
	int rank;
	char string[TMP_STR_LEN];
	float f;
	int tmp;
	int *prod;
	int elm;
	int **outer_list;
	if(argc != 2){
		printf("USAGE:\n");
		printf("  outer <comma separated numeric>\n");
		exit(0);
	}
	sscanf(argv[1],"%s",string);
	dim = get_tensor_dim_from_str(string,&rank);
	elm = 1;
	for(i=0;i<rank;i++){
		elm = dim[i] * elm;
	}
	outer_list = i_alloc_mat(elm,rank);
	create_outer_list(rank,dim,outer_list);
	int counter = 0;
	for(i=0;i<elm;i++){
		counter = 0;
		printf("[%d][%d]",counter,outer_list[i][0]);
		counter++;
		for(j=1;j<rank;j++){
			printf(",[%d][%d]",counter,outer_list[i][j]);
			counter++;
		}
		printf("\n");
	}
	return(0);
}
