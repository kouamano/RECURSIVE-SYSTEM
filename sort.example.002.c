#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PROG_NAME "hexsort"

typedef struct{
	char *file;
	int key_pos;
	int max_col;
}OPT;

void help(){
	printf("PROGRAM: %s",PROG_NAME);
	printf("USAGE: %s if=<file> k=<key pos> col=<max num of column>\n",PROG_NAME);
}

int main(int argc, char **argv){
	return(0);
}
