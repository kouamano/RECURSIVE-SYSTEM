#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
	printf("prog:%s:\n",argv[1]);
	//execv(argv[1],argv+2);
	if(argv[1] != NULL){
		execvp(argv[1],argv+1);
	}
	return(0);
}
