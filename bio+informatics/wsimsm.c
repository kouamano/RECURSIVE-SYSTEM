/* Weighted SIMilarity between Strings using N-gram */

/* CODENAME: */
/* wsimsn.c  */
/* :END      */

/* COPYRIGHT:         */ 
/* Kou AMANO          */ 
/* RIKEN-BRC          */ 
/* amano@brc.riken.jp */
/* :END               */

/* NEEDS:                      */
/* <stdio.h>                   */
/* <stdlib.h>                  */
/* <string.h>                  */
/* "/home/pub/include/debug.c" */
/* "/home/pub/include/alloc.c" */
/* :END                        */

/* PROCEDURES:     */
/* wsim_from_vec() */
/* get_options()   */
/* init_options()  */
/* help()          */
/* :END            */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/debug.c"
#include "../../include/alloc.c"
#define FILE_NAME_SIZE 1024

struct options {
	char *input_file;
	int lskip;
	int cskip;
	char h_sep;
	int help;
};

void init_options(struct options *opt){
	(*opt).input_file = c_calloc_vec(FILE_NAME_SIZE);
	(*opt).lskip = 0;
	(*opt).cskip = 0;
	(*opt).h_sep = '\0';
	(*opt).help = 0;
}

float wsim_from_vec(int num_vec, int size_vec, int *count_vec, float **gram_vec_vec){
	/* num_vec : number of vectors
	   size_vec : size(length) of vectors. all vectors are as same size.
	   *count_vec : count of each vector.
	   gram_vec_vec : n-gram counts.  */
	int i = 0;
	int j = 0;
	float *prod_vec = NULL;
	float *weight_vec = NULL;
	float sim = 0;
	float Sigma = 0;
	float Pi = 1;
	/* (* weight_vec */
	weight_vec = f_calloc_vec(size_vec);
	for(i=0;i<num_vec;i++){
		for(j=0;j<size_vec;j++){
			weight_vec[j] += gram_vec_vec[i][j];
		}
	}
	for(j=0;j<size_vec;j++){
		if(weight_vec[j] != 0){
			weight_vec[j] = 1/weight_vec[j];
		}
	}
	/* *) */
	//f_print_vec(3,weight_vec,stdout);
	/* (* prod_vec */
	prod_vec = f_balloc_vec(size_vec,1);
	for(i=0;i<num_vec;i++){
		for(j=0;j<size_vec;j++){
			prod_vec[j] *= gram_vec_vec[i][j];
		}
	}
	/* *) */
	//f_print_vec(3,prod_vec,stdout);
	/* (* weight_vec * prod_vec */
	for(j=0;j<size_vec;j++){
		prod_vec[j] = weight_vec[j] * prod_vec[j];
	}
	/* *) */
	//f_print_vec(3,prod_vec,stdout);
	/* (* Sigma count_vec */
	for(i=0;i<num_vec;i++){
		Sigma += count_vec[i];
	}
	/* *) */
	//f_print(Sigma,stdout);
	/* (* Pi count_vec */
	for(i=0;i<num_vec;i++){
		Pi *= count_vec[i];
	}
	/* *) */
	//f_print(Pi,stdout);
	/* (* sim */
	for(j=0;j<size_vec;j++){
		sim += prod_vec[j];
	}
	sim = sim * Sigma / Pi;
	/* *) */
	//f_print(sim,stdout);
	return(sim);
}

void help(void){
	printf("USAGE:");
	printf("\twsimsn n str1 str2\n");
	printf("\twsimsn n if=<input file>\n");
}

int main(int argc, char **argv){
	int i;
	float *test_vec;
	int *c;
	float **v;
	/* (* test */
	c = i_alloc_vec(2);
	v = f_alloc_mat(2,3);
	c[0] = 3;
	c[1] = 3;
	v[0][0] = 2;
	v[0][1] = 0;
	v[0][2] = 1;
	v[1][0] = 1;
	v[1][1] = 1;
	v[1][2] = 1;
	test_vec = f_balloc_vec(4,1);
	f_print_vec(4,test_vec,stdout);
	printf("%f\n",wsim_from_vec(2,3,c,v));
	/* *) */
	return(0);
}
