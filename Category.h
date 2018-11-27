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

struct Object *create_Object_zero(void){
	struct Object *obj;
	obj = malloc(sizeof(struct Object) * 1);
	if(obj == NULL){ printf("[Fail] malloc.\n"); exit(1); }
	(*obj).ID=0;
	(*obj).val=0;
	(*obj).Category=0;
	(*obj).DCself=0;
	(*obj).CCself=0;
	(*obj).Arrow = malloc(sizeof(struct Object) * 1);
	if((*obj).Arrow == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).function=NULL;
	(*obj).DCount=0;
	(*obj).Dom = malloc(sizeof(struct Object *) * 1);
	if((*obj).Dom == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	(*obj).CCount=0;
	(*obj).Cod = malloc(sizeof(struct Object *) * 1);
	if((*obj).Cod == NULL){ printf("[Fail] alloc.\n"); exit(1); }
	return(obj);
}

struct Object *create_Object(int _id, int _val, int _cat, int _dcs, int _ccs, struct Object *_arrow, struct Object *(*_func)(), int _dc, struct Object **_dom, int _cc, struct Object **_cod){
	struct Object *obj;
	obj = create_Object_zero();
	(*obj).ID = _id;
	(*obj).val = _val;
	(*obj).Category = _cat;
	(*obj).DCself = _dcs;
	(*obj).CCself = _ccs;
	(*obj).Arrow = _arrow;
	(*obj).function = _func;
	(*obj).DCount = _dc;
	(*obj).Dom = _dom;
	(*obj).CCount = _cc;
	(*obj).Cod = _cod;
	return(obj);
}

