#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv){
	FILE *IFP;
	int IFP_open = 0;
	//signed char c;
	int c;
	if(argc == 1){
		IFP = stdin;
	}else if(argc == 2){
		IFP = fopen(argv[1],"r");
		IFP_open++;
	}

	while((c = fgetc(IFP)) != EOF){
		if((char)c == '\n'){
			printf("%c",(char)c);
		}else{
			printf(":%02X:",c);
			//printf("<%02X>",c);
		}
	}

	if(IFP_open > 0){
		fclose(IFP);
	}
}
