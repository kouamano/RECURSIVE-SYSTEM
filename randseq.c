#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define SHORT_STRLEN 82
#define PARAM_1 3
#define PARAM_2 4
#define PARAM_3 7 
#define PARAM_4 33
#define PARAM_5 44
#define PARAM_6 77

struct option {
	int help;
	int check;
	int length;
	int entry;
	int seed;
	int with_head;
	char *str_head;
	int with_number;
	char *str_coeff;
	char *str_power;
};

void print_help(void){
	printf("USAGE:\n");
	printf("  randseq -l<length> [-e<entries>] [-s<random seed>] [-H<head>|+H] [-n|+n] [-S<n0,n1,...n7>] [-N<number,power,constant>] [--help|-h] [--check|-c]\n");
	printf("DESCRIBE:\n");
	printf("  <length>:      length of random sequence(s).\n");
	printf("  <entry>:       entry of sequences.\n");
	printf("  <random seed>: seed for srand().\n");
	printf("  -H<head>:      FASTA annotation of each sequence (start at >).\n");
	printf("  -n:            append serial numbers to FASTA annotations.\n");
	printf("  -S<n0,...>:    coefficients of polynominal for generating next seed of sequence.\n");
	printf("  -N<power,...>: parameter for generating next seed of nucleotide.\n");
}

int init_option(struct option *opt){
	int s = 0;
	int init_seed = 0;
	srand(init_seed);
	opt->help = 0;
	opt->check = 0;
	opt->length = 1;
	opt->entry = 1;
	opt->seed = init_seed;
	opt->with_head = 1;
	if((opt->str_head = calloc(SHORT_STRLEN,sizeof(char))) ==  NULL){
		fprintf(stderr,"[E] failed: calloc() in init_option() -- return.\n");
		s = 1;
		return(s);
	}
	opt->with_number = 1;
	if((opt->str_coeff = calloc(SHORT_STRLEN,sizeof(char))) ==  NULL){
		fprintf(stderr,"[E] failed: calloc() in init_option() -- return.\n");
		s = 2;
		return(s);
	}
	sprintf(opt->str_coeff,"%s","33,1");
	if((opt->str_power = calloc(SHORT_STRLEN,sizeof(char))) ==  NULL){
		fprintf(stderr,"[E] failed: calloc() in init_option() -- return.\n");
		s = 2;
		return(s);
	}
	sprintf(opt->str_power,"%s","44,-1,77");
	return(s);
}

int get_option(struct option *opt, int optc, char **optv){
	int s = 0;
	int i;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"--help") == 0){
			opt->help = 1;
		}else if(strcmp(optv[i],"-h") == 0){
			opt->help = 1;
		}else if(strcmp(optv[i],"--check") == 0){
			opt->check = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			opt->check = 1;
		}else if(strncmp(optv[i],"-l",2) == 0){
			sscanf(optv[i],"-l%d",&opt->length);
		}else if(strncmp(optv[i],"-e",2) == 0){
			sscanf(optv[i],"-e%d",&opt->entry);
		}else if(strncmp(optv[i],"-s",2) == 0){
			sscanf(optv[i],"-s%d",&opt->seed);
		}else if(strncmp(optv[i],"-H",2) == 0){
			opt->with_head = 1;
			sscanf(optv[i],"-H%s",opt->str_head);
		}else if(strncmp(optv[i],"+H",2) == 0){
			opt->with_head = 0;
		}else if(strcmp(optv[i],"-n") == 0){
			opt->with_number = 1;
		}else if(strcmp(optv[i],"+n") == 0){
			opt->with_number = 0;
		}else if(strncmp(optv[i],"-S",2) == 0){
			sscanf(optv[i],"-S%s",opt->str_coeff);
		}else if(strncmp(optv[i],"-N",2) == 0){
			sscanf(optv[i],"-N%s",opt->str_power);
		}
	}
	return(s);
}

void print_option(struct option opt){
	printf("OPTIONS:\n");
	printf("  sequence length                  :%d:\n",opt.length);
	printf("  number of sequences              :%d:\n",opt.entry);
	printf("  random seed                      :%d:\n",opt.seed);
	printf("  with head                        :%d:\n",opt.with_head);
	printf("  head string                      :%s:\n",opt.str_head);
	printf("  with sequence number             :%d:\n",opt.with_head);
	printf("  polynominal coefficeient string  :%s:\n",opt.str_coeff);
	printf("  parameter string                 :%s:\n",opt.str_power);
}

int str_to_f_array(char *str, float *arr){
	int i=0;
	int j=0;
	int k=0;
	char tmp_word[SHORT_STRLEN];
	int len = strlen(str);
	for(i=0;i<len;i++){
		if(str[i] == ','){
			tmp_word[j] = '\0';
			sscanf(tmp_word,"%f",arr);
			k++;
			arr++;
			j = 0;
		}else{
			tmp_word[j] = str[i];
			j++;
		}
	}
	tmp_word[j] = '\0';
	sscanf(tmp_word,"%f",arr);
	k++;
	return(k);
}

int next_S(int I, int dim, float *arr){
	int i;
	int ret_I = I;
	double tmp_I = 0;
	for(i=0;i<dim;i++){
		tmp_I = tmp_I + pow(I,i)*arr[i];
	}
	ret_I = ((int)tmp_I%I);
	return(ret_I);
}

int print_nuc(int v){
	if((0 <= v) && (v < RAND_MAX/4)){
		printf("A");
	}else if((RAND_MAX/4 <= v) && (v < RAND_MAX/2)){
		printf("G");
	}else if((RAND_MAX/2 <= v) && (v < RAND_MAX/4*3)){
		printf("T");
	}else if((RAND_MAX/4*3 <= v) && (v < RAND_MAX)){
		printf("C");
	}
	return(0);
}

int print_seq(int l, int seed, float *array){
	int i;
	int _seed;
	//_seed = rand() / PARAM_5 + PARAM_6;
	_seed = rand() * pow(array[0],array[1]) + array[2];
	for(i=0;i<l;i++){
		//_seed = rand() / PARAM_5 + PARAM_6;
		_seed = rand() * pow(array[0],array[1]) + array[2];
		srand(_seed);
		print_nuc(rand());
	}
	return(0);
}

int main(int argc, char **argv){
	int i;
	int len = 1;       //opt.length
	int try = 1;       //opt.entry
	int seed_seed;     //opt.seed

	float *parr;       //opt.str_coeff
	int slen_parr = 0;
	int dim_parr = 1;

	float pow_par[4];    //opt.str_power
	int slen_pow_par = 0;
	int dim_pow_par = 1;

	struct option opt;
	int count = 0;
	init_option(&opt);
	get_option(&opt,argc-1,argv+1);
	if(opt.help == 1){
		print_help();
	}
	if(opt.check == 1){
		print_option(opt);
	}
	if((opt.help == 1)||(opt.check == 1)){
		exit(0);
	}
	len = opt.length;
	try = opt.entry;
	seed_seed = opt.seed;
	/* (* polynominal parameter setting */
	slen_parr = strlen(opt.str_coeff);
	for(i=0;i<slen_parr;i++){
		if(opt.str_coeff[i] == ','){
			dim_parr++;
		}
	}
	if(dim_parr < 2){
		fprintf(stderr,"[E]detected dimension < 2 -- exit.\n");
		exit(1);
	}
	if((parr = calloc(dim_parr+1,sizeof(float))) == NULL){
		fprintf(stderr,"[E]failed: calloc() in main -- exit.\n");
		exit(1);
	}
	str_to_f_array(opt.str_coeff,parr);
	/* *) */
	/* (* power parameter setting */
	slen_pow_par = strlen(opt.str_power);
	for(i=0;i<slen_pow_par;i++){
		if(opt.str_power[i] == ','){
			dim_pow_par++;
		}
	}
	if(dim_pow_par < 3){
		fprintf(stderr,"[E]detected number of power parameters < 3 -- exit.\n");
		exit(1);
	}
	str_to_f_array(opt.str_power,pow_par);
	/* *) */
	seed_seed = (seed_seed - time(0))/PARAM_6 * (rand()%PARAM_6);
	for(i=0;i<try;i++){
		srand(seed_seed);
		seed_seed = next_S(seed_seed,dim_parr,parr);
		if(opt.with_head == 1){
			printf(">");
			printf("%s",opt.str_head);
		}
		if(opt.with_number == 1){
			printf("%08d",count);
		}
		if((opt.with_head == 1)||(opt.with_number == 1)){
			printf("\n");
		}
		print_seq(len,seed_seed,pow_par);
		printf("\n");
		count++;
	}
	return(0);
}
