/*drop-ascii.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME_SIZE 1024

struct options {
	int help;
	int check;
	int print_err_pos;
	char *file_name;
};

void help(void){
	printf("USAGE:\n");
	printf("  check_ascii [-h] [-c] [-p] if=<file>\n");
	printf("    -h : print help.\n");
	printf("    -c : print args.\n");
	printf("    -p : print error position.\n");
	printf("    <file> : input file.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).file_name = malloc(sizeof(char) * FILE_NAME_SIZE )) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).check = 0;
	(*opt).print_err_pos = 0;
	(*opt).file_name[0] = '\0';
}

void get_options(int optc, char **optv, struct options *opt){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check = 1;
		}else if(strcmp(optv[i],"-p") == 0){
			(*opt).print_err_pos = 1;
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",(*opt).file_name);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf("  opt.help:%d:\n",(*opt).help);
	printf("  opt.check:%d:\n",(*opt).check);
	printf("  opt.print_err_pos:%d:\n",(*opt).print_err_pos);
	printf("  opt.file_name:%s:\n",(*opt).file_name);
}


int main(int argc, char **argv){
	/* vars, alloc */
	struct options *opt;
	  opt = alloc_options();
	  init_options(opt);
	int ie = 0;
	FILE *IN;
	int is_open = 0;
	int C = 0;
	get_options(argc-1, argv+1, opt);

	/* arg check */
	if((*opt).help == 1){
		help();
		ie++;
	}
	if((*opt).check == 1){
		check_options(opt);
		ie++;
	}
	if(ie > 0){
		exit(0);
	}

	/* open file */
	IN = fopen((*opt).file_name,"r");
	if(IN == NULL){
		perror((*opt).file_name);
	}else{
		is_open++;
	}

	/* func */
	if((*opt).print_err_pos == 0){
		while((C = fgetc(IN)) != EOF){
			if(C > 0x00 && C < 0x7f){
				;
			}else{
				putc(C,stdout);
			}
		}
	}else{
		int counter = 0;
		while((C = fgetc(IN)) != EOF){
			counter++;
			if(C > 0x00 && C < 0x7f){
				;
			}else{
				printf(":%d:%X:\n",counter,C);
				//putc(C,stdout);
			}
		}
	}
	
	/* close file */
	if(is_open > 0){
		fclose(IN);
	}

	exit(0);
}
