/* administrative functions */
void print_war(char _C, struct Tree *_tree, int level){
        printf("\n:C=%c: ",_C);
        printf(":Pp=%ld:",(long int)(*_tree).Parent);
        printf(":Cp=%ld:",(long int)_tree);
        printf(":Cj=%d:",(*_tree).Conj);
        //printf(":Op=%d:",(*_tree).Bopen);
        printf(":current=%s:",(*_tree).Head);
        //printf(":Cl=%d:",(*_tree).Bclose);
        printf(":LV=%d:",(*_tree).LVself);
        printf(":NCs=%d:",(*_tree).NCself);
        printf(":NC=%d:",(*_tree).NextCount);
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
	//(*tree).Bopen=0;
	(*tree).Head = malloc(sizeof(char) * H_size);
	if((*tree).Head == NULL){
		fprintf(stderr,"[Fail]:malloc@Create_Node.\n");
		exit(1);
	}
	//(*tree).suffix=NULL;
	//(*tree).Bclose=0;
	(*tree).NextCount=0;
	(*tree).Next = malloc((size_t)sizeof(struct Tree *) * 1);
	if((*tree).Next == NULL){
		fprintf(stderr,"[Fail]:malloc@Create_Node.\n");
		exit(1);
	}
	(*tree).Parent=NULL;
	return(tree);
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
	}else if(strncmp(string,"$R",2) == 0){
		fails++;
	}else if(strncmp(string,"$E",2) == 0){
		fails++;
	}else if(strncmp(string,"$X",2) == 0){
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
int Function_Clear_Head(struct Tree *tree){
	(*tree).Head[0] = '\0';
	return(0);
	
}
int Function_Dot_Head(struct Tree *tree){
	if((*tree).Head[0] != '\0'){
		(*tree).Head[0] = '.';
		(*tree).Head[1] = '\0';
	}
	return(0);
}
int Function_Compile_Head(struct Tree *tree){
	char *tmp_head;
	int len = 0;
	len = strlen((*tree).Head);
	if((tmp_head = malloc(sizeof(char) * (len+1))) == NULL){
		perror("[Fail]:malloc@Function_Compile_Head.\n");
		exit(1);
	}
	strcpy(tmp_head,(*tree).Head);
	if(strncmp(tmp_head,"$X$",3) == 0){
		strcpy((*tree).Head,tmp_head+3);
		strcpy(tmp_head,(*tree).Head);
	}else if(strncmp(tmp_head,"$M$",3) == 0){
		strcpy((*tree).Head,tmp_head+3);
		strcpy(tmp_head,(*tree).Head);
	}else if(strncmp(tmp_head,"$~",2) == 0){
		strcpy((*tree).Head,tmp_head+2);
		strcpy(tmp_head,(*tree).Head);
	}else if(strncmp(tmp_head,"$`",2) == 0){ //quating Head
		(*tree).Head=realloc((*tree).Head, (sizeof(char) * (len+1)));
		if((*tree).Head == NULL){
			perror("[Fail]:realloc@Function_Compile_Head.\n");
			exit(1);
		}
		(*tree).Head[0]='"';
		strcpy((*tree).Head+1,tmp_head+2);
		(*tree).Head[len-1]='"';
		(*tree).Head[len]='\0';
	}else if(is_reteral((*tree).Head) == 0){
		strcpy((*tree).Head,tmp_head+1);
		strcpy(tmp_head,(*tree).Head);
	}
	return(0);
}

/* formated print functions */
void Function_Print_Smems(struct Tree *tree){
	struct Tree *parent = (*tree).Parent;
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
	//printf(":BO=%d:",(*tree).Bopen);
	//printf(":BC=%d:",(*tree).Bclose);
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

/* TQ */
//* print primitives */
struct Tree *Function_Print_Conj_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).Conj == 1){
			printf(",");
		}else if((*tree).NCself > 1){
			printf(")(");
		}
	return(tree);
}
struct Tree *Function_Print_Conj_C(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).Conj == 1){
			//printf(",");
			printf(INDENT);
		}else if((*tree).NCself > 1){
			//printf(")(");
			printf("\n");
			printf(INDENT);
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
struct Tree *Function_Print_Conj_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).Conj == 1){
			printf(",");
		}else if((*tree).NCself > 1){
			printf(" ");
		}
	return(tree);
}
struct Tree *Function_Print_Conj_S(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).NCself > 1 && (*tree).Conj != 1){
			printf(")");
		}
		if((*tree).LVself != 0 && strlen((*tree).Head) != 0){
			printf(",");
		} 
	return(tree);
}
struct Tree *Function_Print_Conj_JS(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).NCself > 1 && (*tree).Conj != 1){
			printf("]");
		}
		if((*tree).LVself != 0 && strlen((*tree).Head) != 0){
			printf(",");
		} 
	return(tree);
}

struct Tree *Function_Print_Head(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	printf("%s",(*tree).Head);
	return(tree);
}
struct Tree *Function_Print_Head_SN(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	printf("%d",(*tree).ser);
	return(tree);
}
struct Tree *Function_Print_Head_JS(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	int sw = 0;
	int *dim_pos;
	int head_len = 0;
	char *head_str;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]:calloc@Function_Print_Head_J.\n");
		exit(1);
	}
	sw = Detect_Dim((*tree).Head,dim_pos);
	if(sw == 2){
		head_len = strlen((*tree).Head);
		if((head_str = malloc(sizeof(char) * (head_len+1))) == NULL){
			perror("[Fail]:calloc@Function_Print_Head_W.\n");
			exit(1);
		}
		strcpy(head_str,(*tree).Head);
		//(*tree).Head[dim_pos[0]] = '\0';
		head_str[dim_pos[0]] = '\0';
		//printf("[\"%s\",\"DIM\",",(*tree).Head);
		printf("[\"%s\",\"DIM\",",head_str);
		//printf("%s",(*tree).Head+dim_pos[0]+1);
		printf("%s",head_str+dim_pos[0]+1);
	}else{
		head_len = strlen((*tree).Head);
		if(head_len > 0){
			printf("\"%s\"",(*tree).Head);
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
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]:calloc@Function_Print_Head_W.\n");
		exit(1);
	}
	sw = Detect_Dim((*tree).Head,dim_pos);
	if(sw == 2){
		head_len = strlen((*tree).Head);
		if((head_str = malloc(sizeof(char) * (head_len+1))) == NULL){
			perror("[Fail]:calloc@Function_Print_Head_W.\n");
			exit(1);
		}
		strcpy(head_str,(*tree).Head);
		//(*tree).Head[dim_pos[0]] = '\0';
		head_str[dim_pos[0]] = '\0';
		//printf("%s[DIM,",(*tree).Head);
		printf("%s[DIM,",head_str);
		//printf("%s",(*tree).Head+dim_pos[0]+1);
		printf("%s",head_str+dim_pos[0]+1);
	}else{
		head_len = strlen((*tree).Head);
		if(head_len > 0){
			printf("%s",(*tree).Head);
		}else{
			;
		}
	}
	return(tree);
}
struct Tree *Function_Print_Head_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount == 0){
		printf("%s",(*tree).Head);
	}
	return(tree);
}

struct Tree *Function_Print_Bopen_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){	//OK
		if((*tree).NextCount != 0){
			printf("(");
		}
	}
	return(tree);
}
struct Tree *Function_Print_Bopen_C(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){	//OK
		if((*tree).NextCount != 0){
			printf(INDENT);
		}
	}
	return(tree);
}
struct Tree *Function_Print_Bopen_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){	//OK
		if((*tree).NextCount != 0){
			printf("[");
		}
	}
	return(tree);
}
struct Tree *Function_Print_Bopen_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){	//OK
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
struct Tree *Function_Print_Bopen_S(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 0){	// testing
		int i;
		for(i=0;i<(*tree).NextCount;i++){
			if((*tree).Next[i]->Conj == 0){
				printf("(");
			}
		}
	}
	return(tree);
}
struct Tree *Function_Print_Bopen_JS(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 0){	// testing
		int i;
		for(i=0;i<(*tree).NextCount;i++){
			if((*tree).Next[i]->Conj == 0){
				printf("[");
			}
		}
	}
	return(tree);
}

struct Tree *Function_Print_Bclose(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount != 0){
		printf(")");
	}
	return(tree);
}
struct Tree *Function_Print_Bclose_C(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount != 0){
		printf("\n");
	}
	return(tree);
}
struct Tree *Function_Print_Bclose_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount != 0){
		printf("]");
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
struct Tree *ExFunction_Recursive_Ser( struct Tree *tree, struct Tree *(*e_function)(struct Tree *, int), struct function_options *_fopt, struct compile_options *_copt, int ser ){
	int i;
	struct Tree *out = tree;
	if(tree == NULL || e_function == NULL){
		fprintf(stderr,"NULL.\n");
		exit(1);
	}
	(*e_function)(tree,ser);
	for(i=0;i<(*tree).NextCount;i++){
		ExFunction_Recursive_Ser((*tree).Next[i],e_function,_fopt,_copt,ser);
	}
	return(out);
}
struct Tree *ExFunction_Recursive_Ser_MultiPrint( struct Tree *tree, struct Tree *(*conj_function)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*head_function)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*bopen_function)(struct Tree *, struct function_options *, struct compile_options *, int),  struct Tree *(*bclose_function)(struct Tree *, struct function_options *, struct compile_options *),  struct function_options *_fopt, struct compile_options *_copt, int ser ){
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
		ExFunction_Recursive_Ser_MultiPrint((*tree).Next[i],conj_function,head_function,bopen_function,bclose_function,_fopt,_copt,ser);
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
