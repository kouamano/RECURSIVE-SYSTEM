#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List {
	int ID;
	int LVself;
	int ACself;
	char *Head;
	int val;
	struct List *(*function)();
	int NextCount;
	struct List **Next;
	int ArgCount;
	struct List **Arg;
};
struct List *init_List_zero(struct List *list){
	(*list).ID=0;
	(*list).LVself=0;
	(*list).ACself=0;
	if(((*list).Head = malloc(sizeof(char) * 1)) == NULL){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).val=0;
	(*list).Head[0] = '\0';
	(*list).NextCount=0;
	if( ((*list).Next = malloc(sizeof(struct List) * 1)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).ArgCount=0;
	if( ((*list).Arg = malloc(sizeof(struct List) * 1)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	return(list);
}

struct List *init_List(struct List *list, int _ID, int lv, int ac, size_t head_size, int v, struct List *(*fun)(), int NC, int AC){
	(*list).ID=_ID;
	(*list).LVself=lv;
	(*list).ACself=ac;
	if(((*list).Head = malloc(sizeof(char) * head_size)) == NULL){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).Head[0] = '\0';
	(*list).val = v;
	(*list).NextCount = NC;
	if( ((*list).Next = malloc(sizeof(struct List) * NC)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).ArgCount = AC;
	if( ((*list).Arg = malloc(sizeof(struct List) * NC)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	return(list);
}

struct List *Function_Print_Head(struct List *list){
	printf("%s\n",(*list).Head);
	return(list);
}

struct List *Function_Recursive_List(struct List *list){
	int i;
	int j;
	struct List *out = list;
	if(list == NULL){
		printf("NULL\n");
		return(NULL);
	}
	if((*list).function != NULL){
		(*list).function(list);
	}
	for(i=0;i<(*list).NextCount;i++){
		Function_Recursive_List((*list).Next[i]);
	}

	for(j=0;j<(*list).ArgCount;j++){
		Function_Recursive_List((*list).Arg[j]);
	}
	return(out);
}



