/* column_standardize.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LEN 4000000
#define SEP ' '

float *mat;

int get_mat_from_stdin(char *fname, int *num_of_columns, int *num_of_lines, float *outmat){
	int h = 0;	/* temporaly use for string "tmp" */
	int i = 0;	/* number of columns */
	int j = 0;	/* number of lines */
	int k = 0;	/* number of elements (i * j) */
	char c;
	char tmp[128];
	while((scanf("%c",&c)) != EOF){
		if((c != SEP)&&(c != '\n')){
			tmp[h] = c;
			h++;
		}else if(c == SEP){
			tmp[h] = '\0';
			sscanf(tmp,"%f",&outmat[k]);
			h = 0;
			i++;
			k++;
		}else if(c == '\n'){
			tmp[h] = '\0';
			sscanf(tmp,"%f",&outmat[k]);
			i++;
			*num_of_columns = i;
			h = 0;
			i = 0;
			j++;
			k++;
		}
	}
	*num_of_lines = j;
	return(0);
}

int get_mat_from_file(char *fname, int *num_of_columns, int *num_of_lines, float *outmat){
	int h = 0;	/* temporaly use for string "tmp" */
	int i = 0;	/* number of columns */
	int j = 0;	/* number of lines */
	int k = 0;	/* number of elements (i * j) */
	char c;
	char tmp[128];
	FILE *IN;
	if((IN = fopen(fname, "r")) == NULL){
		perror(fname);
		exit(1);
	}
	while((c = fgetc(IN)) != EOF){
		if((c != SEP)&&(c != '\n')){
			tmp[h] = c;
			h++;
		}else if(c == SEP){
			tmp[h] = '\0';
			sscanf(tmp,"%f",&outmat[k]);
			h = 0;
			i++;
			k++;
		}else if(c == '\n'){
			tmp[h] = '\0';
			sscanf(tmp,"%f",&outmat[k]);
			i++;
			*num_of_columns = i;
			h = 0;
			i = 0;
			j++;
			k++;
		}
	}
	*num_of_lines = j;
	return(0);
}

int main(int argc, char **argv){
	int i;
	int j;
	int columns;
	int lines;
	int N;
	double *av_columns;
	double *v_columns;
	mat = calloc(MAX_LEN,sizeof(float));
	if(argc == 1){
		get_mat_from_stdin(argv[1],&columns,&lines,mat);
	}else if(argc == 2){
		get_mat_from_file(argv[1],&columns,&lines,mat);
	}else{
		printf("type input file name.\n");
		exit(1);
	}
	av_columns = calloc((columns+1),sizeof(double));
	v_columns = calloc((columns+1),sizeof(double));
	if((strcmp(argv[0],"column_standardizeMLE") == 0)||(strcmp(argv[0],"./column_standardizeMLE") == 0)){
		N = lines;
	}else if((strcmp(argv[0],"column_standardize") == 0)||(strcmp(argv[0],"./column_standardize") == 0)){
		N = lines - 1;
	}
	for(i=0;i<lines*columns;i++){
		av_columns[i%columns] += mat[i]/lines;
	}
	for(i=0;i<lines*columns;i++){
		v_columns[i%columns] += pow(mat[i] - av_columns[i%columns],2);
	}
	for(i=0;i<columns;i++){
		if(v_columns[i] == 0){
			v_columns[i] = 1;
		}
	}
	for(i=0;i<lines;i++){
		printf("%f",(mat[i*columns+0] - av_columns[0])/sqrt(v_columns[0]/N));
		for(j=1;j<columns;j++){
			printf(" %f",(mat[i*columns+j] - av_columns[j])/sqrt(v_columns[j]/N));
		}
		printf("\n");
	}
	return(0);
}
