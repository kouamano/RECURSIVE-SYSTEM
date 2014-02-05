/* RNG.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/alloc.c"
#include "../include/data_read.c"
#define FILE_NAME_LEN 1024

struct options {
	int help;
	int stat;
	int check;
	char *dfile;
};

void help(void){
	printf("USAGE:\n");
	printf(" RNG [-h] [-s] [-c] df=<file of distance matrix> .\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  file of distance matrix : with no header.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" underconstruction.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).dfile = malloc(sizeof(char) * FILE_NAME_LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	//(*opt).argint = 0;
	(*opt).dfile[0] = '\0';
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
		}else if(strncmp(optv[i],"df=",3) == 0){
			sscanf(optv[i],"df=%s",(*opt).dfile);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.dfile:%s:\n",(*opt).dfile);
}

int main(int argc, char **argv){
	struct options *opt;
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	if((*opt).help == 1){
		help();
	}
	if((*opt).stat == 1){
		status();
	}
	if((*opt).check == 1){
		check_options(opt);
	}
	return(0);
}
