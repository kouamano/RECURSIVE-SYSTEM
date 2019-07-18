#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SEP ':'
#define ISEC ".."

struct option{
	int status;
	int frame;
	int size;
	int start;
};

void init_option(struct option *opt){
	opt->status = 0;
	opt->frame = 0;
	opt->size = 0;
	opt->start = 0;
};

void print_option(struct option opt){
	printf("status :%d:\n",opt.status);
	printf("frames :%d:\n",opt.frame);
	printf("frame size :%d:\n",opt.size);
	printf("start at :%d:\n",opt.start);
};

int get_option(int optc, char**optv, struct option *opt){
	int i = 0;
	int s = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-c") == 0){
			if((s&1) == 0){s = s + 1;}
		}else if(strcmp(optv[i],"-h") == 0){
			if((s&2) == 0){s = s + 2;}
		}else if(strncmp(optv[i],"-n",2) == 0){
			sscanf(optv[i],"-n%d",&opt->frame);
		}else if(strncmp(optv[i],"-l",2) == 0){
			sscanf(optv[i],"-l%d",&opt->size);
		}else if(strncmp(optv[i],"-s",2) == 0){
			sscanf(optv[i],"-s%d",&opt->start);
		}
	}
	opt->status = s;
	return(s);
};

void print_help(){
	printf("USAGE:\n");
	printf("  mkq_regionprint -n<number of frames> -l<length of a frame> -s<start number> [-c] [-h]\n");
};

int main(int argc, char **argv){
	int i = 0;
	struct option opt;
	init_option(&opt);
	get_option(argc-1,argv+1,&opt);
	if((opt.status&1) == 1){
		print_option(opt);
	}
	if((opt.status&2) == 2){
		print_help();
	}
	if(((opt.status&1) == 1)||((opt.status&2) == 2)){
		exit(0);
	}
	printf("%d%s",0*opt.size + opt.start + 1,ISEC);
	printf("%d",0*opt.size + opt.start + opt.size);
	for(i=1;i<opt.frame;i++){
		printf("%c\n",SEP);
		printf("%d%s",i*opt.size + opt.start + 1,ISEC);
		printf("%d",i*opt.size + opt.start + opt.size);
	}
	printf("\n");
	return(0);
}
