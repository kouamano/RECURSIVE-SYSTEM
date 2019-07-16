/* line_variance.c */
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
	int columns;
	int lines;
	int llines;
	double *av_lines;
	double *v_lines;
	mat = calloc(MAX_LEN,sizeof(float));
	if(argc == 1){
		get_mat_from_stdin(argv[1],&columns,&lines,mat);
	}else if(argc == 2){
		get_mat_from_file(argv[1],&columns,&lines,mat);
	}else{
		printf("type input file name.\n");
		exit(1);
	}
	av_lines = calloc((lines+1),sizeof(double));
	v_lines = calloc((lines+1),sizeof(double));
	llines = lines - 1;
	for(i=0;i<lines*columns;i++){
		av_lines[i/llines] += mat[i]/columns;
	}
	for(i=0;i<lines*columns;i++){
		v_lines[i/llines] += pow(mat[i] - av_lines[i/llines],2);
	}
	if((strcmp(argv[0],"line_varianceMLE") == 0)||(strcmp(argv[0],"./line_varianceMLE") == 0)){
		for(i=0;i<lines;i++){
			printf("%f ",v_lines[i]/columns);
		}
	}else if((strcmp(argv[0],"line_variance") == 0)||(strcmp(argv[0],"./line_variance") == 0)){
		for(i=0;i<lines;i++){
			printf("%f ",v_lines[i]/(columns - 1));
		}
	}
	printf("\n");
	return(0);
}
