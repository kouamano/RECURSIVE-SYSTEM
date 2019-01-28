#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024
#define BUFF_LEN 1024
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
#include "../RECURSIVE-SYSTEM/T-structure.h"
#include "../RECURSIVE-SYSTEM/T-basic_functions.h"
#include "../RECURSIVE-SYSTEM/T-import_export.h"

void status(void){
	printf("STATUS:\n");
	printf(" Constructing functions.\n");
}

void help(void){
	printf("USAGE:\n");
	printf(" tq [-h] [-s] [-c] buff=<size(int)> in=<input file> w=<print warnning> -F<x>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  buff : set integer.\n");
	printf("  in : set *chars (len < 1024).\n");
	printf("  war : set integer.\n");
}
void function_help(void){
	printf("  -F<x> : function symbol, e.g. \"-FS\" prints S-form.\n");
	printf("   -FT : prints T-form.\n");
	printf("   -FS : prints S-form.\n");
	printf("   -Fh : prints hierarchical-form.\n");
	printf("   -Fst : prints import status.\n");
	printf("   -Fhst : prints import status with hierarchical-form.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).in = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}
struct function_options *alloc_function_options(void){
	struct function_options *p;
	if((p = malloc(sizeof(struct function_options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).buff = BUFF_LEN;
	(*opt).in[0] = '\0';
	(*opt).war = 0;
}
void init_function_options(struct function_options *fopt){
	(*fopt).f_counter = 0;
	(*fopt).f_print_T = 0;
	(*fopt).f_print_S = 0;
	(*fopt).f_print_status = 0;
	(*fopt).f_print_hierarchy = 0;
	(*fopt).f_print_hierarchy_status = 0;
}

void get_options(int optc, char **optv, struct options *opt){
	/*
	char *opstr;
	if((opstr = calloc(LEN,sizeof(char))) == NULL){
		perror("[Fail] malloc()@get_options.\n");
		exit(1);
	}
	*/
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0 && strlen(optv[i]) == 2){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-s") == 0){
			(*opt).stat = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check = 1;
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff);
		}else if(strncmp(optv[i],"w=",2) == 0){
			sscanf(optv[i],"w=%d",&(*opt).war);
		}else if(strncmp(optv[i],"-hF",3) == 0){
			(*opt).hF = 1;
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).in);
		}
	}
}
void get_function_options(int optc, char **optv, struct function_options *fopt){
	int i = 0;
	(*fopt).f_counter = 0;
	for(i=0;i<optc;i++){
		if(strncmp(optv[i],"-FT",3) == 0){
			(*fopt).f_print_T = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-Fst",4) == 0){
			(*fopt).f_print_status = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-FS",3) == 0){
			(*fopt).f_print_S = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-Fhst",4) == 0){
			(*fopt).f_print_hierarchy_status = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-Fh",3) == 0){
			(*fopt).f_print_hierarchy = 1;
			(*fopt).f_counter++;
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.buff:%d:\n",(*opt).buff);
	printf(" opt.in:%s:\n",(*opt).in);
	printf(" opt.war:%d:\n",(*opt).war);
}
void check_function_options(struct function_options *fopt){
	printf(" functions:\n");
	printf("  opt.fcount:%d:\n",(*fopt).f_counter);
	printf("  opt.FT:%d:\n",(*fopt).f_print_T);
	printf("  opt.FS:%d:\n",(*fopt).f_print_S);
	printf("  opt.Fst:%d:\n",(*fopt).f_print_status);
	printf("  opt.Fh:%d:\n",(*fopt).f_print_hierarchy);
	printf("  opt.Fhst:%d:\n",(*fopt).f_print_hierarchy_status);
}

int main(int argc, char **argv){
	struct options *opt;
	struct function_options *fopt;
	int ie = 0;
	FILE *IN;
	int is_open = 0;
	int c;
	opt = alloc_options();
	fopt = alloc_function_options();
	init_options(opt);
	init_function_options(fopt);
	get_options(argc-1, argv+1, opt);
	get_function_options(argc-1, argv+1, fopt);
	if(argc == 1){
		(*opt).help = 1;
	}
	if((*opt).help == 1){
		help();
		function_help();
		ie = 1;
	}
	if((*opt).stat == 1){
		status();
		ie = 1;
	}
	if((*opt).check == 1){
		check_options(opt);
		check_function_options(fopt);
		ie = 1;
	}
	if(ie == 1){
		exit(0);
	}
	// open file
	if((IN = fopen((*opt).in,"r")) == NULL){
		perror((*opt).in);
		exit(1);
	}
	is_open = 1;

	// main function
	c = 1;
	struct Tree *top;
	top = Create_Node(BUFF_LEN);
	c = importApp_Tree(IN,top,opt,fopt); // removed mem leak code.
		/*
		if(c == '\n'){
			function();
		}
		*/

	// close file
	if(is_open > 0){
		fclose(IN);
	}

	// finish
	return(c);
}
