#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void help(void){
	printf("USAGE:\n");
	printf("  wxvp <program> <arg1> <arg2> ...\n");
}

int main(int argc, char **argv){
	printf("prog:%s:\n",argv[1]);
	if(argv[1] != NULL){
		execvp(argv[1],argv+1);
	}else{
		help();
	}
	return(0);
}
