#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF
#define BUFF 1024
#endif

struct Object {
	int ID;
	int val;
	int Category;	// 1:A, 2:D, 4:C
	int DCself;
	int CCself;
	struct Object *Parent;
	struct Object *Arrow;
	struct Object *(*function)();
	int DCount;
	struct Object **Dom;
	int CCount;
	struct Object **Cod;
};

struct Object *init_Object_zero(struct Object *obj){
	(*obj).ID=0;
	(*obj).val=0;
	(*obj).Category=0;
	(*obj).DCself=0;
	(*obj).CCself=0;
	(*obj).Parent=NULL;
	(*obj).Arrow = malloc(sizeof(struct Object) * 1);
	if((*obj).Arrow == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).function=NULL;
	(*obj).DCount=0;
	(*obj).Dom = malloc(sizeof(struct Object *) * 1);
	if((*obj).Dom == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).CCount=0;
	(*obj).Cod = malloc(sizeof(struct Object *) * 1);
	if((*obj).Cod == NULL){ printf("[Fail] alloc.\n"); exit(1); }
}
