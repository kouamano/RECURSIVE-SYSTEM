#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "/home/pub/include/alloc.c"
#include "/home/pub/include/fasta.h"
#include "/home/pub/include/fasta.c"
#define LEN_FILE_NAME 1024
#define SEP '\n'

struct option {
	int status;
	char query_file[LEN_FILE_NAME];
	char base_file[LEN_FILE_NAME];
	int num_query;
	int num_base;
	int size_query;
	int size_head;
	int size_body;
	int upper;
};

void init_option(struct option *opt){
	opt->status = 0;
	opt->query_file[0] = '\0';
	opt->base_file[0] = '\0';
	opt->num_query = 1000;
	opt->num_base = 1000;
	opt->size_query = 10;
	opt->size_head = 128;
	opt->size_body = 10000;
	opt->upper = 1;
};

void print_option(struct option opt){
	printf("status :%d:\n",opt.status);
	printf("query file :%s:\n",opt.query_file);
	printf("base file :%s:\n",opt.base_file);
	printf("number of queries :%d:\n",opt.num_query);
	printf("number of bases :%d:\n",opt.num_base);
	printf("size of a query :%d:\n",opt.size_query);
	printf("size of a base head :%d:\n",opt.size_head);
	printf("size of a base body :%d:\n",opt.size_body);
	printf("to upper? :%d:\n",opt.upper);
	printf("with head? :%d:\n",opt.status&4);
};

int get_option(int optc, char **optv, struct option *opt){
	int i = 0;
	int s = opt->status;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			if((s&1) == 0){s = s + 1;}
		}else if(strcmp(optv[i],"--help") == 0){
			if((s&1) == 0){s = s + 1;}
		}else if(strcmp(optv[i],"-c") == 0){
			if((s&2) == 0){s = s + 2;}
		}else if(strcmp(optv[i],"--check") == 0){
			if((s&2) == 0){s = s + 2;}
		}else if(strcmp(optv[i],"-H") == 0){
			if((s&4) == 0){s = s + 4;}
		}else if(strcmp(optv[i],"--out-with-head") == 0){
			if((s&4) == 0){s = s + 4;}
		}else if(strcmp(optv[i],"+H") == 0){
			if((s&4) == 4){s = s - 4;}
		}else if(strcmp(optv[i],"--out-without-head") == 0){
			if((s&4) == 4){s = s - 4;}
		}else if(strcmp(optv[i],"-u") == 0){
			opt->upper = 1;
		}else if(strcmp(optv[i],"+u") == 0){
			opt->upper = 0;
		}else if(strncmp(optv[i],"qf=",3) == 0){
			sscanf(optv[i],"qf=%s",opt->query_file);
		}else if(strncmp(optv[i],"bf=",3) == 0){
			sscanf(optv[i],"bf=%s",opt->base_file);
		}else if(strncmp(optv[i],"qn=",3) == 0){
			sscanf(optv[i],"qn=%d",&opt->num_query);
		}else if(strncmp(optv[i],"qs=",3) == 0){
			sscanf(optv[i],"qs=%d",&opt->size_query);
		}else if(strncmp(optv[i],"bn=",3) == 0){
			sscanf(optv[i],"bn=%d",&opt->num_base);
		}else if(strncmp(optv[i],"hs=",3) == 0){
			sscanf(optv[i],"hs=%d",&opt->size_head);
		}else if(strncmp(optv[i],"bs=",3) == 0){
			sscanf(optv[i],"bs=%d",&opt->size_body);
		}else{
			fprintf(stderr,"[W]unknown option : %s\n",optv[i]);
		}
	}
	opt->status = s;
	return(s);
};

void print_help(){
	printf("USEAGE:\n");
	printf("  regionposition qf=<query file> bf=<base file> [qn=<max number of query>] [qs=<max query size>] [bn=<max number of base>] [hs=<max head size>] [bs=<max body size>] [-u|+u] [-H|+H] [-h] [-c]\n");
};

int main(int argc, char **argv){
	struct option opt;
	struct fasta *fst;
	char **query_arr;
	char *tmp_query;
	int num_query = 0;
	int len_query = 0;
	int len_base = 0;
	int len_scan = 0;
	FILE *IN;
	int h = 0;
	int i = 0;
	int j = 0;
	int cp = 0;
	int num_bases = 0;
	signed char c;
	/* (* option operation */
	init_option(&opt);
	get_option(argc-1,argv+1,&opt);
	if((opt.status&1) == 1){
		print_help();
	}
	if((opt.status&2) == 2){
		print_option(opt);
	}
	if(((opt.status&1) == 1)||((opt.status&2) == 2)){
		exit(0);
	}
	if(opt.query_file[0] == '\0'){
		fprintf(stderr,"[E]indicate query file.\n");
		exit(1);
	}
	if(opt.base_file[0] == '\0'){
		fprintf(stderr,"[E]indicate base file.\n");
		exit(1);
	}
	/* *) */
	/* (* allocations */
	query_arr = c_alloc_mat(opt.num_query,opt.size_query);
	tmp_query = c_alloc_vec(opt.size_query);
	tmp_query[0] = '\0';
	if((fst = malloc((size_t)sizeof(struct fasta)*opt.num_base)) == NULL){
		fprintf(stderr,"[E]failed : malloc().\n");
		exit(1);
	}
	for(i=0;i<opt.num_base;i++){
		if((fst[i].head = malloc((size_t)sizeof(char)*opt.size_head)) == NULL){
			fprintf(stderr,"[E]failed : malloc().\n");
			exit(1);
		}
		if((fst[i].body = malloc((size_t)sizeof(char)*opt.size_body)) == NULL){
			fprintf(stderr,"[E]failed : malloc().\n");
			exit(1);
		}
	}
	/* *) */
	/* (* open, read and close query file */
	IN = fopen(opt.query_file,"r");
	while((c = fgetc(IN)) != EOF){
		if(c != SEP){
			tmp_query[cp] = c;
			cp++;
		}else{
			tmp_query[cp] = '\0';
			strcpy(query_arr[num_query],tmp_query);
			num_query++;
			cp = 0;
		}
	}
	fclose(IN);
	/* *) */
	/* (* open, read and close base file */
	IN = fopen(opt.base_file,"r");
	num_bases = read_fastaArray_from_fp(IN,fst,opt.size_head,opt.size_body);
	fclose(IN);
	/* *) */
	/* (* test
		for(i=0;i<num_query;i++){
			printf("%s\n",query_arr[i]);
		}
		printf("%s\n",fst->body);
	*) */
	/* (* count and print */
	for(h=0;h<num_bases;h++){
		len_base = strlen(fst[h].body);
		if(opt.upper == 1){
			for(i=0;i<len_base;i++){
				c = toupper(fst[h].body[i]);
				fst[h].body[i] = c;
			}
		}
		for(i=0;i<num_query;i++){
			len_query = strlen(query_arr[i]);
			len_scan = len_base - len_query + 1;
			if((opt.status&4) == 4){
				printf("%s:%s ",fst[h].head,query_arr[i]);
			}
			for(j=0;j<len_scan;j++){
				if(strncmp(fst[h].body+j,query_arr[i],len_query) == 0){
					printf("%d ",j+1);
				}
			}
			printf("\n");
		}
	}
	/* *) */
	return(0);
}
