/*drop-ascii.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME_SIZE 1024

/* input file */
char file_name[FILE_NAME_SIZE];

int main(int argc, char **argv){
	/* vars */
	FILE *IN;
	int is_open = 0;
	int C = 0;

	/* open file */
	if(argc == 1){
		IN = stdin;
	}else if(argc == 2){
		sscanf(argv[1],"%s",file_name);
		IN = fopen(file_name,"r");
		if(IN == NULL){
			perror(file_name);
		}else{
			is_open++;
		}
	}

	/* func */
	while((C = fgetc(IN)) != EOF){
		if(C > 0x00 && C < 0x7f){
			;
		}else{
			putc(C,stdout);
		}
	}
	
	/* close file */
	if(is_open > 0){
		fclose(IN);
	}
	exit(0);
}
