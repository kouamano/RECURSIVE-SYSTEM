#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024

struct options {
	int help;
	int stat;
	int check;
	//int argint;
	char *file;
	char idt;
};

void help(void){
	printf("DESCRIPTION:\n");
	printf(" indentToT prints T-form from indent format.\n");
	printf("USAGE:\n");
	printf(" indentToT [-h] [-s] [-c] in=<file> idt=<char>\n");
	printf("  -h : help.\n");
	printf("  -s : status.\n");
	printf("  -c : check args.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Under construction.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).file = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).file[0] = '\0';
	(*opt).idt = ' ';
}

void get_options(int optc, char **optv, struct options *opt){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-s") == 0){
			(*opt).stat = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check = 1;
		}else if(strncmp(optv[i],"idt=",4) == 0){
			sscanf(optv[i],"idt=%c",&(*opt).idt);
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).file);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.help:%d:\n",(*opt).help);
	printf(" opt.stat:%d:\n",(*opt).stat);
	printf(" opt.file:%s:\n",(*opt).file);
	printf(" opt.idt:%c:\n",(*opt).idt);
}

int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	int is_open = 0;
	int C = 0;
	FILE *IN;
	if(argc == 1){
		(*opt).help = 1;
	}
	if((*opt).help == 1){
		help();
		ie = 1;
	}
	if((*opt).stat == 1){
		status();
		ie = 1;
	}
	if((*opt).check == 1){
		check_options(opt);
		ie = 1;
	}
	if(ie == 1){
		exit(0);
	}
	if((IN = fopen((*opt).file,"r")) == NULL){
		perror((*opt).file);
		exit(1);
	}
	is_open = 1;
	int i = 0;
	int LV = 0;
	int PLV = 0;
	int currentLV = 0;
	int diffLV = 0;
	int LF = 0;
	int IDT = 0;
	int IPready = 0;
	while((C = fgetc(IN)) != EOF){
		if(C == (*opt).idt){
			LV++;
			IDT++;
		}
		if(C != (*opt).idt){
			IDT = 0;
		}
		if(C == '\n'){
			putc(',',stdout);
			PLV = LV;
			LV = currentLV;
			IPready = 1;
		}
		putc((char)C,stdout);
		if(IPready == 1){
			diffLV = PLV-LV;
			printf(":%d:",diffLV);
			if(diffLV > 0){
				for(i=0;i<diffLV;i++){
					putc('(',stdout);
				}
			}else if(diffLV == 0){
				;
			}else{
				for(i=0;i<diffLV;i++){
					putc(')',stdout);
				}
			}
			IPready = 0;
			LV = 0;
			PLV = 0;
		}
	}
//					putc(')',stdout);
	if(is_open > 0){
		fclose(IN);
	}

	return(0);
}
