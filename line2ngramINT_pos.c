#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/alloc.c"

#define NAME_LEN 1024
#define B_ORDER_MAX_32 3
#define PROG_NAME "line2ngramINT_pos"

typedef struct{
	char *file;
	int n;
	int skip;
	int head;
	int help;
	int tail;
	char LF;
	char FS;
	int check;
}OPT;

typedef union{
	unsigned long long int i;
	char c[9];
}UNION_UNSIG_64;

void help(){
	printf("PROGRAM : %s\n",PROG_NAME);
	printf("USAGE : \n");
	printf("  %s if=<file> n=<n> skip=<line skip> [-H|+H] [-h]\n",PROG_NAME);
	printf("  <file>: input file.\n");
	printf("  <n>: N of N-gram.\n");
	printf("  <line skip>: skip first line(s).\n");
	printf("  -H: data with ID. / +H: data without ID.\n");
	printf("  -T: Tail operation: On / +T Tail operation: Off.\n");
	printf("  -h: print help.\n");
	printf("\n");
}

void InitOption(OPT *option){
	option->file = c_calloc_vec(1000);
	option->n = 4;
	option->skip = 1;
	option->head = 1;
	option->help = 0;
	option->tail = 0;
	option->LF = '\n';
	option->FS = '\t';
	option->check = 0;
}

void GetOption(int optc, char **optv, OPT *option){
	int i;
	for(i=0;i<optc;i++){
		if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",option->file);
		}else if(strncmp(optv[i],"n=",2) == 0){
			sscanf(optv[i],"n=%d",&option->n);
		}else if(strncmp(optv[i],"skip=",5) == 0){
			sscanf(optv[i],"skip=%d",&option->skip);
		}else if(strcmp(optv[i],"-H") == 0){
			option->head = 1;
		}else if(strcmp(optv[i],"+H") == 0){
			option->head = 0;
		}else if(strcmp(optv[i],"-T") == 0){
			option->tail = 1;
		}else if(strcmp(optv[i],"+T") == 0){
			option->tail = 0;
		}else if(strcmp(optv[i],"-h") == 0){
			option->help = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			option->check = 1;
		}else if(strcmp(optv[i],"-check") == 0){
			option->check = 1;
		}else{
			fprintf(stderr,"Unknown option:%s:\n",optv[i]);
		}
	}
}

void PrintOption(const OPT option){
	printf("OPTION :\n");
	printf("  input file:%s:\n",option.file);
	printf("  N:%d:\n",option.n);
	printf("  LF(hex):%0X:\n",option.LF);
	printf("  FS(hex):%0X:\n",option.FS);
	printf("  skip:%d:\n",option.skip);
	printf("  head:%d:\n",option.head);
	printf("  tail:%d:\n",option.tail);
	printf("  help:%d:\n",option.help);
	printf("  check:%d:\n",option.check);
	printf("\n");
}

void data_read_print_ngram_from_fp(FILE *fp, OPT option){
	int c;
	int i;
	int j;
	int LF_count = 0;
	char term[5];
	UNION_UNSIG_64 ngram;
	ngram.i = 0;
	ngram.c[8] = '\0';
	int term_pos = 0;
	for(i=0;i<5;i++){
		term[i] = '\0';
	}
	if(option.skip > 0){
		for(i=0;i<option.skip;i++){
			while((c = fgetc(fp)) != option.LF){
			}
			LF_count++;
		}
	}
	if(option.head == 1){
		int in_body = 0;
		while((c = fgetc(fp)) != EOF){
			if((c == option.FS)&&(in_body == 0)){
				c = fgetc(fp);
				in_body = 1;
			}
			if((c == option.FS)&&(in_body == 1)){
				in_body = 1;
			}
			if((c == option.LF)){
				if(option.tail == 1){
					//for(j=option.n-1;j>0;j--){
					for(j=0;j<option.n-1;j++){
						term_pos++;
						//term[j] = '\0';
						//ngram.c[j] = '\0';
						ngram.i = ngram.i >> 8;
						//printf("\t%d|%s",term_pos-option.n,term);
						printf("\t%d|%llX",term_pos-option.n,ngram.i);
					}
				}
				for(j=0;j<option.n;j++){term[j] = '\0';};
				for(j=0;j<option.n;j++){ngram.c[j] = '\0';};
				putc(option.LF,stdout);in_body = 0;
				term_pos = 0;
			}
			if(in_body == 1){
				term_pos++;
				for(i=0;i<option.n-1;i++){
					term[i] = term[i+1];
					ngram.c[i] = ngram.c[i+1];
				}
				term[option.n-1] = c;
				ngram.c[option.n-1] = c;
				if(strlen(term) > 0){
					//printf("\t%d|%s",term_pos-option.n,term);
					printf("\t%d|%llX",term_pos-option.n,ngram.i);
				}
			}else{
				if(c != option.LF){
					putc(c,stdout);
				}
			}
		}
	}else if(option.head == 0){
		while((c = fgetc(fp)) != EOF){
			term_pos++;
			if(c == option.LF){
				if(option.tail == 1){
					//for(j=option.n-1;j>0;j--){
					for(j=0;j<option.n-1;j++){
						term_pos++;
						//term[j] = '\0';
						//ngram.c[j] = '\0';
						ngram.i = ngram.i >> 8;
						//printf("\t%d|%s",term_pos-option.n,term);
						printf("\t%d|%llX",term_pos-option.n,ngram.i);
					}
				}
				putc(option.LF,stdout);
				for(j=0;j<option.n;j++){term[j] = '\0';};
				for(j=0;j<option.n;j++){ngram.c[j] = '\0';};
				term_pos = 0;
			}else{
				for(i=0;i<option.n-1;i++){
					term[i] = term[i+1];
					ngram.c[i] = ngram.c[i+1];
				}
				term[option.n-1] = c;
				ngram.c[option.n-1] = c;
				if(strlen(term) > 0){
					//printf("\t%d|%s",term_pos-option.n,term);
					printf("\t%d|%llX",term_pos-option.n,ngram.i);
				}
			}
		}
	}
}

int main(int argc, char **argv){
	//def and init
	OPT option;
	int im_ext = 0;
	FILE *IN;
	int file_open = 0;
	InitOption(&option);

	//opt analysis
	GetOption(argc-1,argv+1,&option);
	if(option.check > 0){
		PrintOption(option);
		im_ext++;
	}
	if(option.help > 0){
		help();
		im_ext++;
	}
	if((option.n < 1)||(option.n > 8)){
		fprintf(stderr,"available range of N : 0 < N < 9.\n");
		im_ext++;
	}
	if(im_ext > 0){
		exit(0);
	}
	if(strlen(option.file) > 0){
		if((IN = fopen(option.file,"rw")) == NULL){perror("fopen()\n"); exit(0);}
		file_open = 1;
	}else{
		IN = stdin;
	}

	//core func
	data_read_print_ngram_from_fp(IN,option);

	//file closer
	if(file_open > 1){
		fclose(IN);
	}
	return(0);
}
