#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_FILE 1024
/*
struct option {
	int status;
	char file[LEN_FILE];
};

int get_option(int optc, char **optv, struct option *opt){
	int s = 0;
	return(s);
};
*/
int main(int argc, char **argv){
	signed char c;
	unsigned int count = 0;
	FILE *IN;
	int in_head = 0;
	int in_seq = 0;
	if(argc == 1){
		IN = stdin;
	}else if(argc == 2){
		if((IN = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
	}
	while((c = fgetc(IN)) != EOF){
		if((in_head == 0)&&(in_seq == 0)){
			if(c == '>'){
				in_head = 1;
			}else{
				in_head = 0;
				in_seq = 1;
			}
		}else if((in_head == 1)&&(in_seq == 0)){
			if(c == '\n'){
				in_head = 0;
				in_seq = 1;
			}
		}else if((in_head == 0)&&(in_seq == 1)){
			if(c == '>'){
				fprintf(stderr,"warning: multiple fasta sequence found.\n");
				in_head = 1;
				in_seq = 0;
			}else if((65 <= (int)c)&&((int)c <=90)||(97 <= (int)c)&&((int)c <= 122)){
				count++;
				//printf("%c",c);
			}
		}else{
			fprintf(stderr,"system confusing: check file format.\n");
			exit(1);
		}
	}
	printf("%d\n",count);
	return(0);
}
