#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF_LEN
#define BUFF_LEN 1024
#endif
#include "T-structure.h"

struct Triple {
	int ID;
	struct Tree *Arrow;
	int Dcount;
	struct Tree **Dom;
	int Ccount;
	struct Tree **Cod;
};

struct Triple *init_Triple_zero(struct Triple *obj){
	(*obj).ID=0;
	(*obj).Arrow = malloc(sizeof(struct Tree) * 1);
	if((*obj).Arrow == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).Dcount=0;
	(*obj).Dom = malloc(sizeof(struct Tree *) * 1);
	if((*obj).Dom == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).Ccount=0;
	(*obj).Cod = malloc(sizeof(struct Tree *) * 1);
	if((*obj).Cod == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	return(obj);
}

struct Triple *create_Triple_zero(void){
	struct Triple *obj;
	obj = malloc(sizeof(struct Triple) * 1);
	if(obj == NULL){ printf("[Fail] malloc.\n"); exit(1); }
	(*obj).Arrow = malloc(sizeof(struct Tree) * 1);
	if((*obj).Arrow == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).Dcount=0;
	(*obj).Dom = malloc(sizeof(struct Tree *) * 1);
	if((*obj).Dom == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).Ccount=0;
	(*obj).Cod = malloc(sizeof(struct Tree *) * 1);
	if((*obj).Cod == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	return(obj);
}

