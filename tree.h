#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF_LEN
#define BUFF_LEN 1024
#endif

struct Tree {
	int LVself;
	int NCself;
	int Conj;
	int Bopen;
	char *Head;
	int Bclose;
	int NextCount;
	struct Tree **Next;
};

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
	return(tree);
}

struct Tree *Add_Next(struct Tree *current, struct Tree *next){
	(*current).Next = realloc((*current).Next,(size_t)sizeof(struct Tree *) * (*current).NextCount+1);
	if((*current).Next == NULL){
		fprintf(stderr,"[Fail] malloc.\n");
	}
	(*current).Next[(*current).NextCount] = next;
	(*current).Next[(*current).NextCount]->LVself = (*current).LVself+1;
	(*current).Next[(*current).NextCount]->NCself = (*current).NextCount+1;
	(*current).NextCount++;
	return(next);
}



