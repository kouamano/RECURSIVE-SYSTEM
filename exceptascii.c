#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME_LEN 1024

struct option {
	int help;
	char *input_file_name;
};

int init_option(struct option *opt){
	opt->help = 0;
	if((opt->input_file_name = calloc(FILE_NAME_LEN,sizeof(char))) == NULL){
		fprintf(stderr,"[E]failed: calloc() in init_option(). ");
		fprintf(stderr," -- exit.\n");
		exit(1);
	}
	return(0);
}

int get_option(int optc, char **optv, struct option *opt){
	int err_status = 0;
	int i;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"--help") == 0){
			opt->help = 1;
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",opt->input_file_name);
		}else{
			fprintf(stderr,"[W] Unknown option\t:%s:\n",optv[i]);
			err_status++;
		}
	}
	return(err_status);
}

void help(void){
	printf("Usage:\n");
	printf("  exceptascii if=<file>\n");
}

int main(int argc, char **argv){
	FILE *in;
	int c;
	int opterr = 0;
	struct option opt;
	init_option(&opt);
	get_option(argc-1,argv+1,&opt);
	if(strlen(opt.input_file_name) <= 0){
		fprintf(stderr,"no input file.\n");
		exit(0);
	}
	//printf("%s",opt.input_file_name);
	if((in = fopen(opt.input_file_name,"r")) == NULL){
		perror(opt.input_file_name);
		exit(1);
	}
	while((c = fgetc(in)) != EOF){
		if((0 <= c)&&(c <= 127)){
		}else{
			printf("%c",c);
		}
	}
	fclose(in);
	return(0);
}
