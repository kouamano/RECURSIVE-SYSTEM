//initialize function
struct List *init_List_zero(struct List *list){
	(*list).ID=0;
	(*list).LVself=0;
	(*list).NCself=0;
	(*list).ACself=0;
	(*list).Val=0;
	if(((*list).Head = malloc(sizeof(char) * BUFF_LEN)) == NULL){
		fprintf(stderr,"[Fail] @ malloc() @ init_List_zero .\n");
	}
	(*list).Head[0]='\0';
	(*list).NextCount=0;
	if( ((*list).Next = malloc(sizeof(struct List *) * 1)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List_zero .\n");
	}
	(*list).ArgCount=0;
	if( ((*list).Arg = malloc(sizeof(struct List *) * 1)) == NULL ){
		fprintf(stderr,"[Fail] @ malloc() @ init_List_zero .\n");
	}
	(*list).Parent=NULL;
	return(list);
}
struct List *Function_Create_Node(void){
	struct List *node;
	if((node = malloc(sizeof(struct List) * 1)) == NULL){
		fprintf(stderr,"[Fail] malloc.\n");
		exit(1);
	}
	init_List_zero(node);
	return(node);
}

//restructure function
////restructure Next
struct List *Function_Add_NextRtd(struct List *parent, struct List *list, struct List *next_list){
	(*list).Next = realloc((*list).Next,(size_t)sizeof(struct List *) * (*list).NextCount+1);
	if((*list).Next == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_NextRtd .\n");
		exit(1);
	}
	(*list).Next[(*list).NextCount] = next_list;
	(*list).Next[(*list).NextCount]->LVself = (*list).LVself+1;
	(*list).Next[(*list).NextCount]->NCself = (*list).NextCount+1;
	(*list).Next[(*list).NextCount]->ACself = 0;
	(*list).Next[(*list).NextCount]->Parent = list;
	(*list).NextCount++;
	if(parent != NULL){
		(*list).Parent = parent;
	}
	return(next_list);
}
struct List *Function_Create_NextRtd(struct List *parent, struct List *list){
	struct List *next_list;
	next_list = malloc((size_t)sizeof(struct List) * 1);
	if(next_list == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Create_NextRtd .\n");
		exit(1);
	}
	(*list).Next = realloc((*list).Next,(size_t)sizeof(struct List *) * (*list).NextCount+1);
	if((*list).Next == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Create_NextRtd .\n");
		exit(1);
	}
	if(parent != NULL){
		(*list).Parent = parent;
	}
	(*list).Next[(*list).NextCount] = next_list;
	(*list).Next[(*list).NextCount]->LVself = (*list).LVself+1;
	(*list).Next[(*list).NextCount]->NCself = (*list).NextCount+1;
	(*list).Next[(*list).NextCount]->ACself = 0;
	(*list).Next[(*list).NextCount]->Parent = list;
	(*list).NextCount++;
	return(next_list);
}
////restructure Arg
struct List *Function_Add_ArgRtd(struct List *parent, struct List *list, struct List *arg_list){
	if((*list).ACself > 0){
		fprintf(stderr,"[Err] Restriction: tandem argument alloc.\n");
		exit(1);
	}
	if((*list).LVself == 0){
		fprintf(stderr,"[Err] Restriction: top level argument must be single.\n");
		exit(1);
	}
	(*list).Arg = realloc((*list).Arg,(size_t)sizeof(struct List *) * (*list).ArgCount+1);
	if((*list).Arg == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Add_ArgRtd .\n");
		exit(1);
	}
	(*list).Arg[(*list).ArgCount] = arg_list;
	(*list).Arg[(*list).ArgCount]->LVself = (*list).LVself;
	(*list).Arg[(*list).ArgCount]->ACself = (*list).ArgCount+1;
	(*list).Arg[(*list).ArgCount]->Parent = list;
	(*list).ArgCount++;
	if(parent != NULL){
		(*list).Parent = parent;
	}
	return(arg_list);
}
/*
struct List *Function_Create_ArgRtd(struct List *parent, struct List *list){
	if((*list).ACself > 0){
		fprintf(stderr,"[Err] Restriction: tandem argument alloc.\n");
		exit(1);
	}
	if((*list).LVself == 0){
		fprintf(stderr,"[Err] Restriction: top level argument must be single.\n");
		exit(1);
	}

	if(parent != NULL){
		(*list).Parent = parent;
	}
	struct List *arg_list;
	arg_list = malloc((size_t)sizeof(struct List) * 1);
	if(arg_list == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Create_ArgRtd .\n");
		exit(1);
	}
	(*list).Arg = realloc((*list).Arg,(size_t)sizeof(struct List *) * (*list).ArgCount+1);
	if((*list).Arg == NULL){
		fprintf(stderr,"[Fail] malloc @ Function_Create_ArgRtd .\n");
		exit(1);
	}
	(*list).Arg[(*list).ArgCount] = arg_list;
	(*list).Arg[(*list).ArgCount]->LVself = (*list).LVself;
	(*list).Arg[(*list).ArgCount]->ACself = (*list).ArgCount+1;
	(*list).Arg[(*list).ArgCount]->Parent = list;
	(*list).ArgCount++;
	return(arg_list);
}
*/
////free
int Function_Free_List(struct List *list){
	int i;
	if(list == NULL){
		return(1);
	}
	for(i=0;i<(*list).NextCount;i++){
		Function_Free_List((*list).Next[i]);
		free((*list).Next[i]);
		(*list).Next[i]=NULL;
	}
	free((*list).Next);
	(*list).Next = NULL;
	(*list).NextCount = 0;

	for(i=0;i<(*list).ArgCount;i++){
		Function_Free_List((*list).Arg[i]);
		free((*list).Arg[i]);
		(*list).Arg[i]=NULL;
	}
	free((*list).Arg);
	(*list).Arg = NULL;
	(*list).ArgCount = 0;

	free((*list).Head);
	(*list).Head = NULL;

	return(0);
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
struct List *ExFunction_Recursive_T_Print(struct List *list, struct List *(*e_function)(struct List *),int WAR, struct List *Parent, int p_opt){
	int i;
	int j;
	struct List *out = list;
	if(list == NULL){
		printf("NULL\n");
		return(NULL);
	}

	/* (* check */
	if(WAR > 0){
	}
	/* *) */

	//SELF
	if((p_opt&1) == 1){
		printf("$%ld",(long int)list);
	}
	if((p_opt&2) == 2){
		printf("%s",(*list).Head);
	}

	//Next
	for(i=0;i<(*list).NextCount;i++){
		printf("(");
		ExFunction_Recursive_T_Print((*list).Next[i],e_function,WAR,list,p_opt);
		printf(")");
	}

	//Arg
	for(j=0;j<(*list).ArgCount;j++){
		printf(",");
		ExFunction_Recursive_T_Print((*list).Arg[j],e_function,WAR,list,p_opt);
	}
	return(out);
}
struct List *ExFunction_Recursive_S_Print(struct List *list, struct List *(*e_function)(struct List *), int WAR, struct List *Parent, int p_opt){
	int i;
	int j;
	struct List *out = list;
	if(list == NULL){
		printf("NULL\n");
		return(NULL);
	}

	/* (* check */
	if(WAR>0){
	}
	/* *) */

	//COMM
	if((*list).NCself > 0 || (*list).ACself > 0){
		if(strlen((*list).Head) == 0 && (*list).NCself > 0){
			;
		}else{
			printf(",");
		}
	}

	//BRK
	for(i=0;i<(*list).NextCount;i++){
		printf("(");
	}

	//SELF
	if((p_opt&1) == 1){
		printf("$%ld",(long int)list);
	}
	if((p_opt&2) == 2){
		printf("%s",(*list).Head);
	}

	//NEXT
	for(i=0;i<(*list).NextCount;i++){
		ExFunction_Recursive_S_Print((*list).Next[i],e_function,WAR,list,p_opt);
		printf(")");
	}

	//Arg
	for(j=0;j<(*list).ArgCount;j++){
		ExFunction_Recursive_S_Print((*list).Arg[j],e_function,WAR,list,p_opt);
	}

	//return
	return(out);
}

int scan_char(FILE *_IN, struct List *top, int WAR){
	int C;
	int DLM_ACC = 1;
	int LIST_LV = 0;
	int ARG_COUNT = 0;
	char *BUFF;
	int buf_ptr = 0;
	struct List *current;
	struct List *next;
	struct List *arg;
	int close = 0;
	current = top;
	if((BUFF = malloc(sizeof(char) * BUFF_LEN)) == NULL){
		printf("[Fail] malloc.\n");
		exit(1);
	}
	while((C = fgetc(_IN))){
		//check chars
		if(WAR > 0){
		printf("\n:C=%c: ",C);
		}
		//set conditions
		if(C == '['){
			DLM_ACC--;
		}
		if(C == ']'){
			DLM_ACC++;
		}
		if(C == ',' && DLM_ACC > 0){
			ARG_COUNT++;
		}
		if(C == '('){
			LIST_LV++;
		}
		if(C == ')'){
			LIST_LV--;
		}
		//function code
		if(C == '('){
			//confirm current
			BUFF[buf_ptr] = '\0';
			if(strlen(BUFF) > 0 && close == 0){
				strcpy((*current).Head,BUFF);
			}
			if(WAR > 0){
			}
			//alloc next
			next = Function_Create_Node();
			//create next
			Function_Add_NextRtd((*current).Parent,current,next);
			//prepare next
			current = next;
			//clear BUFF
			BUFF[0] = '\0';
			buf_ptr = 0;
			close = 0;
		}else if(C == ',' && DLM_ACC > 0){
			//confirm current
			BUFF[buf_ptr] = '\0';
			if(close == 0){
				strcpy((*current).Head,BUFF);
			}
			if(WAR > 0){
			printf(":B=%s:",(*current).Head);
			printf(":Pp=%ld:",(long int)(*current).Parent);
			printf(":Cp=%ld:",(long int)current);
			printf(":LVs=%d:",(*current).LVself);
			printf(":NCs=%d:",(*current).NCself);
			printf(":ACs=%d:",(*current).ACself);
			printf(":Cl=%d:",close);
			}
			//alloc arg
			arg = Function_Create_Node();
			//create arg
			if((*current).ACself == 0){
				Function_Add_ArgRtd((*current).Parent,current,arg);
			}else{
				current = (*current).Parent;
				Function_Add_ArgRtd((*current).Parent,current,arg);
			}
			//prepare arg
			current = arg;
			//clear BUFF
			BUFF[0] = '\0';
			buf_ptr = 0;
			close = 0;
		}else if(C == ')'){
			//confirm current
			BUFF[buf_ptr] = '\0';
			if(close == 0){
				strcpy((*current).Head,BUFF);
			}
			if(WAR > 0){
			}
			//clear BUFF
			BUFF[0] = '\0';
			buf_ptr = 0;
			//prepare current
			if((*current).ACself > 0){
				current = (*current).Parent;
			}
			if((*current).Parent != NULL){
				current = (*current).Parent;
			}
			close++;
		}else if(C == '\n'){
			//print BUFF
			BUFF[buf_ptr] = '\0';
			printf("%s",BUFF);
			//clear BUFF
			BUFF[0] = '\0';
			buf_ptr = 0;
			//print check code
			if(WAR > 1){
			}
			//final putput
			ExFunction_Recursive_S_Print(top,(struct List *(*)())Function_Print_Status,0,NULL,2); printf("\n");
			//clear tree
			Function_Free_List(top);
			free(top);
			top=Function_Create_Node();
			close = 0;
		}else if(C == EOF){
			return(C);
		}else{
			//buffering
			BUFF[buf_ptr] = C;
			BUFF[buf_ptr+1] = '\0';
			buf_ptr++;
			close = 0;
		}
	}
	return(C);
}


