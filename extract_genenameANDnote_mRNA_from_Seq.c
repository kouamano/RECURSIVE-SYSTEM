#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_GENE 6
#define SIZE_MRNA 6
#define SIZE_CDS 5
#define SIZE_genename 6
#define SIZE_note 6

#define GENE " gene "
#define MRNA " mRNA "
#define CDS " CDS "
#define genename "/gene="
#define note "/note="

static char *bf_GENE = NULL;
static char *bf_mRNA = NULL;
static char *bf_CDS = NULL;
static char *bf_genename = NULL;
static char *bf_note = NULL;

static int in_mRNA = 0;
static int in_genename = 0;
static int in_note = 0;

int main(int argc, char **argv){
	int i = 0;
	signed char c;
	FILE *IN = NULL;
	bf_GENE = calloc(SIZE_GENE+1,sizeof(char));
	bf_mRNA = calloc(SIZE_MRNA+1,sizeof(char));
	bf_CDS = calloc(SIZE_CDS+1,sizeof(char));
	bf_genename = calloc(SIZE_genename+1,sizeof(char));
	bf_note = calloc(SIZE_note+1,sizeof(char));
	if(argc == 1){
		while((c = fgetc(stdin)) != EOF){
			for(i=0;i<SIZE_GENE-1;i++){
				*(bf_GENE+i) = *(bf_GENE+i+1);
			}
			*(bf_GENE+SIZE_GENE-1) = c;
			*(bf_GENE+SIZE_GENE) = 0;

			for(i=0;i<SIZE_MRNA-1;i++){
				*(bf_mRNA+i) = *(bf_mRNA+i+1);
			}
			*(bf_mRNA+SIZE_MRNA-1) = c;
			*(bf_mRNA+SIZE_MRNA) = 0;

			for(i=0;i<SIZE_CDS-1;i++){
				*(bf_CDS+i) = *(bf_CDS+i+1);
			}
			*(bf_CDS+SIZE_CDS-1) = c;
			*(bf_CDS+SIZE_CDS) = 0;

			for(i=0;i<SIZE_genename-1;i++){
				*(bf_genename+i) = *(bf_genename+i+1);
			}
			*(bf_genename+SIZE_genename-1) = c;
			*(bf_genename+SIZE_genename) = 0;

			for(i=0;i<SIZE_note-1;i++){
				*(bf_note+i) = *(bf_note+i+1);
			}
			*(bf_note+SIZE_note-1) = c;
			*(bf_note+SIZE_note) = 0;

			/*
			if(strcmp(bf_GENE,GENE) == 0){
				in_mRNA = 0;
			}
			*/
			if(strcmp(bf_mRNA,MRNA) == 0){
				in_mRNA = 1;
			}
			if(strcmp(bf_CDS,CDS) == 0){
				in_mRNA = 0;
			}

			if(strcmp(bf_genename,genename) == 0){
				in_genename = 1;
			}
			if((in_genename == 1)&&(c == '\"')){
				in_genename = 2;
			}else if((in_genename == 2)&&(c == '\"')){
				in_genename = 0;
				if(in_mRNA == 1){
					printf("%c",c);
					printf("|");
				}
			}

			if(strcmp(bf_note,note) == 0){
				in_note = 1;
			}
			if((in_note == 1)&&(c == '\"')){
				in_note = 2;
			}else if((in_note == 2)&&(c == '\"')){
				in_note = 0;
				if(in_mRNA == 1){
					printf("%c",c);
					printf("\n");
				}
			}
			if(((in_mRNA > 0)&&(in_note > 1))||((in_mRNA > 0)&&(in_genename > 1))){
				printf("%c",c);
			}
		}
	}else if(argc == 2){
		if((IN = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
		while((c = fgetc(IN)) != EOF){
			for(i=0;i<SIZE_GENE-1;i++){
				*(bf_GENE+i) = *(bf_GENE+i+1);
			}
			*(bf_GENE+SIZE_GENE-1) = c;
			*(bf_GENE+SIZE_GENE) = 0;

			for(i=0;i<SIZE_MRNA-1;i++){
				*(bf_mRNA+i) = *(bf_mRNA+i+1);
			}
			*(bf_mRNA+SIZE_MRNA-1) = c;
			*(bf_mRNA+SIZE_MRNA) = 0;

			for(i=0;i<SIZE_CDS-1;i++){
				*(bf_CDS+i) = *(bf_CDS+i+1);
			}
			*(bf_CDS+SIZE_CDS-1) = c;
			*(bf_CDS+SIZE_CDS) = 0;

			for(i=0;i<SIZE_genename-1;i++){
				*(bf_genename+i) = *(bf_genename+i+1);
			}
			*(bf_genename+SIZE_genename-1) = c;
			*(bf_genename+SIZE_genename) = 0;

			for(i=0;i<SIZE_note-1;i++){
				*(bf_note+i) = *(bf_note+i+1);
			}
			*(bf_note+SIZE_note-1) = c;
			*(bf_note+SIZE_note) = 0;

			/*
			if(strcmp(bf_GENE,GENE) == 0){
				in_mRNA = 0;
			}
			*/
			if(strcmp(bf_mRNA,MRNA) == 0){
				in_mRNA = 1;
			}
			if(strcmp(bf_CDS,CDS) == 0){
				in_mRNA = 0;
			}

			if(strcmp(bf_genename,genename) == 0){
				in_genename = 1;
			}
			if((in_genename == 1)&&(c == '\"')){
				in_genename = 2;
			}else if((in_genename == 2)&&(c == '\"')){
				in_genename = 0;
				if(in_mRNA == 1){
					printf("%c",c);
					printf("|");
				}
			}

			if(strcmp(bf_note,note) == 0){
				in_note = 1;
			}
			if((in_note == 1)&&(c == '\"')){
				in_note = 2;
			}else if((in_note == 2)&&(c == '\"')){
				in_note = 0;
				if(in_mRNA == 1){
					printf("%c",c);
					printf("\n");
				}
			}
			if(((in_mRNA > 0)&&(in_note > 1))||((in_mRNA > 0)&&(in_genename > 1))){
				printf("%c",c);
			}

		}
		fclose(IN);
	}
	return(0);
}
