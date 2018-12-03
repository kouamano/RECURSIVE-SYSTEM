#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define LEN 1024
#define BUFF_LEN 1024
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif

struct options {
	int help;
	int stat;
	int check;
	int buff;
	int war;
	char *in;
};

void help(void){
	printf("USAGE:\n");
	printf(" cst [-h] [-s] [-c] buff=<size(int)> in=<input file> w=<print warnning>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  buff : set integer.\n");
	printf("  in : set *chars (len < 1024).\n");
	printf("  war : set integer.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Testing.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).in = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).buff = BUFF_LEN;
	(*opt).in[0] = '\0';
	(*opt).war = 0;
}

void get_options(int optc, char **optv, struct options *opt){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-s") == 0){
			(*opt).stat = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check = 1;
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff);
		}else if(strncmp(optv[i],"w=",2) == 0){
			sscanf(optv[i],"w=%d",&(*opt).war);
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).in);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.buff:%d:\n",(*opt).buff);
	printf(" opt.in:%s:\n",(*opt).in);
	printf(" opt.war:%d:\n",(*opt).war);
}

// function definition

int relay_CHAR(FILE *_IN, char *_HEAD_BUF, int WAR){
	int C;
	int DLM_ACC = 1;
	int LIST_LV = 0;
	int NEXT_COUNT = 0;
	int ARG_COUNT = 0;
	while(C = fgetc(_IN)){

		if(C == '['){
			DLM_ACC--;
		}
		if(C == ']'){
			DLM_ACC++;
		}
		if(C == ',' && DLM_ACC > 0){
			ARG_COUNT++;
		}
		if(C == '('){
			LIST_LV++;
		}
		if(C == ')'){
			LIST_LV--;
		}
	
		if(C == '('){
		//confirm current
		//alloc next
		}else if(C == ',' && DLM_ACC > 0){
		//confirm current
		//alloc arg
		}else if(C == ')'){
		//confirm current
		//close list
		}else if(C == '\n'){
		//clear list
		}else if(C == EOF){
		}else{
		//buffering
		}
	}
	return(C);
}


int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	FILE *IN;
	int is_open = 0;
	int c;
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	if(argc == 1){
		(*opt).help = 1;
	}
	if((*opt).help == 1){
		help();
		ie = 1;
	}
	if((*opt).stat == 1){
		status();
		ie = 1;
	}
	if((*opt).check == 1){
		check_options(opt);
		ie = 1;
	}
	if(ie == 1){
		exit(0);
	}

	// open file
	if((IN = fopen((*opt).in,"r")) == NULL){
		perror((*opt).in);
		exit(1);
	}
	is_open = 1;

	// main function
	c = 1;
	int DLM_ACC = 1;
	int R_COUNT = 0;
	int BRK_REMAIN = 0;
	int LIST_LV = 0;
	char *HEAD_BUF;
	struct List *top;
	while(c != EOF){
	//while((c = fgetc(IN)) != EOF){
		c = relay_CHAR(IN,HEAD_BUF,(*opt).war);
	
	}

	// close file
	if(is_open > 0){
		fclose(IN);
	}

	// finish
	return(0);
}
