#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024

struct option {
	int help;
	int check;
	char *in;
};

void init_option(struct option *opt){
	(*opt).help = 0;
	(*opt).check = 0;
	(*opt).in = malloc(sizeof(char) * LEN);
	if((*opt).in == NULL){
		printf("F:malloc@init_option\n");
		exit(1);
	}
	(*opt).in[0] = '\0';
}

void get_option(int optc, char **optv, struct option *opt){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check = 1;
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).in);
		}
	}
}

void help(void){
	printf("\n");
	printf("USAGE\n");
	printf(" code_to_str in=<file>\n");
}

/* Under construction */
int main(int argc, char **argv){
	int str[2];
	str[0] = 0x41;
	str[1] = 0x0;
	printf("%s\n",str);
}
