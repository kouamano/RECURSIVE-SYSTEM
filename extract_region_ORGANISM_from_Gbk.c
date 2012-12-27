#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ORG "ORGANISM"
#define REF "REFERENCE"
#define SIZE_ORG 8
#define SIZE_REF 9

static int in_org = 0;
static char *bf_org = NULL;
static char *bf_ref = NULL;

int main(int argc, char **argv){
	/* vars */
	int i = 0;
	signed char c = '\0';
	FILE *IN = NULL;
	int is_open = 0;

	/* malloc */
	if((bf_org = calloc(SIZE_ORG+1,sizeof(char))) == NULL){printf("malloc failed\n"); exit(1);}
	if((bf_ref = calloc(SIZE_REF+1,sizeof(char))) == NULL){printf("malloc failed\n"); exit(1);}

	/* file open */
	if(argc == 1){
		IN = stdin;
		is_open = 0;
	}else if(argc == 2){
		if((IN = fopen(argv[1],"r")) == NULL){perror(argv[1]); exit(1);}
		is_open = 1;
	}

	/* while */
	while((c = fgetc(IN)) != EOF){
		for(i=0;i<SIZE_ORG-1;i++){
			*(bf_org+i) = *(bf_org+i+1);
		}
		*(bf_org+SIZE_ORG-1) = c;
		*(bf_org+SIZE_ORG) = 0;

		for(i=0;i<SIZE_REF-1;i++){
			*(bf_ref+i) = *(bf_ref+i+1);
		}
		*(bf_ref+SIZE_REF-1) = c;
		*(bf_ref+SIZE_REF) = 0;

		if(strncmp(bf_org,ORG,SIZE_ORG) == 0){
			in_org++;
		}
		if(strncmp(bf_ref,REF,4) == 0){
			in_org--;
			if(in_org == 0){
				printf("%c",'\n');
			}
		}
		if(in_org > 0){
			printf("%c",c);
		}
	}

	/* file close */
	if(is_open > 0){
		fclose(IN);
	}

	/* finish */
	return(0);
}
