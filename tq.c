#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../RECURSIVE-SYSTEM/T-definition.h"
#include "../RECURSIVE-SYSTEM/T-structure.h"
#include "../RECURSIVE-SYSTEM/T-basic_functions.h"
#include "../RECURSIVE-SYSTEM/T-compiler.h"
#include "../RECURSIVE-SYSTEM/T-import_export.h"

const char cdate[] = __DATE__;
const char ctime[] = __TIME__;

void status(void){
	printf("STATUS:\n");
	printf(" Testing of JSON print.\n");
	printf(" The option FMa : under construction.\n");
	printf(" The option form : under construction.\n");
	printf("COMPILED:\n");
	printf(" %s\n",ctime);
	printf(" %s\n",cdate);
}

/*help*/
void help(void){
	printf("USAGE:\n");
	printf(" tq [-h|-hF|-hC] [-s] [-c] buff=<size(int)> in=<input file> form=<input form> w=<warnning level> -F<x> -C<x>.\n");
	printf("  -h : help.\n");
	printf("  -hF : function help.\n");
	printf("  -hC : compile help.\n");
	printf("  -s : prints status.\n");
	printf("  -c : check args.\n");
	printf("  buff : set integer for buffer size to read the nodes.\n");
	printf("  in : set input file name (length < 1024).\n");
	printf("  form : decrear input-form\n");
	printf("   0 single: operate whole as single line,\n");
	printf("   1 multi: apply reference lines (under construction),\n");
	printf("   2 individual: operate line by line.\n");
	printf("  war : set integer for warnnig level.\n");
}
void function_help(void){
	printf("  -F<x> : function symbol, e.g. \"-FS\" prints S-form.\n");
	printf("   -FT : prints T-form.\n");
	printf("   -FS : prints S-form.\n");
	printf("   -FJ : prints JSON.\n");
	printf("   -FW : prints Wolfram language.\n");
	printf("   -FMa : prints Adjacency matrix (under construction).\n");
	printf("   -Fh : prints hierarchical-form.\n");
	printf("   -Fst : prints import status.\n");
	printf("   -Fhst : prints import status with hierarchical-form.\n");
}
void compile_help(void){
	printf("  -C<x> : compile symbol, e.g. \"-CW\" compiles to Wolfram.\n");
	printf("   -CW : to Wolfram language (under construction).\n");
}

/*allocation*/
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
struct compile_options *alloc_compile_options(void){
	struct compile_options *p;
	if((p = malloc(sizeof(struct compile_options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}


/*initialize*/
void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).buff = BUFF_LEN;
	(*opt).war = 0;
	(*opt).in[0] = '\0';
	(*opt).form = 2;
	(*opt).hF = 0;
	(*opt).hC = 0;
}
void init_function_options(struct function_options *fopt){
	(*fopt).f_counter = 0;
	(*fopt).f_print_T = 0;
	(*fopt).f_print_S = 0;
	(*fopt).f_print_J = 0;
	(*fopt).f_print_W = 0;
	(*fopt).f_print_Ma = 0;
	(*fopt).f_print_status = 0;
	(*fopt).f_print_hierarchy = 0;
	(*fopt).f_print_hierarchy_status = 0;
}
void init_compile_options(struct compile_options *copt){
        (*copt).c_counter = 0;
        (*copt).c_wolfram = 0;
}

/*get options*/
void get_options(int optc, char **optv, struct options *opt){
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
		}else if(strncmp(optv[i],"-hC",3) == 0){
			(*opt).hC = 1;
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).in);
		}else if(strncmp(optv[i],"form=single",11) == 0){
			(*opt).form = 0;
		}else if(strncmp(optv[i],"form=multi",10) == 0){
			(*opt).form = 1;
		}else if(strncmp(optv[i],"form=individual",15) == 0){
			(*opt).form = 2;

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
		}else if(strncmp(optv[i],"-FJ",3) == 0){
			(*fopt).f_print_J = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-FW",3) == 0){
			(*fopt).f_print_W = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-FMa",4) == 0){
			(*fopt).f_print_Ma = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-Fhst",4) == 0 && strlen(optv[i]) == 5){
			(*fopt).f_print_hierarchy_status = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-Fh",3) == 0 && strlen(optv[i]) == 3){
			(*fopt).f_print_hierarchy = 1;
			(*fopt).f_counter++;
		}
	}
}
void get_compile_options(int optc, char **optv, struct compile_options *copt){
	int i = 0;
	(*copt).c_counter = 0;
	for(i=0;i<optc;i++){
		if(strncmp(optv[i],"-CW",3) == 0){
			(*copt).c_wolfram = 1;
			(*copt).c_counter++;
		}
	}
}

/*checking*/
void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.buff:%d:\n",(*opt).buff);
	printf(" opt.in:%s:\n",(*opt).in);
	printf(" opt.war:%d:\n",(*opt).war);
	printf(" opt.hF:%d:\n",(*opt).hF);
	printf(" opt.form:%d: (under construction) \n",(*opt).form);
}
void check_function_options(struct function_options *fopt){
	printf(" functions:\n");
	printf("  opt.fcount:%d:\n",(*fopt).f_counter);
	printf("  opt.FT:%d:\n",(*fopt).f_print_T);
	printf("  opt.FS:%d:\n",(*fopt).f_print_S);
	printf("  opt.FJ:%d:\n",(*fopt).f_print_J);
	printf("  opt.FW:%d:\n",(*fopt).f_print_W);
	printf("  opt.FMa:%d: (under construction) \n",(*fopt).f_print_Ma);
	printf("  opt.Fst:%d:\n",(*fopt).f_print_status);
	printf("  opt.Fh:%d:\n",(*fopt).f_print_hierarchy);
	printf("  opt.Fhst:%d:\n",(*fopt).f_print_hierarchy_status);
}
void check_compile_options(struct compile_options *copt){
	printf(" compilers:\n");
	printf("  opt.fcount:%d:\n",(*copt).c_counter);
	printf("  opt.wolfram:%d:\n",(*copt).c_wolfram);
}

/*main*/
int main(int argc, char **argv){
	struct options *opt;
	struct function_options *_fopt;
	struct compile_options *_copt;
	int ie = 0;
	FILE *IN;
	int is_open = 0;
	int c;

	/*options*/
	// main opt
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	// function opt
	_fopt = alloc_function_options();
	init_function_options(_fopt);
	get_function_options(argc-1, argv+1, _fopt);
	// compile opt
	_copt = alloc_compile_options();
	init_compile_options(_copt);
	get_compile_options(argc-1, argv+1, _copt);

	/*exit/print help operation*/
	if(argc == 1){
		(*opt).help = 1;
	}
	if((*opt).hF == 1){
		(*opt).help = 1;
		//function_help();
		ie = 1;
	}
	if((*opt).hC == 1){
		(*opt).help = 1;
		//compile_help();
		ie = 1;
	}
	if((*opt).help == 1){
		help();
		ie = 1;
	}
	if((*opt).hF == 1){
		function_help();
		ie = 1;
	}
	if((*opt).hC == 1){
		compile_help();
		ie = 1;
	}
	if((*opt).stat == 1){
		status();
		ie = 1;
	}
	if((*opt).check == 1){
		check_options(opt);
		check_function_options(_fopt);
		check_compile_options(_copt);
		ie = 1;
	}
	if(ie == 1){
		exit(0);
	}

	/*open file*/
	if((IN = fopen((*opt).in,"r")) == NULL){
		perror((*opt).in);
		exit(1);
	}
	is_open = 1;

	/*main function*/
	c = 1;
	struct Tree *top;
	top = Create_Node(BUFF_LEN);
	c = importApp_Tree(IN,top,opt,_fopt,_copt);
	if((*opt).form == 0){
		#include "T-import_export_app-branch.h"
	}else if((*opt).form == 1){
		; //under construction
	}else if((*opt).form == 2){
		; //already executed @ importApp_Tree
	}

	/*close file*/
	if(is_open > 0){
		fclose(IN);
	}

	/*finish*/
	return(c);
}
