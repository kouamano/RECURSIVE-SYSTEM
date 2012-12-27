#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_GENE 6
#define SIZE_COMPLEMENT 11
#define GENE ">gene<"
#define COMPLEMENT "complement("

static int in_gene = 0;
static int in_complement = 0;
static char *bf_gene = NULL;
static char *bf_complement = NULL;

int main(int argc, char **argv){
	int i = 0;
	signed char c;
	FILE *IN = NULL;
	bf_gene = calloc(SIZE_GENE,sizeof(char));
	bf_complement = calloc(SIZE_COMPLEMENT,sizeof(char));
	if(argc == 1){
		while((c = fgetc(stdin)) != EOF){
			for(i=0;i<SIZE_GENE-1;i++){
				*(bf_gene+i) = *(bf_gene+i+1);
			}
			*(bf_gene+SIZE_GENE-1) = c;
			*(bf_gene+SIZE_GENE) = 0;
			for(i=0;i<SIZE_COMPLEMENT-1;i++){
				*(bf_complement+i) = *(bf_complement+i+1);
			}
			*(bf_complement+SIZE_COMPLEMENT-1) = c;
			*(bf_complement+SIZE_COMPLEMENT) = 0;
			if(strcmp(bf_gene,GENE) == 0){
				in_gene = 1;
			}
			if((in_gene == 1)&&(strcmp(bf_complement,COMPLEMENT) == 0)&&(in_complement == 0)){
				printf("c;");
				in_complement = 1;
			}
			if((in_complement == 1)&&(c == ')')){
				in_complement = 0;
			}
			if((in_gene==1)&&(c=='\n')){
				printf("\n");
				in_gene = 0;
			}
			if(in_gene == 1){
				if(((48<=c)&&(c<=57))||(c=='.')||(c==',')){
					printf("%c",c);
				}
			}
			/*
			printf(":%s::%s::%s::%d:\n",bf_CDS,bf_join,bf_complement,in_cds);
			*/
		}
	}else if(argc == 2){
		if((IN = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
		while((c = fgetc(IN)) != EOF){
			for(i=0;i<SIZE_GENE-1;i++){
				*(bf_gene+i) = *(bf_gene+i+1);
			}
			*(bf_gene+SIZE_GENE-1) = c;
			*(bf_gene+SIZE_GENE) = 0;
			for(i=0;i<SIZE_COMPLEMENT-1;i++){
				*(bf_complement+i) = *(bf_complement+i+1);
			}
			*(bf_complement+SIZE_COMPLEMENT-1) = c;
			*(bf_complement+SIZE_COMPLEMENT) = 0;
			if(strcmp(bf_gene,GENE) == 0){
				in_gene = 1;
			}
			if((in_gene == 1)&&(strcmp(bf_complement,COMPLEMENT) == 0)&&(in_complement == 0)){
				printf("c;");
				in_complement = 1;
			}
			if((in_complement == 1)&&(c == ')')){
				in_complement = 0;
			}
			if((in_gene==1)&&(c=='\n')){
				printf("\n");
				in_gene = 0;
			}
			if(in_gene == 1){
				if(((48<=c)&&(c<=57))||(c=='.')||(c==',')){
					printf("%c",c);
				}
			}
			/*
			printf(":%s::%s::%s::%d:\n",bf_CDS,bf_join,bf_complement,in_cds);
			*/
		}

		fclose(IN);

	}
	return(0);
}
