/* tensor_out.c */

/*************************************************/
/* Copyright (c) 2003-2005 AMANO Kou             */
/* University of Tsukuba                         */
/* University of Library And Information Science */
/* National Institute of Agrobilogical Sciences  */
/* kamano@affrc.go.jp                            */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "soc.h"
#include "files.h"
#include "soc.c"

struct plane_tensor {
	int rank;
	int *dim;
	int *body;
};

int *get_tensor_dimANDrank(const int rank, char *str){
	int i;
	int j;
	int k;
	int *dim;
	int local_rank;
	int len;
	char tmp_c[128];
	int tmp;
	len = strlen(str);
	for(i=0;i<len;i++){
		if(str[i] == ','){
			(local_rank)++;
		}
	}
	(local_rank)++;
	dim = malloc(sizeof(int)*(rank));
	if(dim == NULL){
		printf("error\n");
	}
	j = 0;
	k = 0;
	for(i=0;i<len;i++){
		if(str[i] != ','){
			tmp_c[j] = str[i];
			j++;
		}else{
			tmp_c[j] = '\0';
			sscanf(tmp_c,"%d",&tmp);
			dim[k] = tmp;
			k++;
			j = 0;
		}
	}
	tmp_c[j] = '\0';
	sscanf(tmp_c,"%d",&tmp);
	dim[k] = tmp;
	k++;
	for(i=k;i<rank;i++){
		dim[i] = 1;
	}
	return(dim);
}

int **make_outer_tensor_position_mat(int rank, int *n_elm, int *dim){
	int i;
	int j;
	int *prod;
	int elm;
	int tmp;
	float f;
	int **out_mat;
	if((prod = malloc(sizeof(int)*(rank+1))) == NULL){
		printf("error\n");
		exit(1);
	}
	elm = 1;
	for(i=0;i<rank;i++){
		elm = dim[i] * elm;
	}
	out_mat = i_alloc_mat(elm,rank);
	j = 1;
	tmp = 1;
	prod[0] = 1;
	for(i=1;i<rank;i++){
		tmp = tmp * dim[i-1];
		prod[j] = tmp;
		j++;
	}
	for(i=0;i<elm;i++){
		for(j=0;j<rank;j++){
			f = (float)i/prod[j];
			out_mat[i][j] = ((int)f)%dim[j];
		}
	}
	*n_elm = elm;
	return(out_mat);
}

void print_outer_tensor_position(int rank, int *dim){
	int i;
	int j;
	int *prod;
	int elm;
	int tmp;
	float f;
	//int **out_mat;
	if((prod = malloc(sizeof(int)*(rank+1))) == NULL){
		printf("error\n");
		exit(1);
	}

	elm = 1;
	for(i=0;i<rank;i++){
		elm = dim[i] * elm;
	}
	//out_mat = i_alloc_matrix(elm,rank);
	j = 1;
	tmp = 1;
	prod[0] = 1;
	for(i=1;i<rank;i++){
		tmp = tmp * dim[i-1];
		prod[j] = tmp;
		j++;
	}
	for(i=0;i<elm;i++){
		printf("i:%d ",i);
		f = (float)i/prod[0];
		printf("%d",((int)f)%dim[0]);
		for(j=1;j<rank;j++){
			f = (float)i/prod[j];
			printf(",%d",((int)f)%dim[j]);
		}
		printf("\n");
	}
}

int main(int argc, char **argv){
	int i;
	int j;
	int *dim;
	int **mat;
	int rank;
	char string[512];
	float f;
	float f2;
	float f3;
	int c;
	int tmp;
	int *prod;
	int elm;
	sscanf(argv[1],"%d",&rank);
	sscanf(argv[2],"%s",string);
	dim = get_tensor_dimANDrank(rank,string);
	print_outer_tensor_position(rank, dim);
	mat = make_outer_tensor_position_mat(rank, &elm, dim);
	printf("----- -----\n");
	printf("elm:%d\n",elm);
	for(i=0;i<elm;i++){
		for(j=0;j<rank;j++){
			printf("%d,",mat[i][j]);
		}
		printf("\n");
	}
}
