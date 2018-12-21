#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF_LEN
#define BUFF_LEN 1024
#endif

//structure
struct Tree {
	int LVself;
	int NCself;
	int Conj;
	int Bopen;
	char *Head;
	int Bclose;
	int NextCount;
	struct Tree **Next;
	struct Tree *Parent;
};

//single function
////restructure functions
struct Tree *Create_Node(int H_size){
	struct Tree *tree;
	if((tree = malloc(sizeof(struct Tree) * 1)) == NULL){
		fprintf(stderr,"[Fail] malloc.\n");
		exit(1);
	}
	(*tree).LVself=0;
	(*tree).NCself=0;
	(*tree).Conj=0;
	(*tree).Bopen=0;
	(*tree).Head = malloc(sizeof(char) * H_size);
	if((*tree).Head == NULL){
		fprintf(stderr,"[Fail] malloc.\n");
		exit(1);
	}
	(*tree).Bclose=0;
	(*tree).NextCount=0;
	(*tree).Next = malloc((size_t)sizeof(struct Tree *) * 1);
	if((*tree).Next == NULL){
		fprintf(stderr,"[Fail] malloc.\n");
		exit(1);
	}
	(*tree).Parent=NULL;
	return(tree);
}
struct Tree *Add_Next(struct Tree *parent, struct Tree *next){
	(*parent).Next = realloc((*parent).Next,(size_t)sizeof(struct Tree *) * (*parent).NextCount+1);
	if((*parent).Next == NULL){
		fprintf(stderr,"[Fail] malloc.\n");
	}
	(*parent).Next[(*parent).NextCount] = next;
	(*parent).Next[(*parent).NextCount]->LVself = (*parent).LVself+1;
	(*parent).Next[(*parent).NextCount]->NCself = (*parent).NextCount+1;
	(*parent).Next[(*parent).NextCount]->Parent = parent;
	(*parent).NextCount++;
	return(next);
}
int Add_Bclose_To_Next(struct Tree *tree){
	//Bcloseの回数を、Closeしていない親からCloseしている子に加算する
	if((*tree).NextCount == 0){
		(*tree).Bclose++;
		return(1);
	}else{
		Add_Bclose_To_Next((*tree).Next[(*tree).NextCount-1]);
		return(0);
	}
}
////status-check functions
void Function_Print_Status(struct Tree *tree){
	struct Tree *parent = (*tree).Parent;
	printf("  :LVs=%d:",(*tree).LVself);
	printf(":NCs=%d:",(*tree).NCself);
	printf(":Cj=%d:",(*tree).Conj);
	printf(":O=%d:",(*tree).Bopen);
	printf(":H=%s:",(*tree).Head);
	printf(":C=%d:",(*tree).Bclose);
	printf(":Nc=%d:",(*tree).NextCount);
	if(parent != NULL){
		printf(":Pa=%s:",(*parent).Head);
	}else{
		printf(":Pa=%s:","");
	}
	printf("\n");
}
int Function_Count_NextConjZero(struct Tree *tree){
	int i;
	int count = 0;
	if((*tree).NextCount == 0){
		return(0);
	}else{
		for(i=0;i<(*tree).NextCount;i++){
			if((*tree).Next[i]->Conj == 0){
				count++;
			}
		}
	}
	return(count);
}
////print-head function
int Function_Print_Head(struct Tree *tree){
	int i;
	int not_print_Bclose = 0;
	if((*tree).Conj){
		printf(",");
	}
	if((*tree).Bopen){
		printf("(");
	}
	printf("%s",(*tree).Head);
	//if((*tree).Bclose > 0 && (*tree).NextCount == 0){
	if((*tree).Bclose > 0 && (*tree).NextCount == 0){
		for(i=0;i<((*tree).Bclose);i++){
			printf(")");
		}
	}else if((*tree).Bclose > 0){
		not_print_Bclose = not_print_Bclose + (*tree).Bclose;
	}
	return(not_print_Bclose);
}
////print indent head function
int Function_Print_HeadIndent(struct Tree *tree){
	int i;
	for(i=0;i<(*tree).LVself;i++){
		printf("  ");
	}
	if((*tree).Conj == 1 && (*tree).NCself > 1){
		printf("+");
	}else{
		printf("-");
	}

	printf("%s\n",(*tree).Head);
}
int Function_Print_Head_S(struct Tree *tree){
	int i;
	int countCZ = 0;
	countCZ = Function_Count_NextConjZero(tree);
	/* print "," for Conj */
	if((*tree).Conj == 1 || (*tree).Bopen > 0){
		printf(",");
	}
	/* print Bopen */
	for(i=0;i<countCZ;i++){
		printf("(");
	}
	/* print Head */
	printf("%s",(*tree).Head);
	/* print Bclose */
	for(i=0;i<(*tree).Bclose;i++){
		printf(")");
	}
	/* print "," for Next */
	if((*tree).NextCount > 0){
		//printf(",");
	}
}
int Function_Print_HeadAndStatus(struct Tree *tree){
	int i;
	int countCZ = 0;
	countCZ = Function_Count_NextConjZero(tree);
	for(i=0;i<(*tree).LVself;i++){
		printf("  ");
	}
	if((*tree).Conj == 1 && (*tree).NCself > 1){
		printf("+");
	}else{
		printf("-");
	}
	/* print "," for Conj */
	if((*tree).Conj == 1){
		printf(",");
	}
	/* print Bopen */
	for(i=0;i<countCZ;i++){
		printf("(");
	}
	/* print Head */
	printf("%s",(*tree).Head);
	/* print Bclose */
	for(i=0;i<(*tree).Bclose;i++){
		printf(")");
	}
	/* print "," for Next */
	if((*tree).NextCount > 0){
		printf(",");
	}
	printf("  :CZ=%d:",countCZ);
	printf(":NC=%d:",(*tree).NextCount);
	printf(":Cj=%d:",(*tree).Conj);
	printf(":Cl=%d:",(*tree).Bclose);
	printf("\n");
}
////recursive meta-function
struct Tree *ExFunction_Recursive( struct Tree *tree, struct Tree *(*e_function)(struct Tree *) ){
	int i;
	struct Tree *out = tree;
	if(tree == NULL || e_function == NULL){
		fprintf(stderr,"NULL.\n");
		exit(1);
	}
	(*e_function)(tree);
	for(i=0;i<(*tree).NextCount;i++){
		ExFunction_Recursive((*tree).Next[i],e_function);
	}
	return(out);
}
//complex function
////recursive print function
void Function_RecursivePrint_Head(struct Tree *tree){
	int i;
	if((*tree).NCself > 0){
		if((*tree).Conj == 1 && (*tree).NCself > 1){
			printf(",");
		}else if((*tree).NCself > 1){
			printf(")(");
		}
	}
	printf("%s",(*tree).Head);
	if((*tree).NextCount > 0){
		printf("(");
		for(i=0;i<(*tree).NextCount;i++){
			Function_RecursivePrint_Head((*tree).Next[i]);
		}
		printf(")");
	}
}

//import/export 
////import function
int read_Tree(FILE *_IN, struct Tree *top, int WAR){
	//int i;
	//int itrs;
	int C;
	int DLM_ACC = 1;
	int LIST_LV = 0;
	//int NEXT_COUNT = 0;
	int ARG_COUNT = 0;
	char *BUFF;
	int buf_ptr = 0;
	//struct Tree *parent;
	struct Tree *current;
	struct Tree *next;
	int close = 0;
	//parent = NULL;
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
		/* function code */
		if(C == '('){
			/* confirm current */
			BUFF[buf_ptr] = '\0';
			if(close == 0){
				strcpy((*current).Head,BUFF);
			}
			(*current).Bclose = 0;
			/* check */
			if(WAR > 0){
			printf(":Pp=%ld:",(*current).Parent);
			printf(":Cp=%ld:",current);
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
		}else if(C == ',' && DLM_ACC > 0){
			/* confirm current */
			BUFF[buf_ptr] = '\0';
			if(close == 0){
				strcpy((*current).Head,BUFF);
			}
			(*current).Bclose = 0;
			/* check */
			if(WAR > 0){
			printf(":Pp=%ld:",(*current).Parent);
			printf(":Cp=%ld:",current);
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
		}else if(C == ')'){
			//parent = (*current).Parent;
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
			printf(":Pp=%ld:",(*current).Parent);
			printf(":Cp=%ld:",current);
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
		}else if(C == '\n'){
			/* print BUFF */
			BUFF[buf_ptr] = '\0';
			printf("%s",BUFF);
			/* clear BUFF */
			BUFF[0] = '\0';
			buf_ptr = 0;

			/* clear tree */
			close = 0;
		}else if(C == EOF){
			close = 0;
			return(C);
		}else{
			/* buffering */
			BUFF[buf_ptr] = C;
			BUFF[buf_ptr+1] = '\0';
			buf_ptr++;
			close = 0;
		}
	}
	return(C);
}

