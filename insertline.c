#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FULL 70
#define LEN_TAB 8

void scan_print(int num_c){
	int i;
	char c;
	while(scanf("%c",&c) != EOF){
		i++;
		if(c == '\n'){
			i = 0;
		}else if(c == '\t'){
			i = i+8;
		}
		printf("%c",c);
		if(i >= num_c){
			printf("\n");
			i = 0;
		}
	}
}

int main(int argc, char **argv){
	int num;
	if(argc == 1){
		scan_print(50);
	}else if(argc == 2){
		sscanf(argv[1],"%d",&num);
		scan_print(num);
	}
	return(0);
}
