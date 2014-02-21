/* d_short.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024
#define MEM_BLK 1024
#include "../include/alloc.c"
#include "d_route.edgeop.h"
#include "d_route.edgeop.c"

struct options {
	int help;
	int stat;
	int check;
	int dsize;
	char *df;
	char *rf;
};

void help(void){
	printf("USAGE:\n");
	printf(" d_short [-h] [-s] [-c] dsize=<size of dsit matrix> df=<dist matrix> rf=<route list file> .\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  size of dist matrix : single integer .\n");
	printf("  dist matrix : not triangle .\n");
	printf("  route list : output of d_route .\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" under construction.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).df = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).rf = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).dsize = 1000;
	(*opt).df[0] = '\0';
	(*opt).rf[0] = '\0';
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
		}else if(strncmp(optv[i],"dsize=",6) == 0){
			sscanf(optv[i],"dsize=%d",&(*opt).dsize);

		}else if(strncmp(optv[i],"df=",3) == 0){
			sscanf(optv[i],"df=%s",(*opt).df);
		}else if(strncmp(optv[i],"rf=",3) == 0){
			sscanf(optv[i],"rf=%s",(*opt).rf);

		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.df:%s:\n",(*opt).df);
	printf(" opt.dsize:%d:\n",(*opt).dsize);
	printf(" opt.rf:%s:\n",(*opt).rf);
}

int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	FILE *fp;
	char *line;
	struct edge RNG_edge;
	int edge,num_RNG_edge = 0;
	int level,max_level;
	int cmp_path,num_path;
	int **path_list;
	int num_path_new = 0;
	int **path_list_new;
	int i,j;
	int c;
	int adding_num_path;
	int cmp_path_new = 0;

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

	


	return(0);
}
