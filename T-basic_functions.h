#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF_LEN
#define BUFF_LEN 1024
#endif

//basic function
////testing functions
int Detect_Dim(const char *head, int *pos){
	//under construction
	int len;
	int dim_s = -1;
	int dim_e = -1;
	int esc = 0;
	int i;
	int ret = 0;
	len = strlen(head);
	//printf(":%d:",len);
	/*
	if((_new_head = malloc(sizeof(char) * (len+10))) == NULL){
		perror("[Fail] malloc @ Reform_DimJ.\n");
		exit(1);
	}
	_new_head[0] = '\0';
	*/
	for(i=0;i<len;i++){
		if(head[i] == '\\'){
			esc = 1;
		}else if(head[i] == '[' && esc == 0){
			dim_s = i;
			esc = 0;
		}else if(head[i] == ']' && esc == 0){
			dim_e = i;
			esc = 0;
		}else{
			esc = 0;
		}
	}
	pos[0] = dim_s;
	pos[1] = dim_e;
	if(dim_s > -1){
		ret++;
	}
	if(dim_e > -1){
		ret++;
	}
	if(ret == 2){
	}
	return(ret);
}
////restructure functions
struct Tree *Create_Node(int H_size){
	struct Tree *tree;
	if((tree = malloc(sizeof(struct Tree) * 1)) == NULL){
		fprintf(stderr,"[Fail] malloc.\n");
		exit(1);
	}
	(*tree).LVself=0;
	//(*tree).NCself=0;
	(*tree).NCself=1;
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
	printf(":LVs=%d:",(*tree).LVself);
	printf(":NCs=%d:",(*tree).NCself);
	printf(":Cj=%d:",(*tree).Conj);
	printf(":BO=%d:",(*tree).Bopen);
	printf(":H=%s:",(*tree).Head);
	printf(":BC=%d:",(*tree).Bclose);
	printf(":NC=%d:",(*tree).NextCount);
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
void Function_Print_HeadHierarchy(struct Tree *tree){
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
////print indent head function and status
void Function_Print_HeadHierarchyStatus(struct Tree *tree){
	//bug remains.
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
		//printf(",");
	}
	/* print Bopen */
	for(i=0;i<countCZ;i++){
		//printf("(");
	}
	/* print Head */
	printf("%s",(*tree).Head);
	/* print Bclose */
	for(i=0;i<(*tree).Bclose;i++){
		//printf(")");
	}
	/* print "," for Next */
	if((*tree).NextCount > 0 && strlen((*tree).Next[(*tree).NextCount-1]->Head) > 0){
		//printf(",");
	}
	printf("  :LV=%d:",(*tree).LVself);
	printf(":NCs=%d:",(*tree).NCself);
	printf(":C0=%d:",countCZ);
	printf(":NC=%d:",(*tree).NextCount);
	printf(":Cj=%d:",(*tree).Conj);
	printf(":Cl=%d:",(*tree).Bclose);
	printf("\n");
}
////print S-form
void Function_Print_Head_S(struct Tree *tree){
	//debug complete?
	int i;
	int countCZ = 0;
	countCZ = Function_Count_NextConjZero(tree);
	/* print "," for Conj */
	if(((*tree).Conj == 1 || (*tree).Bopen > 0)&&(strlen((*tree).Head) > 0)){
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
////print JSON-form
////Under construction
void Function_Print_Head_J(struct Tree *tree){
	//debug complete?
	int i;
	int countCZ = 0;
	countCZ = Function_Count_NextConjZero(tree);
	/* print "," for Conj */
	if(((*tree).Conj == 1 || (*tree).Bopen > 0)&&(strlen((*tree).Head) > 0)){
		printf(",");
	}
	/* print Bopen */
	for(i=0;i<countCZ;i++){
		//printf("(");
		printf("[");
	}
	/* print Head */
	char *new_head;
	int sw = 0;
	int *dim_pos;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail] malloc @ Function_Print_Head_J.\n");
		exit(1);
	}
	sw = Detect_Dim((*tree).Head,dim_pos);
	if(sw == 2){
		//printf(":%d:",dim_pos[0]);
		(*tree).Head[dim_pos[0]] = '\0';
		printf("[\"%s\",\"DIM\",",(*tree).Head);
		printf("%s",(*tree).Head+dim_pos[0]+1);
	}else{
		printf("\"%s\"",(*tree).Head);
	}
	/* print Bclose */
	for(i=0;i<(*tree).Bclose;i++){
		//printf(")");
		printf("]");
	}
	/* print "," for Next */
	if((*tree).NextCount > 0){
		//printf(",");
	}
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
//administrative function
int Function_RecursiveFreeForce(struct Tree *tree){
	int i;
	if(tree == NULL){
		return(1);
	}
	for(i=0;i<(*tree).NextCount;i++){
		Function_RecursiveFreeForce((*tree).Next[i]);
		free((*tree).Next[i]);
		(*tree).Next[i] = NULL;
	}
	(*tree).NextCount = 0;
	free((*tree).Head);
	(*tree).Head = NULL;
	free((*tree).Next);
	(*tree).Next = NULL;
	return(0);
}


//Under constructive functions
////recursive print function
void Function_RecursivePrint_Head(struct Tree *tree){
	//mis-matching code
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
////recursive print function
int Function_RecursiveFree(struct Tree *tree){
	//including bug
	int i;
	if(tree == NULL){
		return(1);
	}
	if((*tree).NextCount > 0){
		for(i=0;i<(*tree).NextCount;i++){
			Function_RecursiveFree((*tree).Next[i]);
			free((*tree).Next[i]);
			(*tree).Next[i] = NULL;
		}
		(*tree).NextCount = 0;
		free((*tree).Head);
		(*tree).Head = NULL;
		free((*tree).Next);
		(*tree).Next = NULL;
	}else{
		if((*tree).Head != NULL){
			free((*tree).Head);
			(*tree).Head = NULL;
		}
		if((*tree).Next != NULL){
			free((*tree).Next);
			(*tree).Next = NULL;
		}
	}
	return(0);
}

