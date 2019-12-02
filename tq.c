#define TQ
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../RECURSIVE-SYSTEM/T-definition.h"
#include "../RECURSIVE-SYSTEM/T-structure.h"
#include "../RECURSIVE-SYSTEM/T-functions.h"
#include "../RECURSIVE-SYSTEM/T-functions_Executor.h"
#include "../RECURSIVE-SYSTEM/T-functions_imex.h"

const char cdate[] = __DATE__;
const char ctime[] = __TIME__;

/* help */
void status(void){
	printf("\n");
	printf("STATUS\n");
	printf("======\n");
	printf(" - Under construction\n");
	printf("\n");
	printf("  * Inner product.\n");
	printf("\n");
	printf(" - COMPILED@\n");
	printf("   %s\n",ctime);
	printf("   %s\n",cdate);
}
void help(void){
	printf("=========================================================\n");
	printf(" tq: A language for tree and graph structure description \n");
	printf("=========================================================\n");
	printf("\n");
	printf("USAGE\n");
	printf("*****\n");
	printf("\n");
	printf(" tq.o [-h|-hF|-hC|-hS|-hD|-hE] [-s] [-c] [-test] buff=<(int)size> in=<file name of input form> out=<file name of outout form> data=<data file> data_buff=<(int)size> w=<warnning level> -F<x> -C<x> -P<x>.\n");
	printf("\n");
	printf(" - Full information\n");
	printf("\n");
	printf("   tq.o -h -hF -hC -hS -hD -hE -s -c -CL\n");
	printf("\n");
	printf(" - Main options\n");
	printf("\n");
	printf("  * -h : help.\n");
	printf("  * -hF : function help.\n");
	printf("  * -hC : compile help.\n");
	printf("  * -hS : search help.\n");
	printf("  * -hD : data help.\n");
	printf("  * -hE : print examples.\n");
	printf("  * -s : prints status.\n");
	printf("  * -c : check args.\n");
	printf("  * -test : execute test code.\n");
	printf("  * -Pin : print input form.\n");
	printf("  * -Pout : print output form.\n");
	printf("  * -Pprod : print inner production of binded data.\n");
	printf("  * buff : set integer for buffer size to read heads.\n");
	printf("  * in : set input-form file name (length < 1024).\n");
	printf("  * out : set output-form file name (length < 1024).\n");
	printf("  * data : CSV data file name.\n");
	printf("  * data_buff : set integer for buffer size to read data.\n");
	printf("  * war : set integer for warnnig level.\n");
}
void function_help(void){
	printf("\n");
	printf(" - Format options\n");
	printf("\n");
	printf("  * -FT : prints T-form.\n");
	printf("  * -FS : prints S-form.\n");
	printf("  * -FJ : prints JSON form.\n");
	printf("  * -FW : prints Wolfram language form.\n");
	printf("  * -FX : prints XML form.\n");
	printf("  * -FC : prints shell script form.\n");
	printf("  * -FN : prints seq node-no.\n");
	printf("  * -FMa : prints Adjacency matrix form.\n");
	printf("  * -Fh : prints hierarchical-form.\n");
	printf("  * -Fst : prints import status.\n");
	printf("  * -Fhst : prints import status with hierarchical-form.\n");
	printf("  * -Ftest : prints from test function.\n");
}
void compile_help(void){
	printf("\n");
	printf(" - Compile options\n");
	printf("\n");
	printf("  * -C : print compiled form.\n");
	printf("  * -CL : list buitin operators.\n");
	printf("  * -Cr : prints the \"print-restrict\" char at the end of line.\n");
	printf("  * -Cc : clear head.\n");
	printf("  * -Cd : rewite head to dot.\n");
}
void search_help(void){
	printf("\n");
	printf(" - Search options\n");
	printf("\n");
	printf("  * Sh=<head> (Under construction).\n");
	printf("  * Sp=<position>.\n");
}
void data_help(void){
	printf("\n");
	printf(" - Data option\n");
	printf("\n");
	printf("  * DD=<delimiter> currently unused, definded by definition file.\n");
}
void language_help(void){
	printf("\n");
	printf("LANGUAGE\n");
	printf("********\n");
	printf("\n");
	printf("  | LANGUAGE :: <head>|<tree>\n");
	printf("  | <head> ::= <label><reference><operator><name><bind>\n");
	printf("  | <tree> ::= <head>('('(<head>|<tree>)(','(<head>|<tree>))*')')*\n");
}
void option_header(void){
	printf("\n");
	printf("OPTIONS\n");
	printf("*******\n");
}
void list_builtins(void){
	printf("\n");
	printf(" - Builtin operators\n");
	printf("\n");
	printf("  * #<n> : <label>: head.\n");
	printf("  * ##<n> : <label>: tree.\n");
	printf("  * $#<n> : <reference>: head.\n");
	printf("  * $##<n> : <reference>: tree.\n");
	printf("  * $`$ : <operator>: quating head.\n");
	printf("  * $``$ : <operator>: quating tree.\n");
	printf("  * $~$ : <operator>: riteral head.\n");
	printf("  * $~~$ : <operator>: riteral tree.\n");
	printf("  * $U$ : <operator>: unpack single level.\n");
	printf("  * $UU$ : <operator>: unpack tree (test ver.).\n");
	printf("  * $PI$ : <operator>: inner production for binded data.\n");
	printf("  * & : <operator>: composition (of functions).\n");
	printf("  * $$<n> : <prefix>: dictionary reference (term ID).\n");
	printf("  * $X$<str> : <prefix>: dictionary reference (term string).\n");
	printf("  * $$$<n> : <prefix>: dictionary reference (class ID).\n");
	printf("  * $$X$<str> : <prefix>: dictionary reference (class string).\n");
	printf("  * $NULL$ : <name>: null object.\n");
	printf("  * @(<string>) : <name>: binded data.\n");
	printf("  * [<n>] : <bind>: data bind.\n");
	printf("  * @(<tree>*) : <bind>: pseudo-bind.\n");
}
void put_examples(void){
	printf("\n");
	printf("EXAMPLES\n");
	printf("********\n");
	printf("\n");
	printf("ex.1::\n");
	printf("\n");
	printf(" test.csv::\n");
	printf("\n");
	printf("  Length,Weight\n");
	printf("\n");
	printf(" $ echo '#1$Op$Name($#1[1])' | tq.o in=/dev/stdin -FT -Pin data=test.csv\n");
	printf("  => #1$Op$Name($#1[1]@@#1$Op$Name(Length))\n");
	printf("\n");
	printf(" - #1 : <label>\n");
	printf(" - $#1 : <reference>\n");
	printf(" - $Op$ : <operator>\n");
	printf(" - Name : <name>\n");
	printf(" - [1] : <bind>\n");
	printf(" - @ : <name>: binded mark\n");
	printf("\n");
	printf("ex.2 (referencing tree)::\n");
	printf("\n");
	printf(" $ echo 'A(B(#1C),$#1(D))'\n");
	printf("  => A(B(#1C),$#1@#1C(D))\n");
	printf("                  ^^^^^^^\n");
	printf("                  Binded referenced-tree.\n");
	printf("\n");
	printf("ex.3 (creating graph)::\n");
	printf("\n");
	printf(" $ echo '$G$($V$(#0,#1,#2),$E$($#0($#1,$#2),$#1($#0,$#2), $#2($#0,$#1)))' | tq.o in=/dev/stdin -FMa -Pin\n");
	printf("  =>\n");
	printf(" ====multiline====>\n");
	printf(" [:$G$:0],1,,,,5,,,,,,,,,,\n");
	printf(" ,[:$V$:1],2,3,4,,,,,,,,,,,\n");
	printf(" ,,[:#0:2],,,,,,,,,,,,,\n");
	printf(" ,,,[:#1:3],,,,,,,,,,,,\n");
	printf(" ,,,,[:#2:4],,,,,,,,,,,\n");
	printf(" ,,2,3,,[:$E$:5],6,,,9,,,12,,,\n");
	printf(" ,,,3,4,,[:$#0:6->2],7,8,,,,,,,\n");
	printf(" ,,,,,,,[:$#1:7->3],,,,,,,,\n");
	printf(" ,,,,,,,,[:$#2:8->4],,,,,,,\n");
	printf(" ,,2,,4,,,,,[:$#1:9->3],10,11,,,,\n");
	printf(" ,,,,,,,,,,[:$#0:10->2],,,,,\n");
	printf(" ,,,,,,,,,,,[:$#2:11->4],,,,\n");
	printf(" ,,2,3,,,,,,,,,[: $#2:12],13,14,\n");
	printf(" ,,,,,,,,,,,,,[:$#0:13->2],,\n");
	printf(" ,,,,,,,,,,,,,,[:$#1:14->3],\n");
	printf(" <====multiline====\n");
	printf("\n");
	printf("ex.4 (binding and reforming CSV)::\n");
	printf("\n");
	printf(" [bind]\n");
	printf("\n");
	printf(" test.csv::\n");
	printf("\n");
	printf("  Length,Weight\n");
	printf("  mm,kg\n");
	printf("  1,2\n");
	printf("  322,4\n");
	printf("  5,68\n");
	printf("\n");
	printf(" in.ddf::\n");
	printf("\n");
	printf("  (#1[2],#2[2],[3](#4[2]))\n");
	printf("\n");
	printf(" out.ddl::\n");
	printf("\n");
	printf("  $PI$($#1,Quantity($#4,$#2))\n");
	printf("\n");
	printf(" $ tq.o in=in.ddf out=out.ddl data=test.csv -FT -Pprod -C\n");
	printf("  => (((Length,Quantity(1,mm)),(Weight,Quantity(2,kg))),((Length,Quantity(322,mm)),(Weight,Quantity(4,kg))),((Length,Quantity(5,mm)),(Weight,Quantity(68,kg))))\n");
	//printf("ex.4 (binding and reforming CSV)::\n");
	printf("\n");
	printf(" [over write (1)]\n");
	printf("\n");
	printf(" test.csv::\n");
	printf("\n");
	printf("  Length,Weight\n");
	printf("  mm,kg\n");
	printf("  1,2\n");
	printf("  322,4\n");
	printf("  5,68\n");
	printf("\n");
	printf(" in.ddf::\n");
	printf("\n");
	printf("  (#1[2],#2[2],[3](#4[2]))\n");
	printf("\n");
	printf(" out2.ddl::\n");
	printf("\n");
	printf("  $PI$(@(L,W),Quantity($#4,$#2))\n");
	printf("       ^^^^^^\n");
	printf("       Binding data (distribution)\n");
	printf("\n");
	printf(" $ tq.o in=in.ddf out=out2.ddl data=test.csv -FT -Pprod -C\n");
	printf("  => (((L,Quantity(1,mm)),(W,Quantity(2,kg))),((L,Quantity(322,mm)),(W,Quantity(4,kg))),((L,Quantity(5,mm)),(W,Quantity(68,kg))))\n");
	printf("\n");
	printf(" [over write (2)]\n");
	printf("\n");
	printf(" DDL file::\n");
	printf("\n");
	printf("  $PI$((L,W),Quantity($#4,$#2))\n");
	printf("       ^^^^^\n");
	printf("       Binding data (bulk)\n");
	printf("\n");
	printf("NIMS Standard SpreadSheet (NS3)\n");
	printf("*******************************\n");
	printf("\n");
	printf("Definition:Cell::\n");
	printf("=================\n");
	printf("\n");
	printf(" <Cell>:: (<item-name>,Quantity(<value>,<unit>))\n");
	printf("\n");
	printf(" OR\n");
	printf("\n");
	printf(" <Cell>:: (<item-name>,<type>(<value>))\n");
	printf("\n");
	printf("Definition:Line (corresponds to a sample)::\n");
	printf("===========================================\n");
	printf("\n");
	printf(" <Line>:: (<Cell>, ... )\n");
	printf("\n");
	printf("Definition:Dataset::\n");
	printf("====================\n");
	printf("\n");
	printf(" <Dataset>:: (<Line>, ... )\n");
	printf("\n");
	printf(" NS3:: <Dataset>\n");
	printf("\n");
}

/* allocation */
struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		perror("[Fail]malloc@alloc_options().\n");
		exit(1);
	}
	if(((*p).in = malloc(sizeof(char) * LEN)) == NULL){
		perror("[Fail]malloc@alloc_options().\n");
		exit(1);
	}
	if(((*p).out = malloc(sizeof(char) * LEN)) == NULL){
		perror("[Fail]malloc@alloc_options().\n");
		exit(1);
	}
	if(((*p).data = malloc(sizeof(char) * LEN)) == NULL){
		perror("[Fail]malloc@alloc_options().\n");
		exit(1);
	}
	return(p);
}
struct function_options *alloc_function_options(void){
	struct function_options *p;
	if((p = malloc(sizeof(struct function_options) * 1)) == NULL){
		printf("[Fail]malloc@alloc_function_options().\n");
		exit(1);
	}
	return(p);
}
struct compile_options *alloc_compile_options(void){
	struct compile_options *p;
	if((p = malloc(sizeof(struct compile_options) * 1)) == NULL){
		printf("[Fail]malloc@alloc_compile_options().\n");
		exit(1);
	}
	return(p);
}
struct search_options *alloc_search_options(void){
	struct search_options *p;
	if((p = malloc(sizeof(struct search_options) * 1)) == NULL){
		printf("[Fail]malloc@alloc_search_options().\n");
		exit(1);
	}
	return(p);
}
struct data_options *alloc_data_options(void){
	struct data_options *p;
	if((p = malloc(sizeof(struct data_options) * 1)) == NULL){
		printf("[Fail]malloc@alloc_data_options().\n");
		exit(1);
	}
	return(p);
}

/* initialize */
void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).war = 0;
	(*opt).test = 0;
	(*opt).buff = BUFF_LEN;
	(*opt).data_buff = BUFF_LEN;
	(*opt).in[0] = '\0';
	(*opt).out[0] = '\0';
	(*opt).data[0] = '\0';
	(*opt).Pin = 0;
	(*opt).Pout = 0;
	(*opt).Pprod = 0;
	(*opt).hF = 0;
	(*opt).hC = 0;
	(*opt).hS = 0;
	(*opt).hD = 0;
	(*opt).hE = 0;
}
void init_function_options(struct function_options *fopt){
	FC(fprintf(stderr,">init_function_options<\n");)
	(*fopt).f_counter = 0;
	(*fopt).f_print_T = 0;
	(*fopt).f_print_S = 0;
	(*fopt).f_print_J = 0;
	(*fopt).f_print_W = 0;
	(*fopt).f_print_X = 0;
	(*fopt).f_print_C = 0;
	(*fopt).f_print_N = 0;
	(*fopt).f_print_Ma = 0;
	(*fopt).f_print_production = 0;
	(*fopt).f_print_status = 0;
	(*fopt).f_print_hierarchy = 0;
	(*fopt).f_print_hierarchy_status = 0;
	(*fopt).f_print_test = 0;
	(*fopt).f_print_self_stat = 0;
	(*fopt).f_skipOnce = 0;
}
void init_compile_options(struct compile_options *copt){
        (*copt).c_counter = 0;
        (*copt).c_list = 0;
        (*copt).c_restrict = 0;
        (*copt).c_clear = 0;
        (*copt).c_dot = 0;
}
void init_search_options(struct search_options *sopt){
        (*sopt).s_counter = 0;
        (*sopt).pos = NULL;
        (*sopt).head = NULL;
}
void init_data_options(struct data_options *dopt){
	(*dopt).d_counter = 0;
	(*dopt).dd = DD;
}

/* get options */
void get_options(int optc, char **optv, struct options *opt){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0 && strlen(optv[i]) == 2){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-s") == 0){
			(*opt).stat = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check = 1;
		}else if(strcmp(optv[i],"-test") == 0){
			(*opt).test = 1;
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff);
		}else if(strncmp(optv[i],"data_buff=",9) == 0){
			sscanf(optv[i],"data_buff=%d",&(*opt).data_buff);
		}else if(strncmp(optv[i],"w=",2) == 0){
			sscanf(optv[i],"w=%d",&(*opt).war);
		}else if(strncmp(optv[i],"-hF",3) == 0){
			(*opt).hF = 1;
		}else if(strncmp(optv[i],"-hC",3) == 0){
			(*opt).hC = 1;
		}else if(strncmp(optv[i],"-hS",3) == 0){
			(*opt).hS = 1;
		}else if(strncmp(optv[i],"-hD",3) == 0){
			(*opt).hD = 1;
		}else if(strncmp(optv[i],"-hE",3) == 0){
			(*opt).hE = 1;
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).in);
		}else if(strncmp(optv[i],"out=",4) == 0){
			sscanf(optv[i],"out=%s",(*opt).out);
		}else if(strncmp(optv[i],"data=",5) == 0){
			sscanf(optv[i],"data=%s",(*opt).data);
		}else if(strncmp(optv[i],"-Pin",4) == 0){
			(*opt).Pin = 2;
		}else if(strncmp(optv[i],"-Pout",5) == 0){
			(*opt).Pout = 2;
		}else if(strncmp(optv[i],"-Pprod",6) == 0){
			(*opt).Pprod = 1;
		}
	}
}
void get_function_options(int optc, char **optv, struct function_options *fopt){
	int i = 0;
	(*fopt).f_counter = 0;
	for(i=0;i<optc;i++){
		if(strncmp(optv[i],"-Ftest",6) == 0){
			(*fopt).f_print_test = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-FT",3) == 0){
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
		}else if(strncmp(optv[i],"-FWW",4) == 0){
			(*fopt).f_print_W = 2;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-FW",3) == 0){
			(*fopt).f_print_W = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-FX",3) == 0){
			(*fopt).f_print_X = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-FC",3) == 0){
			(*fopt).f_print_C = 1;
			(*fopt).f_counter++;
		}else if(strncmp(optv[i],"-FN",3) == 0){
			(*fopt).f_print_N = 1;
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
		if(strncmp(optv[i],"-C",2) == 0){
			(*copt).c_counter++;
		}
		if(strncmp(optv[i],"-CL",3) == 0){
			(*copt).c_list = 1;
			(*copt).c_counter++;
		}else if(strncmp(optv[i],"-Cr",3) == 0){
			(*copt).c_restrict = 1;
			(*copt).c_counter++;
		}else if(strncmp(optv[i],"-Cc",3) == 0){
			(*copt).c_clear = 1;
			(*copt).c_counter++;
		}else if(strncmp(optv[i],"-Cd",3) == 0){
			(*copt).c_dot = 1;
			(*copt).c_counter++;
		}
	}
}
void get_search_options(int optc, char **optv, struct search_options *sopt){
	int i = 0;
	int opt_len = 0;
	(*sopt).s_counter = 0;
	for(i=0;i<optc;i++){
		if(strncmp(optv[i],"Sp=",3) == 0){
			(*sopt).s_counter++;
			opt_len = strlen(optv[i])-3;
			(*sopt).pos = malloc(sizeof(char) * (opt_len + 1));
			if((*sopt).pos == NULL){
				perror("[Fail]malloc@get_search_options.\n");
				exit(1);
			}
			strcpy((*sopt).pos,optv[i]+3);
		}else if(strncmp(optv[i],"Sh=",3) == 0){
			(*sopt).s_counter++;
			opt_len = strlen(optv[i])-3;
			(*sopt).head = malloc(sizeof(char) * (opt_len + 1));
			if((*sopt).head == NULL){
				perror("[Fail]malloc@get_search_options.\n");
				exit(1);
			}
			strcpy((*sopt).head,optv[i]+3);
		}
	}
}
void get_data_options(int optc, char **optv, struct data_options *dopt){
	int i = 0;
	(*dopt).d_counter = 0;
	for(i=0;i<optc;i++){
		if(strncmp(optv[i],"DD=",3) == 0){
			sscanf(optv[i],"DD=%c",&(*dopt).dd);
		}
	}
}

/* checking */
void check_options(struct options *opt){
	printf("\n");
	printf("OPTION SETTING\n");
	printf("==============\n\n");
	printf(" * opt.help:%d:\n",(*opt).help);
	printf(" * opt.stat:%d:\n",(*opt).stat);
	printf(" * opt.check:%d:\n",(*opt).check);
	printf(" * opt.war:%d:\n",(*opt).war);
	printf(" * opt.test:%d:\n",(*opt).test);
	printf(" * opt.buff:%d:\n",(*opt).buff);
	printf(" * opt.data_buff:%d:\n",(*opt).data_buff);
	printf(" * opt.in:\"%s\":\n",(*opt).in);
	printf(" * opt.out:\"%s\":\n",(*opt).out);
	printf(" * opt.data:\"%s\":\n",(*opt).data);
	printf(" * opt.Pin:%d:\n",(*opt).Pin);
	printf(" * opt.Pout:%d:\n",(*opt).Pout);
	printf(" * opt.Pprod:%d:\n",(*opt).Pprod);
	printf(" * opt.hF:%d:\n",(*opt).hF);
	printf(" * opt.hC:%d:\n",(*opt).hC);
	printf(" * opt.hS:%d:\n",(*opt).hS);
	printf(" * opt.hD:%d:\n",(*opt).hD);
	printf(" * opt.hE:%d:\n",(*opt).hE);
}
void check_function_options(struct function_options *fopt){
	printf("\n|\n\n");
	printf(" * converters:\n\n");
	printf("  * opt.fcount:%d:\n",(*fopt).f_counter);
	printf("  * opt.FT:%d:\n",(*fopt).f_print_T);
	printf("  * opt.FS:%d:\n",(*fopt).f_print_S);
	printf("  * opt.FJ:%d:\n",(*fopt).f_print_J);
	printf("  * opt.FW:%d:\n",(*fopt).f_print_W);
	printf("  * opt.FX:%d:\n",(*fopt).f_print_X);
	printf("  * opt.FC:%d:\n",(*fopt).f_print_C);
	printf("  * opt.FN:%d:\n",(*fopt).f_print_N);
	printf("  * opt.FMa:%d:\n",(*fopt).f_print_Ma);
	printf("  * opt.Fst:%d:\n",(*fopt).f_print_status);
	printf("  * opt.Fh:%d:\n",(*fopt).f_print_hierarchy);
	printf("  * opt.Fhst:%d:\n",(*fopt).f_print_hierarchy_status);
	printf("  * opt.Ftest:%d:\n",(*fopt).f_print_test);
}
void check_compile_options(struct compile_options *copt){
	printf("\n|\n\n");
	printf(" * compilers:\n\n");
	printf("  * opt.ccount:%d:\n",(*copt).c_counter);
	printf("  * opt.c_list:%d:\n",(*copt).c_list);
	printf("  * opt.c_restrict:%d:\n",(*copt).c_restrict);
	printf("  * opt.c_clear:%d:\n",(*copt).c_clear);
	printf("  * opt.c_dot:%d:\n",(*copt).c_dot);
}
void check_search_options(struct search_options *sopt){
	printf("\n|\n\n");
	printf(" * search:\n\n");
	printf("  * opt.scount:%d:\n",(*sopt).s_counter);
	printf("  * opt.pos:%s:\n",(*sopt).pos);
	printf("  * opt.head:%s:\n",(*sopt).head);
}
void check_data_options(struct data_options *dopt){
	printf("\n|\n\n");
	printf(" * data:\n\n");
	printf("  * opt.DD:%c:\n",(*dopt).dd);
}

/* main */
int main(int argc, char **argv){
	struct options *opt;
	struct function_options *_fopt;
	struct compile_options *_copt;
	struct search_options *_sopt;
	struct data_options *_dopt;
	int node_count;
	struct Tree *itop = NULL;
	struct Tree *otop = NULL;
	struct Tree *null_node = NULL;
	int ie = 0;
	FILE *IN;
	FILE *DATA = NULL;
	int is_iopen = 0;
	int is_dopen = 0;
	int is_oopen = 0;

	/* options */
	/** main opt */
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	/** function opt */
	_fopt = alloc_function_options();
	init_function_options(_fopt);
	get_function_options(argc-1, argv+1, _fopt);
	/** compile opt */
	_copt = alloc_compile_options();
	init_compile_options(_copt);
	get_compile_options(argc-1, argv+1, _copt);
	/** search opt */
	_sopt = alloc_search_options();
	init_search_options(_sopt);
	get_search_options(argc-1, argv+1, _sopt);
	/** data opt */
	_dopt = alloc_data_options();
	init_data_options(_dopt);
	get_data_options(argc-1, argv+1, _dopt);

	/* print help operation */
	if(argc == 1){
		(*opt).help = 1;
	}
	if((*opt).help == 1){
		help();
		language_help();
		ie = 1;
	}
	if((*opt).hF == 1 || (*opt).hC == 1 || (*_copt).c_list == 1 || (*opt).hS == 1 || (*opt).hD == 1){
		option_header();
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
	if((*_copt).c_list == 1){
		list_builtins();	
		ie = 1;
	}
	if((*opt).hS == 1){
		search_help();
		ie = 1;
	}
	if((*opt).hD == 1){
		data_help();
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
		check_search_options(_sopt);
		check_data_options(_dopt);
		ie = 1;
	}
	if((*opt).hE == 1){
		put_examples();
		ie = 1;
	}


	if(ie == 1){
		exit(0);
	}

	/* for search */
        null_node = Create_Node(-1,(*opt).buff);
        strcpy((*null_node).Head,"$NULL$");
        (*null_node).LVself = -1;
        (*null_node).NCself = 1;

	/* EXEC_FLAG */
	int EFLAG = 0;
	// 0 : no exec
	// 1 : bind data
	// 2 : print
	// 4 : bind ref-node

	/* input-form file */
	if(strlen((*opt).in) > 0){
		/** open data file */
		if(strlen((*opt).data) > 0){
			if((DATA = fopen((*opt).data,"r")) == NULL){
				perror((*opt).data);
				exit(1);
			}
			is_dopen = 1;
		}

		/** open in-file */
		if((IN = fopen((*opt).in,"r")) == NULL){
			perror((*opt).in);
			exit(1);
		}
		is_iopen = 1;
		/** import tree */
		node_count = 0;
		EFLAG = (*opt).Pin+1+8;	//Pin: 2
		itop = import_Tree(IN,opt,_fopt,_copt,_sopt,&node_count,EFLAG,DATA);
		Executor(itop,null_node,null_node,EOF,node_count,opt,_fopt,_copt,_sopt,DATA,EFLAG);	
		/** close in-file */
		if(is_iopen > 0){
			fclose(IN);
		}

		/** close data file*/
		if(is_dopen > 0){
			fclose(DATA);
		}
	}
	/* outout-form file */
	if(strlen((*opt).out) > 0){
		/** open */
		if((IN = fopen((*opt).out,"r")) == NULL){
			perror((*opt).out);
			exit(1);
		}
		is_oopen = 1;
		/** import tree */
		EFLAG = (*opt).Pout+4;	//Pout: 2
		otop = import_Tree(IN,opt,_fopt,_copt,_sopt,&node_count,EFLAG,NULL);
		Executor(otop,itop,null_node,EOF,node_count,opt,_fopt,_copt,_sopt,DATA,EFLAG);
		/** close file */
		if(is_oopen > 0){
			fclose(IN);
		}
	}
	/* inner product */
	if((*opt).Pprod == 1 && itop != NULL && otop != NULL){
		EFLAG = 16;
		(*_fopt).f_print_production = 1;
		Executor(itop,null_node,null_node,EOF,node_count,opt,_fopt,_copt,_sopt,DATA,EFLAG);	//これを実行しないと次が正常に実行されないので注意
		EFLAG = 2 + 16;
		Executor(otop,itop,null_node,EOF,node_count,opt,_fopt,_copt,_sopt,DATA,EFLAG);
	}

	/* terminal report */
	fprintf(stderr,"%d Nodes were operated.\n",node_count);

	/* check */
	if((*opt).test > 0){
		printf("\n=TEST OUTPUT=>\n");
		printf("No test code.\n");
		printf("\n<==\n");
	}

	/* finish */
	return(0);
}
