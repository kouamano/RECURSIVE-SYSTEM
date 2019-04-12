/* administrative functions */
void print_war(char C, struct Tree *tree, int level){
        printf("\n:C=%c: ",C);
        printf(":Pp=%ld:",(long int)(*tree).Parent);
        printf(":Cp=%ld:",(long int)tree);
        printf(":Cj=%d:",(*tree).Conj);
        printf(":current=%s:",(*tree).Head);
        printf(":LV=%d:",(*tree).LVself);
        printf(":NCs=%d:",(*tree).NCself);
        printf(":NC=%d:",(*tree).NextCount);
}
int AnalyzeTree(struct Tree *tree){
}
int Detect_Dim(const char *head, int *pos){
	int len;
	int dim_s = -1;
	int dim_e = -1;
	int esc = 0;
	int i;
	int ret = 0;
	len = strlen(head);
	for(i=0;i<len;i++){
		if(head[i] == '\\'){
			esc = 1;
		}else if(head[i] == '[' && esc == 0){
			dim_s = i;
			esc = 0;
		}else if(head[i] == ']' && esc == 0){
			dim_e = i;
			esc = 0;
		}else{
			esc = 0;
		}
	}
	pos[0] = dim_s;
	pos[1] = dim_e;
	if(dim_s > -1){
		ret++;
	}
	if(dim_e > -1){
		ret++;
	}
	if(ret == 2){
	}
	return(ret);
}
struct Tree *get_node(char *pos_str, struct Tree *tree){
	int len = 0;
	int list_len = 0;
	int i;
	int count = 0;
	int *list;
	struct Tree *current;
	len = strlen(pos_str);
	for(i=0;i<len;i++){
		if(pos_str[i] == ','){
			list_len++;
		}
	}
	list_len++;
	list = malloc(sizeof(int) * list_len);
	sscanf(pos_str,"%d",&list[count]);
	for(i=0;i<len;i++){
		if(pos_str[i] == ','){
			count++;
			sscanf(pos_str+i+1,"%d",&list[count]);
		}
	}
	count++;
	if(list[0] == 0){
		current = tree;
		for(i=1;i<count;i++){
			if((*current).NextCount > list[i]){
				current = current->Next[list[i]];
			}else{
				current = NULL;
				break;
			}
		}
	}else{
		current = NULL;
	}
	free(list);
	return(current);
}

/* restructure functions */
struct Tree *Create_Node(int _ser, int H_size){
	struct Tree *tree;
	if((tree = malloc(sizeof(struct Tree) * 1)) == NULL){
		fprintf(stderr,"[Fail]:malloc@Create_Node.\n");
		exit(1);
	}
	(*tree).ser=_ser;
	(*tree).LVself=0;
	(*tree).NCself=1;
	(*tree).Conj=0;
	(*tree).LabelFlag='\0';
	(*tree).Label=-1;
	(*tree).Category=NULL;
	(*tree).Head = malloc(sizeof(char) * H_size);
	if((*tree).Head == NULL){
		fprintf(stderr,"[Fail]:malloc@Create_Node.\n");
		exit(1);
	}
	(*tree).NextCount=0;
	(*tree).Next = malloc((size_t)sizeof(struct Tree *) * 1);
	if((*tree).Next == NULL){
		fprintf(stderr,"[Fail]:malloc@Create_Node.\n");
		exit(1);
	}
	(*tree).Parent=NULL;
	return(tree);
}
struct Tree *Copy_Node(struct Tree *dest, const struct Tree *src){
	(*dest).ser = (*src).ser;
	(*dest).LVself = (*src).LVself;
	(*dest).NCself = (*src).NCself;
	(*dest).Conj = (*src).Conj;
	(*dest).Head = (*src).Head;
	(*dest).NextCount = (*src).NextCount;
	(*dest).Next = (*src).Next;
	(*dest).Parent = (*src).Parent;
	return(dest);
}
struct Tree *Add_Next(struct Tree *parent, struct Tree *next){
	(*parent).Next = realloc((*parent).Next,(size_t)sizeof(struct Tree *) * (*parent).NextCount+1);
	if((*parent).Next == NULL){
		fprintf(stderr,"[Fail]malloc@Add_Next.\n");
	}
	(*parent).Next[(*parent).NextCount] = next;
	(*parent).Next[(*parent).NextCount]->LVself = (*parent).LVself+1;
	(*parent).Next[(*parent).NextCount]->NCself = (*parent).NextCount+1;
	(*parent).Next[(*parent).NextCount]->Parent = parent;
	(*parent).NextCount++;
	return(next);
}

/* compile functions */
int is_reteral(char *string){
	int fails = 0;
	if(strlen(string) < 2){
		fails++;
	}
	if(strncmp(string,"$",1) != 0){
		fails++;
	}else if(strncmp(string,"$#",2) == 0){
		fails++;
	}else if(strncmp(string,"$M",2) == 0){
		fails++;
	}else if(strncmp(string,"$E",2) == 0){
		fails++;
	}else if(strncmp(string,"$X",2) == 0){
		fails++;
	}else if(strncmp(string,"$U",2) == 0){
		fails++;
	}else if(strncmp(string,"$;",2) == 0){
		fails++;
	}else if(strncmp(string,"$$",2) == 0){
		fails++;
	}else if(strncmp(string,"$`",2) == 0){
		fails++;
	}
	return(fails);
}
char *Function_Clear_Head(struct Tree *tree){
	char *tmp_head;
	if((tmp_head = malloc(sizeof(char) * 1)) == NULL){
		perror("[Fail]:malloc@Function_Clear_Head\n");
		exit(1);
	}
	tmp_head[0] = '\0';
	return(tmp_head);
}
char *Function_Dot_Head(struct Tree *tree){
	if((*tree).Head[0] != '\0'){
		char *tmp_head;
		if((tmp_head = malloc(sizeof(char) * 2)) == NULL){
			perror("[Fail]:malloc@Function_Clear_Head\n");
			exit(1);
		}
		tmp_head[0] = '.';
		tmp_head[1] = '\0';
		return(tmp_head);
	}else{
		return((*tree).Head);
	}
}
char *Function_Compile_Head(struct Tree *tree, struct compile_options *_copt){
	char *tmp_head;
	char *out_head;
	int len = 0;
	len = strlen((*tree).Head);
	if((tmp_head = malloc(sizeof(char) * (len+1))) == NULL){
		perror("[Fail]:malloc@Function_Compile_Head.\n");
		exit(1);
	}
	if((out_head = malloc(sizeof(char) * (len+1))) == NULL){
		perror("[Fail]:malloc@Function_Compile_Head.\n");
		exit(1);
	}

	strcpy(tmp_head,(*tree).Head);

	if((*_copt).c_clear > 0){
		tmp_head = Function_Clear_Head(tree);
	}else if((*_copt).c_dot > 0){
		tmp_head = Function_Dot_Head(tree);
	}else if(strncmp(tmp_head,"$NULL$",6) == 0){
	}else if(strncmp(tmp_head,"$X$",3) == 0){
		strcpy(out_head,tmp_head+3);
		strcpy(tmp_head,out_head);
	}else if(strncmp(tmp_head,"$M$",3) == 0){
		strcpy(out_head,tmp_head+3);
		strcpy(tmp_head,out_head);
	}else if(strncmp(tmp_head,"$U$",3) == 0){
		strcpy(out_head,tmp_head+3);
		strcpy(tmp_head,out_head);
	}else if(strncmp(tmp_head,"$``",3) == 0){ //quating tree
		out_head=realloc(out_head, (sizeof(char) * (len+1)));
		if(out_head == NULL){
			perror("[Fail]:realloc@Function_Compile_Head.\n");
			exit(1);
		}
		out_head[0]='"';
		strcpy(out_head+1,tmp_head+3);
		out_head[len-1]='\0';
		strcpy(tmp_head,out_head);
	}else if(strncmp(tmp_head,"$~",2) == 0){
		strcpy(out_head,tmp_head+2);
		strcpy(tmp_head,out_head);
	}else if(strncmp(tmp_head,"$`",2) == 0){ //quating Head
		out_head=realloc(out_head, (sizeof(char) * (len+1)));
		if(out_head == NULL){
			perror("[Fail]:realloc@Function_Compile_Head.\n");
			exit(1);
		}
		out_head[0]='"';
		strcpy(out_head+1,tmp_head+2);
		out_head[len-1]='"';
		out_head[len]='\0';
		strcpy(tmp_head,out_head);
	}else if(is_reteral((*tree).Head) == 0){
		strcpy(out_head,tmp_head+1);
		strcpy(tmp_head,out_head);
	}
	return(tmp_head);
}

/* formated print functions */
//* structure members */
void Function_Print_Smems(struct Tree *tree){
	struct Tree *parent = (*tree).Parent;
	printf(":Adr=%ld:",(long int)tree);
	printf(":SN=%d:",(*tree).ser);
	printf(":H=%s:",(*tree).Head);
	if(parent != NULL){
		printf(":Pa=%d:",(*parent).ser);
	}else{
		printf(":Pa=%d:",-1);
	}
	printf(":LVs=%d:",(*tree).LVself);
	printf(":Cj=%d:",(*tree).Conj);
	printf(":NCs=%d:",(*tree).NCself);
	printf(":NC=%d:",(*tree).NextCount);
}
void Function_Print_Status(struct Tree *tree){
	Function_Print_Smems(tree);
	printf("\n");
}
void Function_Print_HeadHierarchy(struct Tree *tree){
	int i;
	for(i=0;i<(*tree).LVself;i++){
		printf(INDENT);
	}
	if((*tree).Conj == 1 && (*tree).NCself > 1){
		printf("+");
	}else{
		printf("-");
	}
	printf("%s\n",(*tree).Head);
}
void Function_Print_HeadHierarchyStatus(struct Tree *tree){
	int i;
	for(i=0;i<(*tree).LVself;i++){
		printf(INDENT);
	}
	if((*tree).Conj == 1 && (*tree).NCself > 1){
		printf("+");
	}else{
		printf("-");
	}

	/* print Head */
	printf("%s",(*tree).Head);

	/* print members */
	printf(INDENT);
	Function_Print_Smems(tree);
	printf("\n");
}
int Function_Print_Adj(struct Tree *tree, int nodes){
	int i;
	int j;
	for(i=0;i<nodes;i++){
		if(i == (*tree).ser){
			printf("[%d]",i);
		}
		for(j=0;j<(*tree).NextCount;j++){
			if(((*tree).Next[j])->ser == i){
				printf("%d",((*tree).Next[j])->ser);
			}
		}
		printf(",");
	}
	printf("\n");
	return(nodes);
}

/* meta functions */
void null_func(void){
}

/* print primitives */
//* Conj */
struct Tree *Function_Print_Conj_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).Conj == 1){
			printf(",");
		}else if((*tree).NCself > 1){
			printf(")(");
		}
	return(tree);
}
struct Tree *Function_Print_Conj_S(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).NCself > 1 && (*tree).Conj != 1){
			printf(")");
		}
		if((*tree).LVself != 0 && strlen((*tree).Head) != 0){
			/* for unpack */
			if((*_copt).c_counter > 0 && strncmp((*tree).Head,"$U$",3) == 0){
				if(strlen((*tree).Head) > 3){
					printf(",");
				}
			}else{
				printf(",");	//normal case
			}
		} 
	return(tree);
}
struct Tree *Function_Print_Conj_JS(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).NCself > 1 && (*tree).Conj != 1){
			printf("]");
		}
		if((*tree).LVself != 0 && strlen((*tree).Head) != 0){
			/* for unpack */
			if((*_copt).c_counter > 0 && strncmp((*tree).Head,"$U$",3) == 0){
				if(strlen((*tree).Head) > 3){
					printf(",");
				}
			}else{
				printf(",");	//normal case
			}
		} 
	return(tree);
}
struct Tree *Function_Print_Conj_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).Conj == 1){
			printf(",");
		}else if((*tree).NCself > 1){
			printf("][");
		}
	return(tree);
}
struct Tree *Function_Print_Conj_C(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).Conj == 1){
			printf(INDENT);
		}else if((*tree).NCself > 1){
			printf("\n");
			printf(INDENT);
		}
	return(tree);
}
struct Tree *Function_Print_Conj_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).Conj == 1){
			printf(" ");
		}else if((*tree).NCself > 1){
			printf("<c/>");
		}
	return(tree);
}
//* Head */
struct Tree *Function_Print_Head(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	/* compile */
	if((*_copt).c_counter > 0){
		char *tmp_str;
		tmp_str = Function_Compile_Head(tree,_copt);
		printf("%s",tmp_str);
	}else{
		printf("%s",(*tree).Head);	//normal
	}
	return(tree);
}
struct Tree *Function_Print_Head_JS(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	int sw = 0;
	int *dim_pos;
	int head_len = 0;
	char *head_str;
	char *tmp_str;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]:calloc@Function_Print_Head_J.\n");
		exit(1);
	}
	if((tmp_str = malloc(sizeof(char) * (head_len+1))) == NULL){
		perror("[Fail]:calloc@Function_Print_Head_W.\n");
		exit(1);
	}
	/* compile */
	if((*_copt).c_counter > 0){
		tmp_str = Function_Compile_Head(tree,_copt);
	}else{
		strcpy(tmp_str,(*tree).Head);
	}
	/* conversion */
	sw = Detect_Dim(tmp_str,dim_pos);
	if(sw == 2){
		head_len = strlen(tmp_str);
		if((head_str = malloc(sizeof(char) * (head_len+1))) == NULL){
			perror("[Fail]:calloc@Function_Print_Head_W.\n");
			exit(1);
		}
		strcpy(head_str,tmp_str);
		head_str[dim_pos[0]] = '\0';
		printf("[\"%s\",\"DIM\",",head_str);
		printf("%s",head_str+dim_pos[0]+1);
	}else{
		head_len = strlen(tmp_str);
		if(head_len > 0){
			printf("\"%s\"",tmp_str);
		}else{
			;
		}
	}
	return(tree);
}
struct Tree *Function_Print_Head_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	int sw = 0;
	int *dim_pos;
	int head_len = 0;
	char *head_str;
	char *tmp_str;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]:calloc@Function_Print_Head_W.\n");
		exit(1);
	}
	head_len = strlen((*tree).Head);
	if((tmp_str = malloc(sizeof(char) * (head_len+1))) == NULL){
		perror("[Fail]:calloc@Function_Print_Head_W.\n");
		exit(1);
	}
	/* compile */
	if((*_copt).c_counter > 0){
		tmp_str = Function_Compile_Head(tree,_copt);
	}else{
		strcpy(tmp_str,(*tree).Head);
	}
	/* conversion */
	sw = Detect_Dim(tmp_str,dim_pos);
	if(sw == 2){
		if((head_str = malloc(sizeof(char) * (head_len+1))) == NULL){
			perror("[Fail]:calloc@Function_Print_Head_W.\n");
			exit(1);
		}
		strcpy(head_str,tmp_str);
		head_str[dim_pos[0]] = '\0';
		printf("%s[DIM,",head_str);
		printf("%s",head_str+dim_pos[0]+1);
	}else{
		head_len = strlen(tmp_str);
		if(head_len > 0){
			printf("%s",tmp_str);
		}else{
			;
		}
	}
	return(tree);
}
struct Tree *Function_Print_Head_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount == 0){
		/* compile */
		if((*_copt).c_counter > 0){
			char *tmp_str;
			tmp_str = Function_Compile_Head(tree,_copt);
			printf("%s",tmp_str);
		}else{
			printf("%s",(*tree).Head);	//normal
		}
	}
	return(tree);
}
struct Tree *Function_Print_Head_SN(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	printf("%d",(*tree).ser);
	return(tree);
}
//* Bopen */
struct Tree *Function_Print_Bopen_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){
		if((*tree).NextCount != 0){
			/* for  unpack */
			if((*_copt).c_counter > 0 && strncmp((*tree).Head,"$U$",3) == 0){
				if(strlen((*tree).Head) > 3){
					printf(",");
				}
			}else{
				printf("(");	//normal case
			}
		}
	}
	return(tree);
}
struct Tree *Function_Print_Bopen_S(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 0){
		int i;
		for(i=0;i<(*tree).NextCount;i++){
			if((*tree).Next[i]->Conj == 0){
				/* for unpack */
				if((*_copt).c_counter > 0 && strncmp((*tree).Head,"$U$",3) == 0){
					if(strlen((*tree).Head) > 3){
						;
					}
				}else{
					printf("(");	//normal case
				}
			}
		}
	}
	return(tree);
}
struct Tree *Function_Print_Bopen_JS(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 0){
		int i;
		for(i=0;i<(*tree).NextCount;i++){
			if((*tree).Next[i]->Conj == 0){
				/* for unpack */
				if((*_copt).c_counter > 0 && strncmp((*tree).Head,"$U$",3) == 0){
					if(strlen((*tree).Head) > 3){
						;
					}
				}else{
					printf("[");	//normal case
				}


				//printf("[");
			}
		}
	}
	return(tree);
}
struct Tree *Function_Print_Bopen_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){
		if((*tree).NextCount != 0){
			printf("[");
		}
	}
	return(tree);
}
struct Tree *Function_Print_Bopen_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){
		if((*tree).NextCount != 0){
			int sw = 0;
			int *dim_pos;
			int head_len = 0;
			char *head_str;
			if((dim_pos = calloc(2,sizeof(int))) == NULL){
				perror("[Fail]:calloc@Function_Print_Head_W.\n");
				exit(1);
			}
			sw = Detect_Dim((*tree).Head,dim_pos);
			if(sw == 2){
				head_len = strlen((*tree).Head);
				if((head_str = malloc(sizeof(char) * (head_len+2))) == NULL){
					perror("[Fail]:calloc@Function_Print_Head_W.\n");
					exit(1);
				}
				strcpy(head_str,(*tree).Head);
				head_str[dim_pos[0]] = '\0';
				head_str[head_len-1] = '\0';
				printf("<%s DIM=",head_str);
				printf("%s>",head_str+dim_pos[0]+1);
			}else{
				head_len = strlen((*tree).Head);
				if(head_len > 0){
					printf("<%s>",(*tree).Head);
				}else{
					;
				}
			}
		}
	}
	return(tree);
}
struct Tree *Function_Print_Bopen_C(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){
		if((*tree).NextCount != 0){
			printf(INDENT);
		}
	}
	return(tree);
}
//* Bclose */
struct Tree *Function_Print_Bclose_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount != 0){
			/* for unpack */
			if((*_copt).c_counter > 0 && strncmp((*tree).Head,"$U$",3) == 0){
				//printf("");
				;
			}else{
				printf(")");	//normal case
			}
			/* for quating */
			if((*_copt).c_counter > 0 && strncmp((*tree).Head,"$``",3) == 0){
				printf("\"");
			}
	}
	return(tree);
}
struct Tree *Function_Print_Bclose_S(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount != 0){
			/* for unpack */
			if((*_copt).c_counter > 0 && strncmp((*tree).Head,"$U$",3) == 0){
				//printf("");
				;
			}else{
				printf(")");	//normal case
			}
			/* for quating */
			if((*_copt).c_counter > 0 && strncmp((*tree).Head,"$``",3) == 0){
				printf("\"");
			}
	}
	return(tree);
}
struct Tree *Function_Print_Bclose_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount != 0){
			/* for unpack */
			if((*_copt).c_counter > 0 && strncmp((*tree).Head,"$U$",3) == 0){
				//printf("");
				;
			}else{
				printf("]");	//normal case
			}
			/* for quating */
			if((*_copt).c_counter > 0 && strncmp((*tree).Head,"$``",3) == 0){
				printf("\"");
			}
	}
	return(tree);
}
struct Tree *Function_Print_Bclose_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount != 0){
			int sw = 0;
			int *dim_pos;
			int head_len = 0;
			char *head_str;
			if((dim_pos = calloc(2,sizeof(int))) == NULL){
				perror("[Fail]:calloc@Function_Print_Head_W.\n");
				exit(1);
			}
			sw = Detect_Dim((*tree).Head,dim_pos);
			if(sw == 2){
				head_len = strlen((*tree).Head);
				if((head_str = malloc(sizeof(char) * (head_len+2))) == NULL){
					perror("[Fail]:calloc@Function_Print_Head_W.\n");
					exit(1);
				}
				strcpy(head_str,(*tree).Head);
				head_str[dim_pos[0]] = '\0';
				head_str[head_len-1] = '\0';
				printf("</%s>",head_str);
			}else{
				head_len = strlen((*tree).Head);
				if(head_len > 0){
					printf("</%s>",(*tree).Head);
				}else{
					;
				}
			}
	}
	return(tree);
}
struct Tree *Function_Print_Bclose_C(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount != 0){
		printf("\n");
	}
	return(tree);
}

/* recursive-apply-function */
struct Tree *ExFunction_Recursive( struct Tree *tree, struct Tree *(*e_function)(struct Tree *), struct function_options *_fopt, struct compile_options *_copt ){
	int i;
	struct Tree *out = tree;
	if(tree == NULL || e_function == NULL){
		fprintf(stderr,"NULL.\n");
		exit(1);
	}
	(*e_function)(tree);
	for(i=0;i<(*tree).NextCount;i++){
		ExFunction_Recursive((*tree).Next[i],e_function,_fopt,_copt);
	}
	return(out);
}
struct Tree *ExFunction_Recursive_Ser( struct Tree *tree, struct Tree *(*e_function)(struct Tree *, int), struct function_options *_fopt, struct compile_options *_copt, int _ser ){
	int i;
	struct Tree *out = tree;
	if(tree == NULL || e_function == NULL){
		fprintf(stderr,"NULL.\n");
		exit(1);
	}
	(*e_function)(tree,_ser);
	for(i=0;i<(*tree).NextCount;i++){
		ExFunction_Recursive_Ser((*tree).Next[i],e_function,_fopt,_copt,_ser);
	}
	return(out);
}
struct Tree *ExFunction_Recursive_Ser_MultiPrint( struct Tree *tree, struct Tree *(*conj_function)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*head_function)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*bopen_function)(struct Tree *, struct function_options *, struct compile_options *, int),  struct Tree *(*bclose_function)(struct Tree *, struct function_options *, struct compile_options *),  struct function_options *_fopt, struct compile_options *_copt, int _ser ){
	int i;
	struct Tree *out = tree;
	if(tree == NULL){
		fprintf(stderr,"NULL.\n");
		exit(1);
	}
	/*print conj*/
	conj_function(tree,_fopt,_copt);
	/*print Bopen pre*/
	bopen_function(tree,_fopt,_copt,0);
	/*print head*/
	head_function(tree,_fopt,_copt);
	/*print Bopen post*/
	bopen_function(tree,_fopt,_copt,1);
	for(i=0;i<(*tree).NextCount;i++){
		ExFunction_Recursive_Ser_MultiPrint((*tree).Next[i],conj_function,head_function,bopen_function,bclose_function,_fopt,_copt,_ser);
	}
	/*print Bclose*/
	bclose_function(tree,_fopt,_copt);
	return(out);
}

/* GC */
int Function_Recursive_FreeForce_Tree(struct Tree *tree){
	int i;
	if(tree == NULL){
		return(1);
	}
	/* you must not free (*tree).Parent!! */
	for(i=0;i<(*tree).NextCount;i++){
		Function_Recursive_FreeForce_Tree((*tree).Next[i]);
		free((*tree).Next[i]);
		(*tree).Next[i] = NULL;
	}
	free((*tree).Next);
	(*tree).Next = NULL;
	(*tree).NextCount = 0;

	free((*tree).Head);
	(*tree).Head = NULL;

	return(0);
}
