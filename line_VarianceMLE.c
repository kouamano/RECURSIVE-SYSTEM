/* line_VarianceMLE.c */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "/home/pub/include/dim_alloc.c"
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
#define X 40000
#define Y 4000

void f_read_from_stdin(float **mat, int *dimensions){
	int i = 0;
	int j = 0;
	int j_max = 0;
	int k = 0;
	int prev_sep_i = 0;
	int prev_sep_j = 0;
	char c;
	char num_str[128];
	num_str[0] = '\0';
	while(scanf("%c",&c) != EOF){
		if(c == '\n'){
			num_str[k] = '\0';
			sscanf(num_str,"%f",&mat[i][j]);
			if(prev_sep_j == 0){
				j++;
			}
			if(prev_sep_i == 0){
				i++;
			}
			j_max = max(j,j_max);
			j = 0;
			k = 0;
			prev_sep_i = 1;
		}else if((c == ' ')||(c == ',')){
			num_str[k] = '\0';
			sscanf(num_str,"%f",&mat[i][j]);
			if(prev_sep_j == 0){
				j++;
			}
			k = 0;
			prev_sep_j = 1;
		}else{
			num_str[k] = c;
			k++;
			prev_sep_i = 0;
			prev_sep_j = 0;
		}
	}
	dimensions[0] = i;
	dimensions[1] = j_max;
}

void f_read_from_file(FILE *fp, float **mat, int *dimensions){
	int i = 0;
	int j = 0;
	int j_max = 0;
	int k = 0;
	int prev_sep_i = 0;
	int prev_sep_j = 0;
	char c;
	char num_str[128];
	num_str[0] = '\0';
	while((c = fgetc(fp)) != EOF){
		if(c == '\n'){
			num_str[k] = '\0';
			sscanf(num_str,"%f",&mat[i][j]);
			if(prev_sep_j == 0){
				j++;
			}
			if(prev_sep_i == 0){
				i++;
			}
			j_max = max(j,j_max);
			j = 0;
			k = 0;
			prev_sep_i = 1;
		}else if((c == ' ')||(c == ',')){
			num_str[k] = '\0';
			sscanf(num_str,"%f",&mat[i][j]);
			if(prev_sep_j == 0){
				j++;
			}
			k = 0;
			prev_sep_j = 1;
		}else{
			num_str[k] = c;
			k++;
			prev_sep_i = 0;
			prev_sep_j = 0;
		}
	}
	dimensions[0] = i;
	dimensions[1] = j_max;
}

float *add_column(int dim, int len, float **matrix){
	int i;
	int j;
	float *sum_list;
	sum_list = f_alloc_list(len);
	for(j=0;j<len;j++){
		sum_list[j] = 0;
	}
	for(i=0;i<len;i++){
		for(j=0;j<dim;j++){
			sum_list[i] = sum_list[i] + matrix[j][i];
		}
	}
	return(sum_list);
}

float *add_line(int dim, int len, float **matrix){
	int i;
	int j;
	float *sum_list;
	sum_list = f_alloc_list(dim);
	for(j=0;j<dim;j++){
		sum_list[j] = 0;
	}
	for(i=0;i<len;i++){
		for(j=0;j<dim;j++){
			sum_list[j] = sum_list[j] + matrix[j][i];
		}
	}
	return(sum_list);
}

int main(int argc, char **argv){
	FILE *in;
	int i;
	int j;
	int dims[2];
	float **imat;
	float *sig;
	float *sig_line;
	float *av_line;
	float *sq_sig_line;
	if(argc == 1){
		imat = f_clear_alloc_matrix(X,Y);
		f_read_from_stdin(imat,dims);
	}else if(argc == 2){
		imat = f_clear_alloc_matrix(X,Y);
		if((in = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
		f_read_from_file(in,imat,dims);
		fclose(in);
	}
	sig = add_column(dims[0],dims[1],imat);
	sig_line = add_line(dims[0],dims[1],imat);
	av_line = f_alloc_list(dims[1]);
	for(i=0;i<dims[0];i++){
		av_line[i] = sig_line[i]/dims[1];
	}
	free(sig);
	for(i=0;i<dims[0];i++){
		for(j=0;j<dims[1];j++){
			imat[i][j] = pow((double)(imat[i][j] - av_line[i]),2);
		}
	}
	free(av_line);
	sq_sig_line = add_line(dims[0],dims[1],imat);
	for(i=0;i<dims[0];i++){
		printf("%f\n",sq_sig_line[i]/dims[1]);
	}
	return(0);
}
