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
};

void help(void){
	printf("DESCRIPTION:\n");
	printf(" toPsdJSON prints pseudo JSON form T-format.\n");
	printf("USAGE:\n");
	printf(" toPsdJSON [-h] [-s] [-c] in=<file>\n");
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
	//(*opt).argint = 0;
	(*opt).file[0] = '\0';
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
		//}else if(strncmp(optv[i],"int=",4) == 0){
		//	sscanf(optv[i],"int=%d",&(*opt).argint);
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).file);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.help:%d:\n",(*opt).help);
	printf(" opt.stat:%d:\n",(*opt).stat);
	//printf(" opt.argint:%d:\n",(*opt).argint);
	printf(" opt.argstr:%s:\n",(*opt).file);
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
	int ESC = 0;
	int OC = 0;
	while((C = fgetc(IN)) != EOF){
		OC = C;
		if(C == '\"' && ESC == 0){
			ESC = 1;
			//fprintf(stdout,"%s","hoge");
		}
		if(C == '\"' && ESC == 1){
			ESC = 0;
			//fprintf(stdout,"%s","hoge");
		}
		if(C == '{' && ESC == 1){
			putc((char)OC,stdout);
		}else if(C == '{' && ESC == 0){
			fprintf(stdout,"%s","\"{\"");
			OC = '(';
			putc((char)OC,stdout);
		}else if(C == '[' && ESC == 1){
			putc((char)OC,stdout);
		}else if(C == '[' && ESC == 0){
			fprintf(stdout,"%s","\"[\"");
			OC = '(';
			putc((char)OC,stdout);
		}else if(C == '}' && ESC == 1){
			putc((char)OC,stdout);
		}else if(C == '}' && ESC == 0){
			OC = ')';
			putc((char)OC,stdout);
		}else if(C == ']' && ESC == 1){
			putc((char)OC,stdout);
		}else if(C == ']' && ESC == 0){
			OC = ')';
			putc((char)OC,stdout);
		}else{
			putc((char)OC,stdout);
		}
	}
	if(is_open > 0){
		fclose(IN);
	}

	return(0);
}
