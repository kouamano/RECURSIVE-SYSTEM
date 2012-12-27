#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
			sscanf(tmp,"%f",&mat[k]);
			h = 0;
			i++;
			k++;
		}else if(c == '\n'){
			tmp[h] = '\0';
			sscanf(tmp,"%f",&mat[k]);
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
	return(0);
}
