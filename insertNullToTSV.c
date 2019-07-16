#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DLM '\t'
int main(int argc, char **argv){
	FILE *IN;
	char c = '\0';
	char p = '\0';
	if(argc == 1){
		scanf("%c",&c);
		if(c == DLM){
			printf("Null");
		}
		printf("%c",c);
		p = c;
		while(scanf("%c",&c) != EOF){
			if((p == '\n')&&(c == DLM)){
				printf("Null");
				printf("%c",c);
			}else if((p == DLM)&&(c == DLM)){
				printf("Null");
				printf("%c",c);
			}else if((p == DLM)&&(c == '\n')){
				printf("Null");
				printf("%c",c);
			}else{
				printf("%c",c);
			}
			p = c;
		}
	}else if(argc == 2){
		if((IN = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
		c = fgetc(IN);
		if(c == DLM){
			printf("Null");
		}
		printf("%c",c);
		p = c;
		while((c = fgetc(IN)) != EOF){
			if((p == '\n')&&(c == DLM)){
				printf("Null");
				printf("%c",c);
			}else if((p == DLM)&&(c == DLM)){
				printf("Null");
				printf("%c",c);
			}else if((p == DLM)&&(c == '\n')){
				printf("Null");
				printf("%c",c);
			}else{
				printf("%c",c);
			}
			p = c;
		}
		fclose(IN);
	}else{
		printf("argc expected 1 or 2.\n");
		exit(1);
	}
	return(0);
}
