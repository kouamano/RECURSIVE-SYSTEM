#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_FILE 1024

int main(int argc, char **argv){
	int c = 0;
	char file[LEN_FILE]; file[0] = '\0';
	FILE *IN;
	int in_head = 0;
	int in_seq = 0;
	int count = 0;
	if(argc == 1){
		IN = stdin;
	}else if(argc == 2){
		if((IN = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
	}
	while((c = fgetc(IN)) != EOF){
		//printf("[%d:%d]",in_head,in_seq);
		//printf("%c",c);
		if((in_head == 0)&&(in_seq == 0)){
			if(c == '>'){
				in_head = 1;
			}
		}else if((in_head == 0)&&(in_seq > 0)){
			if(c == '>'){
				in_head = 1;
				in_seq = 0;	
				printf("\n%d\n",count);
				count = 0;
			}else if((65 <= (int)c)&&((int)c <=90)||(97 <= (int)c)&&((int)c <= 122)){
				in_seq++;
				count++;
			}
		}else if((in_head > 0)&&(in_seq == 0)){
			if(in_head == 1){
				printf(">");
			}
			if(c == '\n'){
				in_head = 0;
				in_seq = 1;
			}else{
				in_head++;
				printf("%c",c);
			}
		}else if((in_head > 0)&&(in_seq > 0)){
			fprintf(stderr,"[W]\n");
		}
	}
	printf("\n%d\n",count);
	return(0);
}
