#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_GENE 4
#define SIZE_MRNA 4
#define SIZE_CDS 5
#define SIZE_JOIN 5
#define SIZE_COMPLEMENT 11
#define SIZE_NOTE 6

#define GENE "gene"
#define MRNA "mRNA"
#define CDS " CDS "
#define JOIN "join("
#define COMPLEMENT "complement("
#define NOTE "/note="

static int in_gene = 0;
static int in_note = 0;
static char *bf_GENE = NULL;
static char *bf_MRNA = NULL;
static char *bf_CDS = NULL;
static char *bf_join = NULL;
static char *bf_complement = NULL;
static char *bf_note = NULL;

int main(int argc, char **argv){
	int i = 0;
	signed char c;
	FILE *IN = NULL;
	bf_GENE = calloc(SIZE_GENE,sizeof(char));
	bf_MRNA = calloc(SIZE_MRNA,sizeof(char));
	bf_CDS = calloc(SIZE_CDS,sizeof(char));
	bf_join = calloc(SIZE_JOIN,sizeof(char));
	bf_complement = calloc(SIZE_COMPLEMENT,sizeof(char));
	bf_note = calloc(SIZE_NOTE,sizeof(char));
	//printf(NOTE);
	//exit(0);
	if(argc == 1){
		while((c = fgetc(stdin)) != EOF){
			/* (*allocate valiables */
			for(i=0;i<SIZE_NOTE-1;i++){
				*(bf_note+i) = *(bf_note+i+1);
			}
			*(bf_note+SIZE_NOTE-1) = c;
			*(bf_note+SIZE_NOTE) = 0;

			for(i=0;i<SIZE_COMPLEMENT-1;i++){
				*(bf_complement+i) = *(bf_complement+i+1);
			}
			*(bf_complement+SIZE_COMPLEMENT-1) = c;
			*(bf_complement+SIZE_COMPLEMENT) = 0;


			for(i=0;i<SIZE_JOIN-1;i++){
				*(bf_join+i) = *(bf_join+i+1);
			}
			*(bf_join+SIZE_JOIN-1) = c;
			*(bf_join+SIZE_JOIN) = 0;


			for(i=0;i<SIZE_CDS-1;i++){
				*(bf_CDS+i) = *(bf_CDS+i+1);
			}
			*(bf_CDS+SIZE_CDS-1) = c;
			*(bf_CDS+SIZE_CDS) = 0;


			for(i=0;i<SIZE_MRNA-1;i++){
				*(bf_MRNA+i) = *(bf_MRNA+i+1);
			}
			*(bf_CDS+SIZE_MRNA-1) = c;
			*(bf_CDS+SIZE_MRNA) = 0;

			for(i=0;i<SIZE_GENE-1;i++){
				*(bf_GENE+i) = *(bf_GENE+i+1);
			}
			*(bf_GENE+SIZE_GENE-1) = c;
			*(bf_GENE+SIZE_GENE) = 0;
			/* *) */
			/* (*check condition of gene */
			if(strcmp(bf_GENE,GENE) == 0){
				in_gene = 1;
				printf("\n");
			}
			if(strcmp(bf_MRNA,MRNA) == 0){
				in_gene = 0;
				printf("\n");
			}
			/* *) */
			/* (* check condition of note */
			if(strcmp(bf_note,NOTE) == 0){
				in_note = 1;
			}
			if((in_note == 1)&&(c == '"')){
				in_note = 2;
			}else if((in_note == 2)&&(c == '"')){
				in_note = 0;
				printf("\"");
			}
			/* *) */
			/* (* print */
			if((in_gene > 0)&&(in_note > 1)){
				//if(((48<=c)&&(c<=57))||c=='.'||c==','){
					printf("%c",c);
				//}
			}
			/* *) */
			/*
			printf(":%s::%s::%s::%d:\n",bf_CDS,bf_join,bf_complement,in_cds);
			*/
		}
		printf("\n");
	}else if(argc == 2){
		if((IN = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
		while((c = fgetc(IN)) != EOF){
			/* (*allocate valiables */
			for(i=0;i<SIZE_NOTE-1;i++){
				*(bf_note+i) = *(bf_note+i+1);
			}
			*(bf_note+SIZE_NOTE-1) = c;
			*(bf_note+SIZE_NOTE) = 0;

			for(i=0;i<SIZE_COMPLEMENT-1;i++){
				*(bf_complement+i) = *(bf_complement+i+1);
			}
			*(bf_complement+SIZE_COMPLEMENT-1) = c;
			*(bf_complement+SIZE_COMPLEMENT) = 0;


			for(i=0;i<SIZE_JOIN-1;i++){
				*(bf_join+i) = *(bf_join+i+1);
			}
			*(bf_join+SIZE_JOIN-1) = c;
			*(bf_join+SIZE_JOIN) = 0;


			for(i=0;i<SIZE_CDS-1;i++){
				*(bf_CDS+i) = *(bf_CDS+i+1);
			}
			*(bf_CDS+SIZE_CDS-1) = c;
			*(bf_CDS+SIZE_CDS) = 0;


			for(i=0;i<SIZE_MRNA-1;i++){
				*(bf_MRNA+i) = *(bf_MRNA+i+1);
			}
			*(bf_CDS+SIZE_MRNA-1) = c;
			*(bf_CDS+SIZE_MRNA) = 0;

			for(i=0;i<SIZE_GENE-1;i++){
				*(bf_GENE+i) = *(bf_GENE+i+1);
			}
			*(bf_GENE+SIZE_GENE-1) = c;
			*(bf_GENE+SIZE_GENE) = 0;
			/* *) */
			/* (*check condition of gene */
			if(strcmp(bf_GENE,GENE) == 0){
				in_gene = 1;
				printf("\n");
			}
			if(strcmp(bf_MRNA,MRNA) == 0){
				in_gene = 0;
				printf("\n");
			}
			/* *) */
			/* (* check condition of note */
			if(strcmp(bf_note,NOTE) == 0){
				in_note = 1;
			}
			if((in_note == 1)&&(c == '"')){
				in_note = 2;
			}else if((in_note == 2)&&(c == '"')){
				in_note = 0;
				printf("\"");
			}
			/* *) */
			/* (* print */
			if((in_gene > 0)&&(in_note > 1)){
				//if(((48<=c)&&(c<=57))||c=='.'||c==','){
					printf("%c",c);
				//}
			}
			/* *) */
			/*
			printf(":%s::%s::%s::%d:\n",bf_CDS,bf_join,bf_complement,in_cds);
			*/

		}
		fclose(IN);
		printf("\n");

	}
	return(0);
}
