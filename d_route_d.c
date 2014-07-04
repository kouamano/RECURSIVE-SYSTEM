/* d_route_d.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024
#define MEM_BLK 1024
#include "../include/alloc.c"
#include "../include/math_base.c"
#include "edgeop.h"
#include "edgeop.c"

struct route {
	int length;
	int route_start;
	int route_end;
	float dist_max;
};

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
	printf(" d_route_d [-h] [-s] [-c] dsize=<size of dsit matrix> ef=<edge list file> ; using struct edge .\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  size of dist matrix : single integer .\n");
	printf("  edge list : output of RNGd .\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" complete.\n");
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

		}else{
			printf("Unknown option : %s\n",optv[i]);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.df:%s:\n",(*opt).df);
	printf(" opt.dsize:%d:\n",(*opt).dsize);
	printf(" opt.ef:%s:\n",(*opt).ef);
}

float create_current_route_from_path_list(struct route *_c_route, int _len_p_list, int *_p_list, float **_d_tbl){
	int i;
	float max_v = -1;
	for(i=0;i<_len_p_list-1;i++){
		max_v = max(_d_tbl[_p_list[i]][_p_list[i+1]],max_v);
	}
	(*_c_route).length = _len_p_list;
	(*_c_route).route_start = _p_list[0];
	(*_c_route).route_end = _p_list[_len_p_list-1];
	(*_c_route).dist_max = max_v;
	return(max_v);
}

int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	FILE *fp;
	char *line;
	float **d_tbl;
	float tmp;
	struct edge_d RNG_edge_d;
	struct route *current_route;
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

	/* (* alloc route */
	if((current_route = malloc(sizeof(struct route) * 2)) == NULL){
		fprintf(stderr, "failed : malloc() for current_route.\n");
		exit(1);
	}
	(*current_route).length = 0;
	(*current_route).dist_max = -1;
	/* *) */

	/* (* alloc d_tbl */
	d_tbl = f_alloc_mat((*opt).dsize,(*opt).dsize);
	for(i=0;i<(*opt).dsize;i++){
		for(j=0;j<(*opt).dsize;j++){
			d_tbl[i][j] = -1;
		}
	}
	/* *) */
	
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
	//printf("#num_RNG_edge:%d:\n",num_RNG_edge);
	fseek(fp,0U,SEEK_SET);
	RNG_edge_d.p = i_alloc_vec(num_RNG_edge * 2);
	RNG_edge_d.t = i_alloc_vec(num_RNG_edge * 2);
	RNG_edge_d.d = f_alloc_vec(num_RNG_edge * 2);
	i = 0;
	while((fgets(line,LEN,fp)) != NULL){
		sscanf(line,"%d %d %f",RNG_edge_d.p+i,RNG_edge_d.t+i,RNG_edge_d.d+i);
		i++;
	}
	fclose(fp);
	/*  *) */

	/*  (* extend data */
	for(j=i;j<num_RNG_edge*2;j++){
		RNG_edge_d.t[j] = RNG_edge_d.p[j-num_RNG_edge];
		RNG_edge_d.p[j] = RNG_edge_d.t[j-num_RNG_edge];
		RNG_edge_d.d[j] = RNG_edge_d.d[j-num_RNG_edge];
	}
	/*   (* 
	printf("#RNG_edge both:\n");
	for(j=0;j<num_RNG_edge*2;j++){
		printf("%s %d,%d,%f\n","%",RNG_edge_d.p[j],RNG_edge_d.t[j],RNG_edge_d.d[j]);
	}
	     *) */
	/*  *) */
	/* *) */

	/* (* create d_tbl */
	for(j=0;j<num_RNG_edge*2;j++){
		d_tbl[RNG_edge_d.p[j]][RNG_edge_d.t[j]] = RNG_edge_d.d[j];
	}
	/* *) */
	/* (* print d_tbl 
	printf("#primer d_tbl:\n");
	for(i=0;i<(*opt).dsize;i++){
		printf("%c",'%');
		for(j=0;j<(*opt).dsize;j++){
			printf(" %f",d_tbl[i][j]);
		}
		printf("\n");
	}
	   *) */

	/* (* analyze path */
	/*  (* create first pathes level 1 */
	level = 1;
	num_path = (*opt).dsize;
	path_list = i_alloc_mat(num_path,level);
	for(i=0;i<num_path;i++){
		path_list[i][0] = i;
	}
	//printf("#path level %d:\n",level);
	/*
	for(i=0;i<num_path;i++){
		for(j=0;j<level;j++){
			printf("%d,",path_list[i][j]);
		}
		printf("*\n");
	}
	printf("#;\n");
	*/
	/*  *) */
	/*  (* extend path */
	max_level = (*opt).dsize;
	for(level=2;level<=max_level;level++){
		//printf("#path level %d:\n",level);
		adding_num_path = 0;
		/* (* count for malloc of path_list_new */
		for(cmp_path=0;cmp_path<num_path;cmp_path++){ /* comp to RNG edge */
			for(edge=0;edge<num_RNG_edge*2;edge++){
				//printf("%d vs %d\n",path_list[cmp_path][level-2],RNG_edge_d.p[edge]);
				if(path_list[cmp_path][level-2] == RNG_edge_d.p[edge]){
					//printf(" t:%d:\n",RNG_edge_d.t[edge]);
					if(if_match_int_sc_vec(RNG_edge_d.t[edge],path_list[cmp_path],level-2) == 0){
						/*
						for(j=0;j<level-1;j++){
							printf("%d,",path_list[cmp_path][j]);
						}
						*/
						//printf("%d-*\n",RNG_edge_d.t[edge]);
						adding_num_path++;
					}else{
						;
					}
				}
				/* check 
				for(i=0;i<num_path;i++){
					for(j=0;j<level-1;j++){
						printf("%d,",path_list[i][j]);
					}
					printf("* vs %d\n",RNG_edge_d.p[edge]);
				}
				*/
			}
		}
		/* *) */
		/* (* add */
		//printf("  add_path:%d:\n",adding_num_path);
		num_path_new = adding_num_path;
		path_list_new = i_alloc_mat(num_path_new,level);
		cmp_path_new = 0;
		for(cmp_path=0;cmp_path<num_path;cmp_path++){ /* comp to RNG edge */
			for(edge=0;edge<num_RNG_edge*2;edge++){
				if(path_list[cmp_path][level-2] == RNG_edge_d.p[edge]){
					//printf(" t:%d:\n",RNG_edge_d.t[edge]);
					if(if_match_int_sc_vec(RNG_edge_d.t[edge],path_list[cmp_path],level-2) == 0){
						for(j=0;j<level-1;j++){
							//printf("%d-",path_list[cmp_path][j]);
							path_list_new[cmp_path_new][j] = path_list[cmp_path][j];
							
						}
						//printf("%d-*\n",RNG_edge_d.t[edge]);
						path_list_new[cmp_path_new][level-1] = RNG_edge_d.t[edge];
						cmp_path_new++;
					}
				}
			}
		}
		/* *) */
		/* (* test: print cmp_path_new 
		printf("  path_list_new:\n");
		for(i=0;i<num_path_new;i++){
			for(j=0;j<level;j++){
				printf("%d,",path_list_new[i][j]);
			}
			printf("*\n");
		}
		printf("  :\n");
		*) */
		/* (* copy path_list_new to path_list */
		free(path_list[0]);
		free(path_list);
		num_path = num_path_new;
		path_list = i_alloc_mat(num_path,level);
		/* copy */
		for(i=0;i<num_path;i++){
			for(j=0;j<level;j++){
				path_list[i][j] = path_list_new[i][j];
			}
		}
		free(path_list_new[0]);
		free(path_list_new);
		/*  *) */
		/*  (* print preparation */
		for(i=0;i<num_path;i++){
			/*
			for(j=0;j<level;j++){
				printf("%d,",path_list[i][j]);
			}
			*/
			//printf("*\n");
			create_current_route_from_path_list(current_route,level,path_list[i],d_tbl);
			//printf("len:%d: ",(*current_route).length);
			//printf("S:%d: E:%d: dmax:%f: \n",(*current_route).route_start,(*current_route).route_end,(*current_route).dist_max);
			if(d_tbl[(*current_route).route_start][(*current_route).route_end] >= 0){
				d_tbl[(*current_route).route_start][(*current_route).route_end] = min(d_tbl[(*current_route).route_start][(*current_route).route_end],(*current_route).dist_max);
			}else{
				d_tbl[(*current_route).route_start][(*current_route).route_end] = (*current_route).dist_max;
			}
		}
		/*  *) */
		/* *) */
		//printf("#;\n");
	}
	/* *) */
	/* (* print d_tbl */
	for(i=0;i<(*opt).dsize;i++){
		d_tbl[i][i] = 0;
	}
	for(i=0;i<(*opt).dsize;i++){
		printf("%f",d_tbl[i][0]);
		for(j=1;j<(*opt).dsize;j++){
			printf(" %f",d_tbl[i][j]);
		}
		printf("\n");
	}
	/* *) */

	return(0);
}
