/* mk_temporary_d_short.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/alloc.c"
#define LEN 1024

#include "edgeop.h"

struct options {
	int help;
	int stat;
	int check;
	char *df;
	char *ef;
	int dsize;
};

void help(void){
	printf("USAGE:\n");
	printf(" template [-h] [-s] [-c] dsize=<mat size>  ef=<edge file with dist> \n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  mat size : integer.\n");
	printf("  edge file : list of node vs node and the distance, output of RNG_d .\n");
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
	(*opt).ef[0] = '\0';
	(*opt).dsize = 0;
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
	printf(" opt.ef:%s:\n",(*opt).ef);
	printf(" opt.dsize:%d:\n",(*opt).dsize);
}

int main(int argc, char **argv){
	struct options *opt;
	int ie=0;
	FILE *fp;
	char *line;
	int c;
	int num_RNG_edge = 0;
	struct edge RNG_edge;
	struct edge_table RNG_tbl;

	float **dmat;

	int i,j,k,count;
	int *tmp_i_vec;

	/* (* check options */
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
	/* *) */

	/* (* read RNG */
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
	for(j=i;j<num_RNG_edge*2;j++){
		RNG_edge.t[j] = RNG_edge.p[j-num_RNG_edge];
		RNG_edge.p[j] = RNG_edge.t[j-num_RNG_edge];
	}
	/* *) */
	/* (* create dmat (RNG_tbl) */
	//must be rewite
	tmp_i_vec = i_alloc_vec((*opt).dsize);
	RNG_tbl.size = i_alloc_vec((*opt).dsize);
	RNG_tbl.next_pos = pi_alloc_vec((*opt).dsize);
	RNG_tbl.next_pos_used = pi_alloc_vec((*opt).dsize);
	for(i=0;i<(*opt).dsize;i++){
		//printf("i:%d:\n",i);
		count = 0;
		for(j=0;j<num_RNG_edge*2;j++){
			//printf(" j:%d:\n",j);
			if(i == RNG_edge.p[j]){
				tmp_i_vec[count] = RNG_edge.t[j];
				count++;
			}
		}
		RNG_tbl.size[i] = count;
		RNG_tbl.next_pos[i] = i_alloc_vec(RNG_tbl.size[i]);
		//RNG_tbl.next_pos_used[i] = i_alloc_vec(RNG_tbl.size[i]);
		for(k=0;k<RNG_tbl.size[i];k++){
			RNG_tbl.next_pos[i][k] = tmp_i_vec[k];
		}
	}
	printf("RNG_tbl:\n");
	for(i=0;i<(*opt).dsize;i++){
		printf("[%d]",i);
		for(k=0;k<RNG_tbl.size[i];k++){
			printf(",%d",RNG_tbl.next_pos[i][k]);
		}
		printf("\n");
	}
	printf(":\n");
	/* *) */


	/* (* refine dmat */
	//for i in row
		//for j in row
			//for k in column
				//comp(dmat[i] dmat[j])
				//if dmat[i][k]!=0, dmat[j][k]!=0
				//add stack max(pair);
			//end for k
		//end for j
	//end for i
	/* *) */



	return(0);
}
