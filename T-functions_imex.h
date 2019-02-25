#include "../RECURSIVE-SYSTEM/T-definition.h"
//import/export 
////current unctions
////import and apply(NEW)
void print_war(char _C, struct Tree *_tree, int level){
	printf("\n:C=%c: ",_C);
	printf(":Pp=%ld:",(long int)(*_tree).Parent);
	printf(":Cp=%ld:",(long int)_tree);
	printf(":Cj=%d:",(*_tree).Conj);
	printf(":Op=%d:",(*_tree).Bopen);
	printf(":current=%s:",(*_tree).Head);
	printf(":Cl=%d:",(*_tree).Bclose);
	printf(":LV=%d:",(*_tree).LVself);
	printf(":NCs=%d:",(*_tree).NCself);
	printf(":NC=%d:",(*_tree).NextCount);
}
int import_Tree(FILE *_IN, struct Tree *top, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, int *ncount){
	int WAR;
	int C;
	int DLM_ACC = 1;
	char *BUFF;
	int buf_ptr = 0;
	struct Tree *current;
	struct Tree *next;
	int close = 0;
	int ESC = 0;
	int SN = 1;
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
			print_war(C,current,WAR);
		}
		/* set conditions */
		if(C == '[' && ESC == 0){
			DLM_ACC--;
		}
		if(C == ']' && ESC == 0){
			DLM_ACC++;
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
				print_war(C,current,WAR);
			}
			/* create next */
			next = Create_Node(SN,BUFF_LEN);
			SN++;
			*ncount = SN;
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
				print_war(C,current,WAR);
			}
			/* create next */
			next = Create_Node(SN,BUFF_LEN);
			SN++;
			*ncount = SN;
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
			/* Bclose transfar */
			//再帰呼び出し関数ではかっこをprintしないので、
			//かっこのprint情報を子に移す。
			if(close == 0){
				strcpy((*current).Head,BUFF);
				(*current).Bclose = 1;
			}else{
				Add_Bclose_To_Next(current);
			}
			/* check */
			if(WAR > 0){
				print_war(C,current,WAR);
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
		}else if(C == LF || C == TAB){
			/* 0 single/1 multi/2 individual */
			if((*_opt).form == 0){
				; // executed bellow
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
				#include "T-functions_imex-branch.h"
				/* clear tree */
				Function_RecursiveFreeForce(top);
				free(top);
				top = Create_Node(SN,BUFF_LEN);
				SN++;
				*ncount = SN;
				ESC = 0;
			}
			/* post-check code */
			#ifdef DB
			printf("nodes_in_importAPP:%d:\n",*ncount);
			#endif
		}else if(C == EOF){
			close = 0;
			ESC = 0;
			if((*_opt).form == 0){
				#include "T-functions_imex-branch.h"
			}
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


