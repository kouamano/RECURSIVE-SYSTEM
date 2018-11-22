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
	int ACself;
	int Val;
	char *Head;
	struct List *(*function)();
	int NextCount;
	struct List **Next;
	int ArgCount;
	struct List **Arg;
	int NXprog;
};

//initialize function
struct List *init_List_zero(struct List *list){
	(*list).ID=0;
	(*list).LVself=0;
	(*list).ACself=0;
	(*list).Val=0;
	if(((*list).Head = malloc(sizeof(char) * BUFF)) == NULL){
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
	(*list).NXprog = 0;
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
	(*list).NXprog = 0;
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
	(*list).function = fun;
	(*list).NextCount = NC;
	if( ((*list).Next = malloc(sizeof(struct List) * NC)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).ArgCount = AC;
	if( ((*list).Arg = malloc(sizeof(struct List) * AC)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List .\n");
	}
	(*list).NXprog = 0;
	return(list);
}

//functions
////restructure func
struct List *Function_Add_Next(struct List *list, struct List *next_list){
	(*list).Next = realloc((*list).Next,(size_t)sizeof(struct List) * (*list).NextCount+1);
	if((*list).Next == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_Next .\n");
		exit(1);
	}
	(*list).Next[(*list).NextCount] = next_list;
	(*list).Next[(*list).NextCount]->LVself = (*list).LVself+1;
	(*list).Next[(*list).NextCount]->NXprog = (*list).NextCount;
	(*list).Next[(*list).NextCount]->ACself = 0;
	//(*(*list).Next[(*list).NextCount]).ACself = 0;
	(*list).NextCount++;
	return((*list).Next[(*list).NextCount]);
}
struct List *Function_Add_Arg(struct List *list, struct List *arg_list){
	(*list).Arg = realloc((*list).Arg,(size_t)sizeof(struct List) * (*list).ArgCount+1);
	if((*list).Arg == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_Next .\n");
		exit(1);
	}
	(*list).Arg[(*list).ArgCount] = arg_list;
	(*list).Arg[(*list).ArgCount]->LVself = (*list).LVself+1;
	//(*list).Arg[(*list).ArgCount]->ACself = (*list).ACself+1;
	(*list).Arg[(*list).ArgCount]->ACself = (*list).ArgCount;
	(*list).ArgCount++;
	return((*list).Arg[(*list).ArgCount]);
}

////print func
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
	printf("{:%ld:\n",list);
	printf("  :::ID:%d:::\n",(*list).ID);
	printf("  :::LVself:%d:::\n",(*list).LVself);
	printf("  :::ACself:%d:::\n",(*list).ACself);
	printf("  :::Val:%d:::\n",(*list).Val);
	printf("  :::Head:%s:::\n",(*list).Head);
	printf("  :::function -skip- :::\n");
	printf("  :::NextCount:%d:::\n",(*list).NextCount);
	printf("  :::NextCountProg:%d:::\n",(*list).NXprog);
	printf("  :::NextPointers:\n");
	for(i=0;i<(*list).NextCount;i++){
		printf("    :%ld:\n",(*list).Next[i]);
		//printf("    :%ld:\n",*(*list).Next+i);
	}
	printf("  :::\n");
	printf("  :::ArgCount:%d:::\n",(*list).ArgCount);
	printf("  :::ArgPointers:\n");
	for(j=0;j<(*list).ArgCount;j++){
		printf("    :%ld:\n",(*list).Arg[j]);
	}
	printf("  :::\n");
	printf("}\n");
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
////print&apply function
struct List *ExFunction_Recursive_Tree_Print(struct List *list, struct List *(*e_function)(struct List *),int WAR){
	int i;
	int j;
	struct List *out = list;
	if(list == NULL){
		printf("NULL\n");
		return(NULL);
	}
	if((*list).function != NULL){
		if(WAR >= 0){
			printf("$%ld",list);
		}
		if(WAR > 0){
			printf(":LV=%d:AC=%d:NXp=%d:",(*list).LVself,(*list).ACself,(*list).NXprog);
		}
		if(WAR > 4){
			e_function(list);  //OR
			//(*list).function = e_function;
			//(*list).function(list);
		}
	}
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
	if(Parent == NULL){
		//printf("\n:::$%ld:LV=%d:sAC=%d:pNXc=%d:NXp=%d:NXc=%d:AC=%d::: ",list,(*list).LVself,(*list).ACself,NULL,(*list).NXprog,(*list).NextCount,(*list).ArgCount);
	}else{
		//printf("\n:::$%ld:LV=%d:sAC=%d:pNXc=%d:NXp=%d:NXc=%d:AC=%d::: ",list,(*list).LVself,(*list).ACself,(*Parent).NextCount,(*list).NXprog,(*list).NextCount,(*list).ArgCount);
	}
	/* *) */

	//BRK COMM
	if(Parent != NULL){
		if((*Parent).NextCount > 1 && (*list).NXprog == (*Parent).NextCount-1 && (*list).NextCount != 0){
			printf(",");
		}
	}
	for(i=0;i<(*list).NextCount;i++){
		printf("(");
	}

	if((*list).LVself==0 && (*list).ACself==0 && (*list).NextCount==0 && (*list).ArgCount > 0){
		printf("(");
	}

	if((*list).LVself==1 && (*list).ACself==0 && (*Parent).NextCount!=1 && (*list).NextCount==0){
		printf(",");
	}else if((*list).ACself>0){
		printf(",");
	}else if((*list).NXprog==0 && (*list).NextCount==0 && (*list).ACself==0){
		//printf(",");
	}

	//SELF
	printf("$%ld",list);
	//if((*list).NXprog==0 && (*list).NextCount==1 && (*list).ACself==0){
	if((*list).NextCount==1 && (*list).ACself==0){
		printf(",");
	}

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
	}
	return(out);
}

struct List *ExFunction_Recursive_ES_Print(struct List *list, struct List *(*e_function)(struct List *), int WAR, struct List *Parent){
	int i;
	int j;
	struct List *out = list;
	if(list == NULL){
		printf("NULL\n");
		return(NULL);
	}

	/* (* check */
	if(Parent == NULL){
		//printf("\n:::$%ld:LV=%d:sAC=%d:pNXc=%d:NXp=%d:NXc=%d:AC=%d::: ",list,(*list).LVself,(*list).ACself,NULL,(*list).NXprog,(*list).NextCount,(*list).ArgCount);
	}else{
		//printf("\n:::$%ld:LV=%d:sAC=%d:pNXc=%d:NXp=%d:NXc=%d:AC=%d::: ",list,(*list).LVself,(*list).ACself,(*Parent).NextCount,(*list).NXprog,(*list).NextCount,(*list).ArgCount);
	}
	/* *) */

	//BRK COMM
	for(i=0;i<(*list).NextCount;i++){
		printf("(");
	}
	if((*list).LVself==0 && (*list).ACself==0 && (*list).NextCount==0 && (*list).ArgCount > 0){
		printf("(");
	}

	//if((*list).LVself==1 && (*list).ACself==0 && (*Parent).NextCount != 1){
	if((*list).LVself==1 && (*list).ACself==0 && (*Parent).NextCount!=1 && (*list).NextCount==0){
		printf(",");
	}else if((*list).ACself>0){
		printf(",");
	}else if((*list).NXprog==0 && (*list).NextCount==0 && (*list).ACself==0){
		//printf(",");
	}

	//SELF
	printf("$%ld",list);

	if((*list).NXprog==0 && (*list).NextCount==1 && (*list).ACself==0){
		printf(",");
	}
	if((*list).LVself == 0){
		//printf(",");
	}

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
	}
	return(out);
}


