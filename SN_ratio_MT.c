#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "/home/pub/include/alloc.c"
//#include "/home/pub/include/data_read.c"
//#include "t_score.c"

float **f_alloc_mat(int num, int dim){
        float **m;
        int i;
        if((m = malloc((size_t)sizeof(float*)*(num+1))) == NULL){
                printf("failed : malloc(), exit.\n");
                exit(1);
        }
        if((m[0] = malloc((size_t)sizeof(float)*(num*dim+dim))) == NULL){
                printf("failed : malloc(), exit.\n");
                exit(1);
        }
        for(i=1;i<num;i++){
                m[i] = m[i-1]+dim;
        }
        return(m);
}

float *f_alloc_vec(int num){
        float *v;
        if((v = malloc((size_t)sizeof(float)*num+1)) == NULL){
                printf("failed : malloc(), exit.\n");
                exit(1);
        }
        return(v);
}

int t_score(float **f, int size_f_t, int size_f_d, float *n){
        int t;
        int d;
        float *F;
        F = malloc(sizeof(float) * size_f_t);
        for(t=0;t<size_f_t;t++){
                for(d=0;d<size_f_d;d++){
                        F[t] += f[d][t];
                }
        }
        for(t=0;t<size_f_t;t++){
                for(d=0;d<size_f_d;d++){
                        n[t] += (-(f[d][t]/F[t]) * log(f[d][t]/F[t])/log(2));
                }
        }
        return(0);
}

int read_ftable_from_stream(int t, int d, FILE *stream, float **table){
        int i;
        int j;
        float ftmp;
        for(i=0;i<d;i++){
                for(j=0;j<t;j++){
                        fscanf(stream,"%f",&ftmp);
                        table[i][j] = ftmp;
                }
        }
        return(0);
}

int main(int argc, char **argv){
	int i;
	int size_t = 0;
	int size_d = 0;
	char f_name[512];
	FILE *in;
	float **a;
	float *v;
	sscanf(argv[1],"%s",f_name);
	sscanf(argv[2],"%d,%d",&size_t,&size_d);
	a = f_alloc_mat(size_d,size_t);
	in = fopen(f_name,"r");
	read_ftable_from_stream(size_t, size_d, in, a);
	fclose(in);
	v = f_alloc_vec(size_t);
	/*
	for(i=0;i<size_d;i++){
		for(j=0;j<size_t;j++){
			printf("%f ",a[i][j]);
		}
		printf("\n");
	}
	*/
	t_score(a,size_t,size_d,v);
	for(i=0;i<size_t;i++){
		printf("%f ",v[i]);
	}
	printf("\n");
	return(0);
}
