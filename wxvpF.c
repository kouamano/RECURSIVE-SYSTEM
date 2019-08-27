#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZ 1000

void help(void){
	printf("USAGE:\n");
	printf("  wxvpF <file>\n");
}

int main(int argc, char **argv){
	char **commlist = NULL;
	int C;
	int LFcount = 0;
	int i;
	int j;
	FILE *IN;

	IN = fopen(argv[1],"r");
	fclose(IN);
	/*
	printf("prog:%s:\n",argv[1]);
	if(argv[1] != NULL){
		execvp(argv[1],argv+1);
	}else{
		help();
	}
	*/
	return(0);
}
