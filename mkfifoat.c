#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#define LEN 1024

struct options {
	int help;
	int stat;
	int check;
	int argint;
	char *argstr;
};

void help(void){
	printf("USAGE:\n");
	printf(" mkfifoat [-h] [-s] [-c] int=<mode> str=<path>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  int : set mode.\n");
	printf("  str : target (len < 1024).\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Under construction.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).argstr = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).argint = 0;
	(*opt).argstr[0] = '\0';
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
		}else if(strncmp(optv[i],"int=",4) == 0){
			sscanf(optv[i],"int=%d",&(*opt).argint);
		}else if(strncmp(optv[i],"str=",4) == 0){
			sscanf(optv[i],"str=%s",(*opt).argstr);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.argint:%d:\n",(*opt).argint);
	printf(" opt.argstr:%s:\n",(*opt).argstr);
}

int main(int argc, char **argv){
	int fifostat = 0;
	struct options *opt;
	int ie = 0;
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

	//fifostat = mkfifo((*opt).argstr, 0666);
	fifostat = mkfifo((*opt).argstr, (*opt).argint);
	printf("stat:%d:\n",fifostat);

	return(0);
}
