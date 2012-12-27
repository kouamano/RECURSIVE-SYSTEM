#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAIR 2
#define TABLE_SIZE 1000
#define STR_SIZE 1024
#define LARGE_STR_SIZE 1024000
#define WORD_SIZE 128
#define DLM '\n'

void help(void){
	printf("USAGE:\n");
	printf(" body <n1>-<n2>,<n3>-<n4>,... [<file>]\n");
	printf(" body qf=<query file> <file>\n");
	printf("OPTIONS:\n");
	printf(" n1,n2,n3,... -- line number, must be n1 <= n2 <= n3 ...\n");
}

void swp_ep(int *elm){
	if(*elm == 0){
		*elm = 1;
	}else if(*elm == 1){
		*elm = 0;
	}else{
		*elm = 0;
	}
}

int str_to_table(char *str, int **table){
	int sp = 0;
	int lp = 0;
	int ep = 0;
	int wp = 0;
	int len;
	char *num;
	int in_ws = 0;
	if((num = calloc(sizeof(char),WORD_SIZE)) == NULL){
		printf("failed: malloc() - exit.\n");
		exit(1);
	}
	len = strlen(str);
	for(sp=0;sp<len;sp++){
		if(str[sp] == ','){
			if(in_ws == 1){
				fprintf(stderr,"warning: check format.\n");
			}
			num[wp] = '\0';
			sscanf(num,"%d",&table[lp][ep]);
			lp++;
			swp_ep(&ep);
			wp = 0;
			in_ws = 1;
		}else if(str[sp] == '-'){
			if(in_ws == 1){
				fprintf(stderr,"warning: check format.\n");
			}
			num[wp] = '\0';
			sscanf(num,"%d",&table[lp][ep]);
			swp_ep(&ep);
			wp = 0;
			in_ws = 1;
		}else{
			num[wp] = str[sp];
			wp++;
			in_ws = 0;
		}
	}
	num[wp] = '\0';
	sscanf(num,"%d",&table[lp][ep]);
	lp++;
	swp_ep(&ep);
	wp = 0;
	return(lp);
}

void sequence_print_char(char c, int lc, int table_size, int**table){
	int i;
	for(i=0;i<table_size;i++){
		if((table[i][0] <= lc)&&(lc <= table[i][1])){
			fputc(c,stdout);
		}
	}
}

int main(int argc, char **argv){
	int i;
	char *str;
	char *file;
	char *query_file;
	FILE *ifp;
	FILE *qfp;
	int **table;
	int table_size = 0;
	char c;
	int lc = 0;
	if((str = calloc(sizeof(char),STR_SIZE)) == NULL){
		printf("failed: malloc() -- exit.\n");
		exit(1);
	}
	if((file = calloc(sizeof(char),STR_SIZE)) == NULL){
		printf("failed: malloc() -- exit.\n");
		exit(1);
	}
	if((query_file = calloc(sizeof(char),STR_SIZE)) == NULL){
		printf("failed: malloc() -- exit.\n");
		exit(1);
	}
	if((table = malloc(sizeof(int*) * TABLE_SIZE)) == NULL){
		printf("failed: malloc() -- exit.\n");
		exit(1);
	}
	for(i=0;i<TABLE_SIZE;i++){
		if((*(table+i) = calloc(sizeof(int),PAIR)) == NULL){
			printf("failed: calloc() -- exit.\n");
			exit(1);
		}
	}
	if(argc == 1){
		help();
	}else if(argc == 2){
		sscanf(argv[1],"%s",str);
		if(strcmp(str,"-h") == 0){
			help();
			exit(1);
		}
		table_size = str_to_table(str,table);
		lc++;
		while((c = fgetc(stdin)) != EOF){
			if(c == DLM){
				lc++;
			}
			sequence_print_char(c,lc,table_size,table);
		}
		printf("\n");
	}else if(argc == 3){
		if(strncmp(argv[1],"qf=",3) == 0){
			free(str);
			if((str = calloc(sizeof(char),LARGE_STR_SIZE)) == NULL){
				printf("failed: malloc() -- exit.\n");
				exit(1);
			}
			sscanf(argv[1],"qf=%s",query_file);
			if((qfp = fopen(query_file,"r")) == NULL){
				perror(query_file);
				exit(1);
			}
			i = 0;
			while((c = fgetc(qfp)) != EOF){
				if((c != ' ')&&(c != '\t')&&(c != '\n')){
					str[i] = c;
					i++;
				}
			}
			str[i] = '\0';
			fclose(qfp);
		}else{
			sscanf(argv[1],"%s",str);
		}
		sscanf(argv[2],"%s",file);
		table_size = str_to_table(str,table);
		ifp = fopen(file,"r");
		lc++;
		while((c = fgetc(ifp)) != EOF){
			sequence_print_char(c,lc,table_size,table);
			if(c == DLM){
				lc++;
			}
		}
		fclose(ifp);
		//printf("\n");
	}
	return(0);
}
