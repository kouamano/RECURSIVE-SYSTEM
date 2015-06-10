/* quotCSVtoTSV.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024

struct options {
	int help;
	int stat;
	int check;
//	int argint;
//	char *argstr;
	char *fname;
};

void help(void){
	printf("USAGE:\n");
	printf("  quotCSVtoTSV [-h] [-s] [-c] if=<file>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  <file> : input file name (len < 1024).\n");
}

void status(void){
	printf("STATUS:\n");
	printf("  under construction.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).fname = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).fname[0] = '\0';
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
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",(*opt).fname);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.fname:%s:\n",(*opt).fname);
}

int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	FILE *in;
	int c = 0;
	int IN_COL = 0;
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

	if( (in = fopen((*opt).fname,"r")) == NULL ){
		perror((*opt).fname);
		exit(1);
	}
	IN_COL = 0;
	while((c = fgetc(in)) != EOF){
		if(c == '"'){
			if(IN_COL == 0){
				IN_COL = 1;
			}else{
				IN_COL = 0;
			}
		}
		if(c == ','){
			if(IN_COL == 0){
				putc('\t',stdout);
			}else{
				putc(c,stdout);
			}
		}else{
			putc(c,stdout);
		}
	}
	
	return(0);
}
