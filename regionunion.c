#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_LINE 200000
#define SIZE_LINE 96
#define SIZE_WORD 32
#define POS 0

int comp_int(int *x, int *y){
	if(*(x+POS) < *(y+POS)){
		return(-1);
	}else if(*(x+POS) >= *(y+POS)){
		return(1);
	}else{
		return(0);
	}
}

int main(int argc, char **argv){
	int i;
	FILE *IN;
	char c;
	int is_open = 0;
	int matrix[NUM_LINE][2];
	int start_or_end = 0;	/* 0:out of regin, 1:start, 2:inner region, 3:end */
	char start[SIZE_WORD];
	char end[SIZE_WORD];
	int p_line = 0;
	int p_start = 0;
	int p_end = 0;
	int is_print = 0;
	int prev_is_print = 0;
	if(argc == 2){
		if((IN = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
		is_open = 1;
	}else{
		IN = stdin;
		is_open = 0;
	}
	while((c = fgetc(IN)) != EOF){
		if((48 <= c)&&(c <= 57)){
			if(start_or_end == 0){
				start_or_end = 1;
				start[p_start] = c;
				p_start++;
			}else if(start_or_end == 1){
				start[p_start] = c;
				p_start++;
			}else if(start_or_end == 2){
				start_or_end = 3;
				end[p_end] = c;
				p_end++;
			}else if(start_or_end == 3){
				end[p_end] = c;
				p_end++;
			}
		}else if(c == '.'){
			if(start_or_end == 0){
				fprintf(stderr,"check file format.\n");
				fprintf(stderr,"line:%d:\n",p_line);
				fprintf(stderr,"c:%c:\n",c);
				exit(1);
			}else if(start_or_end == 1){
				start[p_start] = '\0';
				sscanf(start,"%d",&matrix[p_line][0]);
				matrix[p_line][1] = 1;
				p_start = 0;
				start_or_end = 2;
				p_line++;
			}else if(start_or_end == 2){

			}else if(start_or_end == 3){
				fprintf(stderr,"check file format.\n");
				fprintf(stderr,"line:%d:\n",p_line);
				fprintf(stderr,"c:%c:\n",c);
				exit(1);
			}
		}else if((c == ':')||(c == '\n')){
			if(start_or_end == 0){
			}else if(start_or_end == 1){
				fprintf(stderr,"check file format.\n");
				fprintf(stderr,"line:%d:\n",p_line);
				fprintf(stderr,"c:%c:\n",c);
				exit(1);
			}else if(start_or_end == 2){
				fprintf(stderr,"check file format.\n");
				fprintf(stderr,"line:%d:\n",p_line);
				fprintf(stderr,"c:%c:\n",c);
				exit(1);
			}else if(start_or_end == 3){
				start_or_end = 0;
				end[p_end] = '\0';
				sscanf(end,"%d",&matrix[p_line][0]);
				matrix[p_line][1] = -1;
				p_end = 0;
				p_line++;
			}
		}else{
			fprintf(stderr,"unexpected charctor including. check file.\n");
			fprintf(stderr,"at line:%d:\n",p_line);
			exit(1);
		}
	}
	if(is_open == 1){
		fclose(IN);
	}
	for(i=0;i<p_line;i++){
		if(matrix[i][1] == 1){
			matrix[i][0]--;
		}
	}
	qsort(matrix,p_line,sizeof(int)*2,(int(*)())comp_int);
	/*
	printf("---\n");
	for(i=0;i<p_line;i++){
		prev_is_print = is_print;
		is_print += matrix[i][1];
		printf("%d..%d: %d %d\n",matrix[i][0],matrix[i][1],prev_is_print,is_print);
	}
	printf("---\n");
	*/
	for(i=0;i<p_line;i++){
		prev_is_print = is_print;
		is_print += matrix[i][1];
		if((matrix[i][1] == 1)&&(prev_is_print == 0)&&(is_print == 1)){
			printf("%d..",matrix[i][0]+1);
		}else if((matrix[i][1] == -1)&&(prev_is_print == 1)&&(is_print == 0)){
			printf("%d:\n",matrix[i][0]);
		}
	}
	return(0);
}
