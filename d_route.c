/*d_route.c*/
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
	printf("path level %d:\n",level);
	for(i=0;i<num_path;i++){
		for(j=0;j<level;j++){
			printf("%d-",path_list[i][j]);
		}
		printf("*\n");
	}
	printf(":\n");
	/*  *) */
	/*  (* extend path */
	max_level = (*opt).dsize;
	for(level=2;level<=max_level;level++){
		printf("path level %d:\n",level);
		/* current level : to be made */
		/* TODO : count num_path */
		/* comp_node : path_list[cmp_path][level-2] */
		//path_list_new = i_calloc_mat(MEM_BLK,level);
		//num_path_new = 0;
		adding_num_path = 0;
		/* (* count */
		for(cmp_path=0;cmp_path<num_path;cmp_path++){ /* comp to RNG edge */
			for(edge=0;edge<num_RNG_edge*2;edge++){
				printf("%d vs %d\n",path_list[cmp_path][level-2],RNG_edge.p[edge]);
				/* if path_list[][] == RNG_edge.p[] ; comp RNG_edge.t[] != path_list[][0:level-2] then ; add */
				if(path_list[cmp_path][level-2] == RNG_edge.p[edge]){
					printf(" t:%d:\n",RNG_edge.t[edge]);
					if(if_match_int_sc_vec(RNG_edge.t[edge],path_list[cmp_path],level-2) == 0){
						//for(i=0;i<num_path;i++){
						for(j=0;j<level-1;j++){
							printf("%d-",path_list[cmp_path][j]);
							
						}
						//}
						printf("%d-*\n",RNG_edge.t[edge]);
						adding_num_path++;
					}
				}
				/* check 
				for(i=0;i<num_path;i++){
					for(j=0;j<level-1;j++){
						printf("%d-",path_list[i][j]);
					}
					printf("* vs %d\n",RNG_edge.p[edge]);
				}
				*/
			}
		}
		/* *) */
		/* (* add */
		printf("  add_path:%d:\n",adding_num_path);
		num_path_new = adding_num_path;
		path_list_new = i_alloc_mat(num_path_new,level);
		/* TODO : extend path at level from level-1 OK */
		cmp_path_new = 0;
		for(cmp_path=0;cmp_path<num_path;cmp_path++){ /* comp to RNG edge */
			for(edge=0;edge<num_RNG_edge*2;edge++){
				if(path_list[cmp_path][level-2] == RNG_edge.p[edge]){
					printf(" t:%d:\n",RNG_edge.t[edge]);
					if(if_match_int_sc_vec(RNG_edge.t[edge],path_list[cmp_path],level-2) == 0){
						//for(i=0;i<num_path;i++){
						for(j=0;j<level-1;j++){
							printf("%d-",path_list[cmp_path][j]);
							path_list_new[cmp_path_new][j] = path_list[cmp_path][j];
							
						}
						//}
						printf("%d-*\n",RNG_edge.t[edge]);
						path_list_new[cmp_path_new][level-1] = RNG_edge.t[edge];
						cmp_path_new++;
						//adding_num_path++;
					}
				}

			}
		}
		/* *) */
		/* (* print cmp_path_new <NEED> */
		printf("  path_list_new:\n");
		for(i=0;i<num_path_new;i++){
			for(j=0;j<level;j++){
				printf("%d-",path_list_new[i][j]);
			}
			printf("*\n");
		}
		printf("  :\n");
		/* *) */
		/* (* copy */
		/*TODO : free path_list at level-1 */
		/* *) */
		printf(":\n",level);
	}
	/*  *) */
	/* *) */

	return(0);
}
