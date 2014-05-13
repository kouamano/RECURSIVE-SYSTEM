/* count_ascii.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/alloc.c"

int main(int argc, char **argv){
	FILE *IN;
	int i=0, j=0;
	int c = 0;
	int s_size = 0;
	int counter[128];
	char *base;

	if(argc == 1){
		printf("no input file.\n");
		exit(0);
	}

	if((IN = fopen(argv[1],"r")) == NULL){
		perror(argv[1]);
		exit(1);
	}
	while((c = fgetc(IN)) != EOF){
		s_size++;
	}
	base = c_alloc_vec(s_size + 1);
	fseek(IN,0U,SEEK_SET);
	i = 0;
	while((c = fgetc(IN)) != EOF){
		base[i] = c;
		i++;
	}
	base[i] = '\0';
	fclose(IN);

	for(j=0;j<128;j++){
		counter[j] = 0;
	}
	for(i=0;i<s_size;i++){
		for(j=0;j<128;j++){
			if((int)base[i] == j){
				counter[j]++;
			}
		}
	}
	for(j=0;j<128;j++){
		printf("%d\t%d\n",j,counter[j]);

	}

	return(0);
}
