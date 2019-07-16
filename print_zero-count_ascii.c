/* print_zero-count_ascii.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	FILE *IN;
	int count,ascii;

	if(argc == 1){
		printf("no input file.\n");
		exit(0);
	}

	if((IN = fopen(argv[1],"r")) == NULL){
		perror(argv[1]);
		exit(1);
	}
	while(fscanf(IN, "%d\t%d\n",&ascii,&count) != EOF){
		if(count == 0){
			printf("%c\n",(char)ascii);
		}
	}
	fclose(IN);
	return(0);
}
