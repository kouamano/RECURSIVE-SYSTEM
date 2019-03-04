#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int print_CHAR(FILE *_IN, int *_LIST_LV, int *_DLM_ACC, int *_R_COUNT, int *_BRK_REMAIN, int WAR){
	int RC = 0;
	int C;
	int DLM_ACC = 1;
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
			(*_LIST_LV)++;
		}
		if(C == ')'){
			(*_LIST_LV)--;
		}
	
		if(C == '('){
			//printf("\n  :::R:::");
			//putchar(C);
			//if(ARG_COUNT == 0){
			(*_BRK_REMAIN)++;
			//}
			if(WAR > 0){ fprintf(stderr,"\n:::LV:%d:::DLM:%d::ARG:%d:::R:%d:::BRK:%d:::C:%c:::",*_LIST_LV,DLM_ACC,ARG_COUNT,*_R_COUNT,*_BRK_REMAIN,C); }
			if(WAR > 0){ fprintf(stderr,"\n  :::+R:::"); }
			(*_R_COUNT)++;
			RC = print_CHAR(_IN,_LIST_LV,_DLM_ACC,_R_COUNT,_BRK_REMAIN,WAR);
		}else if(C == ','){
			if(DLM_ACC <= 0){
				//putchar('(');
				if(WAR > 0){ fprintf(stderr,"\n:::LV:%d:::DLM:%d::ARG:%d:::R:%d:::BRK:%d:::C:%c:::",*_LIST_LV,DLM_ACC,ARG_COUNT,*_R_COUNT,*_BRK_REMAIN,C); }
				putchar(C);
			}else if(DLM_ACC > 0 && ARG_COUNT <= 1){
				if(WAR > 0){ fprintf(stderr,"\n:::LV:%d:::DLM:%d::ARG:%d:::R:%d:::BRK:%d:::C:%c:::",*_LIST_LV,DLM_ACC,ARG_COUNT,*_R_COUNT,*_BRK_REMAIN,C); }
				putchar('(');
				(*_BRK_REMAIN)--;
			}else{
				if(WAR > 0){ fprintf(stderr,"\n:::LV:%d:::DLM:%d::ARG:%d:::R:%d:::BRK:%d:::C:%c:::",*_LIST_LV,DLM_ACC,ARG_COUNT,*_R_COUNT,*_BRK_REMAIN,C); }
				putchar(C);
			}
		}else if(C == ')'){
			if(*_BRK_REMAIN > 0 && ARG_COUNT == 0){
			//if(*_BRK_REMAIN > 0){
				putchar('(');
				(*_BRK_REMAIN)--;
			}
			if(WAR > 0){ fprintf(stderr,"\n:::LV:%d:::DLM:%d::ARG:%d:::R:%d:::BRK:%d:::C:%c:::",*_LIST_LV,DLM_ACC,ARG_COUNT,*_R_COUNT,*_BRK_REMAIN,C); }
			putchar(C);
			if(WAR > 0){ fprintf(stderr,"\n  :::-R:::"); }
			(*_R_COUNT)--;
			return(C);
		}else if(C == '\n'){
			putchar(C);
			if(WAR > 0){ fprintf(stderr,"\n -EOL- :::LV:%d:::DLM:%d::ARG:%d:::R:%d:::BRK:%d:::C:%c:::",*_LIST_LV,DLM_ACC,ARG_COUNT,*_R_COUNT,*_BRK_REMAIN,C); }
			(*_R_COUNT) = 0;
			return(C);
		}else if(C == EOF){
			if(WAR > 0){ fprintf(stderr,"\n:::LV:%d:::DLM:%d::ARG:%d:::R:%d:::BRK:%d:::C:%c:::",*_LIST_LV,DLM_ACC,ARG_COUNT,*_R_COUNT,*_BRK_REMAIN,C); }
			(*_R_COUNT)--;
			return(C);
		}else{
			if(WAR > 0){ fprintf(stderr,"\n:::LV:%d:::DLM:%d::ARG:%d:::R:%d:::BRK:%d:::C:%c:::",*_LIST_LV,DLM_ACC,ARG_COUNT,*_R_COUNT,*_BRK_REMAIN,C); }
			putchar(C);
		}
	//return(C);
	}
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
	while(c != EOF){
	//while((c = fgetc(IN)) != EOF){
		c = print_CHAR(IN,&LIST_LV,&DLM_ACC,&R_COUNT,&BRK_REMAIN,(*opt).war);
	
	}

	// close file
	if(is_open > 0){
		fclose(IN);
	}

	// finish
	return(0);
}
