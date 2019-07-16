#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_fill_str(int len, char *seed, char *head){
	int seed_len;
	int fill_len;
	int head_len;
	int i;
	seed_len = strlen(seed);
	fill_len = len - seed_len;
	head_len = strlen(head);
	for(i=0;i<fill_len;i++){
		printf("%c",head[i%head_len]);
	}
	printf("%s\n",seed);
	return(0);
}

void print_help(void){
	printf("fill the string with character.\n");
	printf("fill \"whole length\" \"character with which filled\" \"seed string\"\n");
}

int main(int argc, char **argv){
	int len;
	char head[128];
	char seed[128];
	char c;
	char tmp[128];
	int i;
	i = 0;
	if(argc == 3){
		sscanf(argv[1],"%d",&len);
		sscanf(argv[2],"%s",head);
		while(scanf("%c",&c) != EOF){
			if(c != '\n'){
				tmp[i] = c;
				i++;
			}else{
				tmp[i] = '\0';
				print_fill_str(len,tmp,head);
				i = 0;
			}
		}
	}else if(argc == 4){
		sscanf(argv[1],"%d",&len);
		sscanf(argv[2],"%s",head);
		sscanf(argv[3],"%s",seed);
		print_fill_str(len,seed,head);
	}else{
		print_help();
	}
	return(0);
}
