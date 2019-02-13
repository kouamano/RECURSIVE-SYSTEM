#include "../RECURSIVE-SYSTEM/T-definition.h"
//import/export 
////current unctions
////import and apply(NEW)
int importApp_Tree(FILE *_IN, struct Tree *top, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt){
	int WAR;
	int C;
	int DLM_ACC = 1;
	int LIST_LV = 0;
	int ARG_COUNT = 0;
	char *BUFF;
	int buf_ptr = 0;
	struct Tree *current;
	struct Tree *next;
	int close = 0;
	int ESC = 0;
	WAR = (*_opt).war;
	current = top;
	next = NULL;
	if((BUFF = malloc(sizeof(char) * BUFF_LEN)) == NULL){
		printf("[Fail] malloc.\n");
		exit(1);
	}
	while((C = fgetc(_IN))){
		/* check chars */
		if(WAR > 0){
		printf("\n:C=%c: ",C);
		}
		/* set conditions */
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
		if(C == '\\'){
			ESC = 1;
		}
		/* function code */
		if(C == '(' && ESC == 0){
			/* confirm current */
			BUFF[buf_ptr] = '\0';
			if(close == 0){
				strcpy((*current).Head,BUFF);
			}
			(*current).Bclose = 0;
			/* check */
			if(WAR > 0){
			printf(":Pp=%ld:",(long int)(*current).Parent);
			printf(":Cp=%ld:",(long int)current);
			printf(":Cj=%d:",(*current).Conj);
			printf(":Op=%d:",(*current).Bopen);
			printf(":current=%s:",(*current).Head);
			printf(":Cl=%d:",(*current).Bclose);
			printf(":LV=%d:",(*current).LVself);
			printf(":NCs=%d:",(*current).NCself);
			printf(":NC=%d:",(*current).NextCount);
			}
			/* create next */
			next = Create_Node(BUFF_LEN);
			/* add next to current / current.NextCount / next.LVself, NCself */
			Add_Next(current,next);
			/* set properties of next */
			(*next).Bclose = 0;
			(*next).Bopen = 1;
			(*next).Conj = 0;
			/* clear BUFF */
			BUFF[0] = '\0';
			buf_ptr = 0;
			/* set node_parent */
			//parent = current;
			/* set node_current */
			current = next;
			close = 0;
		}else if(C == ',' && DLM_ACC > 0 && ESC == 0){
			/* confirm current */
			BUFF[buf_ptr] = '\0';
			if(close == 0){
				strcpy((*current).Head,BUFF);
			}
			(*current).Bclose = 0;
			/* check */
			if(WAR > 0){
			printf(":Pp=%ld:",(long int)(*current).Parent);
			printf(":Cp=%ld:",(long int)current);
			printf(":Cj=%d:",(*current).Conj);
			printf(":Op=%d:",(*current).Bopen);
			printf(":current=%s:",(*current).Head);
			printf(":Cl=%d:",(*current).Bclose);
			printf(":LV=%d:",(*current).LVself);
			printf(":NCs=%d:",(*current).NCself);
			printf(":NC=%d:",(*current).NextCount);
			}
			/* create next */
			next = Create_Node(BUFF_LEN);
			/* add next */
			Add_Next((*current).Parent,next);
			/* set properties of next */
			(*next).Bclose = 0;
			(*next).Bopen = 0;
			(*next).Conj = 1;
			/* clear BUFF */
			BUFF[0] = '\0';
			buf_ptr = 0;
			/* set node_parent */
			// parent = parent;
			/* set node_current */
			current = next;
			close = 0;
		}else if(C == ')' && ESC == 0){
			/* confirm current */
			BUFF[buf_ptr] = '\0';
			if(close == 0){
				strcpy((*current).Head,BUFF);
				(*current).Bclose = 1;
			}else{
				Add_Bclose_To_Next(current);
			}
			/* check */
			if(WAR > 0){
			printf(":Pp=%ld:",(long int)(*current).Parent);
			printf(":Cp=%ld:",(long int)current);
			printf(":Cj=%d:",(*current).Conj);
			printf(":Op=%d:",(*current).Bopen);
			printf(":current=%s:",(*current).Head);
			printf(":Cl=%d:",(*current).Bclose);
			printf(":LV=%d:",(*current).LVself);
			printf(":NCs=%d:",(*current).NCself);
			printf(":NC=%d:",(*current).NextCount);
			}
			/* clear BUFF */
			BUFF[0] = '\0';
			buf_ptr = 0;
			/* set node_parent */
			// parent = parent;
			/* set node_current */
			if((*current).Parent != NULL){
				current = (*current).Parent;
			}
			close++;
		}else if(C == LF){
			/* 0 single/1 multi/2 individual */
			if((*_opt).form == 0){
				; // already executed on highter level
			}else if((*_opt).form == 1){
				; // under construction
			}else if((*_opt).form == 2){
				/* copy BUFF */
				BUFF[buf_ptr] = '\0';
				if(close == 0){
					strcpy((*current).Head,BUFF);
				}
				/* clear BUFF */
				BUFF[0] = '\0';
				buf_ptr = 0;
				close = 0;
				/* apply functions */
				// basic formatter,
				// compiler.
				#include "T-import_export_app-branch.h"
				/* clear tree */
				Function_RecursiveFreeForce(top);
				free(top);
				top = Create_Node(BUFF_LEN);
				ESC = 0;
			}
		}else if(C == EOF){
			close = 0;
			ESC = 0;
			return(C);
		}else{
			/* buffering */
			BUFF[buf_ptr] = C;
			BUFF[buf_ptr+1] = '\0';
			buf_ptr++;
			close = 0;
			if(C == '\\'){
				ESC = 1;
			}else{
				ESC = 0;
			}
		}
	}
	return(C);
}


