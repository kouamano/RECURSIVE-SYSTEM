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

//function
////restructure function
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
struct Tree *Add_Bclose_To_Next(struct Tree *tree){
	//Under construction
	//Bcloseの回数を、Closeしていない親からCloseしている子に加算する
}
////status-check function
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
////recursive function
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
struct Tree *ExFunction_RecursivePrint(struct Tree *tree){
	//Under construction
	return(out);
}
