#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n = 10;
int b = 0;
int c = 0;
int count = 0;

int main(int argc, char **argv){
	if(argc == 2){
		printf("USAGE:\n  insertLF <char> <n>.\n");
	}else if(argc == 3){
		sscanf(argv[1],"%c",&b);
		sscanf(argv[2],"%d",&n);
	}else{
		exit(0);
	}
	//printf("%c",b);
	n = n + 1;
	while((c = fgetc(stdin)) != EOF){
		if(c == b){
			count++;
		}
		if(count == n){
			printf("%c",'\n');
			printf("%c",c);
			count = 1;
		}else{
			printf("%c",c);
		}
	}
	return(0);
}
