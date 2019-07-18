#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "../../include/fasta.h"
#include "../../include/fasta.c"
#define LEN_FILE_NAME 1024
#define LEN_SHORT_STRING 2048
#define LEN_HEAD 512
#define LEN_WORD 128


struct option {
	int status;
	char short_query_string[LEN_SHORT_STRING];
	char query_file[LEN_FILE_NAME];
	char base_file[LEN_FILE_NAME];
	int size_head;
	int size_body;
	int out_with_head;
	char out_head[LEN_HEAD];
	int with_serial_number;
	int start_number;
};

void init_option(struct option *opt){
	opt->status = 0;
	opt->short_query_string[0] = '\0';
	opt->query_file[0] = '\0';
	opt->base_file[0] = '\0';
	opt->size_head = 1024; /* 1024 byte  */
	opt->size_body = 300000000; /* 300M byte */
	opt->out_with_head = 1;
	opt->out_head[0] = '\0';
	opt->with_serial_number = 1;
	opt->start_number = 0;
};

void print_option(struct option opt){
	printf("status :%d:\n",opt.status);
	printf("direct query string :%s:\n",opt.short_query_string);
	printf("query file :%s:\n",opt.query_file);
	printf("base file :%s:\n",opt.base_file);
	printf("head size :%d:\n",opt.size_head);
	printf("base size :%d:\n",opt.size_body);
	printf("with head :%d:\n",opt.out_with_head);
	printf("head :%s:\n",opt.out_head);
	printf("with serial number :%d:\n",opt.with_serial_number);
	printf("start number :%d:\n",opt.start_number);
};

int get_option(int optc, char **optv, struct option *opt){
	int i = 0;
	int s = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			if((s&1) == 0){s = s + 1;}
		}else if(strcmp(optv[i],"--help") == 0){
			if((s&1) == 0){s = s + 1;}
		}else if(strcmp(optv[i],"-c") == 0){
			if((s&2) == 0){s = s + 2;}
		}else if(strcmp(optv[i],"--check") == 0){
			if((s&2) == 0){s = s + 2;}
		}else if(strncmp(optv[i],"q=",2) == 0){
			if((s&4) == 0){s = s + 4;}
			sscanf(optv[i],"q=%s",opt->short_query_string);
		}else if(strncmp(optv[i],"qf=",3) == 0){
			sscanf(optv[i],"qf=%s",opt->query_file);
		}else if(strncmp(optv[i],"bf=",3) == 0){
			sscanf(optv[i],"bf=%s",opt->base_file);
		}else if(strncmp(optv[i],"-hs",3) == 0){
			sscanf(optv[i],"-hs%d",&opt->size_head);
		}else if(strncmp(optv[i],"-bs",3) == 0){
			sscanf(optv[i],"-bs%d",&opt->size_body);
		}else if(strncmp(optv[i],"-f",2) == 0){
			opt->out_with_head = 1;
			sscanf(optv[i],"-f%s",opt->out_head);
		}else if(strcmp(optv[i],"+f") == 0){
			opt->out_with_head = 0;
			opt->out_head[0] = '\0';
		}else if(strcmp(optv[i],"-s") == 0){
			opt->with_serial_number = 1;
		}else if(strcmp(optv[i],"+s") == 0){
			opt->with_serial_number = 0;
		}else if(strncmp(optv[i],"-S",2) == 0){
			sscanf(optv[i],"-S%d",&opt->start_number);
		}else{
			fprintf(stderr,"[E]unknown option : %s\n",optv[i]);
			exit(1);
		}
	}
	opt->status = s;
	return(s);
};

void print_help(){
	printf("USAGE:\n");
	printf("  regionprint [qf=<query file>|q=<start>..<end>:] bf=<base file> [-hs<head size>] [-bs<base size>] [-f<fasta head>|+f] [-s|+s] [-S<start number>] [-c|--check]\n");
};

void print_base(int start, int end, char *base){
	int i;
	if((end - start) >= 0){
		start = start - 1;
		for(i=start;i<end;i++){
			printf("%c",base[i]);
		}
	}else{
		start = start - 1;
		end = end - 1;
		for(i=start;i>=end;i--){
			if(base[i] == 'A'){
				printf("T");
			}else if(base[i] == 'C'){
				printf("G");
			}else if(base[i] == 'G'){
				printf("C");
			}else if(base[i] == 'T'){
				printf("A");
			}else if(base[i] == 'a'){
				printf("t");
			}else if(base[i] == 'c'){
				printf("g");
			}else if(base[i] == 'g'){
				printf("a");
			}else if(base[i] == 't'){
				printf("t");
			}else{
				printf("%c",base[i]);
			}
		}
	}
};

int main(int argc, char **argv){
	struct option opt;
	struct fasta *fst;
	FILE *BIN;
	FILE *QIN;
	int query_length = 0;
	signed char c;
	int i = 0;
	char *char_start;
	char *char_end;
	int csp = 0;
	int cep = 0;
	int start = 0;
	int end = 0;
	int inter_region = 0;
	int inner_region = 0;
	int in_start = 0;
	int in_end = 0;
	int serial_number = 0;
	/* (* operate option */
	init_option(&opt);
	get_option(argc-1,argv+1,&opt);
	if((opt.status&1) == 1){
		print_help();
	}
	if((opt.status&2) == 2){
		print_option(opt);
	}
	if(((opt.status&1) == 1)||((opt.status&2) == 2)){
		exit(0);
	}
	/* *) */
	/* (* check file name */
	if((opt.query_file[0] == '\0')&&((opt.status&4) != 4)){
		fprintf(stderr,"[W]no query file.\n");
		exit(1);
	}
	if(opt.base_file[0] == '\0'){
		fprintf(stderr,"[W]no base file.\n");
		exit(1);
	}
	/* *) */
	/* (* open, read and close base file */
	BIN = NULL;
	if((BIN = fopen(opt.base_file,"r")) == NULL){
		perror(opt.base_file);
		exit(1);
	}
	fst = fasta_alloc(opt.size_head,opt.size_body);
	read_fastaArray_from_fp(BIN,fst,opt.size_head,opt.size_body);
	if(BIN != NULL){
		fclose(BIN);
	}
	/* *) */
	/* (* read query and print region */
	if((char_start = calloc(LEN_WORD,sizeof(char))) == NULL){
		fprintf(stderr,"[E]failed: malloc().\n");
		exit(1);
	}
	if((char_end = calloc(LEN_WORD,sizeof(char))) == NULL){
		fprintf(stderr,"[E]failed: malloc().\n");
		exit(1);
	}
	QIN = NULL;
	if((opt.status&4) != 4){
		if((QIN = fopen(opt.query_file,"r")) == 0){
			perror(opt.query_file);
			exit(1);
		}
	}
	/* if you want to print fasta head specify option -f OR -s */
	serial_number = opt.start_number;
	if((opt.status&4) == 4){
		query_length = strlen(opt.short_query_string);
		for(i=0;i<query_length;i++){
		c = opt.short_query_string[i];
			if((in_start == 0)&&(in_end == 0)&&(inter_region == 0)&&(inner_region == 0)){
				if((48 <= (int)c)&&((int)c <= 57)){
					in_start = 1;
					char_start[csp] = c;
					csp++;
				}
			}else if((in_start == 1)&&(in_end == 0)&&(inter_region == 0)&&(inner_region == 0)){
				if(c == '\n'){
					fprintf(stderr,"check format.\n");
					exit(1);
				}else if(c == ':'){
					fprintf(stderr,"check format.\n");
					exit(1);
				}else if(c == ','){
					fprintf(stderr,"check format.\n");
					exit(1);
				}else if(c == '.'){
					char_start[csp] = '\0';
					sscanf(char_start,"%d",&start);
					csp= 0;
					in_start = 0;
					inner_region = 1;
				}else if((48 <= (int)c)&&((int)c <= 57)){
					char_start[csp] = c;
					csp++;
				}
			}else if((in_start == 0)&&(in_end == 1)&&(inter_region == 0)&&(inner_region == 0)){
				if(c == '\n'){			/* conjugate */
					char_end[cep] = '\0';
					sscanf(char_end,"%d",&end);
					print_base(start,end,fst->body);
					cep = 0;
					in_end = 0;
					inter_region = 1;
				}else if(c == ':'){		/* separate */
					if(opt.out_with_head == 1){
						printf(">%s%08d\n",opt.out_head,serial_number);
					}
					serial_number++;
					char_end[cep] = '\0';
					sscanf(char_end,"%d",&end);
					print_base(start,end,fst->body);
					printf("\n");
					cep = 0;
					in_end = 0;
					inter_region = 1;
				}else if(c == ','){		/* conjugate */
					char_end[cep] = '\0';
					sscanf(char_end,"%d",&end);
					print_base(start,end,fst->body);
					cep = 0;
					in_end = 0;
					inter_region = 1;
				}else if(c == '.'){
					fprintf(stderr,"[E]check format.\n");
					exit(1);
				}else if((48 <= (int)c)&&((int)c <= 57)){
					char_end[cep] = c;
					cep++;
				}
			}else if((in_start == 0)&&(in_end == 0)&&(inter_region == 1)&&(inner_region == 0)){
				if((48 <= (int)c)&&((int)c <= 57)){
					inter_region = 0;
					in_start = 1;
					char_start[csp] = c;
					csp++;
				}
			}else if((in_start == 0)&&(in_end == 0)&&(inter_region == 0)&&(inner_region == 1)){
				if((48 <= (int)c)&&((int)c <= 57)){
					inner_region = 0;
					in_end = 1;
					char_end[cep] = c;
					cep++;
				}
			}else{
			}
		}
	}else{
		if(opt.out_with_head == 1){
			printf(">%s%08d\n",opt.out_head,serial_number);
		}
		while((c = fgetc(QIN)) != EOF){
			if((in_start == 0)&&(in_end == 0)&&(inter_region == 0)&&(inner_region == 0)){
				if((48 <= (int)c)&&((int)c <= 57)){
					in_start = 1;
					char_start[csp] = c;
					csp++;
				}
			}else if((in_start == 1)&&(in_end == 0)&&(inter_region == 0)&&(inner_region == 0)){
				if(c == '\n'){
					fprintf(stderr,"check format.\n");
					exit(1);
				}else if(c == ':'){
					fprintf(stderr,"check format.\n");
					exit(1);
				}else if(c == ','){
					fprintf(stderr,"check format.\n");
					exit(1);
				}else if(c == '.'){
					char_start[csp] = '\0';
					sscanf(char_start,"%d",&start);
					csp= 0;
					in_start = 0;
					inner_region = 1;
				}else if((48 <= (int)c)&&((int)c <= 57)){
					char_start[csp] = c;
					csp++;
				}
			}else if((in_start == 0)&&(in_end == 1)&&(inter_region == 0)&&(inner_region == 0)){
				if(c == '\n'){			/* conjugate */
					char_end[cep] = '\0';
					sscanf(char_end,"%d",&end);
					print_base(start,end,fst->body);
					cep = 0;
					in_end = 0;
					inter_region = 1;
				}else if(c == ':'){		/* separate */
					serial_number++;
					char_end[cep] = '\0';
					sscanf(char_end,"%d",&end);
					print_base(start,end,fst->body);
					if(opt.out_with_head == 1){
						printf("\n>%s%08d",opt.out_head,serial_number);
					}
					printf("\n");
					cep = 0;
					in_end = 0;
					inter_region = 1;
				}else if(c == ','){		/* conjugate */
					char_end[cep] = '\0';
					sscanf(char_end,"%d",&end);
					print_base(start,end,fst->body);
					cep = 0;
					in_end = 0;
					inter_region = 1;
				}else if(c == '.'){
					fprintf(stderr,"[E]check format.\n");
					exit(1);
				}else if((48 <= (int)c)&&((int)c <= 57)){
					char_end[cep] = c;
					cep++;
				}
			}else if((in_start == 0)&&(in_end == 0)&&(inter_region == 1)&&(inner_region == 0)){
				if((48 <= (int)c)&&((int)c <= 57)){
					inter_region = 0;
					in_start = 1;
					char_start[csp] = c;
					csp++;
				}
			}else if((in_start == 0)&&(in_end == 0)&&(inter_region == 0)&&(inner_region == 1)){
				if((48 <= (int)c)&&((int)c <= 57)){
					inner_region = 0;
					in_end = 1;
					char_end[cep] = c;
					cep++;
				}
			}else{
			}
		}
	}
	printf("\n");
	if(QIN != NULL){
		fclose(QIN);
	}
	/* *) */
	return(0);
}
