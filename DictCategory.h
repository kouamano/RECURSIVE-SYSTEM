#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF
#define BUFF 1024
#endif
#include "list.h"

struct Triple {
	int ID;
	struct List *Arrow;
	int Dcount;
	struct List **Dom;
	int Ccount;
	struct List **Cod;
};

struct Triple *init_Object_zero(struct Triple *obj){
	(*obj).ID=0;
	(*obj).Arrow = malloc(sizeof(struct List) * 1);
	if((*obj).Arrow == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).function=NULL;
	(*obj).Dcount=0;
	(*obj).Dom = malloc(sizeof(struct List *) * 1);
	if((*obj).Dom == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).Ccount=0;
	(*obj).Cod = malloc(sizeof(struct List *) * 1);
	if((*obj).Cod == NULL){ printf("[Fail] alloc.\n"); exit(1); }
}

struct Triple *create_Triple_zero(void){
	struct Triple *obj;
	obj = malloc(sizeof(struct Triple) * 1);
	if(obj == NULL){ printf("[Fail] malloc.\n"); exit(1); }
	(*obj).Arrow = malloc(sizeof(struct List) * 1);
	if((*obj).Arrow == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).function=NULL;
	(*obj).Dcount=0;
	(*obj).Dom = malloc(sizeof(struct List *) * 1);
	if((*obj).Dom == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).Ccount=0;
	(*obj).Cod = malloc(sizeof(struct List *) * 1);
	if((*obj).Cod == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	return(obj);
}

