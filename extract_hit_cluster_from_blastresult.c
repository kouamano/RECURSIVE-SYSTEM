#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define QUERY_START "Query="
#define SIZE_QUERY_START 6+1
#define QUERY_END "letters)"
#define SIZE_QUERY_END 8+1
#define HIT_START "\n>ref|"
#define SIZE_HIT_START 6+1
#define HIT_END "     Length = "
#define SIZE_HIT_END 14+1

static int in_query = 0;
static int in_hit = 0;
static char *bf_QUERY_START = NULL;
static char *bf_QUERY_END = NULL;
static char *bf_HIT_START = NULL;
static char *bf_HIT_END = NULL;

int main(int argc, char **argv){
	int i = 0;
	signed char c;
	FILE *IN = NULL;
	bf_QUERY_START = calloc(SIZE_QUERY_START+2,sizeof(char));
	bf_QUERY_END = calloc(SIZE_QUERY_END+2,sizeof(char));
	bf_HIT_START = calloc(SIZE_HIT_START+2,sizeof(char));
	bf_HIT_END = calloc(SIZE_HIT_END+2,sizeof(char));
	if(argc == 1){
		while((c = fgetc(stdin)) != EOF){
			//printf("%c",c);
			for(i=0;i<SIZE_QUERY_START-1;i++){
				*(bf_QUERY_START+i) = *(bf_QUERY_START+i+1);
			}
			*(bf_QUERY_START+SIZE_QUERY_START-1) = c;
			*(bf_QUERY_START+SIZE_QUERY_START) = 0;
			//printf("::%s::",bf_QUERY_START);

			for(i=0;i<SIZE_QUERY_END-1;i++){
				*(bf_QUERY_END+i) = *(bf_QUERY_END+i+1);
			}
			*(bf_QUERY_END+SIZE_QUERY_END-1) = c;
			*(bf_QUERY_END+SIZE_QUERY_END) = 0;

			for(i=0;i<SIZE_HIT_START-1;i++){
				*(bf_HIT_START+i) = *(bf_HIT_START+i+1);
			}
			*(bf_HIT_START+SIZE_HIT_START-1) = c;
			*(bf_HIT_START+SIZE_HIT_START) = 0;

			for(i=0;i<SIZE_HIT_END-1;i++){
				*(bf_HIT_END+i) = *(bf_HIT_END+i+1);
			}
			*(bf_HIT_END+SIZE_HIT_END-1) = c;
			*(bf_HIT_END+SIZE_HIT_END) = 0;

			if(strncmp(bf_QUERY_START,QUERY_START,SIZE_QUERY_START-1) == 0){
				in_query = 1;
				printf("\n");
				printf("%s",QUERY_START);
			}
			if(strncmp(bf_QUERY_END,QUERY_END,SIZE_QUERY_END-1) == 0){
				in_query = 0;
				printf("\n");
			}

			if(strncmp(bf_HIT_START,HIT_START,SIZE_HIT_START-1) == 0){
				in_hit = 1;
				printf("\n");
				printf("%s",HIT_START);
			}
			if(strncmp(bf_HIT_END,HIT_END,SIZE_HIT_END-1) == 0){
				in_hit = 0;
				//printf("\n");
			}

			if(in_query == 1){
				if(c != 0x0a){
					printf("%c",c);
				}
			}
			if(in_hit == 1){
				if((c != 0x0a)&&(c != 0x20)){
				//if((c != 0x0a)){
					printf("%c",c);
				}
			}
			/*
			printf(":%s::%s::%s::%d:\n",bf_CDS,bf_join,bf_complement,in_cds);
			*/
		}
		printf("\n");
	}else{
		printf("USAGE: cat file | extract_hit_cluster_from_blastresult\n");
	}
	return(0);
}
