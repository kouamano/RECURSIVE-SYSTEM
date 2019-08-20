#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
	printf(":%s\n",argv[1]);
	//execv(argv[1],argv+2);
	execvp(argv[1],argv+1);
	return(0);
}
