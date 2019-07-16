#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define PARAM_1 33
#define PARAM_2 7
#define PARAM_3 3
#define PARAM_4 44
#define PARAM_5 77
#define PARAM_6 4

void print_help(void){
	printf("randseq <length> [<entries>] [<random seed>] [<format>]\n");
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

int print_seq(int l, int seed){
	int i;
	int _seed;
	_seed = seed;
	_seed = rand() / PARAM_1 + PARAM_2;
	for(i=0;i<l;i++){
		_seed = rand() / PARAM_1 + PARAM_2;
		srand(_seed);
		//printf("%d:",rand());
		print_nuc(rand());
		//printf(" ");
	}
	return(0);
}

int main(int argc, char **argv){
	int i;
	int len = 1;
	int try = 1;
	int seed_seed;
	if(argc == 2){
		if(strcmp(argv[1],"-h") == 0){
			print_help();
			exit(0);
		}
		sscanf(argv[1],"%d",&len);
	}else if(argc == 3){
		sscanf(argv[1],"%d",&len);
		sscanf(argv[2],"%d",&try);
	}else if(argc == 4){
		sscanf(argv[1],"%d",&len);
		sscanf(argv[2],"%d",&try);
		sscanf(argv[3],"%d",&seed_seed);
	}
	seed_seed = (seed_seed - time(0))/PARAM_6 * (rand()%PARAM_6);
	for(i=0;i<try;i++){
		srand(seed_seed);
		seed_seed = (seed_seed - i*PARAM_4)/PARAM_6 * (rand()%PARAM_6);
		print_seq(len,seed_seed);
		printf("\n");
	}
	return(0);
}
