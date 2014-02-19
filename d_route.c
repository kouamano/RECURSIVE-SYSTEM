/*d_route.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024
#define MEM_BLK 1024
#include "../include/alloc.c"


struct options {
	int help;
	int stat;
	int check;
	//int argint;
	int dsize;
	int psize;
	//char *argstr;
	char *df;
	char *pf;
};

void help(void){
	printf("USAGE:\n");
	printf(" d_route [-h] [-s] [-c] df=<dist matrix file> dsize=<size of dsit matrix> pf=<path list file> psize=<number of lines>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  dist matrix : not triangle .\n");
	printf("  size of dist matrix : single integer .\n");
	printf("  math list : output of RNG.\n");
	printf("  number of lines : number of lines of path list file.\n");
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
	if(((*p).pf = malloc(sizeof(char) * LEN)) == NULL){
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
	(*opt).psize = 1000;
	(*opt).df[0] = '\0';
	(*opt).pf[0] = '\0';
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
		}else if(strncmp(optv[i],"psize=",6) == 0){
			sscanf(optv[i],"psize=%d",&(*opt).psize);

		}else if(strncmp(optv[i],"df=",3) == 0){
			sscanf(optv[i],"df=%s",(*opt).df);
		}else if(strncmp(optv[i],"pf=",3) == 0){
			sscanf(optv[i],"pf=%s",(*opt).pf);

		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.df:%s:\n",(*opt).df);
	printf(" opt.dsize:%d:\n",(*opt).dsize);
	printf(" opt.pf:%s:\n",(*opt).pf);
	printf(" opt.psize:%d:\n",(*opt).psize);
}

/* (* RNG edge */
struct edge {
	int *p;
	int *t;
};

void add_route(int *v, int node);

void print_match_edge(int *r, int r_size, struct edge RNG_edge, int RNG_size){
	int i,j,k,l;
	int match = 0;
	int p_or_t; /* p->1, t->2 */
	for(j=0;j<RNG_size;j++){
		//if(r[r_size] == RNG_edge.p[j] || r[r_size] == RNG_edge.t[j]){
		p_or_t = 0;
		if(r[r_size] == RNG_edge.p[j]){
			p_or_t = 1;
		}else if(r[r_size] == RNG_edge.t[j]){
			p_or_t = 2;
		}else{
			p_or_t = 0;
		}
		if(p_or_t > 0){
			for(i=0;i<r_size-1;i++){
				if(r[i] != RNG_edge.p[j] && r[i] != RNG_edge.t[j]){
					for(l=0;l<r_size-1;l++){printf("%d,",r[l]);};
					if(p_or_t == 1){
					printf("%d",RNG_edge.p[j]);
					}else if(p_or_t == 2){
					printf("%d",RNG_edge.t[j]);
					}
				}
			}

		}
	}
}


void add_match_edge(int *r, int r_size, struct edge RNG_edge, int RNG_size){
	int i,j,k;
	int match = 0;
	for(j=0;j<RNG_size;j++){
		if(r[r_size] == RNG_edge.p[j] || r[r_size] == RNG_edge.t[j]){
			for(i=0;i<r_size-1;i++){
				if(r[i] != RNG_edge.p[j] && r[i] != RNG_edge.t[j]){
					printf("%d,%d",RNG_edge.p[j],RNG_edge.t[j]);
				}
			}

		}
	}
}

int **create_path_vec_ref(int start_node, struct edge RNG, int num_tuple, int *num){
	int **curr;
	int i,j;
	curr = i_alloc_mat(num_tuple,2);
	for(i=0;i<num_tuple;i++){
		curr[i][0] = RNG.p[i];
		curr[i][1] = RNG.t[i];
	}
	*num = i;
	return(curr);
}

int **create_path_vec_prime(int start_node, struct edge RNG, int num_tuple, int *num){
	int **curr;
	int i,j;
	int len = 0;
	curr = i_alloc_mat(num_tuple,2);
	for(i=0;i<num_tuple;i++){
		printf("s:%d,p:%d,t:%d\n",start_node,RNG.p[i],RNG.t[i]);
		if(start_node == RNG.p[i]){
			curr[len][0] = RNG.p[i];
			curr[len][1] = RNG.t[i];
			len++;
		}else if(start_node == RNG.t[i]){
			curr[len][0] = RNG.t[i];
			curr[len][1] = RNG.p[i];
			len++;
		}else{
			;
		}
	}
	*num = len;
	return(curr);
}

int **create_path_vec(int **prev, int num_tuple, int level){ /*return curr*/
	int **curr;
	int i,j;
	return(curr);
};
/* *) */

int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	FILE *fp;
	char *line;
	int num_RNG_edge = 0;
	struct edge RNG_edge;
	int i,j;
	int p_node,level,next_pos; /* < num_RNG_edge */
	int curr_level;
	int **d_route_prev;
	int **d_route_curr;
	int num_of_route = 0;

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

	RNG_edge.p = i_alloc_vec((*opt).psize);
	RNG_edge.t = i_alloc_vec((*opt).psize);
	line = c_calloc_vec(LEN);
	if((fp = fopen((*opt).pf,"r")) == NULL){
		perror((*opt).pf);
		exit(1);
	}
	num_RNG_edge = 0;
	while(fgets(line,LEN-1,fp) != NULL){
		sscanf(line,"%d,%d",RNG_edge.p+num_RNG_edge,RNG_edge.t+num_RNG_edge);
		num_RNG_edge++;
	}
	fclose(fp);
	/* (* check
	for(i=0;i<num_RNG_edge;i++){
		printf("%d,%d\n",RNG_edge.p[i],RNG_edge.t[i]);
	}
	*) */
	printf("dsize:%d:\n",(*opt).dsize);
	for(p_node=0;p_node<(*opt).dsize;p_node++){	
		printf("start node:%d:\n",p_node);
		printf("num_RNG_edge:%d:\n",num_RNG_edge);
		curr_level = 1;
		d_route_curr = create_path_vec_prime(p_node,RNG_edge,num_RNG_edge,&num_of_route);
		printf("num_of_route:%d:\n",num_of_route);
		/* (* check */
		for(i=0;i<num_of_route;i++){
			for(j=0;j<=curr_level;j++){
				printf("%d,",d_route_curr[i][j]);
			}
			printf("\n");
		}
		/* *) */
		for(level=curr_level;level<num_RNG_edge;level++){
			d_route_curr = create_path_vec(d_route_prev, num_RNG_edge/*???*/, curr_level);
		}
		curr_level++;
	}

	return(0);
}
