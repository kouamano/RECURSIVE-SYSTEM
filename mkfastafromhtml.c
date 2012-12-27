#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	int c;
	if(argc == 1){
		while((c = fgetc(stdin)) != EOF){
			printf("%c",(char)c);
		}
	}
	return(0);
}
