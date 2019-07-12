#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "byte_mask.h"
#include "../include/alloc.c"

#define NAME_LEN 1024
#define B_ORDER_MAX_32 3
#define B_ORDER_MAX_64 7
#define PROG_NAME "ngram_pos2int_pos"
#define NGRAM_MAX 9

typedef union{
	unsigned int i;
	char c[4];
}UNION_UNSIG_32;

typedef union{
	long long unsigned int i;
	char c[8];
}UNION_UNSIG_64;

typedef struct{
	char *file;
	int N;
	int skip;
	int head;
	char LF;
	char FS;
	char *form;
	int help;
	int check;
}OPT;

void PrintHelp(){
	printf("PROGRAM: %s\n",PROG_NAME);
	printf("USAGE: %s if=<file> n=<N> [skip=<number of line-skips>] [-H|+H] [LF=<line-feed char>] [FS=<field separator char>] [form=<form>] [-h] [-c]\n",PROG_NAME);
	printf("OPTIONS: \n");
	printf("  <file>: input file, output of \"ngram\".\n");
	printf("  <N>: N of \"ngram\".\n");
	printf("  <number of line-skips>: for skipping head of file.\n");
	printf("  [-H|+H]: -H: data with head / +H: data without head.\n");
	printf("  <int size>: 32 or 64.\n");
	printf("  <line-feed char>: line feed.\n");
	printf("  <field separator char>: field separator.\n");
	printf("  <form>: print format.\n");
}

void InitOption(OPT *option){
	option->file = c_calloc_vec(NAME_LEN);
	option->N = 4;
	option->skip = 0;
	option->head = 1;
	option->LF = '\n';
	option->FS = '\t';
	option->form = c_alloc_vec(NAME_LEN);
	strcpy(option->form,"%lld");
	option->help = 0;
	option->check = 0;
}

void GetOption(OPT *option, int optc, char **optv){
	int i;
	for(i=0;i<optc;i++){
		if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",option->file);
		}else if(strncmp(optv[i],"n=",2) == 0){
			sscanf(optv[i],"n=%d",&option->N);
		}else if(strncmp(optv[i],"skip=",5) == 0){
			sscanf(optv[i],"skip=%d",&option->skip);
		}else if(strcmp(optv[i],"-H") == 0){
			option->head = 1;
		}else if(strcmp(optv[i],"+H") == 0){
			option->head = 0;
		}else if(strncmp(optv[i],"LF=",3) == 0){
			sscanf(optv[i],"LF=%c",&option->LF);
		}else if(strncmp(optv[i],"FS=",3) == 0){
			sscanf(optv[i],"FS=%c",&option->FS);
		}else if(strncmp(optv[i],"form=",5) == 0){
			sscanf(optv[i],"form=%s",option->form);
		}else if(strcmp(optv[i],"-h") == 0){
			option->help = 1;
		}else if(strcmp(optv[i],"help") == 0){
			option->help = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			option->check = 1;
		}else if(strcmp(optv[i],"check") == 0){
			option->check = 1;
		}else{
			fprintf(stderr,"Unknown option:%s:\n",optv[i]);
		}
	}
}

void PrintOption(OPT option){
	printf("file:%s:\n",option.file);
	printf("N:%d:\n",option.N);
	printf("skip:%d:\n",option.skip);
	printf("head:%d:\n",option.head);
	printf("LF(hex):%0X:\n",option.LF);
	printf("FS(hex):%0X:\n",option.FS);
	printf("form:%s:\n",option.form);
	printf("help:%d:\n",option.help);
	printf("check:%d:\n",option.check);
}

void prnit_ngram2int(FILE *fp, OPT option){
	int c;
	int i;
	int in_head = 1;
	int in_pos = 0;
	int in_term = 0;
	int term_end = 0;
	int count_term = 0;
	UNION_UNSIG_64 ngram;
	ngram.i = 0u;
	if(option.skip > 0){
		for(i=0;i<option.skip;i++){
			while((c = fgetc(fp)) != option.LF){
			}
		}
	}
	if(option.head == 1){
		in_head = 1;
		in_pos = 0;
		in_term = 0;
		term_end = 0;
		count_term = 0;
		while((c = fgetc(fp)) != EOF){
			//printf("[%d][%d][%d](%c)",in_head,in_pos,in_term,c);
			if((in_head > 0)&&(in_pos == 0)&&(in_term == 0) && (c == option.FS)){
				in_head = 0;
				in_pos = 1;
				in_term = 0;
				term_end = 0;
			}
			if((in_head == 0)&&(in_pos > 0)&&(in_term == 0) && (c == '|')){
				in_head = 0;
				in_pos = 0;
				in_term = 0;
				term_end = 0;
				c = fgetc(fp);
			}
			if((in_term > 0)&&(c == option.FS)){
				in_head = 0;
				in_pos = 1;
				in_term = 0;
				term_end = 1;
			}
			if((in_term > 0)&&(c == option.LF)){
				in_head = 1;
				in_pos = 0;
				in_term = 0;
				term_end = 1;
			}
			if((in_head == 0)&&(in_pos == 0)&&(c != option.LF)&&(c != option.FS)){
				in_term++;
				term_end = 0;
			}

			if(in_head > 0){
				putc(c,stdout);
			}
			if(in_pos > 0){
				putc(c,stdout);
			}
			if(in_term > 0){
				//fprintf(stdout,"%d",in_term);
				//putc(c,stdout);
				for(i=0;i<option.N-1;i++){
					ngram.c[i] = ngram.c[i+1];
				}
				ngram.c[i] = (char)c;
			}
			if(term_end == 1){
			//if(in_term == option.N){
				printf("|");
				for(i=0;i<option.N;i++){
					putc(ngram.c[i],stdout);
				}
				printf(option.form,(unsigned long long int)ngram.i);
				ngram.i = 0u;
				term_end = 0;
			}
		}
	}else if(option.head == 0){
		in_term = 1;
		while((c = fgetc(fp)) != EOF){
			if(c == option.FS){
				fputc(c,stdout);
				in_term = 0;
			}else{
				in_term++;
			}
			if(in_term > 0){
				for(i=0;i<option.N-1;i++){
					ngram.c[i] = ngram.c[i+1];
				}
				ngram.c[i] = (char)c;
			}
			if(in_term == option.N){
				printf(option.form,(unsigned long long int)ngram.i);
				ngram.i = 0u;
			}
		}

	}
}

int main(int argc, char **argv){
	int im_exit = 0;
	FILE *IN;
	int file_open = 0;
	OPT option;
	InitOption(&option);
	GetOption(&option,argc-1,argv+1);
	if(option.help == 1){
		PrintHelp();
		im_exit++;
	}
	if(option.check == 1){
		PrintOption(option);
		im_exit++;
	}
	if(im_exit > 0){
		exit(0);
	}
	if(strlen(option.file) > 0){
		IN = fopen(option.file,"r");
		file_open++;
	}else{
		IN = stdin;
	}

	prnit_ngram2int(IN,option);
	
	if(file_open > 0){
		fclose(IN);
	}
	return(0);
}
