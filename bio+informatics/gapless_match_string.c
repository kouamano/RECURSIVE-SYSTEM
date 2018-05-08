/* gapless_match_string.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IS_FLOAT 0
#define GAP_PRINT 1
#define IS_PRINT_C 1

static char *base_seq;
static char *query_seq;
static unsigned int base_len;
static unsigned int query_len;
FILE *in_bfile;
FILE *in_qfile;
unsigned int read_from_stdin();
unsigned int read_from_file();
int print_score_list();
//int print_string_list();
//float char_n_match();
float print_char_n_match();
float print_match_string();

int main(int argc, char **argv){
	if(argc == 1){		//base <- stdin, query <- stdin.
		base_seq = malloc(1080000000*sizeof(char));
		base_len = read_from_stdin(base_seq);
		query_seq = malloc(1050000*sizeof(char));
		query_len = read_from_stdin(query_seq);
		print_score_list(base_seq,query_seq,IS_PRINT_C);
		//print_string_list(base_seq,query_seq);
		printf("\n");
	}else if(argc == 3){	//base <- file, query <- stdin.
		if(strcmp(argv[1],"-b") == 0){
			if((in_bfile = fopen(argv[2],"r")) == NULL){
				perror(argv[2]);
				exit(1);
			}else{	
				query_seq = malloc(1050000*sizeof(char));
				query_len = read_from_stdin(query_seq);
				base_seq = malloc(1080000000*sizeof(char));
				base_len = read_from_file(in_bfile,base_seq);
				fclose(in_bfile);
				print_score_list(base_seq,query_seq,IS_PRINT_C);
				//print_string_list(base_seq,query_seq);
				printf("\n");
			}
		}else{
			printf("option(s) : [-b]\n");
		}	
	}else if(argc == 5){	// base <- file, query <- file.
		if((strcmp(argv[1],"-b") == 0)&&(strcmp(argv[3],"-q") == 0)){
			if((in_bfile = fopen(argv[2],"r")) == NULL){
				perror(argv[2]);
				exit(1);
			}else{
				base_seq = malloc(1080000000*sizeof(char));
				base_len = read_from_file(in_bfile,base_seq);
				fclose(in_bfile);
			}
			if((in_qfile = fopen(argv[4],"r")) == NULL){
				perror(argv[4]);
				exit(1);
			}else{
				query_seq = malloc(1050000*sizeof(char));
				query_len = read_from_file(in_qfile,query_seq);
				fclose(in_qfile);
			}
			print_score_list(base_seq,query_seq,IS_PRINT_C);
			//print_string_list(base_seq,query_seq);
			printf("\n");
		}else{
			printf("option(s) : [-b] [-q]\n");
		}
	}else{
		printf("option(s) : [-b] [-q]\n");
	}
	return(0);
}

unsigned int read_from_stdin(char *str){
	char c;
	unsigned int i;
	i = 0;
	while(scanf("%c",&c) != EOF){
		if((c != '\n')&&(c != ' ')){
			if(c == '>'){
				break;
			}else{
				*(str+i) = c;
				i++;
			}
		}
	}
	*(str+i) = '\0';
	return(i);
}

unsigned int read_from_file(FILE *fp, char *str){
	char c;
	unsigned int i;
	i = 0;
	while((c = fgetc(fp)) != EOF){
		if((c != '\n')&&(c != ' ')){
			*(str+i) = c;
			i++;
		}
	}
	*(str+i) = '\0';
	return(i);
}

int print_score_list(char *base, char *query, int is_print_c){
	int i = 0;
	char *partofbase;
	if(is_print_c == 0){
		for(i = 0;i <= base_len - query_len;i++){
			partofbase = base_seq+i;
			print_char_n_match(partofbase, query, query_len, IS_FLOAT);
		}
	}else if(is_print_c == 1){
		for(i = 0;i <= base_len - query_len;i++){
			partofbase = base_seq+i;
			print_match_string(partofbase, query, query_len, IS_FLOAT);
		}
	}
	return(0);
}

/*
int print_string_list(char *base, char *query){
	int i = 0;
	char *partofbase;
	for(i = 0;i <= base_len - query_len;i++){
		partofbase = base_seq+i;
		//print_char_n_match(partofbase, query, query_len, IS_FLOAT);
		print_match_string(partofbase, query, query_len, IS_FLOAT);
	}
}
*/

/*
float char_n_match(char *c1, char *c2, int n){
	unsigned int i;
	unsigned int score = 0;
	for(i = 0;i < n;i++){
		if(*(c1+i) == *(c2+i)){
			score++;
		}
	}
	return(score);
}
*/

float print_char_n_match(char *c1, char *c2, int n, int is_float){
	unsigned int i;
	unsigned int score = 0;
	float fscore;
	for(i = 0;i < n;i++){
		if((*(c1+i) == *(c2+i))||(*(c1+i) == 'N')||(*(c1+i) == 'n')){
			score++;
		}
	}
	if(is_float == 0){
		printf("%d ",score);
		return(score);
	}else if(is_float == 1){
		fscore = (float)score / n;
		printf("%f ",fscore);
		return(fscore);
	}
	return(0);
}

float print_match_string(char *c1, char *c2, int n, int is_float){
	unsigned int i;
	unsigned int score = 0;
	float fscore;
	for(i = 0;i < n;i++){
		if(*(c1+i) == *(c2+i)){
			printf("%c",*(c1+i));
			score++;
		}else if((*(c1+i) == 'N')||(*(c1+i) == 'n')){
			printf("%c",'N');
			score++;
		}else if((*(c2+i) == 'N')||(*(c2+i) == 'n')){
			printf("%c",'N');
			score++;
		}else if(GAP_PRINT == 1){
			printf("%c",'_');
		}
	}
	if(is_float == 0){
		//printf("%d ",score);
		printf(" ");
		return(score);
	}else if(is_float == 1){
		fscore = (float)score / n;
		//printf("%f ",fscore);
		printf(" ");
		return(fscore);
	}
	return(0);
}
