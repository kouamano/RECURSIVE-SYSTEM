#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/data_read.c"
#define LIST_LEN 10000
#define FILE_NAME_LEN 2048
#define LINE_LEN 2000000
#define FS ' '
#define LF '\n'

struct option {
	int help;
	int check;
	char file[FILE_NAME_LEN];
	int cskip;
	int rskip;
	int len;
	int elm;	/*list elms*/
};

void init_option(struct option *opt){
	opt->help = 0;
	opt->check = 0;
	opt->file[0] = '\0';
	opt->cskip = 0;
	opt->rskip = 0;
	opt->len = LINE_LEN;
	opt->elm = LIST_LEN;
}

void print_option(struct option opt){
	printf("file :%s:\n",opt.file);
	printf("cskip :%d:\n",opt.cskip);
	printf("rskip :%d:\n",opt.rskip);
	printf("len :%d:\n",opt.len);
	printf("elm :%d:\n",opt.elm);
}

void get_option(int optc, char **optv, struct option *opt){
	int i;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			opt->help = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			opt->check = 1;
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",opt->file);
		}else if(strncmp(optv[i],"cskip=",6) == 0){
			sscanf(optv[i],"cskip=%d",&opt->cskip);
		}else if(strncmp(optv[i],"rskip=",6) == 0){
			sscanf(optv[i],"rskip=%d",&opt->rskip);
		}else if(strncmp(optv[i],"len=",4) == 0){
			sscanf(optv[i],"len=%d",&opt->len);
		}else if(strncmp(optv[i],"elm=",4) == 0){
			sscanf(optv[i],"elm=%d",&opt->elm);
		}else{
			fprintf(stderr,"[WARN] option not found :%s:",optv[i]);
		}
	}
}

void help(void){
	printf("USAGE:\n");
	printf("  frequency_to_appearance if=<file> [cskip=<column skip>] [rskip=<row skip>] [len=<line buffer>] [elm=<elements in line>]\n");
}

int main(int argc, char **argv){
	/* vars */
	FILE *IFP;
	struct option opt;
	int i;
	int c = 0;
	int ie = 0;
	char *line;
	int line_ptr = 0;
	int line_inner_ptr = 0;
	int lines = 0;
	int ccount = 0;
	float *flist = NULL;
	int flist_elm = 0;

	/* check options */
	init_option(&opt);
	get_option(argc-1,argv+1,&opt);
	if(opt.help == 1){
		help();
		ie++;
	}
	if(opt.check == 1){
		print_option(opt);
		ie++;
	}
	if(argc < 2){
		help();
		ie++;
	}
	if(ie > 0){
		exit(0);
	}

	/* allocation */
	line = malloc(sizeof(char)*(size_t)opt.len);
	if(line == NULL){
		fprintf(stderr,"[ERROR] failed : malloc() for line buf.\n");
		exit(1);
	}
	line[0] = '\0';
	flist = malloc(sizeof(float)*(size_t)opt.elm);
	if(flist == NULL){
		fprintf(stderr,"[ERROR] failed : malloc() for float list buf.\n");
		exit(1);
	}

	/* open file */
	IFP = fopen(opt.file,"r");
	if(IFP == NULL){
		perror(opt.file);
		exit(1);
	}
	/* skip rows */
	while(lines < opt.rskip){
		c = fgetc(IFP);
		printf("%c",(char)c);
		if(c == '\n'){
			lines++;
		}
	}

	/* oerate each line */
	while((c = fgetc(IFP)) != EOF){
		if(c != LF){
			line[line_ptr] = c;
			line_ptr++;
		}else{
			line[line_ptr] = '\0';
			i = 0;
			ccount = 0;
			while(ccount < opt.cskip){
				if(line[i] == FS){
					ccount++;
				}
				printf("%c",line[i]);
				i++;
			}
			line_inner_ptr = i;
			i = 0;
			flist_elm = read_flist_from_string(line+line_inner_ptr,flist);
			for(i=0;i<flist_elm;i++){
				if(flist[i] > 0){
					printf("%c ",'1');
				}else{
					printf("%c ",'0');
				}
			}
			printf("\n");
			line_ptr = 0;
		}
	}

	/* close file */
	fclose(IFP);
	return(0);
}
