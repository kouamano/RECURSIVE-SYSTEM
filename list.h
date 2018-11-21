#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure
struct List {
	int ID;
	int LVself;
	int ACself;
	int Val;
	char *Head;
	struct List *(*function)();
	int NextCount;
	struct List **Next;
	int ArgCount;
	struct List **Arg;
};

//initialize function
struct List *init_List_zero(struct List *list){
	(*list).ID=0;
	(*list).LVself=0;
	(*list).ACself=0;
	(*list).Val=0;
	if(((*list).Head = malloc(sizeof(char) * 1)) == NULL){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
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
struct List *init_List_Head(struct List *list, size_t h_size){
	(*list).ID=0;
	(*list).LVself=0;
	(*list).ACself=0;
	(*list).Val=0;
	if(((*list).Head = malloc(sizeof(char) * h_size)) == NULL){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
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
	(*list).Val = v;
	if(((*list).Head = malloc(sizeof(char) * head_size)) == NULL){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).Head[0] = '\0';
	(*list).NextCount = NC;
	if( ((*list).Next = malloc(sizeof(struct List) * NC)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).ArgCount = AC;
	if( ((*list).Arg = malloc(sizeof(struct List) * AC)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	return(list);
}

//functions
struct List *Function_Print_Head(struct List *list){
	printf("%s\n",(*list).Head);
	return(list);
}
struct List *Function_Print_Val(struct List *list){
	printf("%d\n",(*list).Val);
	return(list);
}
struct List *Function_Print_Status(struct List *list){
	int i,j;
	printf("{\n");
	printf("  :::ID:%d:::\n",(*list).ID);
	printf("  :::LVself:%d:::\n",(*list).LVself);
	printf("  :::ACself:%d:::\n",(*list).ACself);
	printf("  :::Val:%d:::\n",(*list).Val);
	printf("  :::Head:%s:::\n",(*list).Head);
	printf("  :::function -skip- \n");
	printf("  :::NextCount:%d:::\n",(*list).NextCount);
	printf("  :::NextPointers:\n");
	for(i=0;i<(*list).NextCount;i++){
		printf("    :%ld:\n",&(*list).Next[i]);
		printf("    :%ld:\n",(*list).Next+i);
	}
	printf("  :::ArgCount:%d:::\n",(*list).ArgCount);
	printf("  :::ArgPointers:\n");
	for(i=0;i<(*list).ArgCount;i++){
		printf("    :%ld:\n",&(*list).Arg[i]);
		printf("    :%ld:\n",(*list).Arg+i);
	}
	printf("\n}\n");
	return(list);
}


//Apply function
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
struct List *ExFunction_Recursive_List(struct List *list, struct List *(*e_function)(struct List *)){
	int i;
	int j;
	struct List *out = list;
	if(list == NULL){
		printf("NULL\n");
		return(NULL);
	}
	if((*list).function != NULL){
		e_function(list);  //OR
		//(*list).function = e_function;
		//(*list).function(list);
	}
	for(i=0;i<(*list).NextCount;i++){
		ExFunction_Recursive_List((*list).Next[i],e_function);
	}

	for(j=0;j<(*list).ArgCount;j++){
		ExFunction_Recursive_List((*list).Arg[j],e_function);
	}
	return(out);
}



