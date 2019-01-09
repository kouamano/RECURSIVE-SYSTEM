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
#include "../RECURSIVE-SYSTEM/list.h"

struct options {
	int help;
	int stat;
	int check;
	int buff;
	int war;
	char *in;
};

void help(void){
	printf("USAGE:\n");
	printf(" cts [-h] [-s] [-c] buff=<size(int)> in=<input file> w=<print warnning>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  buff : set integer.\n");
	printf("  in : set *chars (len < 1024).\n");
	printf("  war : set integer.\n");
}

void status(void){
	printf("STATUS:\n");
	printf("  testging.\n");
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

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).buff = BUFF_LEN;
	(*opt).in[0] = '\0';
	(*opt).war = 0;
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
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff);
		}else if(strncmp(optv[i],"w=",2) == 0){
			sscanf(optv[i],"w=%d",&(*opt).war);
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).in);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.buff:%d:\n",(*opt).buff);
	printf(" opt.in:%s:\n",(*opt).in);
	printf(" opt.war:%d:\n",(*opt).war);
}

// function definition
int store_CHAR(FILE *_IN, struct List *top, int WAR){
	int i;
	int itrs;
	int C;
	int DLM_ACC = 1;
	int LIST_LV = 0;
	int NEXT_COUNT = 0;
	int ARG_COUNT = 0;
	char *BUFF;
	int buf_ptr = 0;
	struct List *parent;
	struct List *current;
	struct List *next;
	struct List *arg;
	int close = 0;
	current = top;
	if((BUFF = malloc(sizeof(char) * BUFF_LEN)) == NULL){
		printf("[Fail] malloc.\n");
		exit(1);
	}
	while(C = fgetc(_IN)){
		//check chars
		if(WAR > 0){
		printf("\n:C=%c: ",C);
		}
		//set conditions
		if(C == '['){
			DLM_ACC--;
		}
		if(C == ']'){
			DLM_ACC++;
		}
		if(C == ',' && DLM_ACC > 0){
			ARG_COUNT++;
		}
		if(C == '('){
			LIST_LV++;
		}
		if(C == ')'){
			LIST_LV--;
		}
		//function code
		if(C == '('){
			//confirm current
			BUFF[buf_ptr] = '\0';
			if(strlen(BUFF) > 0 && close == 0){
				strcpy((*current).Head,BUFF);
			}
			if(WAR > 0){
			printf(":B=%s:",(*current).Head);
			printf(":Pp=%ld:",(*current).Parent);
			printf(":Cp=%ld:",current);
			printf(":LVs=%d:",(*current).LVself);
			printf(":NCs=%d:",(*current).NCself);
			printf(":ACs=%d:",(*current).ACself);
			printf(":Cl=%d:",close);
			}
			//alloc next
			next = Function_Create_Node();
			//create next
			Function_Add_NextRtd((*current).Parent,current,next);
			//prepare next
			current = next;
			//clear BUFF
			BUFF[0] = '\0';
			buf_ptr = 0;
			close = 0;
		}else if(C == ',' && DLM_ACC > 0){
			//confirm current
			BUFF[buf_ptr] = '\0';
			if(close == 0){
				strcpy((*current).Head,BUFF);
			}
			if(WAR > 0){
			printf(":B=%s:",(*current).Head);
			printf(":Pp=%ld:",(*current).Parent);
			printf(":Cp=%ld:",current);
			printf(":LVs=%d:",(*current).LVself);
			printf(":NCs=%d:",(*current).NCself);
			printf(":ACs=%d:",(*current).ACself);
			printf(":Cl=%d:",close);
			}
			//alloc arg
			arg = Function_Create_Node();
			//create arg
			if((*current).ACself == 0){
				Function_Add_ArgRtd((*current).Parent,current,arg);
			}else{
				current = (*current).Parent;
				Function_Add_ArgRtd((*current).Parent,current,arg);
			}
			//prepare arg
			current = arg;
			//clear BUFF
			BUFF[0] = '\0';
			buf_ptr = 0;
			close = 0;
		}else if(C == ')'){
			//confirm current
			BUFF[buf_ptr] = '\0';
			if(close == 0){
				strcpy((*current).Head,BUFF);
			}
			if(WAR > 0){
			printf(":B=%s:",(*current).Head);
			printf(":Pp=%ld:",(*current).Parent);
			printf(":Cp=%ld:",current);
			printf(":LVs=%d:",(*current).LVself);
			printf(":NCs=%d:",(*current).NCself);
			printf(":ACs=%d:",(*current).ACself);
			printf(":Cl=%d:",close);
			}
			//clear BUFF
			BUFF[0] = '\0';
			buf_ptr = 0;
			//prepare current
			if((*current).ACself > 0){
				current = (*current).Parent;
			}
			if((*current).Parent != NULL){
				current = (*current).Parent;
			}
			close++;
		}else if(C == '\n'){
			//print BUFF
			BUFF[buf_ptr] = '\0';
			printf("%s",BUFF);
			//clear BUFF
			BUFF[0] = '\0';
			buf_ptr = 0;
			//print check code
			if(WAR > 1){
			printf("\n-----\n");
			ExFunction_Recursive_Tree_Print(top,(struct List *(*)())Function_Print_Status,0,NULL,1);
			printf("\n#T "); ExFunction_Recursive_Tree_Print(top,(struct List *(*)())Function_Print_Status,0,NULL,2);
			printf("\n#S "); ExFunction_Recursive_S_Print(top,(struct List *(*)())Function_Print_Status,0,NULL,2);
			ExFunction_Recursive_Tree_Print(top,(struct List *(*)())Function_Print_Status,1,NULL,3);
			printf("\n-----\n");
			}
			//final putput
			ExFunction_Recursive_S_Print(top,(struct List *(*)())Function_Print_Status,0,NULL,2); printf("\n");
			//clear tree
			//Function_Free_List(top,0);
			init_List_zero(top);
			close = 0;
		}else if(C == EOF){
			return(C);
		}else{
			//buffering
			BUFF[buf_ptr] = C;
			BUFF[buf_ptr+1] = '\0';
			buf_ptr++;
			close = 0;
		}
	}
	return(C);
}


int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	FILE *IN;
	int is_open = 0;
	int c;
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
	// open file
	if((IN = fopen((*opt).in,"r")) == NULL){
		perror((*opt).in);
		exit(1);
	}
	is_open = 1;

	// main function
	c = 1;
	struct List *top;
	if((top = malloc(sizeof(struct List) * 1)) == NULL){
		printf("[Fail] malloc.\n");
		exit(1);
	}
	init_List_zero(top);
	while(c != EOF){
		c = store_CHAR(IN,top,(*opt).war);
	}

	// close file
	if(is_open > 0){
		fclose(IN);
	}

	// finish
	return(0);
}
