/* FILE_NAME        */
/* separatorcount.c */
/* END              */

/* NEEDS */
/* END */

/* DEFINITIONS */
/* END */

/* CODE */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif

#define FS '\t'
#define LF '\n'
#define LEN_FILE_NAME 2048

struct option {
	char *input_file;
	char fsep;
	char linefeed;
	int lskip;
	int help;
	int check;
};

void init_option(struct option *opt){
	if((opt->input_file = calloc(LEN_FILE_NAME,sizeof(char))) == NULL){
		fprintf(stderr,"[ERROR] failed : calloc in init_option().\n");
		exit(1);
	}
	opt->fsep = FS;
	opt->linefeed = LF;
	opt->lskip = 0;
	opt->help = 0;
	opt->check = 0;
}

int  get_option(int optc, char **optv, struct option *opt){
	int i;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			opt->help = 1;
		} else if(strcmp(optv[i],"-c") == 0){
			opt->check = 1;
		} else if(strncmp(optv[i],"fs=",3) == 0){
			sscanf(optv[i],"fs=%c",&opt->fsep);
		} else if(strncmp(optv[i],"lf=",3) == 0){
			sscanf(optv[i],"lf=%c",&opt->linefeed);
		} else if(strncmp(optv[i],"lskip=",6) == 0){
			sscanf(optv[i],"lskip=%d",&opt->lskip);
		} else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",opt->input_file);
		} else {
			fprintf(stderr,"[WARN] undefined option :%s:\n",optv[i]);
		}
	}
	return(0);
}

void print_option(struct option opt){
	printf("PARAMETERS :\n");
	printf("  feald separator:%c:\n",opt.fsep);
	printf("  line feeder:%c:\n",opt.linefeed);
	printf("  line skip:%d:\n",opt.lskip);
	printf("  input file:%s:\n",opt.input_file);
}

void help(void){
	printf("USAGE: \n");
	printf("  count_separator [-h] [-c] [fs=<separator>] [lf=<line feed>] [lskip=<line skip>] if=<input file>\n");
	printf("\n");
	printf("OPTIONS: \n");
	printf("  -h: print help.\n");
	printf("  -c: print parameters.\n");
	printf("  <separator>: field separator (character).\n");
	printf("  <line feed>: line feeder (character).\n");
	printf("  <line skip>: first n line(s) skip.\n");
	printf("  <input file>: input file.\n");
}

int main(int argc, char **argv){
	/* vars */
	FILE *IN = NULL;
	struct option opt;
	int i = 0;
	int c = 0;
	int lines = 0;
	int max_fs = 0;
	int min_fs = 0;
	int count_fs = 0;
	int ie = 0;
	int is_open = 0;

	/* init/get options */
	init_option(&opt);
	get_option(argc-1,argv+1,&opt);

	/* check args */
	if(opt.help > 0){
		help();
		ie++;
	}
	if(ie > 0){
		exit(0);
	}
	if(opt.check > 0){
		print_option(opt);
		ie++;
	}
	if(ie > 0){
		exit(0);
	}

	/* open file */
	if((strlen(opt.input_file) > 0)&&(opt.help == 0)&&(opt.check == 0)){
		if((IN = fopen(opt.input_file,"r")) == NULL){
			perror(opt.input_file);
			exit(1);
		}
		is_open++;
	}else{
		IN = stdin;
	}

	/* skip */
	for(i=0;i<opt.lskip;i++){
		while((c = fgetc(IN)) != opt.linefeed);
	}
	/* first read */
	while((c = fgetc(IN)) != opt.linefeed){
		if(c == opt.fsep){
			count_fs++;
		}
	}
	max_fs = count_fs;
	min_fs = count_fs;
	count_fs = 0;
	lines++;
	/* long raed */
	while((c = fgetc(IN)) != EOF){
		if(c == opt.linefeed){
			max_fs = max(max_fs,count_fs);
			min_fs = min(min_fs,count_fs);
			count_fs = 0;
			lines++;
		}else if(c == opt.fsep){
			count_fs++;
		}
	}

	/* close file */
	if(is_open > 0){
		fclose(IN);
	}

	/* report */
	printf("LINES:%d:\n",lines);
	printf("MAX:%d:\n",max_fs);
	printf("MIN:%d:\n",min_fs);

	/* exit */
	return(0);
}
/* END */
