#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024

struct options {
	int help;
	int stat;
	int check;
	char *fname;
	char dlm;
	char brk_start;
	char brk_end;
};

void help(void){
	printf("USAGE:\n");
	printf(" CM_to_LF_out_Bracket [-h] [-s] [-c] if=<file> dlm=<delimiter> .\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  file : input file name (len < 1024).\n");
	printf("  delimiter : char (1 byte).\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" UNDER CONSTRUCTION\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).fname = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).fname[0] = '\0';
	(*opt).dlm = ',';
	(*opt).brk_start = '(';
	(*opt).brk_end = ')';
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
			//sscanf(optv[i],"int=%d",&(*opt).argint);
		}else if(strncmp(optv[i],"dlm=",4) == 0){
			sscanf(optv[i],"dlm=%c",&(*opt).dlm);
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",(*opt).fname);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.fname:%s:\n",(*opt).fname);
	printf(" opt.dlm:%c:\n",(*opt).dlm);
	printf(" opt.brk_start:%c:\n",(*opt).brk_start);
	printf(" opt.brk_end:%c:\n",(*opt).brk_end);
}

int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	FILE *IN;
	int c;
	int IN_BRK = 0;
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
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
	if((IN = fopen((*opt).fname, "r")) == NULL){
		perror((*opt).fname);
		exit(1);
	}
	while((c = fgetc(IN)) != EOF){
		//putc(c,stdout);
		if(c == (int)(*opt).brk_start){
			IN_BRK++;
		}else if(c == (int)(*opt).brk_end){
			IN_BRK--;
		}else{
			;
		}
		//printf("%d",IN_BRK);
		if((IN_BRK == 0) && (c == (int)(*opt).dlm)){
			putc('\t',stdout);
		}else{
			putc(c,stdout);
		}
	}
	fclose(IN);
	return(0);
}
