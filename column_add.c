#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_FILE_NAME 1024
#define LEN_WORD 128
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif

struct option {
	int status;
	int num_column;
	char delim;
	char file[LEN_FILE_NAME];
	int cskip;
	int rskip;
	int is_mean;
};

void init_option(struct option *opt){
	opt->status = 0;
	opt->num_column = 2000;
	opt->delim = '\n';
	opt->file[0] = '\0';
	opt->cskip = 0;
	opt->rskip = 0;
	opt->is_mean = 0;
};

void print_option(struct option opt){
	printf("status:%d:\n",opt.status);
	printf("column:%d:\n",opt.num_column);
	printf("delimter:%c:\n",opt.delim);
	printf("file:%s:\n",opt.file);
	printf("column skip:%d:\n",opt.cskip);
	printf("row skip:%d:\n",opt.rskip);
	printf("is mean?:%d:\n",opt.is_mean);
}

int get_option(int optc, char **optv, struct option *opt){
	int s = 0;
	int i;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			if((s&32) == 0){s = s + 32;}
		}else if(strcmp(optv[i],"--help") == 0){ /* check options */
			if((s&32) == 0){s = s + 32;}
		}else if(strcmp(optv[i],"-C") == 0){ /* check options */
			if((s&1) == 0){s = s + 1;}
		}else if(strcmp(optv[i],"--check") == 0){ /* check options */
			if((s&1) == 0){s = s + 1;}
		}else if(strcmp(optv[i],"-M") == 0){ /* check options */
			opt->is_mean = 1;
		}else if(strcmp(optv[i],"--mean") == 0){ /* check options */
			opt->is_mean = 1;
		}else if(strncmp(optv[i],"-c",2) == 0){
			sscanf(optv[i],"-c%d",&opt->num_column);
			if((s&2) == 0){s = s + 2;}
		}else if(strncmp(optv[i],"-d",2) == 0){
			sscanf(optv[i],"-d%c",&opt->delim);
		}else if(strncmp(optv[i],"-i",2) == 0){ /* as integer */
			if((s&4) == 0){s = s + 4;}
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",*&opt->file);
			if((s&128) == 0){s = s + 128;}
		}else if(strncmp(optv[i],"cskip=",6) == 0){
			sscanf(optv[i],"cskip=%d",&opt->cskip);
		}else if(strncmp(optv[i],"rskip=",6) == 0){
			sscanf(optv[i],"rskip=%d",&opt->rskip);
		}else{
			sscanf(optv[i],"%s",*&opt->file);
			if((s&128) == 0){s = s + 128;}
		}
	}
	opt->status = s;
	return(s);
};

void print_help(){
	printf("USAGE: \n");
	printf("column_add [-h|--help] [-C|--check] [-c<max number of column>] [-d<delimter>] [-i] [cskip=<specify 1st column>] [rskip=<specify 1st row>] [-M|--mean] [if=<file>] [<file>]\n");
};

int main(int argc, char **argv){
	FILE *IN;
	char c;
	struct option opt;
	int status = 0;
	float *line;
	double *line_sum;
	int B = 0;
	int C = 0;
	int C_max = 0;
	int L = 0;
	int i;
	char tmp_word[LEN_WORD];

	/* (*option setting AND memory allocation */
	init_option(&opt);
	status = get_option(argc-1,argv+1,&opt);
	if((status&1) == 1){
		print_option(opt);
	}
	if((status&32) == 32){
		print_help();
	}
	if(((status&1) == 1)||((status&32) == 32)){
		exit(0);
	}
	if((line = calloc(opt.num_column,sizeof(float))) == NULL){
		fprintf(stderr,"failed : calloc() -- exit.\n");
		exit(1);
	}
	if((line_sum = calloc(opt.num_column,sizeof(double))) == NULL){
		fprintf(stderr,"failed : calloc() -- exit.\n");
		exit(1);
	}
	/* *) */

	/* (*file open */
	if((status&128) == 128){
		if((IN = fopen(opt.file,"r")) == NULL){
			perror(opt.file);
			exit(1);
		}
	}else{
		IN = stdin;
	}
	/* *) */

	/* (*main operation */
	if(opt.rskip > 0){
		i = opt.rskip;
		while(i>0){
			c = fgetc(IN);
			if(c == '\n'){
				i--;
			}
		}
	}
	while((c = fgetc(IN)) != EOF){
		if(c == ' '){
			tmp_word[B] = '\0';
			sscanf(tmp_word,"%f",&line[C]);
			B = 0;
			C++;
		}else if(c == '\n'){
			tmp_word[B] = '\0';
			sscanf(tmp_word,"%f",&line[C]);
			for(i=0;i<=C;i++){
				line_sum[i] += line[i];
			}
			C_max = max(C_max,C);
			B = 0;
			C = 0;
			L++;
		}else{
			tmp_word[B] = c;
			B++;
		}
	}
	/* *) */

	/* (*file close */
	if((status&128) == 128){
		fclose(IN);
	}
	/* *) */

	/* (*output */
	if(opt.is_mean == 0){
		for(i=opt.cskip;i<=C_max;i++){
			printf("%lf ",line_sum[i]);
		}
		printf("\n");
	}else if(opt.is_mean == 1){
		for(i=opt.cskip;i<=C_max;i++){
			printf("%lf ",line_sum[i]/L);
		}
		printf("\n");
	}
	/* *) */

	return(0);
}
