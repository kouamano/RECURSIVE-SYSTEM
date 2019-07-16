/* extract-ESC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME_SIZE 1024

int main(int argc, char **argv){
	/* vars */
	FILE *IN;
	int is_open = 0;
	int C = 0;

	/* open file */
	if(argc == 1){
		IN = stdin;
	}else if(argc == 2){
		IN = fopen(argv[1],"r");
		if(IN == NULL){
			perror(argv[1]);
			exit(0);
		}else{
			is_open++;
		}
	}

	/* func */
	while((C = fgetc(IN)) != EOF){
		if(C == 0x1b){
			fputc(C,stdout);
		}
	}

	/* close file */
	if(is_open > 0){
		fclose(IN);
	}
}
