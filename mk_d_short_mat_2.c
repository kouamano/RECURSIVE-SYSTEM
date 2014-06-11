/* mk_d_short_mat.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/alloc.c"
#include "../include/math_base.c"
#define LEN 1024

#include "edgeop.h"

struct options {
	int help;
	int stat;
	int check;
	int diag;
	int loop;
	char *df;
	char *ef;
	int dsize;
};

void help(void){
	printf("USAGE:\n");
	printf(" mk_d_short_mat [-h] [-s] [-c] [-d] loop=<max loop> dsize=<mat size>  ef=<edge file with dist> \n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  -d : rewrite diagonal -> -1 .\n");
	printf("  max loop : integer.\n");
	printf("  mat size : integer.\n");
	printf("  edge file : list of node vs node and the distance, output of RNG_d .\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" check algorithm : diag; condition of rewrite dist .\n");
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
	(*opt).diag = 0;
	(*opt).ef[0] = '\0';
	(*opt).dsize = 0;
	(*opt).loop = 0;
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
		}else if(strcmp(optv[i],"-d") == 0){
			(*opt).diag = 1;
		}else if(strncmp(optv[i],"dsize=",6) == 0){
			sscanf(optv[i],"dsize=%d",&(*opt).dsize);
		}else if(strncmp(optv[i],"loop=",5) == 0){
			sscanf(optv[i],"loop=%d",&(*opt).loop);
		//}else if(strncmp(optv[i],"df=",3) == 0){
			//sscanf(optv[i],"df=%s",(*opt).df);
		}else if(strncmp(optv[i],"ef=",3) == 0){
			sscanf(optv[i],"ef=%s",(*opt).ef);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	//printf(" opt.df:%s:\n",(*opt).df);
	printf(" opt.diag:%d:\n",(*opt).diag);
	printf(" opt.ef:%s:\n",(*opt).ef);
	printf(" opt.dsize:%d:\n",(*opt).dsize);
	printf(" opt.loop:%d:\n",(*opt).loop);
}

int main(int argc, char **argv){
	struct options *opt;
	int ie=0;
	FILE *fp;
	char *line;
	int c;
	int num_RNG_edge = 0;
	struct edge_d RNG_edge_d;
	//struct edge_table RNG_tbl;

	//float **dmat;
	float **RNG_d_tbl;
	float *min_stack;
	int min_stack_len;
	float maxmin = 0;

	int i,j,k,l;

	/* (* check options */
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	if((*opt).loop == 0){
		(*opt).loop = (*opt).dsize;
	}
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
	/* *) */

	/* (* read RNG_d */
	//must be rewrite
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
	//printf("num_RNG_edge:%d:\n",num_RNG_edge);
	fseek(fp,0U,SEEK_SET);
	RNG_edge_d.p = i_alloc_vec(num_RNG_edge);
	RNG_edge_d.t = i_alloc_vec(num_RNG_edge);
	RNG_edge_d.d = f_alloc_vec(num_RNG_edge);
	i = 0;
	while((fgets(line,LEN,fp)) != NULL){
		sscanf(line,"%d %d %f",RNG_edge_d.p+i,RNG_edge_d.t+i,RNG_edge_d.d+i);
	i++;
	}
	fclose(fp);
	//check
	/*
	for(i=0;i<num_RNG_edge;i++){
		printf("%d %d %f\n",RNG_edge_d.p[i],RNG_edge_d.t[i],RNG_edge_d.d[i]);
	}
	*/
	/* *) */

	/* (* create RNG_d_tbl */
	//must be rewite
	RNG_d_tbl = f_calloc_mat((*opt).dsize,(*opt).dsize);
	for(i=0;i<(*opt).dsize;i++){
		for(j=0;j<(*opt).dsize;j++){
			RNG_d_tbl[i][j] = -1;
		}
	}
	for(i=0;i<num_RNG_edge;i++){
		RNG_d_tbl[RNG_edge_d.p[i]][RNG_edge_d.t[i]] = RNG_edge_d.d[i];
		RNG_d_tbl[RNG_edge_d.t[i]][RNG_edge_d.p[i]] = RNG_edge_d.d[i];
	}
	//check
	/*
	printf("dsize:%d:\n",(*opt).dsize);
	for(i=0;i<(*opt).dsize;i++){
		for(j=0;j<(*opt).dsize;j++){
			printf(" %f",RNG_d_tbl[i][j]);
		}
		printf("\n");
	}
	*/
	/* *) */


	/* (* refine RNG_d_tbl */
	min_stack = f_alloc_vec((*opt).dsize + 1);
	//for l in loop
	for(l=0;l<(*opt).loop;l++){
		//for i in row
		for(i=0;i<(*opt).dsize;i++){
			//for j in row
			for(j=0;j<(*opt).dsize;j++){
				//for k in column
				//min_stack_len = 0;
				maxmin = 0;
				min_stack_len = 0;
				for(k=0;k<(*opt).dsize;k++){
					//comp(dmat[i] dmat[j])
					//if dmat[i][k]!=0, dmat[j][k]!=0
					//if((RNG_d_tbl[i][k] != -1) && (RNG_d_tbl[j][k] != -1)){
					if((RNG_d_tbl[i][k] >= 0) && (RNG_d_tbl[j][k] >= 0)){
						//add max(pair) to min_stack; nim_stack_len++;
						min_stack[min_stack_len] = max(RNG_d_tbl[i][k],RNG_d_tbl[j][k]);
						min_stack_len++;
					}
				//end for k
				}
				//min of nim_stack
				if(RNG_d_tbl[i][j] >= 0){
					min_stack[min_stack_len] = RNG_d_tbl[i][j];
					min_stack_len++;
				}
				maxmin = f_min_list(min_stack_len,min_stack); // ?? can rewrite maxmin ??
				if((*opt).diag==1 && i==j){ maxmin = -1; } // ?? needs ??
				//printf("maxmin:%f:\n",maxmin);
				//rewrite RNG_d_tbl[i][j] <- nim(nin_stack);
				if(min_stack_len > 0){
					RNG_d_tbl[i][j] = maxmin;
				}
			//end for j
			}
		//end for i
		}
	//end for l
	}
	/* *) */

	/* (* print results */
	//printf("result after %d times loop:\n",l);
	for(i=0;i<(*opt).dsize;i++){
		printf("%f",RNG_d_tbl[i][0]);
		for(j=1;j<(*opt).dsize;j++){
			printf(" %f",RNG_d_tbl[i][j]);
		}
		printf("\n");
	}
	/* *) */

	return(0);
}
