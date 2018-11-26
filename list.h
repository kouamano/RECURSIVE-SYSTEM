#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF
#define BUFF 1024
#endif

//structure
struct List {
	int ID;
	int LVself;
	int NCself;
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
	(*list).NCself=0;
	(*list).ACself=0;
	(*list).Val=0;
	if(((*list).Head = malloc(sizeof(char) * BUFF)) == NULL){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).Head[0]='\0';
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
	(*list).NCself=0;
	(*list).ACself=0;
	(*list).Val=0;
	if(((*list).Head = malloc(sizeof(char) * h_size)) == NULL){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).Head[0]='\0';
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
	(*list).NCself=0;
	(*list).ACself=ac;
	(*list).Val=v;
	if(((*list).Head = malloc(sizeof(char) * head_size)) == NULL){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).Head[0]='\0';
	(*list).function=fun;
	(*list).NextCount=NC;
	if( ((*list).Next = malloc(sizeof(struct List) * NC)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).ArgCount=AC;
	if( ((*list).Arg = malloc(sizeof(struct List) * AC)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	return(list);
}

//restructure function
struct List *Function_Add_Next(struct List *list, struct List *next_list){
	(*list).Next = realloc((*list).Next,(size_t)sizeof(struct List) * (*list).NextCount+1);
	if((*list).Next == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_Next .\n");
		exit(1);
	}
	(*list).Next[(*list).NextCount] = next_list;
	(*list).Next[(*list).NextCount]->LVself = (*list).LVself+1;
	(*list).Next[(*list).NextCount]->NCself = (*list).NextCount;
	(*list).Next[(*list).NextCount]->ACself = 0;
	(*list).NextCount++;
	return((*list).Next[(*list).NextCount]);
}
struct List *Function_Add_NextRtd(struct List *list, struct List *next_list){
	if((*list).ArgCount > 0){
		fprintf(stderr,"[Err] Restriction: already allocated Arg.\n");
		exit(1);
	}
	(*list).Next = realloc((*list).Next,(size_t)sizeof(struct List) * (*list).NextCount+1);
	if((*list).Next == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_Next .\n");
		exit(1);
	}
	(*list).Next[(*list).NextCount] = next_list;
	(*list).Next[(*list).NextCount]->LVself = (*list).LVself+1;
	(*list).Next[(*list).NextCount]->NCself = (*list).NextCount;
	(*list).Next[(*list).NextCount]->ACself = 0;
	(*list).NextCount++;
	return((*list).Next[(*list).NextCount]);
}
struct List *Function_Create_Next(struct List *list){
	struct List *next_list;
	next_list = malloc((size_t)sizeof(struct List) * 1);
	if(next_list == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_Next .\n");
		exit(1);
	}
	(*list).Next = realloc((*list).Next,(size_t)sizeof(struct List) * (*list).NextCount+1);
	if((*list).Next == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_Next .\n");
		exit(1);
	}
	(*list).Next[(*list).NextCount] = next_list;
	(*list).Next[(*list).NextCount]->LVself = (*list).LVself+1;
	(*list).Next[(*list).NextCount]->NCself = (*list).NextCount;
	(*list).Next[(*list).NextCount]->ACself = 0;
	(*list).NextCount++;
	return(next_list);
}
struct List *Function_Add_Arg(struct List *list, struct List *arg_list){
	(*list).Arg = realloc((*list).Arg,(size_t)sizeof(struct List) * (*list).ArgCount+1);
	if((*list).Arg == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_Next .\n");
		exit(1);
	}
	(*list).Arg[(*list).ArgCount] = arg_list;
	(*list).Arg[(*list).ArgCount]->LVself = (*list).LVself+1;
	(*list).Arg[(*list).ArgCount]->ACself = (*list).ArgCount;
	(*list).ArgCount++;
	return((*list).Arg[(*list).ArgCount]);
}
struct List *Function_Add_ArgRtd(struct List *list, struct List *arg_list){
	if((*list).NextCount > 0){
		fprintf(stderr,"[Err] Restriction: already allocated Next.\n");
		exit(1);
	}
	(*list).Arg = realloc((*list).Arg,(size_t)sizeof(struct List) * (*list).ArgCount+1);
	if((*list).Arg == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_Next .\n");
		exit(1);
	}
	(*list).Arg[(*list).ArgCount] = arg_list;
	(*list).Arg[(*list).ArgCount]->LVself = (*list).LVself+1;
	(*list).Arg[(*list).ArgCount]->ACself = (*list).ArgCount;
	(*list).ArgCount++;
	return((*list).Arg[(*list).ArgCount]);
}
struct List *Function_Create_Arg(struct List *list){
	struct List *arg_list;
	arg_list = malloc((size_t)sizeof(struct List) * 1);
	if(arg_list == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_Next .\n");
		exit(1);
	}
	(*list).Arg = realloc((*list).Arg,(size_t)sizeof(struct List) * (*list).ArgCount+1);
	if((*list).Arg == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_Next .\n");
		exit(1);
	}
	(*list).Arg[(*list).ArgCount] = arg_list;
	(*list).Arg[(*list).ArgCount]->LVself = (*list).LVself+1;
	(*list).Arg[(*list).ArgCount]->ACself = (*list).ArgCount;
	(*list).ArgCount++;
	return(arg_list);
}

//print function primitive
struct List *Function_Print_Head(struct List *list){
	printf("%s\n",(*list).Head);
	return(list);
}
struct List *Function_Print_Val(struct List *list){
	printf("%d\n",(*list).Val);
	return(list);
}
struct List *Function_Print_Status(struct List *list){
	int i;
	int j;
	printf("{:%ld:\n",(long int)list);
	printf("  :::ID:%d:::\n",(*list).ID);
	printf("  :::LVself:%d:::\n",(*list).LVself);
	printf("  :::NCself:%d:::\n",(*list).NCself);
	printf("  :::ACself:%d:::\n",(*list).ACself);
	printf("  :::Val:%d:::\n",(*list).Val);
	printf("  :::Head:%s:::\n",(*list).Head);
	printf("  :::function -skip- :::\n");
	printf("  :::NextCount:%d:::\n",(*list).NextCount);
	printf("  :::NextPointers:\n");
	for(i=0;i<(*list).NextCount;i++){
		printf("    :%ld:\n",(long int)(*list).Next[i]);
		//printf("    :%ld:\n",*(*list).Next+i);
	}
	printf("  :::\n");
	printf("  :::ArgCount:%d:::\n",(*list).ArgCount);
	printf("  :::ArgPointers:\n");
	for(j=0;j<(*list).ArgCount;j++){
		printf("    :%ld:\n",(long int)(*list).Arg[j]);
	}
	printf("  :::\n");
	printf("}\n");
	return(list);
}
struct List *Function_Print_Index(struct List *list){
	printf("{%ld",(long int)list);
	printf(",LVself=%d",(*list).LVself);
	printf(",NCself=%d",(*list).NCself);
	printf(",ACself=%d",(*list).ACself);
	printf("}\n");
	return(list);
}

//apply function
struct List *Function_Recursive_List(struct List *list){
	int i;
	int j;
	struct List *out = list;
	if(list == NULL){
		fprintf(stderr,"NULL\n");
		return(NULL);
	}
	if((*list).function != NULL){
		(*(*list).function)(list);
		//(*list).function(list);
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
	if(list == NULL || e_function == NULL){
		fprintf(stderr,"NULL\n");
		return(NULL);
	}
	(*e_function)(list);
	for(i=0;i<(*list).NextCount;i++){
		ExFunction_Recursive_List((*list).Next[i],e_function);
	}
	for(j=0;j<(*list).ArgCount;j++){
		ExFunction_Recursive_List((*list).Arg[j],e_function);
	}
	return(out);
}

//complex function (print&apply)
struct List *ExFunction_Recursive_Tree_Print(struct List *list, struct List *(*e_function)(struct List *),int WAR){
	int i;
	int j;
	struct List *out = list;
	if(list == NULL){
		printf("NULL\n");
		return(NULL);
	}

	printf("$%ld",(long int)list);

	for(i=0;i<(*list).NextCount;i++){
		printf("(");
		ExFunction_Recursive_Tree_Print((*list).Next[i],e_function,WAR);
		printf(")");
	}

	for(j=0;j<(*list).ArgCount;j++){
		if(j == 0){
			printf("(");
		}else{
			printf(",");
		}
		ExFunction_Recursive_Tree_Print((*list).Arg[j],e_function,WAR);
		if(j == (*list).ArgCount-1){
			printf(")");
		}
	}
	return(out);
}
struct List *ExFunction_Recursive_S_Print(struct List *list, struct List *(*e_function)(struct List *), int WAR, struct List *Parent){
	int i;
	int j;
	struct List *out = list;
	if(list == NULL){
		printf("NULL\n");
		return(NULL);
	}

	/* (* check */
	if(WAR>0){
	if(Parent == NULL){
		printf("\n:::$%ld:sLV=%d:pAC=%ld:sAC=%d:pNC=%ld:sNC=%d:NC=%d:AC=%d::: ",(long int)list,(*list).LVself,(long int)NULL,(*list).ACself,(long int)NULL,(*list).NCself,(*list).NextCount,(*list).ArgCount);
	}else{
		printf("\n:::$%ld:sLV=%d:pAC=%d:sAC=%d:pNC=%d:sNC=%d:NC=%d:AC=%d::: ",(long int)list,(*list).LVself,(*Parent).ArgCount,(*list).ACself,(*Parent).NextCount,(*list).NCself,(*list).NextCount,(*list).ArgCount);
	}
	}
	/* *) */

	//COMM
	if(Parent != NULL){
		if((*Parent).NextCount>0 || (*Parent).ArgCount>0){
			printf(",");
		}
	}

	//BRK
	for(i=0;i<(*list).NextCount;i++){
		printf("(");
	}
	if((*list).ArgCount>0){
		printf("(");
	}

	//SELF
	printf("$%ld",(long int)list);

	//NEXT
	for(i=0;i<(*list).NextCount;i++){
		ExFunction_Recursive_S_Print((*list).Next[i],e_function,WAR,list);
		printf(")");
	}

	//Arg
	for(j=0;j<(*list).ArgCount;j++){
		ExFunction_Recursive_S_Print((*list).Arg[j],e_function,WAR,list);
	}
	if((*list).LVself==0 && (*list).ACself==0 && (*list).ArgCount>0){
		printf(")");
	}else if(Parent != NULL){
		if((*list).LVself>1 && (*list).ACself==0 && (*Parent).NextCount==0 && (*list).NCself==0 && (*list).NextCount==0 && (*list).ArgCount==0){
			printf(")");
		}
	}

	//return
	return(out);
}


