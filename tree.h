#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF_LEN
#define BUFF_LEN 1024
#endif

struct Tree {
	int LVself;
	int ACself;
	int Conj;
	int Bopen;
	char *Head;
	int Bclose;
	int NextCount;
	struct Tree **Next;
};

struct Tree *Create_Tree(int H_size){
	struct Tree *tree;
	if((tree = malloc(sizeof(struct Tree) * 1)) == NULL){
		fprintf(stderr,"[Fail] malloc.\n");
		exit(1);
	}
	(*tree).LVself=0;
	(*tree).ACself=0;
	(*tree).Conj=0;
	(*tree).Bopen=0;
}
