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
	struct edge_d RNG_edge_d;
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
	printf("num_RNG_edge:%d:\n",num_RNG_edge);
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
	for(i=0;i<num_RNG_edge;i++){
		printf("%d %d %f\n",RNG_edge_d.p[i],RNG_edge_d.t[i],RNG_edge_d.d[i]);
	}
	/* *) */

	/* (* create dmat (RNG_tbl) */
	//must be rewite
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
