#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 1024
#define BRK_S '('
#define BRK_E ')'
#define split_DLM ' '
#define out_DLM '\t'

//type definition
struct option {
	int stat;
	int help;
	char fname[MAX_LEN];
};

//status
void stat(void){
	printf("STATUS:\n");
	printf(" Available.\n");
	//printf(" //read from file.\n");
}

//help
void help(void){
	printf("USAGE:\n");
	printf("  cutStrSPintrBrk [-s] [-h] [if=<file>]\n");
	printf("    -s : status\n");
	printf("    -h : help\n");
	printf("    file : input file\n");
}

//opt operation
struct option *alloc_option(void){
	struct option *p;
	p = malloc(sizeof(struct option) * 1);
	if(p == NULL){
		printf("failed: malloc() in arg_alloc().\n");
		exit(1);
	}
	return(p);
}

void init_option(struct option *opt){
	(*opt).stat=0;
	(*opt).help=0;
	(*opt).fname[0] = 0;
}

void get_option(struct option *opt, int optc, char **optv){
	int i=0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-s") == 0){
			(*opt).stat = 1;
		}else if(strcmp(optv[i],"-h") == 0){
			(*opt).help = 1;
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",(*opt).fname);
		}
	}
}

//main
int main(int argc, char **argv){
	struct option *opt;
	FILE *IN;
	int is_open = 0;
	int c = 0;
	int in_BRK = 0;

	//option analysis
	opt = alloc_option();
	init_option(opt);
	get_option(opt, argc-1, argv+1);

	//put status
	if((*opt).stat == 1){
		stat();
		exit(1);
	}

	//put help
	if((*opt).help == 1){
		help();
		exit(0);
	}

	//open file
	if(strlen((*opt).fname) == 0){
		IN = stdin;
		is_open = 0;
	}else{
		if((IN = fopen((*opt).fname,"r")) == NULL){
			perror((*opt).fname);
			exit(1);
		}
	}

	//read from file
	while((c=fgetc(IN)) != EOF){
		if(c == BRK_S){
			in_BRK++;
		}
		if(c == BRK_E){
			in_BRK--;
		}
		//printf("%d",in_BRK);
		if(c == split_DLM){
			if(in_BRK == 0){
				putchar(out_DLM);
			}else{
				putchar(c);
			}
		}else{
				putchar(c);
		}
	}
	
	//close file
	if(is_open == 1){
		fclose(IN);
	}

	//return
	return(0);
}
