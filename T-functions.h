/* README */
/* //%P : print-function which contains NO converter. */
/* //%I : incomplete function. */

/* program */
/* prottype */
struct Tree *Function_Print_Head(struct Tree *, struct function_options *, struct compile_options *);

struct Tree *Executor(struct Tree *, struct Tree *, struct Tree *, int, int, struct options *, struct function_options *, struct compile_options *, struct search_options *, FILE *, int);

struct Tree *ExFunction_Recursive_Ser_MultiPrint(struct Tree *, struct Tree *(*)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*)(struct Tree *, struct function_options *, struct compile_options *, int),  struct Tree *(*)(struct Tree *, struct function_options *, struct compile_options *), struct options *, struct function_options *, struct compile_options *, int);

struct Tree *ExFunction_Recursive_Ser(struct Tree *, struct Tree *(*)(struct Tree *, int, struct options *), struct options *, struct function_options *, struct compile_options *, int , int);

struct Tree *ExFunction_Recursive(struct Tree *, struct Tree *(*)(struct Tree *, struct options *), struct options *, struct function_options *, struct compile_options *);

struct Tree *ExFunction_Recursive_Set_Obj(struct Tree *, struct Tree *(*)(struct Tree *, void *), void *);

/* meta functions */
void null_func(void){
}

/* GC */
int Function_Recursive_FreeForce_Tree(struct Tree *tree){
	FC(fprintf(stderr,">Function_Recursive_FreeForce_Tree<\n");)
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
	free((*tree).dimstr);
	(*tree).dimstr = NULL;
	free((*tree).valstr);
	(*tree).valstr = NULL;
	return(0);
}

/* analyzers */
/** tree analysis */
struct Tree *Function_Get_Node(char *pos_str, struct Tree *tree){
	FC(fprintf(stderr,">Function_Get_Node<\n");)
	int len = 0;
	int list_len = 0;
	int i;
	int count = 0;
	int *list;
	struct Tree *current = NULL;
	len = strlen(pos_str);
	for(i=0;i<len;i++){
		if(pos_str[i] == ','){
			list_len++;
		}
	}
	list_len++;
	if((list = malloc(sizeof(int) * list_len)) == NULL){
		perror("[Fail]malloc@get_node\n");
		exit(1);
	}
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
/** head analysis */
int Analyze_HeadLabel(struct Tree *tree){ // for labeling
	FC(fprintf(stderr,">Analyze_HeadLabel<\n");)
	int i = 0;
	int labelreadptr = 0;
	int labelnumlen = 0;
	char *labelnumstr;
	int headlen = 0;
	int labeled = 0;
	/* label type */
	if((*tree).Head[0] == '#' && (*tree).Head[1] == '#'){
		(*tree).LabelType = 't';
		labelreadptr = 2;
		labeled++;
	}else if((*tree).Head[0] == '#' && (*tree).Head[1] != '#'){
		(*tree).LabelType = 'h';
		labelreadptr = 1;
		labeled++;
	}
	/* label */
	if((*tree).LabelType != '\0'){
		/* check num char */
		for(i=labelreadptr; ((*tree).Head[i] >= 0x30) && ((*tree).Head[i] <= 0x39);i++){	//Hex
			labelnumlen++;
		}
		if((labelnumstr = malloc(sizeof(char) * (labelnumlen + 1))) == NULL){
			perror("[Fail]malloc@Analyze_HeadLabel\n");
			exit(1);
		}
		strncpy(labelnumstr,(*tree).Head+labelreadptr,labelnumlen);
		sscanf(labelnumstr,"%d",&(*tree).Label);
		free(labelnumstr);
		labeled++;
	}
	/* IndicatorPtr */
	headlen = strlen((*tree).Head);
	for(i=labelreadptr;i<headlen;i++){
		if((*tree).Head[i] < 0x30 || (*tree).Head[i] > 0x39){
			(*tree).IndicatorPtr = i;
			break;
		}
	}
	DB(printf("\nH:%s:Ptr:%d:\n",(*tree).Head,(*tree).IndicatorPtr);)
	//fprintf(stderr,"labeled:%d.\n",labeled);
	return(0);
}
/** reference analysis */
struct Tree *Function_Recursive_SearchBind_LabelNode(struct Tree *tree, char type, int label, struct Tree *binded){	//for referred
	FC(fprintf(stderr,">Function_Recursive_SearchBind_LabelNode<\n");)
	int i;
	if(tree == NULL){
		return(NULL);
	}
	if((*tree).LabelType == 't' && (*tree).Label == label){
		(*binded).RefNode = tree;	//bind tree,head
	}
	if((*tree).LabelType == type && (*tree).Label == label){
		(*binded).RefNode = tree;	//bind tree
	}
	for(i=0;i<(*tree).NextCount;i++){
		Function_Recursive_SearchBind_LabelNode((*tree).Next[i],type,label,binded);
	}
	return(NULL);
}
int get_ref(char *head, char *type, int *label){	//for binded
	FC(fprintf(stderr,">get_ref<\n");)
	//search for $# or $##
	int i;
	int len = 0;
	len = strlen(head);
	if(len < 3){
		return(0);
	}
	if(head[0] != '$' || head[1] != '#'){
		return(0);
	}
	if(head[2] >= 0x30 && head[2] <= 0x39){
		sscanf(head+2,"%d",label);
		*type = 'h';
		for(i=0;;i++){
			if(head[2+i] >= 0x30 && head[2+i] <= 0x39){
				;
			}else{
				break;
			}
		}
		//printf("pgs:%d:\n",2+i);
		//printf("nc:%c:\n",head[2+i]);
		return(2+i);
	}
	if(len > 3){
		if(head[2] == '#' && head[3] >= 0x30 && head[3] <= 0x39){
			sscanf(head+3,"%d",label);
			*type = 't';
			for(i=0;;i++){
				if(head[3+i] >= 0x30 && head[3+i] <= 0x39){
					;
				}else{
					break;
				}
			}
			//printf("pgs:%d:\n",3+i);
			//printf("nc:%c:\n",head[3+i]);
			return(3+i);
		}
	}
	return(0);
}

/* restructure functions */
int get_nval(char *str){
	FC(fprintf(stderr,">get_nval<\n");)
	int i;
	int len;
	int count = 1;
	int tmpval = 1;
	len = strlen(str);
	for(i=0;i<len;i++){
		if(str[i] == '[' || str[i] == ','){
			tmpval = 1;
			sscanf(str+i+1,"%d",&tmpval);
			count = count*tmpval;
		}
	}
	return(count);
}
int Add_DimStr(struct Tree *tree, int *dim_pos, char *buff){
	FC(fprintf(stderr,">Add_DimStr<\n");)
	int len;
	len = strlen(buff);
	snprintf(buff+len,dim_pos[1]-dim_pos[0]+1,"%s",(*tree).Head+dim_pos[0]);
	return(len);
}
int Ins_DimStr(struct Tree *tree, int *dim_pos, char *buff){
	FC(fprintf(stderr,">Ins_DimStr<\n");)
	int len;
	char *minibuff;
	if((minibuff = malloc(sizeof(char) * LEN)) == NULL){
		perror("[Fail]malloc@Ins_DimStr");
		exit(1);
	}
	/* currentbuff -> minibuff */
	strcpy(minibuff,buff);
	snprintf(buff,dim_pos[1]-dim_pos[0]+1,"%s",(*tree).Head+dim_pos[0]);
	len = strlen(buff);
	strcpy(buff+len,minibuff);
	free(minibuff);
	return(len);
}
int Detect_DimRegion(const char *head, int *pos){
	FC(fprintf(stderr,">Detect_DimRegion<\n");)
	int len;
	int dim_s = -1;
	int dim_e = -1;
	int esc = 0;
	int i;
	int ret = 0;
	len = strlen(head);
	for(i=0;i<len;i++){
		//if(head[i] == '\\'){
		//	esc = 1;
		if(head[i] == '"' && esc == 0){
        		esc = 1;
		}else if(head[i] == '"' && esc == 1){
		        esc = 0;
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
int SPrint_UpRecursive_Head(struct Tree *tree, char *buff){
	FC(fprintf(stderr,">SPrint_UpRecursive_Head<\n");)
	int sw;
	int *dim_pos;
	int len;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]calloc@SPrint_UpRecursive_Head\n");
		exit(1);
	}
	if((*tree).Parent == NULL){
		sw = Detect_DimRegion((*tree).Head,dim_pos);
		if(sw == 2){
			Ins_DimStr(tree,dim_pos,buff);
		}
		return(0);
	}else{
		sw = Detect_DimRegion((*tree).Head,dim_pos);
		if(sw == 2){
			Ins_DimStr(tree,dim_pos,buff);
		}
		SPrint_UpRecursive_Head((*tree).Parent,buff);
	}
	len = strlen(buff);
	return(len);
}
struct Tree *Detect_DimBlock(struct Tree *tree, struct options *_opt){
	FC(fprintf(stderr,">Detect_DimBlock<\n");)
	int sw = 0;
	int *dim_pos;
	char *buff;
	int len = 0;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]calloc@SPrint_UpRecursive_Head\n");
		exit(1);
	}
	if((*tree).NextCount != 0){
		return(NULL);
	}
	sw = Detect_DimRegion((*tree).Head,dim_pos);
	if(sw != 2){
		return(NULL);
	}
	if((buff = malloc(sizeof(char) * (*_opt).buff)) == NULL){
		perror("[Fail]malloc@Detect_DimBlock.\n");
		exit(1);
	}
	buff[0] = '\0';
	/* tmp -> dim */	
	len = SPrint_UpRecursive_Head(tree,buff);
	if(((*tree).dimstr = malloc(sizeof(char) * (len + 1))) == NULL){
		perror("[Fail]malloc@Detect_DimBlock.\n");
		exit(1);
	}
	strcpy((*tree).dimstr,buff);
	(*tree).nval = get_nval(buff);
	free(buff);
	return(tree);
}
struct Tree *Function_Recursive_Search_BindNode(struct Tree *top, int *bn_count, struct Tree **bn_table){
	FC(fprintf(stderr,">Function_Recursive_Search_BindNode<\n");)
	int i;
	struct Tree *current = NULL;
	current = top;
	if((*current).nval > 0){
		bn_table = realloc(bn_table,(sizeof(struct Tree *) * (*bn_count + 2)));
		if(bn_table == NULL){
			perror("[Fail]realloc@Function_Recursive_Search_BindNode");
			exit(1);
		}
		bn_table[(*bn_count)] = current;
		(*bn_count)++;
	}
	for(i=0;i<(*current).NextCount;i++){
		Function_Recursive_Search_BindNode((*current).Next[i],bn_count,bn_table);
	}
	return(NULL);
}
int Function_Bind_Data(FILE *DATA, struct Tree *tree, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt){
	FC(fprintf(stderr,">Function_Bind_Data<\n");)
	int i;
        int C = '\0';
        int bn_count = 0;
        struct Tree **bn_table = NULL;
	if((bn_table = malloc(sizeof(struct Tree *) * 1)) == NULL){
		perror("[]malloc@bind_data");
		exit(1);
	}
        Function_Recursive_Search_BindNode(tree,&bn_count,bn_table);
	int delim_count = 0;
	int node_count = 0;
	int buff_ptr = 0;
	int buff_len = 0;
	char *buff;
	int ESC = 0;
	if((buff = malloc(sizeof(char) * (*_opt).data_buff)) == NULL){
		perror("[]malloc@bind_data.\n");
		exit(1);
	}
	buff[0] = '\0';
        while((C = fgetc(DATA))){
		if(node_count >= bn_count){
			break;
		}
                if(C == EOF){
                        return(0);
                }else{

			buff[buff_ptr] = C;
			buff_ptr++;
			if((C == DD || C == '\n') && ESC == 0){
				delim_count++;
			}
			if(bn_table[node_count]->nval == delim_count && ESC == 0){
				buff[buff_ptr] = '\0';
				buff_len = strlen(buff);
				for(i=0;i<buff_len;i++){
					if(buff[i] == '\n'){
						buff[i] = DD;
					}
				}
				if(buff[buff_len-1] == DD || buff[buff_len-1] == '\n'){
					buff[buff_len-1] = '\0';
				}
				buff_len = strlen(buff);
				bn_table[node_count]->valstr = malloc(sizeof(char) * (buff_len + 1));
				if(bn_table[node_count]->valstr == NULL){
					perror("[Fail]malloc@bind_data().\n");
					exit(1);
				}
				strcpy((*bn_table[node_count]).valstr,buff);
				delim_count = 0;
				node_count++;
				buff_ptr = 0;
			}
			#include "escape_sw.c"
                }
        }
	free(buff);
        return(0);
}
int Assign_RefedValPtr(struct Tree *tree){	// for product
	FC(fprintf(stderr,">Assign_RefedValPtr<\n");)
	if(tree == NULL){
		return(0);
	}
	if((*tree).valstr == NULL){
		return(0);
	}
	if((*tree).nval > 0){
		if(((*tree).valPtr = malloc(sizeof(int) * (*tree).nval)) == NULL){
			perror("[Fail]malloc@Assign_RefedValPtr().\n");
			exit(1);
		}
		int i;
		int len = 0;
		char C = '\0';
		int ESC = 0;
		int count = 0;
		len = strlen((*tree).valstr);
		(*tree).valPtr[count] = 0;
		count++;
		for(i=0;i<len;i++){
			C = (*tree).valstr[i];
			if(C == DD && ESC == 0){
				(*tree).valPtr[count] = i + 1;
				count++;
			}
			#include "escape_sw.c"
		}
	}
	return(0);
}
void Function_Recursive_Bind_RefNode(struct Tree *binded, struct Tree *referred){
	FC(fprintf(stderr,">Function_Recursive_Bind_RefNode<\n");)
	int i;
	char target_type = '\0';
	int target_label = -1;
	int stat = -1;
	stat = get_ref((*binded).Head+(*binded).IndicatorPtr,&target_type,&target_label);
	// ここにheadのIndicatorPtrをプログレスするコードか? だめ、レファレンスバインドできなくなる
	//(*binded).IndicatorPtr = (*binded).IndicatorPtr + stat;
	if(stat > 0){
		struct Tree *addr = NULL;
		addr = Function_Recursive_SearchBind_LabelNode(referred,target_type,target_label,binded);
	}
	for(i=0;i<(*binded).NextCount;i++){
		Function_Recursive_Bind_RefNode((*binded).Next[i],referred);
	}
}

struct Tree *Create_Node(int _ser, int H_size){
	FC(fprintf(stderr,">Create_Node<\n");)
	struct Tree *tree;
	if((tree = malloc(sizeof(struct Tree) * 1)) == NULL){
		perror("[Fail]:malloc@Create_Node.\n");
		exit(1);
	}
	(*tree).ser = _ser;
	(*tree).LVself = 0;
	(*tree).NCself = 1;
	(*tree).Conj = 0;
	(*tree).LabelType = '\0';
	(*tree).Label = -1;
	(*tree).IndicatorPtr = 0;
	if(H_size < 1){
		(*tree).Head = NULL;
	}else{
		if(((*tree).Head = malloc(sizeof(char) * H_size)) == NULL){
			perror("[Fail]:malloc@Create_Node.\n");
			exit(1);
		}
	}
	(*tree).NextCount = 0;
	if(((*tree).Next = malloc((size_t)sizeof(struct Tree *) * 1)) == NULL){
		perror("[Fail]:malloc@Create_Node.\n");
		exit(1);
	}
	(*tree).dimstr = NULL;
	(*tree).nval = 0;
	(*tree).valPtr = NULL;
	(*tree).valstr = NULL;
	(*tree).Parent = NULL;
	(*tree).RefNode = NULL;
	(*tree).extra_stat = 0;
	return(tree);
}
struct Tree *Add_Next(struct Tree *parent, struct Tree *next){
	FC(fprintf(stderr,">Add_Next<\n");)
	if(parent == NULL){
		perror("NULL parent detected -- exit.\n");
		exit(1);
	}
	(*parent).Next = realloc((*parent).Next,(size_t)sizeof(struct Tree *) * (*parent).NextCount+1);
	if((*parent).Next == NULL){
		perror("[Fail]malloc@Add_Next.\n");
	}
	(*parent).Next[(*parent).NextCount] = next;
	(*parent).Next[(*parent).NextCount]->LVself = (*parent).LVself+1;
	(*parent).Next[(*parent).NextCount]->NCself = (*parent).NextCount+1;
	(*parent).Next[(*parent).NextCount]->Parent = parent;
	(*parent).NextCount++;
	return(next);
}
struct Tree *Set_status(struct Tree *tree, int *bit){
	FC(fprintf(stderr,">Set_status<\n");)
	if(((*tree).extra_stat&*bit) != *bit){
		(*tree).extra_stat = (*tree).extra_stat + *bit;
	}
	return(tree);
}

/* compile functions */
char *Function_Clear_Head(struct Tree *tree){
	FC(fprintf(stderr,">Function_Clear_Head<\n");)
	char *tmp_head;
	if((tmp_head = malloc(sizeof(char) * 1)) == NULL){
		perror("[Fail]:malloc@Function_Clear_Head\n");
		exit(1);
	}
	tmp_head[0] = '\0';
	return(tmp_head);
}
char *Function_Dot_Head(struct Tree *tree){
	FC(fprintf(stderr,">Function_Dot_Head<\n");)
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
char *Function_Interpret_Head(struct Tree *tree, struct compile_options *_copt){
	FC(fprintf(stderr,">Function_Interpret_Head<\n");)
	char *tmp_head;
	char *out_head;
	int compiled = 0;
	int len = 0;
	len = strlen((*tree).Head);
	if((tmp_head = malloc(sizeof(char) * (len+1))) == NULL){
		perror("[Fail]:malloc@Function_Interpret_Head.\n");
		exit(1);
	}
	if((out_head = malloc(sizeof(char) * (len+1))) == NULL){
		perror("[Fail]:malloc@Function_Interpret_Head.\n");
		exit(1);
	}

	strcpy(tmp_head,(*tree).Head+(*tree).IndicatorPtr);

	if((*_copt).c_clear > 0){
		tmp_head = Function_Clear_Head(tree);
	}else if((*_copt).c_dot > 0){
		tmp_head = Function_Dot_Head(tree);
	}else if(strncmp(tmp_head,"$NULL$",6) == 0){
	//}else if(strncmp(tmp_head+(*tree).IndicatorPtr,"$PI$",4) == 0){	// Inner Product
	}else if(strncmp(tmp_head,"$PI$",4) == 0){	// Inner Product
		//strcpy(out_head,tmp_head+(*tree).IndicatorPtr+4);
		strcpy(out_head,tmp_head+4);
		strcpy(tmp_head,out_head);
		if(((*tree).extra_stat&2) != 2){
			(*tree).extra_stat = (*tree).extra_stat + 2;
		}
		compiled++;
	//}else if(strncmp(tmp_head+(*tree).IndicatorPtr,"$X$",3) == 0){
	}else if(strncmp(tmp_head,"$X$",3) == 0){
		//strcpy(out_head,tmp_head+(*tree).IndicatorPtr+3);
		strcpy(out_head,tmp_head+3);
		strcpy(tmp_head,out_head);
		compiled++;
	//}else if(strncmp(tmp_head+(*tree).IndicatorPtr,"$M$",3) == 0){
	}else if(strncmp(tmp_head,"$M$",3) == 0){
		//strcpy(out_head,tmp_head+(*tree).IndicatorPtr+3);
		strcpy(out_head,tmp_head+3);
		strcpy(tmp_head,out_head);
		compiled++;
	//}else if(strncmp(tmp_head+(*tree).IndicatorPtr,"$U$",3) == 0){
	}else if(strncmp(tmp_head,"$UU$",4) == 0){
		strcpy(out_head,tmp_head+4);
		strcpy(tmp_head,out_head);
		if(((*tree).extra_stat&8) != 8){
			(*tree).extra_stat = (*tree).extra_stat + 8;
		}
		int tmp_stat = 8;
		ExFunction_Recursive_Set_Obj(tree, (struct Tree *(*)())Set_status, (int *)&tmp_stat);	// set cascading
		compiled++;
	}else if(strncmp(tmp_head,"$U$",3) == 0){
		//strcpy(out_head,tmp_head+(*tree).IndicatorPtr+3);
		strcpy(out_head,tmp_head+3);
		strcpy(tmp_head,out_head);
		if(((*tree).extra_stat&8) != 8){
			(*tree).extra_stat = (*tree).extra_stat + 8;
		}
		compiled++;
	}else if(strncmp(tmp_head,"$``$",4) == 0){ //quating tree
		int tmp_len = 0;
		out_head = realloc(out_head, (sizeof(char) * (len+1)));
		if(out_head == NULL){
			perror("[Fail]:realloc@Function_Interpret_Head.\n");
			exit(1);
		}

		/*
		out_head[0]='"';
		if((*tree).NextCount == 0){
			strcpy(out_head+1,tmp_head+3);
			out_head[len-2]='"';
			out_head[len-1]='\0';
		}else{
			strcpy(out_head+1,tmp_head+3);
			out_head[len-1]='\0';
		}
		*/

		out_head[0]='"';
		strcpy(out_head+1,tmp_head+4);
		tmp_len = strlen(out_head);
		if((*tree).NextCount == 0){
			out_head[tmp_len]='"';
			out_head[tmp_len+1]='\0';
		}

		strcpy(tmp_head,out_head);
		if(((*tree).extra_stat&4) != 4){
			(*tree).extra_stat = (*tree).extra_stat + 4;
		}
		compiled++;
	}else if(strncmp(tmp_head,"$~~$",4) == 0){
		strcpy(out_head,tmp_head+4);
		strcpy(tmp_head,out_head);
		if(((*tree).extra_stat&1) != 1){
			(*tree).extra_stat = (*tree).extra_stat + 1;
		}
		int tmp_stat = 1;
		ExFunction_Recursive_Set_Obj(tree, (struct Tree *(*)())Set_status, (int *)&tmp_stat);	// set cascading
		compiled++;
	}else if(strncmp(tmp_head,"$~$",3) == 0){
		strcpy(out_head,tmp_head+3);
		strcpy(tmp_head,out_head);
		if(((*tree).extra_stat&1) != 1){
			(*tree).extra_stat = (*tree).extra_stat + 1;
		}
		compiled++;
	}else if(strncmp(tmp_head,"$`$",3) == 0){ //quating Head
		int tmp_len = 0;
		out_head = realloc(out_head, (sizeof(char) * (len+1)));
		if(out_head == NULL){
			perror("[Fail]:realloc@Function_Interpret_Head_Head.\n");
			exit(1);
		}
		out_head[0]='"';
		strcpy(out_head+1,tmp_head+3);
		//printf("len:%d:",len);
		//printf("S:%s:",out_head+1);
		//printf("s:%s:",out_head);
		tmp_len = strlen(out_head);
		out_head[tmp_len]='"';
		out_head[tmp_len+1]='\0';
		strcpy(tmp_head,out_head);
		compiled++;
	}
	free(out_head);
	//fprintf(stderr,"Compiled:%d.\n",compiled);
	return(tmp_head);
}

/* print functions */
/** status */
void Function_Print_Smems(struct Tree *tree){
	printf(":SN=%d:",(*tree).ser);
	printf(":LVs=%d:",(*tree).LVself);
	printf(":Adr=%ld:",(long int)tree);
	printf(":PaAdr=%ld:",(long int)(*tree).Parent);
	printf(":Ref=%ld:",(long int)(*tree).RefNode);
	printf(":LT=%c:",(*tree).LabelType);
	printf(":Lb=%d:",(*tree).Label);
	printf(":Hptr=%d:",(*tree).IndicatorPtr);
	printf(":H=%s:",(*tree).Head);
	printf(":D=%s:",(*tree).dimstr);
	printf(":nval=%d:",(*tree).nval);
	printf(":vstr=%s:",(*tree).valstr);
	printf(":vptr=");
	if((*tree).valPtr != NULL){
		int i;
		for(i=0;i<(*tree).nval;i++){
			printf(",%d",(*tree).valPtr[i]);
		}
	}
	printf(":");
	printf(":Cj=%d:",(*tree).Conj);
	printf(":NCs=%d:",(*tree).NCself);
	printf(":NC=%d:",(*tree).NextCount);
	printf(":stat=%d:",(*tree).extra_stat);
}
void Function_Print_Status(struct Tree *tree){
	Function_Print_Smems(tree);
	printf("\n");
}
void print_war(char C, struct Tree *tree, int level){
	printf(":C=%c:",C);
	printf(":DetectLV=%d:",level);
	Function_Print_Smems(tree);
}
int Function_Print_Adj(struct Tree *tree, int nodes, struct options *_opt){
	int i;
	int j;
	for(i=0;i<nodes;i++){
		if(i == (*tree).ser){
			printf("[:%s:%d",(*tree).Head,i);
			if((*tree).RefNode != NULL){
				printf("->%d",((*tree).RefNode)->ser);
			}
			printf("]");
		}
		for(j=0;j<(*tree).NextCount;j++){
			if(((*tree).Next[j])->ser == i){
				printf("%d",((*tree).Next[j])->ser);
				break;
			}else if((*tree).Next[j]->RefNode != NULL){
				if((*tree).Next[j]->RefNode->ser == i){
					printf("%d",(*tree).Next[j]->RefNode->ser);
				}
			}
		}
		printf(",");
	}
	printf("\n");
	return(nodes);
}
/** Conj */
struct Tree *Function_Print_Conj_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		DB(fprintf(stderr," before op : skip:%d:\n",(*_fopt).f_skipOnce);)
		if((((*_fopt).f_skipOnce)&1) == 1){
			(*_fopt).f_skipOnce = (*_fopt).f_skipOnce - 1;
			return(tree);
		}
		DB(fprintf(stderr," after op : skip:%d:\n",(*_fopt).f_skipOnce);)
		if((*tree).Conj == 1){
			printf(",");
		}else if((*tree).NCself > 1 && (*tree).Conj == 0){	// for search
			printf(")(");
		}
	return(tree);
}
struct Tree *Function_Print_Conj_S(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
		if((*tree).NCself > 1 && (*tree).Conj != 1){
			printf(")");
		}
		if((*tree).LVself != 0 && strlen((*tree).Head) != 0){ 
			if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
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
			if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
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
/** Bopen */
struct Tree *Function_Print_Bopen_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){
		if((*tree).NextCount != 0){ 
			if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8&& ((*tree).extra_stat&1) != 1){	// for unpack
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
				if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
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
				if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
					if(strlen((*tree).Head) > 3){
						;
					}
				}else{
					printf("[");	//normal case
				}
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
				perror("[Fail]:calloc@Function_Print_Bopen_X.\n");
				exit(1);
			}
			sw = Detect_DimRegion((*tree).Head,dim_pos);
			if(sw == 2){
				head_len = strlen((*tree).Head);
				if((head_str = malloc(sizeof(char) * (head_len+2))) == NULL){
					perror("[Fail]:calloc@Function_Print_Bopen_X.\n");
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
/** Bclose */
struct Tree *Function_Print_Bclose_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount != 0){
			if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8&& ((*tree).extra_stat&1) != 1){	// for unpack
				;
			}else{
				printf(")");	//normal case
			}
			if((*_copt).c_counter > 0 && ((*tree).extra_stat&4) == 4){	// for quating
				printf("\"");
			}
	}
	return(tree);
}
struct Tree *Function_Print_Bclose_S(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount != 0){
			if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
				;
			}else{
				printf(")");	//normal case
			}
			if((*_copt).c_counter > 0 && ((*tree).extra_stat&4) == 4){	// for quating
				printf("\"");
			}
	}
	return(tree);
}
struct Tree *Function_Print_Bclose_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	if((*tree).NextCount != 0){
			if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
				;
			}else{
				printf("]");	//normal case
			}
			if((*_copt).c_counter > 0 && ((*tree).extra_stat&4) == 4){	// for quating
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
				perror("[Fail]:calloc@Function_Print_Bclose_X.\n");
				exit(1);
			}
			sw = Detect_DimRegion((*tree).Head,dim_pos);
			if(sw == 2){
				head_len = strlen((*tree).Head);
				if((head_str = malloc(sizeof(char) * (head_len+2))) == NULL){
					perror("[Fail]:calloc@Function_Print_Bclose_X.\n");
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
/** val */
int Function_Recursive_Get_nvalMax(struct Tree *tree){
	int i;
	int MAX = 0;
	//Self
	MAX = max(MAX,(*tree).nval);
	//Ref
	if((*tree).RefNode != NULL){
		MAX = max(MAX,(*tree).RefNode->nval);
	}
	for(i=0;i<(*tree).NextCount;i++){
		MAX = max(MAX,Function_Recursive_Get_nvalMax((*tree).Next[i]));
	}
	return(MAX);
}
int Function_Recursive_Get_nvalList(struct Tree *tree, int *nvalList, int nval_start){
	FC(fprintf(stderr,">Function_Recursive_Get_nvalList<\n");)
	int i;
	int nval = 0;
	int nval_count = nval_start;
	//Pseudo bind
		//goto EXIT_pseudo;
	//testing
	int tmp_head_len = 0;
	tmp_head_len = strlen((*tree).Head);
	//printf("l:%d:e:%c:\n",tmp_head_len,(*tree).Head[tmp_head_len-1]);
	//if(*(*tree).Head+(*tree).IndicatorPtr != '@' || (*tree).Head+(*tree).IndicatorPtr == NULL){
	if(tmp_head_len == 0 || (*tree).Head[tmp_head_len-1] != '@'){
		goto EXIT_pseudo;
	}
	nval = (*tree).NextCount;
	if(nval > 0){
		for(i=0;i<nval_count;i++){
			if(nvalList[i] == nval){
				goto EXIT_pseudo;
			}
		}
		nvalList = realloc(nvalList,sizeof(int) * (nval_count + 1));
		if(nvalList == NULL){
			perror("[Fail]realloc@Function_Recursive_Get_nvalList\n");
			exit(1);
		}
		nvalList[nval_count] = nval;
		nval_count++;
	}
	EXIT_pseudo:
	//Self
	nval = (*tree).nval;
	if(nval > 0){
		for(i=0;i<nval_count;i++){
			if(nvalList[i] == nval){
				goto EXIT_self;
			}
		}
		nvalList = realloc(nvalList,sizeof(int) * (nval_count + 1));
		if(nvalList == NULL){
			perror("[Fail]realloc@Function_Recursive_Get_nvalList\n");
			exit(1);
		}
		nvalList[nval_count] = nval;
		nval_count++;
	}
	EXIT_self:
	//Ref
	nval = 0;
	if((*tree).RefNode != NULL){
		nval = (*(*tree).RefNode).nval;
		if(nval > 0){
			for(i=0;i<nval_count;i++){
				if(nvalList[i] == nval){
					goto EXIT_ref;
				}
			}
			nvalList = realloc(nvalList,sizeof(int) * (nval_count + 1));
			if(nvalList == NULL){
				perror("[Fail]realloc@Function_Recursive_Get_nvalList\n");
				exit(1);
			}
			nvalList[nval_count] = nval;
			nval_count++;
		}
	}
	EXIT_ref:
	// Next
	for(i=0;i<(*tree).NextCount;i++){
		//nval_count =+ Function_Recursive_Get_nvalList((*tree).Next[i],nvalList,nval_count);
		nval_count = Function_Recursive_Get_nvalList((*tree).Next[i],nvalList,nval_count);
	}
	return(nval_count);
}
int print_singleVal(char *str){
	FC(fprintf(stderr,">print_singleVal<\n");)
	int C;
	int i;
	int ESC = 0;
	for(i=0;1;i++){
		C = (int)str[i];
		if(C == '\0'){
			return(0);
		}
		if(ESC == 1){
			putchar(C);
		}
		if(C != ',' && ESC == 0){
			putchar(C);
		}
		if(C == ',' && ESC == 0){
			return(0);
		}
		#include "escape_sw.c"
	}
	return(i);
}
struct Tree *Function_Print_nthVal(struct Tree *tree, int nth){
	FC(fprintf(stderr,">Function_Print_nthVal<\n");)
	// nth : loop iterator
	int p = 0;
	if((*tree).valstr != NULL && (*tree).valPtr != NULL){
		p = nth%(*tree).nval;
		print_singleVal((*tree).valstr+(*tree).valPtr[p]);
	}
	return(tree);
}
struct Tree *Function_Recursive_Print_nthVal(struct Tree *tree, int nth, struct function_options *_fopt, struct compile_options *_copt){ //%P
	FC(fprintf(stderr,">Function_Recursive_Print_nthVal<\n");)
	int i;
	int conjR = 0;
	if((*tree).NCself > 1){
		printf(",");
	}
	if((*tree).nval > 0){
		Function_Print_nthVal(tree,nth);
		conjR = 1;
	}
	if((*tree).RefNode == NULL && ((*tree).extra_stat&2) != 2){
		//Under rev
		int tmp_head_len = 0;
		tmp_head_len = strlen((*tree).Head);
		//printf("l:%d:e:%c:\n",tmp_head_len,(*tree).Head[tmp_head_len-1]);
		//if(*(*tree).Head+(*tree).IndicatorPtr != '@'){
		if(tmp_head_len == 0 || (*tree).Head[tmp_head_len-1] != '@'){
			printf("%s",(*tree).Head+(*tree).IndicatorPtr);
		}else{	//force-bind
			//printf("%s",(*tree).Next[nth%(*tree).NextCount]->Head);
			//int Cj_org = (*tree).Next[nth%(*tree).NextCount]->Conj;
			//int NCs_org = (*tree).Next[nth%(*tree).NextCount]->NCself;
			//(*tree).Next[nth%(*tree).NextCount]->Conj = 0;
			//(*tree).Next[nth%(*tree).NextCount]->NCself = 1;
			if(((*_fopt).f_skipOnce&1) != 1){
				(*_fopt).f_skipOnce = (*_fopt).f_skipOnce + 1;
				//(*_fopt).f_skipOnce = 1;
			}
			ExFunction_Recursive_Ser_MultiPrint((*tree).Next[nth%(*tree).NextCount], (struct Tree *(*)())Function_Print_Conj_T, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_T,  (struct Tree *(*)())Function_Print_Bclose_T,NULL,_fopt,_copt,0);
			//(*tree).Next[nth%(*tree).NextCount]->Conj = Cj_org;
			//(*tree).Next[nth%(*tree).NextCount]->NCself = NCs_org;
			return(tree);
		}
	}
	if((*tree).RefNode != NULL){
		if((*tree).RefNode->nval > 0){
			if(conjR > 0){
				printf(",");
			}
			Function_Print_nthVal((*tree).RefNode,nth);
		}
		if((*tree).RefNode->NextCount > 0){
			printf("(");
			for(i=0;i<(*tree).RefNode->NextCount;i++){
				Function_Recursive_Print_nthVal((*tree).RefNode->Next[i],nth,_fopt,_copt);
			}
			printf(")");
		}
	}
	if((*tree).NextCount > 0){
		printf("(");
		for(i=0;i<(*tree).NextCount;i++){
			Function_Recursive_Print_nthVal((*tree).Next[i],nth,_fopt,_copt);
		}
		printf(")");
	}
	return(tree);
}
/** Head */
struct Tree *Function_RecursiveCyclic_Print_IProductVal(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){ //%P
	FC(fprintf(stderr,">Function_RecursiveCyclic_Print_IProductVal<\n");)
	/* Function_Print_Head の特殊型 */
	/* 子要素も含めてprint */
	int i;	// for max_nval
	int j;	// for nval_count
	int max_nval = 1;
	int *nval_list = NULL;
	int nval_count = 0;
	if((nval_list = malloc(sizeof(int) * 1)) == NULL){
		perror("[Fail]malloc@Function_RecursiveCyclic_Print_IProductVal\n");
		exit(1);
	}
	max_nval = Function_Recursive_Get_nvalMax(tree);
	nval_count = Function_Recursive_Get_nvalList(tree,nval_list,0);
	for(i=0;i<nval_count-1;i++){
		printf("(");
	}
	for(i=0;i<max_nval;i++){
		if(i != 0){
			for(j=0;j<nval_count;j++){
				if(i%nval_list[j] == 0){
					printf(")");
				}
			}
			printf(",");
			for(j=0;j<nval_count;j++){
				if(i%nval_list[j] == 0){
					printf("(");
				}
			}
		}
		Function_Recursive_Print_nthVal(tree,i,_fopt,_copt);
	}
	for(i=0;i<nval_count-1;i++){
		printf(")");
	}
	//print後は子ノードを切る
	if(((*tree).extra_stat&2) != 2){
		(*tree).extra_stat = (*tree).extra_stat + 2;
	}
	return(tree);
}
struct Tree *Print_RecursiveSeq_Head(struct Tree *tree, int conj, int ind){
	int i;
	if(conj == 1){
		printf(",");
	}
	if(ind == 1){
		printf("%s",(*tree).Head+(*tree).IndicatorPtr);
	}else{
		printf("%s",(*tree).Head);
	}
	for(i=0;i<(*tree).NextCount;i++){
		Print_RecursiveSeq_Head((*tree).Next[i],1,ind);
	}
	//print後は子ノードを切る
	if(((*tree).extra_stat&2) != 2){
		(*tree).extra_stat = (*tree).extra_stat + 2;
	}
	return(tree);
}
struct Tree *Function_Print_Head(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){ //%P
	FC(fprintf(stderr,">Function_Print_Head<\n");)
	/* 特殊型にFunction_Print_ProductValあり、上位関数で切り替え */
	struct Tree *ins_head = NULL;
	char target_type = '\0';
	int target_label = -1;
	int prg = 0;
	/* print hierarchy */
	if((*_fopt).f_print_hierarchy == 1 && (*_fopt).f_print_self_stat == 1){
		int i;
		printf("\n");
		for(i=0;i<(*tree).LVself;i++){
			printf(INDENT);
		}
		if((*tree).Conj == 1 && (*tree).NCself > 1){
			printf("+");
			printf("%d:",(*tree).ser);
		}else{
			printf("-");
			printf("%d:",(*tree).ser);
		}
	}
	/* interpret */
	char *tmp_str = NULL;
	tmp_str = Function_Interpret_Head(tree,_copt);
	int put_head_conj = 1;
	put_head_conj = strcmp((*tree).Head+(*tree).IndicatorPtr,"$UU$");
	//printf(":%d:",put_head_conj);
	/* print head */
	if(((*tree).extra_stat&1) == 1){
		printf("%s",(*tree).Head);	//normal
	}else if((*_copt).c_counter > 0){
		printf("%s",tmp_str);
		free(tmp_str);
		if(((*tree).extra_stat&8) == 8 && (*tree).NextCount > 0 && put_head_conj != 0){
			putchar(44);
		}
	}else{
		printf("%s",(*tree).Head);	//normal
	}

	/* if extra_stat&2 == 2 then return() */
	if(((*tree).extra_stat&2) == 2){
		return(tree);
	}

	/* print bind mark (1) */
	if((*tree).valstr != NULL){
		printf("@");
	}
	/* print ref node */
	prg = get_ref((*tree).Head+(*tree).IndicatorPtr,&target_type,&target_label);
	if((*tree).RefNode != NULL){
		(*_fopt).f_print_self_stat = 0;
		/* switch 't' 'h' */
		if((*tree).RefNode->LabelType == 'h'){
			DB(fprintf(stderr," LT:h: <= TG:%c:\n",target_type);)
			printf("@");
			ins_head = Function_Print_Head((*tree).RefNode,_fopt,_copt);
		}else if((*tree).RefNode->LabelType == 't' && target_type == 't'){
			DB(fprintf(stderr," LT:t:,TG:t:\n");)
			printf("@");
			if((((*_fopt).f_skipOnce)&1) == 0){	// skip print_conj
				(*_fopt).f_skipOnce = (*_fopt).f_skipOnce + 1;
			}
			DB(fprintf(stderr," print_head:skip:%d:\n",(*_fopt).f_skipOnce);)
			ins_head = ExFunction_Recursive_Ser_MultiPrint((*tree).RefNode, (struct Tree *(*)())Function_Print_Conj_T, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_T,  (struct Tree *(*)())Function_Print_Bclose_T,NULL,_fopt,_copt,0);
		}else if((*tree).RefNode->LabelType == 't' && target_type == 'h'){
			DB(fprintf(stderr," LT:t:,TG:h:\n");)
			printf("@");
			ins_head = Function_Print_Head((*tree).RefNode,_fopt,_copt);
		}
	}
	/* progress IndicatorPtr ? not here */
	//testing
	//(*tree).IndicatorPtr = (*tree).IndicatorPtr + prg;

	/* print binded data (1) */
	if((*tree).valstr != NULL){
		printf("(%s)",(*tree).valstr);
	}

	/* print hierarchy */
	if((*_fopt).f_print_hierarchy == 1 && (*_fopt).f_print_self_stat == 1){
		printf(":");
	}
	if((*_fopt).f_print_hierarchy == 1){
		(*_fopt).f_print_self_stat = 1;
	}

	return(tree);
}
struct Tree *Function_Print_Head_JS(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){ //%I
	int sw = 0;
	int *dim_pos;
	int head_len = 0;
	char *head_str;
	char *tmp_str;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]:calloc@Function_Print_Head_JS.\n");
		exit(1);
	}
	head_len = strlen((*tree).Head);
	if((tmp_str = malloc(sizeof(char) * (head_len+1))) == NULL){
		perror("[Fail]:malloc@Function_Print_Head_JS.\n");
		exit(1);
	}
	/* compile */
	if((*_copt).c_counter > 0){
		tmp_str = Function_Interpret_Head(tree,_copt);
	}else{
		strcpy(tmp_str,(*tree).Head);
	}
	/* conversion */
	sw = Detect_DimRegion(tmp_str,dim_pos);
	if(sw == 2){
		head_len = strlen(tmp_str);
		if((head_str = malloc(sizeof(char) * (head_len+1))) == NULL){
			perror("[Fail]:malloc@Function_Print_Head_JS.\n");
			exit(1);
		}
		strcpy(head_str,tmp_str);
		head_str[dim_pos[0]] = '\0';
		printf("[\"%s\",\"DIM\",",head_str);
		//Under construction for multipule comma
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
struct Tree *Function_Print_Head_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){ //%I
	int sw = 0;
	int *dim_pos;
	int head_len = 0;
	char *head_str;
	char *tmp_str;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]:calloc@Function_Print_Head_WL.\n");
		exit(1);
	}
	head_len = strlen((*tree).Head);
	if((tmp_str = malloc(sizeof(char) * (head_len+1))) == NULL){
		perror("[Fail]:malloc@Function_Print_Head_WL.\n");
		exit(1);
	}
	/* compile */
	if((*_copt).c_counter > 0){
		tmp_str = Function_Interpret_Head(tree,_copt);
	}else{
		strcpy(tmp_str,(*tree).Head);
	}
	/* conversion */
	sw = Detect_DimRegion(tmp_str,dim_pos);
	if(sw == 2){
		if((head_str = malloc(sizeof(char) * (head_len+1))) == NULL){
			perror("[Fail]:malloc@Function_Print_Head_WL.\n");
			exit(1);
		}
		strcpy(head_str,tmp_str);
		head_str[dim_pos[0]] = '\0';
		if(strlen(head_str) == 0){
			//printf("List");	//todo or not todo
		}
		printf("%s[DIM,",head_str);
		printf("%s",head_str+dim_pos[0]+1);
	}else{
		head_len = strlen(tmp_str);
		if(head_len > 0){
			printf("%s",tmp_str);
		}else if(head_len == 0 && (*_fopt).f_print_W == 2){
			printf("List");	//todo or not todo
		}
	}
	return(tree);
}
struct Tree *Function_Print_Head_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){ //%I
	if((*tree).NextCount == 0){
		/* compile */
		if((*_copt).c_counter > 0){
			char *tmp_str;
			tmp_str = Function_Interpret_Head(tree,_copt);
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

/* recursive-apply-function */
/** Down tree */
struct Tree *ExFunction_Recursive_Set_Obj(struct Tree *tree, struct Tree *(*e_function)(struct Tree *tree, void *), void *obj){
	FC(fprintf(stderr,">ExFunction_Recursive_Set_Obj<\n");)
	int i;
	(*e_function)(tree,obj);
	for(i=0;i<(*tree).NextCount;i++){
		ExFunction_Recursive_Set_Obj((*tree).Next[i],e_function,obj);
	}
	return(tree);
}
struct Tree *ExFunction_Recursive(struct Tree *tree, struct Tree *(*e_function)(struct Tree *, struct options *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt){
	FC(fprintf(stderr,">ExFunction_Recursive<\n");)
	int i;
	struct Tree *out = tree;
	if(tree == NULL || e_function == NULL){
		perror("NULL node detected -- exit.\n");
		exit(1);
	}
	(*e_function)(tree,_opt);
	for(i=0;i<(*tree).NextCount;i++){
		ExFunction_Recursive((*tree).Next[i],e_function,_opt,_fopt,_copt);
	}
	return(out);
}
struct Tree *ExFunction_Recursive_Ser(struct Tree *tree, struct Tree *(*e_function)(struct Tree *, int, struct options *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, int _ser, int exec){
	FC(fprintf(stderr,">ExFunction_Recursive_Ser<\n");)
	if(exec == 0){
		return(NULL);
	}
	int i;
	struct Tree *out = tree;
	if(tree == NULL || e_function == NULL){
		perror("NULL node detected -- exit.\n");
		exit(1);
	}
	(*e_function)(tree,_ser,_opt);
	for(i=0;i<(*tree).NextCount;i++){
		ExFunction_Recursive_Ser((*tree).Next[i],e_function,_opt,_fopt,_copt,_ser,exec);
	}
	return(out);
}
struct Tree *ExFunction_Recursive_Ser_MultiPrint(struct Tree *tree, struct Tree *(*conj_function)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*head_function)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*bopen_function)(struct Tree *, struct function_options *, struct compile_options *, int),  struct Tree *(*bclose_function)(struct Tree *, struct function_options *, struct compile_options *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, int _ser){
	FC(fprintf(stderr,">ExFunction_Recursive_Ser_MultiPrint<\n");)
	int i;
	struct Tree *out = tree;
	if(tree == NULL){
		perror("NULL node detected -- exit.\n");
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
	// $UU$ : if Tree.extra_stat&2 == 2 then skip for-loop.
	if(((*tree).extra_stat&2) == 2 && (*_copt).c_counter > 0){
		Function_RecursiveCyclic_Print_IProductVal(tree,_fopt,_copt);
	}else{
		for(i=0;i<(*tree).NextCount;i++){
			ExFunction_Recursive_Ser_MultiPrint((*tree).Next[i],conj_function,head_function,bopen_function,bclose_function,_opt,_fopt,_copt,_ser);
		}
	}
	/*print Bclose*/
	bclose_function(tree,_fopt,_copt);
	return(out);
}
/** Up tree */
struct Tree *ExFunction_UpRecursive(struct Tree *tree, struct Tree *(*e_function)(struct Tree *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, char *buff){
	FC(fprintf(stderr,">ExFunction_UpRecursive<\n");)
	struct Tree *parent;
	parent = (*tree).Parent;
	if((*tree).ser == -1 || (*parent).ser == -1 || e_function == NULL){
		return(NULL);
	}
	ExFunction_UpRecursive(parent,e_function,_opt,_fopt,_copt,buff);
	return(parent);
}


