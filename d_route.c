/*d_route.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024
#define MEM_BLK 1024
#include "../include/alloc.c"
#include "d_route.edgeop.h"


struct options {
	int help;
	int stat;
	int check;
	//int argint;
	int dsize;
	//int psize;
	//char *argstr;
	char *df;
	char *ef;
};

void help(void){
	printf("USAGE:\n");
	printf(" d_route [-h] [-s] [-c] df=<dist matrix file> dsize=<size of dsit matrix> ef=<edge list file> .\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  dist matrix : not triangle .\n");
	printf("  size of dist matrix : single integer .\n");
	printf("  edge list : output of RNG.\n");
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
	if(((*p).ef = malloc(sizeof(char) * LEN)) == NULL){
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
	//(*opt).psize = 1000;
	(*opt).df[0] = '\0';
	(*opt).ef[0] = '\0';
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
		}else if(strncmp(optv[i],"ef=",3) == 0){
			sscanf(optv[i],"ef=%s",(*opt).ef);

		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.df:%s:\n",(*opt).df);
	printf(" opt.dsize:%d:\n",(*opt).dsize);
	printf(" opt.ef:%s:\n",(*opt).ef);
}

int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	FILE *fp;
	char *line;
	struct edge RNG_edge;
	int level,N;
	int cmp_path,num_path;
	int edge,num_RNG_edge = 0;
	int **path_list;
	int i,j;
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
	
	/* (* read RNG edge from ef */
	/*  (* raed */
	line = c_alloc_vec(LEN);
	if((fp = fopen((*opt).ef,"r")) == NULL){
		perror((*opt).ef);
		exit(1);
	}
	num_RNG_edge = 0;
	while((c=fgetc(fp)) != EOF){
		if((char)c == '\n'){
			num_RNG_edge++;
		}
	}
	printf("num_RNG_edge:%d:\n",num_RNG_edge);
	fseek(fp,0U,SEEK_SET);
	RNG_edge.p = i_alloc_vec(num_RNG_edge * 2);
	RNG_edge.t = i_alloc_vec(num_RNG_edge * 2);
	i = 0;
	while((fgets(line,LEN,fp)) != NULL){
		sscanf(line,"%d,%d",RNG_edge.p+i,RNG_edge.t+i);
		i++;
	}
	fclose(fp);
	/*  *) */
	/*  (* extend data */
	for(j=i;j<num_RNG_edge*2;j++){
		RNG_edge.t[j] = RNG_edge.p[j-num_RNG_edge];
		RNG_edge.p[j] = RNG_edge.t[j-num_RNG_edge];
	}
	printf("RNG_edge both:\n");
	for(j=0;j<num_RNG_edge*2;j++){
		printf("%d,%d\n",RNG_edge.p[j],RNG_edge.t[j]);
	}
	printf(":\n");
	/*  *) */
	/* *) */

	/* (* analyze path */
	/*  (* create first pathes level 1 */
	level = 1;
	num_path = (*opt).dsize;
	path_list = i_alloc_mat(num_path,level);
	for(i=0;i<num_path;i++){
		path_list[i][0] = i;
	}
	/*  *) */
	/*  (* extend path */
	for(level=2;level<=N;level++){
		/* TODO : count num_path */
		for(cmp_path=0;cmp_path<num_path;cmp_path++){ /* comp to RNG edge */
			for(edge=0;edge<num_RNG_edge*2;edge++){
			}
		}
		/* TODO : allocation */
		/* TODO : extend path */
		for(cmp_path=0;cmp_path<num_path;cmp_path++){ /* comp to RNG edge */
			for(edge=0;edge<num_RNG_edge*2;edge++){
			}
		}
		/*TODO : free path_list at level-1 */
	}
	/*  *) */
	/* *) */


	return(0);
}
