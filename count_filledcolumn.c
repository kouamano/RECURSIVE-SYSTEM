#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif

#define FS ' '
#define LF '\n'
#define LEN_FILE_NAME 2048

struct option {
	char *input_file;
	//int each_count;
	char fsep;
	char lfeed;
	int lskip;
	int help;
	int check;
};

int init_option(struct option *opt){
	if((opt->input_file = calloc(LEN_FILE_NAME,sizeof(char))) == NULL){
		fprintf(stderr,"[ERROR] failed : calloc in init_option().\n");
		exit(1);
	}
	//opt->each_count = 1;
	opt->fsep = FS;
	opt->lfeed = LF;
	opt->lskip = 0;
	opt->help = 0;
	opt->check = 0;
	return(0);
}

int get_option(int optc, char **optv, struct option *opt){
	int i;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			opt->help = 1;
		}
		else if(strcmp(optv[i],"-c") == 0){
			opt->check = 1;
		}
		/*
		else if(strncmp(optv[i],"e=",2) == 0){
			sscanf(optv[i],"e=%d",&opt->each_count);
		}
		*/
		else if(strncmp(optv[i],"fs=",2) == 0){
			sscanf(optv[i],"fs=%c",&opt->fsep);
		}
		else if(strncmp(optv[i],"lf=",2) == 0){
			sscanf(optv[i],"lf=%c",&opt->lfeed);
		}
		else if(strncmp(optv[i],"if=",2) == 0){
			sscanf(optv[i],"if=%s",opt->input_file);
		}
		else if(strncmp(optv[i],"lskip=",6) == 0){
			sscanf(optv[i],"lskip=%d",&opt->lskip);
		}
		else
		{
			fprintf(stderr,"[WARN] undefined option :%s:\n",optv[i]);
		}
	}
	return(0);
}

void print_option(struct option opt){
	printf("PARAMETERS :\n");
	printf("  input file :%s:\n",opt.input_file);
	//printf("  print each colum :%d:\n",opt.each_count);
	printf("  feald separator :%c:\n",opt.fsep);
	printf("  line feed :%c:\n",opt.lfeed);
	printf("  line skip :%d:\n",opt.lskip);
}

void print_help(void){
	printf("USAGE :\n");
	printf("  count_filledcolumn if=<input file> [lf=<line feed char>] [fs=<feild separator char>] [lskip=<line skip>] [e={0|1}]\n");
}

int main(int argc, char **argv){
	FILE *IFP = NULL;
	struct option opt;
	int c = 0;
	int ie = 0;
	int i = 0;
	int IN_TERM = 0;
	int lines = 0;
	int max_col = 0;
	int min_col = 0;
	int columns = 0;
	init_option(&opt);
	get_option(argc-1,argv+1,&opt);
	if(argc < 2){
		print_help();
		ie++;
	}
	if(opt.help > 0){
		print_help();
		ie++;
	}
	if(opt.check > 0){
		print_option(opt);
		ie++;
	}
	if(ie > 0){
		exit(0);
	}
	if((IFP = fopen(opt.input_file,"r")) == NULL){
		perror(opt.input_file);
		exit(1);
	}
	for(i=0;i<opt.lskip;i++){
		while((c = fgetc(IFP)) != opt.lfeed);
	}
	while((c = fgetc(IFP)) != opt.lfeed){
		if(c == opt.fsep){
			IN_TERM = 0;
		}else{
			IN_TERM++;
		}
		if(IN_TERM == 1){
			columns++;
		}
	}
	IN_TERM = 0;
	lines++;
	max_col = columns;
	min_col = columns;
	columns = 0;
	while((c = fgetc(IFP)) != EOF){
		if(c == opt.lfeed){
			max_col = max(max_col,columns);
			min_col = min(min_col,columns);
			columns = 0;
			lines++;
			IN_TERM=0;
		}
		else if(c == opt.fsep){
			IN_TERM=0;
		}
		else{
			IN_TERM++;
		}
		if(IN_TERM == 1){
			columns++;
		}
	}
	fclose(IFP);
	printf("LINES :%d:\n",lines);
	printf("MAX COL :%d:\n",max_col);
	printf("MIN COL :%d:\n",min_col);
	return(0);
}
