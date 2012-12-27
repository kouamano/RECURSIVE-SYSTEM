/* steping-similarity-table.c */

/* COPYRIGHT:    */
/* AMANO, Kou @  */
/* RIKEN BRC     */
/* NIAS AFF      */
/* UNIV. Tsukuba */

/* STRUCTURES:             */
/* struct options          */
/* struct path_similarity  */

/* PROCEDURES:            */
/* print_help()           */
/* init_options()         */
/* get_options()          */
/* print_options()        */
/* print_similarity_lit() */
/* write_similarity_lit() */
/* main()                 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "/home/pub/include/alloc.c"
#include "/home/pub/include/list_operations.c"
#include "/home/pub/include/data_read.c"
#include "hash.c"
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
#define FILE_NAME_LEN 256
#define TMP_STR_LEN_LONG 2050

struct options {
	char base_sim_file[FILE_NAME_LEN];
	char current_sim_file[FILE_NAME_LEN];
	char path_file[FILE_NAME_LEN];
	int number_of_nodes;
	int step;
	float threshold_low_level;
	float threshold_high_level;
	int max_inter_path;
	float def_sim;
	int read_symmetric;
	int help;
	int check;
};

struct path_similarity {
	int node_s;
	int node_e;
	float similarity;
};

void print_help(void){
	printf("USAGE:\n");
	printf("  steping-similarity-table bf=<base similarity file (read only)> cf=<current similarity file (for output)> pf=<path file (not available)> step=<step> [tl=<threshold lower level (re-write for current similarity)>] [th=<threshold higher level (for inter-path similarity)>] [n=<number of nodes>] [ds=<default similarity>] [mp=<max inter-path (not available)>] [-s](raed symmetrical) [-h|--help] [-c|--check]\n");
	printf("FORMAT:\n");
	printf("\n");
	printf("  base similarity file and current similarity file format:\n");
	printf("  001 001 0.2\n");
	printf("  001 002 0.3\n");
	printf("  001 003 0.1\n");
	printf("  ...\n");
	printf("\n");
	printf("  path file format:\n");
	printf("  001 001\n");
	printf("  001 002\n");
	printf("  001 004 008 003\n");
	printf("  001 004\n");
	printf("  001 002 005\n");
	printf("  ...\n");
	printf("\n");
}

void init_options(struct options *opt){
	(*opt).base_sim_file[0] = 0;
	(*opt).current_sim_file[0] = 0;
	(*opt).path_file[0] = 0;
	(*opt).number_of_nodes = 0;
	(*opt).step = 1;
	(*opt).threshold_low_level = 0.3;
	(*opt).threshold_high_level = 0.8;
	(*opt).max_inter_path = 20;
	(*opt).def_sim = 0;
	(*opt).read_symmetric = 0;
	(*opt).help = 0;
	(*opt).check = 0;
}

void get_options(int optc, char **optv, struct options *opt){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strncmp(optv[i],"bf=",3) == 0){
			sscanf(optv[i],"bf=%s",(*opt).base_sim_file);
		}else if(strncmp(optv[i],"cf=",3) == 0){
			sscanf(optv[i],"cf=%s",(*opt).current_sim_file);
		}else if(strncmp(optv[i],"pf=",3) == 0){
			sscanf(optv[i],"pf=%s",(*opt).path_file);
		}else if(strncmp(optv[i],"n=",2) == 0){
			sscanf(optv[i],"n=%d",&(*opt).number_of_nodes);
		}else if(strncmp(optv[i],"step=",5) == 0){
			sscanf(optv[i],"step=%d",&(*opt).step);
		}else if(strncmp(optv[i],"tl=",3) == 0){
			sscanf(optv[i],"tl=%f",&(*opt).threshold_low_level);
		}else if(strncmp(optv[i],"th=",3) == 0){
			sscanf(optv[i],"th=%f",&(*opt).threshold_high_level);
		}else if(strncmp(optv[i],"mp=",3) == 0){
			sscanf(optv[i],"mp=%d",&(*opt).max_inter_path);
		}else if(strncmp(optv[i],"ds=",3) == 0){
			sscanf(optv[i],"ds=%f",&(*opt).def_sim);
		}else if(strcmp(optv[i],"-s") == 0){
			(*opt).read_symmetric = 1;
		}else if(strcmp(optv[i],"--help") == 0){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-h") == 0){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"--check") == 0){
			(*opt).check = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check = 1;
		}else{
			fprintf(stderr,"[W] undefined option: %s",optv[i]);
		}
	}
}

void print_options(struct options opt){
	printf("OPTIONS:\n");
	printf("  base similarity file:%s:\n",opt.base_sim_file);
	printf("  current similarity file:%s:\n",opt.current_sim_file);
	printf("  path file:%s:\n",opt.path_file);
	printf("  number of nodes:%d:\n",opt.number_of_nodes);
	printf("  step:%d:\n",opt.step);
	printf("  threshold similarity lower level:%f:\n",opt.threshold_low_level);
	printf("  threshold similarity higher level:%f:\n",opt.threshold_high_level);
	printf("  max inter-path:%d:\n",opt.max_inter_path);
	printf("  default similarity:%f:\n",opt.def_sim);
	printf("  read symmetrically:%d:\n",opt.read_symmetric);
}

void print_similarity_list(int num, float **table, char *format, float def){
	int i;
	int j;
	if(strcmp(format,"Sparse") == 0){
		for(i=0;i<num;i++){
			for(j=0;j<num;j++){
				if(table[i][j] != def){
					printf("%06d %06d %f\n",i,j,table[i][j]);
				}
			}
		}
	}else if(strcmp(format,"All") == 0){
		for(i=0;i<num;i++){
			for(j=0;j<num;j++){
				printf("%06d %06d %f\n",i,j,table[i][j]);
			}
		}
	}
}

void write_similarity_list(FILE *OUT, int num, float **table, char *format, float def){
	int i;
	int j;
	if(strcmp(format,"Sparse") == 0){
		for(i=0;i<num;i++){
			for(j=0;j<num;j++){
				if(table[i][j] != def){
					fprintf(OUT,"%06d %06d %f\n",i,j,table[i][j]);
				}
			}
		}
	}else if(strcmp(format,"All") == 0){
		for(i=0;i<num;i++){
			for(j=0;j<num;j++){
				fprintf(OUT,"%06d %06d %f\n",i,j,table[i][j]);
			}
		}
	}
}

main(int argc, char **argv){
	/* (* main valiables */
	int i;
	int j;
	int x;
	char c;
	int q = 0;
	struct options opt;
	FILE *FP = NULL;
	char line[TMP_STR_LEN_LONG];
	int base_list_len = 0;
	//int current_list_len = 0;
	//float **base_similarity_matrix = NULL;
	float **current_similarity_matrix = NULL;
	/* *) */

	/* (* option analysis */
	init_options(&opt);
	get_options(argc-1,argv+1,&opt);
	if((opt.help == 1)||(argc < 2)){
		print_help();
		q++;
	}
	if(opt.check == 1){
		print_options(opt);
		q++;
	}
	if(q > 0){
		exit(0);
	}
	/* *) */

	/* (* read from file */
	if(opt.number_of_nodes < 2){
		fprintf(stderr,"[E] defined matrix size is too small for analysis.\n");
		exit(0);
	}
	/*
	base_similarity_matrix = f_alloc_mat(opt.number_of_nodes,opt.number_of_nodes);
	for(i=0;i<opt.number_of_nodes;i++){
		for(j=0;j<opt.number_of_nodes;j++){
			base_similarity_matrix[i][j] = opt.def_sim;
		}
	}
	FP = fopen(opt.base_sim_file,"r");
	read_similarity_table_from_stream(FP,base_similarity_matrix);
	fclose(FP);
	*/
	current_similarity_matrix = f_alloc_mat(opt.number_of_nodes,opt.number_of_nodes);
	for(i=0;i<opt.number_of_nodes;i++){
		for(j=0;j<opt.number_of_nodes;j++){
			current_similarity_matrix[i][j] = opt.def_sim;
		}
		current_similarity_matrix[i][i] = 1;
	}
	/*
	FP = fopen(opt.base_sim_file,"r");
	while((c = fgetc(FP)) != EOF){
		if(c == '\n'){
			current_list_len++;
		}
	}
	fclose(FP);
	*/
	FP = fopen(opt.base_sim_file,"r");
	if(opt.read_symmetric == 0){
		read_similarity_table_from_stream(FP,current_similarity_matrix);
	}else if(opt.read_symmetric == 1){
		read_symmetrical_similarity_table_from_stream(FP,current_similarity_matrix);
	}
	fclose(FP);
	//print_similarity_list(opt.number_of_nodes,base_similarity_matrix,"All",opt.def_sim);
	/* *) */

	/* (* calculate step-similarity */
	int rank = 2;
	int dim[rank];
	struct path_similarity *full_path_list;
	int full_path_list_len = 0;
	int step = 1;
	int *outer_dim;
	int *inter_path_nodes;
	int **candidate_inter_path_list = NULL;
	int candidate_inter_path_list_len = 0;
	int **outer_list = NULL;
	int outer_list_len = 0;
	int a = 0;
	int b = 0;
	int r = 0;
	for(r=0;r<opt.step;r++){
		/* (* decide candidate path */
		candidate_inter_path_list_len = 0;
		for(i=0;i<opt.number_of_nodes;i++){
			for(j=0;j<opt.number_of_nodes;j++){
				if((current_similarity_matrix[i][j] >= opt.threshold_high_level)&&(i != j)){
					candidate_inter_path_list_len++;
					//printf("%f\n",current_similarity_matrix[i][j]);
				}
			}
		}
		candidate_inter_path_list = i_alloc_mat(candidate_inter_path_list_len,rank);
		dim[0] = candidate_inter_path_list_len;
		dim[1] = candidate_inter_path_list_len;
		x = 0;
		for(i=0;i<opt.number_of_nodes;i++){
			for(j=0;j<opt.number_of_nodes;j++){
				if((current_similarity_matrix[i][j] >= opt.threshold_high_level)&&(i != j)){
					candidate_inter_path_list[x][0] = i;
					candidate_inter_path_list[x][1] = j;
					x++;
				}
			}
		}
		outer_list_len = candidate_inter_path_list_len*candidate_inter_path_list_len;
		outer_list = i_alloc_mat(outer_list_len,rank);
		create_outer_list(rank,dim,outer_list);
		/* *) */
		/* (* print candidate path */
		printf("----- candidate path:\n");
		for(i=0;i<candidate_inter_path_list_len;i++){
			printf("%d %d %f\n",candidate_inter_path_list[i][0],candidate_inter_path_list[i][1],current_similarity_matrix[candidate_inter_path_list[i][0]][candidate_inter_path_list[i][1]]);
		}
		printf("-----\n");
		/* *) */
		/* (* selection of legal path */
		printf("----- outer list:\n");
		full_path_list = malloc(sizeof(struct path_similarity)*(outer_list_len / 2));
		full_path_list_len = 0;
		for(i=0;i<outer_list_len;i++){
			for(j=0;j<rank;j++){
				printf("[%d] ",outer_list[i][j]);
				printf("%d %d ",candidate_inter_path_list[outer_list[i][j]][0],candidate_inter_path_list[outer_list[i][j]][1]);
			}
			if((candidate_inter_path_list[outer_list[i][0]][1] == candidate_inter_path_list[outer_list[i][1]][0])&&(candidate_inter_path_list[outer_list[i][0]][0] != candidate_inter_path_list[outer_list[i][1]][1])){
				full_path_list[full_path_list_len].node_s = candidate_inter_path_list[outer_list[i][0]][0];
				full_path_list[full_path_list_len].node_e = candidate_inter_path_list[outer_list[i][1]][1];
				full_path_list[full_path_list_len].similarity = current_similarity_matrix[candidate_inter_path_list[outer_list[i][0]][0]][candidate_inter_path_list[outer_list[i][0]][1]] * current_similarity_matrix[candidate_inter_path_list[outer_list[i][1]][0]][candidate_inter_path_list[outer_list[i][1]][1]];
				printf("=");
				printf(" %f",full_path_list[full_path_list_len].similarity);
				full_path_list_len++;
			}
			printf("\n");
		}
		printf("-----\n");
		printf("----- full path list:\n");
		for(i=0;i<full_path_list_len;i++){
			printf("%d %d %f\n",full_path_list[i].node_s,full_path_list[i].node_e,full_path_list[i].similarity);
		}
		printf("-----\n");
		/* *) */
		/* (* re-wirite matrix */
		printf("----- re-writed similarity:\n");
		for(i=0;i<opt.number_of_nodes;i++){
			for(j=0;j<opt.number_of_nodes;j++){
				if((current_similarity_matrix[i][j] <= opt.threshold_low_level)&&(i != j)){
					printf("(%d %d)",i,j);
					printf(" %f",current_similarity_matrix[i][j]);
					for(a=0;a<full_path_list_len;a++){
						if((i==full_path_list[a].node_s)&&(j==full_path_list[a].node_e)&&(current_similarity_matrix[i][j] < full_path_list[a].similarity)){
							printf(" -> %f",full_path_list[a].similarity);
							current_similarity_matrix[i][j] = full_path_list[a].similarity;
						}
					}
					printf("\n");
				}
			}
		}
		printf("-----\n");
		/* *) */
		/* (* free mem */
		free(candidate_inter_path_list);
		free(outer_list);
		free(full_path_list);
		/* *) */
	}
	/* *) */

	/* (* test */
	printf("----- final similarity matrix:\n");
	print_similarity_list(opt.number_of_nodes,current_similarity_matrix,"All",opt.def_sim);
	printf("-----\n");
	/* *) */

	/* (* write to file */
	if(strlen(opt.current_sim_file) > 0){
		FP = fopen(opt.current_sim_file,"w");
		write_similarity_list(FP,opt.number_of_nodes,current_similarity_matrix,"Sparse",opt.def_sim);
		fclose(FP);
	}
	/* *) */

	/* (* return */
	return(0);
	/* *) */
}
