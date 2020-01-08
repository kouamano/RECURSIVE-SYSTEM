/* README */
/* //%P : print-function which contains NO converter. */
/* //%I : incomplete function. */

/* program */
/* prottype */

// tq: struct Tree *Function_Print_Head(struct Tree *, struct function_options *, struct compile_options *);
NODE Function_Print_Head(NODE, struct function_options *, struct compile_options *);

// tq: struct Tree *Executor(struct Tree *, struct Tree *, struct Tree *, int, int, struct options *, struct function_options *, struct compile_options *, struct search_options *, FILE *, int);
NODE Executor(NODE , NODE , NODE , int, int, struct options *, struct function_options *, struct compile_options *, struct search_options *, FILE *, int);

// tq: struct Tree *ExFunction_Recursive_Ser_MultiPrint(struct Tree *, struct Tree *(*)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*)(struct Tree *, struct function_options *, struct compile_options *, int),  struct Tree *(*)(struct Tree *, struct function_options *, struct compile_options *), struct options *, struct function_options *, struct compile_options *, int);
NODE ExFunction_Recursive_Ser_MultiPrint(NODE , NODE (*)(NODE , struct function_options *, struct compile_options *), NODE (*)(NODE , struct function_options *, struct compile_options *), NODE (*)(NODE , struct function_options *, struct compile_options *, int),  NODE (*)(NODE , struct function_options *, struct compile_options *), struct options *, struct function_options *, struct compile_options *, int);

// tq: struct Tree *ExFunction_Recursive_Ser(struct Tree *, struct Tree *(*)(struct Tree *, int, struct options *), struct options *, struct function_options *, struct compile_options *, int , int);
NODE ExFunction_Recursive_Ser(NODE , NODE (*)(NODE , int, struct options *), struct options *, struct function_options *, struct compile_options *, int , int);

// tq: struct Tree *ExFunction_Recursive(struct Tree *, struct Tree *(*)(struct Tree *, struct options *), struct options *, struct function_options *, struct compile_options *);
NODE ExFunction_Recursive(NODE , NODE (*)(NODE , struct options *), struct options *, struct function_options *, struct compile_options *);

// tq: struct Tree *ExFunction_Recursive_Set_Obj(struct Tree *, struct Tree *(*)(struct Tree *, void *), void *);
NODE ExFunction_Recursive_Set_Obj(NODE , NODE (*)(NODE , void *), void *);

/* meta functions */
void null_func(void){
}

/* GC */
// tq: int Function_Recursive_FreeForce_Tree(struct Tree *tree){
int Function_Recursive_FreeForce_Tree(NODE node){
	int i;
	// tq: if(tree == NULL){
	if(node == NO_NODE){
		return(1);
	}
	/* you must not free (*tree).Parent!! */
	// tq: for(i=0;i<(*tree).NextCount;i++){
	for(i=0;i<child_count(node);i++){
		// tq: Function_Recursive_FreeForce_Tree((*tree).Next[i]);
		Function_Recursive_FreeForce_Tree(child(node,i));
		// tq: free((*tree).Next[i]);
		// tq: (*tree).Next[i] = NULL;
		set_child(node, i, NO_NODE);
	}
	// tq: free((*tree).Next);
	free(children(node));
	// tq: (*tree).Next = NULL;
	// tq: (*tree).NextCount = 0;
	set_child_count(node,0);
	// tq: free((*tree).Head);
	free(head(node));
	// tq: (*tree).Head = NULL;
	set_head(node,NULL);
	// tq: free((*tree).dimstr);
	free(dimension_str(node));
	// tq: (*tree).dimstr = NULL;
	set_dimension_str(node,NULL);
	// tq: free((*tree).valstr);
	free(values_str(node));
	// tq: (*tree).valstr = NULL;
	set_values_str(node,NULL);
	return(0);
}

/* analyzers */
/** tree analysis */
// tq: struct Tree *Function_Get_Node(char *pos_str, struct Tree *tree){
NODE Function_Get_Node(char *pos_str, NODE node){
	int len = 0;
	int list_len = 0;
	int i;
	int count = 0;
	int *list;
	// tq: struct Tree *current = NULL;
	NODE current = NO_NODE;
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
		// tq: current = tree;
		current = node;
		for(i=1;i<count;i++){
			// tq: if((*current).NextCount > list[i]){
			if(child_count(current) > list[i]){
				// tq: current = current->Next[list[i]];
				current = child(current,list[i]);
			}else{
				// tq: current = NULL;
				current = NO_NODE;
				break;
			}
		}
	}else{
		// tq: current = NULL;
		current = NO_NODE;
	}
	free(list);
	return(current);
}
/** label analysis */
// tq: int Analyze_HeadLabel(struct Tree *tree){ // for labeling
int Analyze_Label(NODE node){ // for labeling
	int i = 0;
	int labelreadptr = 0;
	int labelnumlen = 0;
	char *labelnumstr;
	int headlen = 0;
	int labeled = 0;
	/* label type  for referenced node */
	// tq: if((*tree).Head[0] == '#' && (*tree).Head[1] == '#'){
	if(head(node)[0] == '#' && head(node)[1] == '#'){
		// tq: (*tree).LabelType = 't';
		set_label_type(node,'t');
		labelreadptr = 2;
		labeled++;
	// tq: }else if((*tree).Head[0] == '#' && (*tree).Head[1] != '#'){
	}else if(head(node)[0] == '#' && head(node)[1] != '#'){
		// tq: (*tree).LabelType = 'h';
		set_label_type(node,'h');
		labelreadptr = 1;
		labeled++;
	}
	/* label  for referenced node */
	// tq: if((*tree).LabelType != '\0'){
	if(label_type(node) != '\0'){
		/* check num char */
		// tq: for(i=labelreadprt; ((*tree).Head[i] >= 0x30) && ((*tree).Head[i] <= 0x39);i++){	//Hex
		for(i=labelreadptr; (head(node)[i] >= 0x30) && (head(node)[i] <= 0x39);i++){	//Hex
			labelnumlen++;
		}
		if((labelnumstr = malloc(sizeof(char) * (labelnumlen + 1))) == NULL){
			perror("[Fail]malloc@Analyze_Label\n");
			exit(1);
		}
		// tq: strncpy(labelnumstr,(*tree).Head+labelreadprt,labelnumlen);
		strncpy(labelnumstr,head(node)+labelreadptr,labelnumlen);
		// tq: sscanf(labelnumstr,"%d",&(*tree).Label);
		int wk;                                 // SAK
		sscanf(labelnumstr,"%d",&wk);           // SAK
		set_label(node, wk);                    // SAK

		free(labelnumstr);
		labeled++;
	}
	/* IndicatorPtr */
	// tq: headlen = strlen((*tree).Head);
	headlen = strlen(head(node));
	for(i=labelreadptr;i<headlen;i++){
		// tq: if((*tree).Head[i] < 0x30 || (*tree).Head[i] > 0x39){
		if(head(node)[i] < 0x30 || head(node)[i] > 0x39){
			// tq: (*tree).IndicatorPtr = i;
			set_indicator_pos(node,i);
			break;
		}
	}
	// tq: DB(printf("\nH:%s:Ptr:%d:\n",(*tree).Head,(*tree).IndicatorPtr);)
	DB(printf("\nH:%s:Ptr:%d:\n",head(node),indicator_pos(node));)
	return(0);
}
/** reference analysis for referenced node */
// tq: struct Tree *Function_Recursive_SearchBind_LabelNode(struct Tree *tree, char type, int label, struct Tree *referencer){	//for referred
NODE Function_Recursive_SearchBind_LabelNode(NODE node, char type, int lbl, NODE referencer){	//for referred
	int i;
	// tq: if(tree == NULL){
	if(node == NO_NODE){
		// tq: return(NULL);
		return(NO_NODE);
	}
	// tq: if((*tree).LabelType == 't' && (*tree).Label == label){
	if(label_type(node) == 't' && label(node) == lbl){
		// tq: (*referencer).RefNode = tree;	//bind tree,head
		set_ref_node(referencer,node);	//bind tree,head
	}
	// tq: if((*tree).LabelType == type && (*tree).Label == label){
	if(label_type(node) == type && label(node) == lbl){
		// tq: (*referencer).RefNode = tree;	//bind tree
		set_ref_node(referencer,node);	//bind tree
	}
	// tq: for(i=0;i<(*tree).NextCount;i++){
	for(i=0;i<child_count(node);i++){
		// tq: Function_Recursive_SearchBind_LabelNode((*tree).Next[i],type,label,referencer);
		Function_Recursive_SearchBind_LabelNode(child(node,i),type,lbl,referencer);
	}
	return(NO_NODE);
}
/** reference analysis for referencer */
int get_ref(char *head, char *type, int *label){	//for binded
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
			return(3+i);
		}
	}
	return(0);
}

/* restructure functions */
/** for data binding */
int get_nval(char *str){
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
// tq: int Add_DimStr(struct Tree *tree, int *dim_pos, char *buff){
int Add_DimStr(NODE node, int *dim_pos, char *buff){
	int len;
	len = strlen(buff);
	// tq: snprintf(buff+len,dim_pos[1]-dim_pos[0]+1,"%s",(*tree).Head+dim_pos[0]);
	snprintf(buff+len,dim_pos[1]-dim_pos[0]+1,"%s",head(node)+dim_pos[0]);
	return(len);
}
// tq: int Ins_DimStr(struct Tree *tree, int *dim_pos, char *buff){
int Ins_DimStr(NODE node, int *dim_pos, char *buff){
	int len;
	char *minibuff;
	if((minibuff = malloc(sizeof(char) * LEN)) == NULL){
		perror("[Fail]malloc@Ins_DimStr");
		exit(1);
	}
	/* currentbuff -> minibuff */
	strcpy(minibuff,buff);
	// tq: snprintf(buff,dim_pos[1]-dim_pos[0]+1,"%s",(*tree).Head+dim_pos[0]);
	snprintf(buff,dim_pos[1]-dim_pos[0]+1,"%s",head(node)+dim_pos[0]);
	len = strlen(buff);
	strcpy(buff+len,minibuff);
	free(minibuff);
	return(len);
}
int Detect_DimRegion(const char *head, int *pos){
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
// tq: int SPrint_UpRecursive_Head(struct Tree *tree, char *buff){
int SPrint_UpRecursive_Head(NODE node, char *buff){
	int sw;
	//int dim_pos[2];
	int *dim_pos;
	int len;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]calloc@SPrint_UpRecursive_Head\n");
		exit(1);
	}
	// tq: if((*tree).Parent == NULL){
	if(parent(node) == NO_NODE){
		// tq: sw = Detect_DimRegion((*tree).Head,dim_pos);
		sw = Detect_DimRegion(head(node),dim_pos);
		if(sw == 2){
			// tq: Ins_DimStr(tree,dim_pos,buff);
			Ins_DimStr(node,dim_pos,buff);
		}
		return(0);
	}else{
		// tq: sw = Detect_DimRegion((*tree).Head,dim_pos);
		sw = Detect_DimRegion(head(node),dim_pos);
		if(sw == 2){
			// tq: Ins_DimStr(tree,dim_pos,buff);
			Ins_DimStr(node,dim_pos,buff);
		}
		// tq: SPrint_UpRecursive_Head((*tree).Parent,buff);
		SPrint_UpRecursive_Head(parent(node),buff);
	}
	len = strlen(buff);
	return(len);
}
// tq: struct Tree *Function_Detect_DimBlock(struct Tree *tree, struct options *_opt){
NODE Function_Detect_DimBlock(NODE node, struct options *_opt){
	int sw = 0;
	//int dim_pos[2];
	int *dim_pos;
	char *buff;
	int len = 0;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]calloc@SPrint_UpRecursive_Head\n");
		exit(1);
	}
	// tq: if((*tree).NextCount != 0){
	if(child_count(node) != 0){
		// tq: return(NULL);
		return(NO_NODE);
	}
	// tq: sw = Detect_DimRegion((*tree).Head,dim_pos);
	sw = Detect_DimRegion(head(node),dim_pos);
	if(sw != 2){
		// tq: return(NULL);
		return(NO_NODE);
	}
	if((buff = malloc(sizeof(char) * (*_opt).buff)) == NULL){
		perror("[Fail]malloc@Detect_DimBlock.\n");
		exit(1);
	}
	buff[0] = '\0';
	/* tmp -> dim */	
	// tq: len = SPrint_UpRecursive_Head(tree,buff);
	len = SPrint_UpRecursive_Head(node,buff);
#ifdef MEM_DIMENSION_STR
	// tq: if(((*tree).dimstr = malloc(sizeof(char) * (len + 1))) == NULL){
	if(set_dimension_str_ptr(node,malloc(sizeof(char) * (len + 1))) == NULL){
		perror("[Fail]malloc@Detect_DimBlock.\n");
		exit(1);
	}
	// tq: strcpy((*tree).dimstr,buff);
	strcpy(dimension_str(node),buff);
#endif
	// tq: (*tree).nval = get_nval(buff);
	set_value_count(node,get_nval(buff));
	free(buff);
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Search_Recursive_BindNode(struct Tree *top, int *node_count, struct Tree **node_table){
NODE Search_Recursive_BindNode(NODE top, int *bn_count, NODE *bn_table){
	int i;
	// tq: struct Tree *current = NULL;
	NODE current = NO_NODE;
	current = top;
	// tq: if((*current).nval > 0){
	if(value_count(current) > 0){
		// tq: node_table = realloc(node_table,(sizeof(struct Tree *) * (*node_count + 2)));
		bn_table = realloc(bn_table,(sizeof(NODE ) * (*bn_count + 2)));
		if(bn_table == NULL){
			perror("[Fail]realloc@Function_Recursive_Search_BindNode");
			exit(1);
		}
		bn_table[(*bn_count)] = current;
		(*bn_count)++;
	}
	// tq: for(i=0;i<(*current).NextCount;i++){
	for(i=0;i<child_count(current);i++){
		// tq: Search_Recursive_BindNode((*current).Next[i],node_count,node_table);
		Search_Recursive_BindNode(child(current,i),bn_count,bn_table);
	}
	// tq: return(NULL);
	return(NO_NODE);
}
// tq: int Function_Bind_Data(FILE *DATA, struct Tree *tree, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt){
int Function_Bind_Data(FILE *DATA, NODE node, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt){
	int i;
        int C = '\0';
        int bn_count = 0;
        // tq: struct Tree **bn_table = NULL;
        NODE *bn_table = NULL;
	// tq: if((bn_table = malloc(sizeof(struct Tree *) * 1)) == NULL){
	if((bn_table = malloc(sizeof(NODE ) * 1)) == NULL){
		perror("[]malloc@bind_data");
		exit(1);
	}
        // tq: Search_Recursive_BindNode(tree,&bn_count,bn_table);
        Search_Recursive_BindNode(node,&bn_count,bn_table);
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
			// tq: if(bn_table[node_count]->nval == delim_count && ESC == 0){
			if(value_count(bn_table[node_count]) == delim_count && ESC == 0){
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
				// tq: bn_table[node_count]->valstr = malloc(sizeof(char) * (buff_len + 1));
				set_values_str_ptr(bn_table[node_count],malloc(sizeof(char) * (buff_len + 1)));
				// tq: if(bn_table[node_count]->valstr == NULL){
				if(values_str(bn_table[node_count]) == NULL){
					perror("[Fail]malloc@bind_data().\n");
					exit(1);
				}
				// tq: strcpy((*bn_table[node_count]).valstr,buff);
				strcpy(values_str(bn_table[node_count]),buff);
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
// tq: void Function_Recursive_Bind_RefNode(struct Tree *binded, struct Tree *referred, struct compile_options *_copt){
void Function_Recursive_Bind_RefNode(NODE binded, NODE referred, struct compile_options *_copt){
	int i;
	char target_type = '\0';
	int target_label = -1;
	int stat = -1;
	// tq: stat = get_ref((*binded).Head+(*binded).IndicatorPtr,&target_type,&target_label);
	stat = get_ref(head(binded)+indicator_pos(binded),&target_type,&target_label);
	// ここにheadのIndicatorPtrをプログレスするコードか? だめ、レファレンスバインドできなくなる -> 条件分岐を試す。 コンパイルのときのみ実行。
if((*_copt).c_counter > 0){
		// tq: (*binded).IndicatorPtr = (*binded).IndicatorPtr + stat;
		set_indicator_pos(binded,indicator_pos(binded)+ stat);
	}
	if(stat > 0){
		// tq: struct Tree *addr = NULL;
		NODE addr = NO_NODE;
		addr = Function_Recursive_SearchBind_LabelNode(referred,target_type,target_label,binded);
	}
	// tq: for(i=0;i<(*binded).NextCount;i++){
	for(i=0;i<child_count(binded);i++){
		// tq: Function_Recursive_Bind_RefNode((*binded).Next[i],referred,_copt);
		Function_Recursive_Bind_RefNode(child(binded,i),referred,_copt);
	}
}
/** for product */
// tq: int Function_Assign_RefedValPtr(struct Tree *tree){	// for product
int Function_Assign_RefedValPtr(NODE node){	// %P
	// tq: if(tree == NULL){
	if(node == NO_NODE){
		return(0);
	}
	// tq: if((*tree).valstr == NULL){
	if(values_str(node) == NULL){
		return(0);
	}
	// tq: if((*tree).nval > 0){
	if(value_count(node) > 0){
		// tq: if(((*tree).valPtr = malloc(sizeof(int) * (*tree).nval)) == NULL){
		if(set_value_poses_ptr(node,malloc(sizeof(int) * value_count(node))) == NULL){
			perror("[Fail]malloc@Function_Assign_RefedValPtr().\n");
			exit(1);
		}
		int i;
		int len = 0;
		char C = '\0';
		int ESC = 0;
		int count = 0;
		// tq: len = strlen((*tree).valstr);
		len = strlen(values_str(node));
		// tq: (*tree).valPtr[count] = 0;
		set_value_pos(node,count,0);
		count++;
		for(i=0;i<len;i++){
			// tq: C = (*tree).valstr[i];
			C = values_str(node)[i];
			if(C == DD && ESC == 0){
				// tq: (*tree).valPtr[count] = i + 1;
				set_value_pos(node,count,i + 1);
				count++;
			}
			#include "escape_sw.c"
		}
	}
	return(0);
}
// tq: struct Tree *Create_Node(int _ser, int H_size){
NODE Create_Node(int _ser, int H_size){
	// tq: struct Tree *tree;
	NODE node;
	// tq: if((tree = malloc(sizeof(struct Tree) * 1)) == NULL){
	// tq:	perror("[Fail]:malloc@Create_Node.\n");
	// tq:	exit(1);
	// tq:}

	node = create_node();

	// tq: (*tree).ser = _ser;
	set_ser(node,_ser);
	// tq: (*tree).LVself = 0;
	set_level(node,0);
	// tq: (*tree).NCself = 1;
	set_child_no(node,1);
	// tq: (*tree).Conj = 0;
	set_conjugate(node,0);
	// tq: (*tree).LabelType = '\0';
	set_label_type(node,'\0');
	// tq: (*tree).Label = -1;
	set_label(node,-1);
	// tq: (*tree).IndicatorPtr = 0;
	set_indicator_pos(node,0);
	if(H_size < 1){
		// tq: (*tree).Head = NULL;
		set_head(node,NULL);
	}else{
		// tq: if(((*tree).Head = malloc(sizeof(char) * H_size)) == NULL){
		if(set_head_ptr(node,malloc(sizeof(char) * H_size)) == NULL){
			perror("[Fail]:malloc@Create_Node.\n");
			exit(1);
		}
	}
	// tq: (*tree).NextCount = 0;
	set_child_count(node,0);
	// tq: if(((*tree).Next = malloc((size_t)sizeof(struct Tree *) * 1)) == NULL){	// SAK
	// tq:	perror("[Fail]:malloc@Create_Node.\n");					// SAK
	// tq:	exit(1);								// SAK
	// tq:}										// SAK

	// tq: (*tree).dimstr = NULL;
	set_dimension_str(node,NULL);
	// tq: (*tree).nval = 0;
	set_value_count(node,0);
	// tq: (*tree).valPtr = NULL;
	set_value_poses_ptr(node,NULL);
	// tq: (*tree).valstr = NULL;
	set_values_str(node,NULL);
	// tq: (*tree).Parent = NULL;
	set_parent(node,NO_NODE);
	// tq: (*tree).RefNode = NULL;
	set_ref_node(node,NO_NODE);
	// tq: (*tree).extra_stat = 0;
	set_extra_stat(node,0);
	// tq: return(tree);
	return(node);
}

// tq:
/* unused
struct Tree *Add_Next(struct Tree *parent, struct Tree *next){
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
*/

// tq: struct Tree *Set_status(struct Tree *tree, int *bit){
NODE Set_status(NODE node, int *bit){
	// tq: if(((*tree).extra_stat&*bit) != *bit){
	if((extra_stat(node)&*bit) != *bit){
		// tq: (*tree).extra_stat = (*tree).extra_stat + *bit;
		set_extra_stat(node,extra_stat(node) + *bit);
	}
	// tq: return(tree);
	return(node);
}

/* compile functions */
// tq: char *Clear_Head(struct Tree *tree){
char *Clear_Head(NODE node){
	char *tmp_head;
	if((tmp_head = malloc(sizeof(char) * 1)) == NULL){
		perror("[Fail]:malloc@Function_Clear_Head\n");
		exit(1);
	}
	tmp_head[0] = '\0';
	return(tmp_head);
}
// tq: char *Dot_Head(struct Tree *tree){
char *Dot_Head(NODE node){
	// tq: if((*tree).Head[0] != '\0'){
	if(head(node)[0] != '\0'){
		char *tmp_head;
		if((tmp_head = malloc(sizeof(char) * 2)) == NULL){
			perror("[Fail]:malloc@Function_Clear_Head\n");
			exit(1);
		}
		tmp_head[0] = '.';
		tmp_head[1] = '\0';
		return(tmp_head);
	}else{
		// tq: return((*tree).Head);
		return(head(node));
	}
}
// tq: char *Function_Interpret_Head(struct Tree *tree, struct compile_options *_copt){
char *Interpret_Head(NODE node, struct compile_options *_copt){
	char *tmp_head;
	char *out_head;
	int compiled = 0;
	int len = 0;
	// tq: len = strlen((*tree).Head);
	len = strlen(head(node));
	if((tmp_head = malloc(sizeof(char) * (len+1))) == NULL){
		perror("[Fail]:malloc@Function_Interpret_Head.\n");
		exit(1);
	}
	if((out_head = malloc(sizeof(char) * (len+1))) == NULL){
		perror("[Fail]:malloc@Function_Interpret_Head.\n");
		exit(1);
	}

	// tq: strcpy(tmp_head,(*tree).Head+(*tree).IndicatorPtr);
	strcpy(tmp_head,head(node)+indicator_pos(node));

	if((*_copt).c_clear > 0){
		// tq: tmp_head = Clear_Head(tree);
		tmp_head = Clear_Head(node);
	}else if((*_copt).c_dot > 0){
		// tq: tmp_head = Dot_Head(tree);
		tmp_head = Dot_Head(node);
	}else if(strncmp(tmp_head,"$NULL$",6) == 0){
		;
	}else if(strncmp(tmp_head,"$PI$",4) == 0){	// Inner Product
		strcpy(out_head,tmp_head+4);
		strcpy(tmp_head,out_head);
		// tq: if(((*tree).extra_stat&2) != 2){
		if((extra_stat(node)&2) != 2){
			// tq: (*tree).extra_stat = (*tree).extra_stat + 2;
			set_extra_stat(node,extra_stat(node) + 2);
		}
		compiled++;
	}else if(strncmp(tmp_head,"$X$",3) == 0){
		strcpy(out_head,tmp_head+3);
		strcpy(tmp_head,out_head);
		compiled++;
	}else if(strncmp(tmp_head,"$M$",3) == 0){
		strcpy(out_head,tmp_head+3);
		strcpy(tmp_head,out_head);
		compiled++;
	}else if(strncmp(tmp_head,"$UU$",4) == 0){
		strcpy(out_head,tmp_head+4);
		strcpy(tmp_head,out_head);
		// tq: if(((*tree).extra_stat&8) != 8){
		if((extra_stat(node)&8) != 8){
			// tq: (*tree).extra_stat = (*tree).extra_stat + 8;
			set_extra_stat(node,extra_stat(node) + 8);
		}
		int tmp_stat = 8;
		// tq: ExFunction_Recursive_Set_Obj(tree, (struct Tree *(*)())Set_status, (int *)&tmp_stat);	// set cascading
		ExFunction_Recursive_Set_Obj(node, (NODE(*)())Set_status, (int *)&tmp_stat);	// set cascading
		compiled++;
	}else if(strncmp(tmp_head,"$U$",3) == 0){
		strcpy(out_head,tmp_head+3);
		strcpy(tmp_head,out_head);
		// tq: if(((*tree).extra_stat&8) != 8){
		if((extra_stat(node)&8) != 8){
			// tq: (*tree).extra_stat = (*tree).extra_stat + 8;
			set_extra_stat(node,extra_stat(node) + 8);
		}
		compiled++;
	// }else if(strncmp(tmp_head,"$``",3) == 0){ //quating tree
	}else if(strncmp(tmp_head,"$``$",4) == 0){ //quating tree
		int tmp_len = 0;
		out_head = realloc(out_head, (sizeof(char) * (len+1)));
		if(out_head == NULL){
			perror("[Fail]:realloc@Function_Interpret_Head.\n");
			exit(1);
		}

		out_head[0]='"';
		// strcpy(out_head+1,tmp_head+3);
		strcpy(out_head+1,tmp_head+4);
		tmp_len = strlen(out_head);
		// tq: if((*tree).NextCount == 0){
		if(child_count(node) == 0){
			out_head[tmp_len]='"';
			out_head[tmp_len+1]='\0';
		}

		strcpy(tmp_head,out_head);
		// tq: if(((*tree).extra_stat&4) != 4){
		if((extra_stat(node)&4) != 4){
			// tq: (*tree).extra_stat = (*tree).extra_stat + 4;
			set_extra_stat(node,extra_stat(node) + 4);
		}
		compiled++;
	// }else if(strncmp(tmp_head,"$~",3) == 0){
	// 	strcpy(out_head,tmp_head+3);
	}else if(strncmp(tmp_head,"$~~$",4) == 0){
		strcpy(out_head,tmp_head+4);
		strcpy(tmp_head,out_head);
		// tq: if(((*tree).extra_stat&1) != 1){
		if((extra_stat(node)&1) != 1){
			// tq: (*tree).extra_stat = (*tree).extra_stat + 1;
			set_extra_stat(node,extra_stat(node) + 1);
		}
		int tmp_stat = 1;
		// tq: ExFunction_Recursive_Set_Obj(tree, (struct Tree *(*)())Set_status, (int *)&tmp_stat);	// set cascading
		ExFunction_Recursive_Set_Obj(node, (NODE (*)())Set_status, (int *)&tmp_stat);	// set cascading
		compiled++;
	// }else if(strncmp(tmp_head,"$~",2) == 0){
	// 	strcpy(out_head,tmp_head+2);
	}else if(strncmp(tmp_head,"$~$",3) == 0){
		strcpy(out_head,tmp_head+3);
		strcpy(tmp_head,out_head);
		// tq: if(((*tree).extra_stat&1) != 1){
		if((extra_stat(node)&1) != 1){
			// tq: (*tree).extra_stat = (*tree).extra_stat + 1;
			set_extra_stat(node,extra_stat(node) + 1);
		}
		compiled++;
	// }else if(strncmp(tmp_head,"$`",2) == 0){ //quating Head
	}else if(strncmp(tmp_head,"$`$",3) == 0){ //quating Head
		int tmp_len = 0;
		out_head = realloc(out_head, (sizeof(char) * (len+1)));
		if(out_head == NULL){
			perror("[Fail]:realloc@Function_Interpret_Head_Head.\n");
			exit(1);
		}
		out_head[0]='"';
		// strcpy(out_head+1,tmp_head+2);
		strcpy(out_head+1,tmp_head+3);
		tmp_len = strlen(out_head);
		out_head[tmp_len]='"';
		out_head[tmp_len+1]='\0';
		strcpy(tmp_head,out_head);
		compiled++;
	}
	free(out_head);
	return(tmp_head);
}

/* print functions */
/** status */
// tq: void Print_Smems(struct Tree *tree){
void Print_Smems(NODE node){
	// tq: printf(":SN=%d:",(*tree).ser);
	printf(":SN=%d:",ser(node));
	// tq: printf(":LVs=%d:",(*tree).LVself);
	printf(":LVs=%d:",level(node));
	// tq: printf(":Adr=%ld:",(long int)tree);
	printf(":Adr=%d:",node);
	// tq: printf(":PaAdr=%ld:",(long int)(*tree).Parent);
	printf(":PaAdr=%d:",parent(node));
	// tq: printf(":Ref=%ld:",(long int)(*tree).RefNode);
	printf(":Ref=%d:",ref_node(node));
	// tq: printf(":LT=%c:",(*tree).LabelType);
	printf(":LT=%c:",label_type(node));
	// tq: printf(":Lb=%d:",(*tree).Label);
	printf(":Lb=%d:",label(node));
	// tq: printf(":Hi=%d:",(*tree).IndicatorPtr);
	printf(":Hptr=%d:",indicator_pos(node));
	// tq: printf(":H=%s:",(*tree).Head);
	printf(":H=%s:",head(node));
	// tq: printf(":D=%s:",(*tree).dimstr);
	printf(":D=%s:",dimension_str(node));
	// tq: printf(":nval=%d:",(*tree).nval);
	printf(":nval=%d:",value_count(node));
	// tq: printf(":vstr=%s:",(*tree).valstr);
	printf(":vstr=%s:",values_str(node));
	printf(":vptr=");
	// tq: if((*tree).valPtr != NULL){
	if(value_poses(node) != NULL){
		int i;
		// tq: for(i=0;i<(*tree).nval;i++){
		for(i=0;i<value_count(node);i++){
			// tq: printf(",%d",(*tree).valPtr[i]);
			printf(",%d",value_pos(node,i));
		}
	}
	printf(":");
	// tq: printf(":Cj=%d:",(*tree).Conj);
	printf(":Cj=%d:",conjugate(node));
	// tq: printf(":NCs=%d:",(*tree).NCself);
	printf(":NCs=%d:",child_no(node));
	// tq: printf(":NC=%d:",(*tree).NextCount);
	printf(":NC=%d:",child_count(node));
	// tq: printf(":stat=%d:",(*tree).extra_stat);
	printf(":stat=%d:",extra_stat(node));
}
// tq: void Function_Print_Status(struct Tree *tree){
void Function_Print_Status(NODE node){
	// tq: Print_Smems(tree);
	Print_Smems(node);
	printf("\n");
}
// tq: void print_war(char C, struct Tree *tree, int level){
void print_war(char C, NODE node, int level){
	printf(":C=%c:",C);
	printf(":DetectLV=%d:",level);
	// tq: Print_Smems(tree);
	Print_Smems(node);
}
// tq: int Function_Print_Adj(struct Tree *tree, int nodes, struct options *_opt){
int Function_Print_Adj(NODE node, int nodes, struct options *_opt){
	int i;
	int j;
	for(i=0;i<nodes;i++){
		// tq: if(i == (*tree).ser){
		if(i == ser(node)){
			printf("[");
			// tq: if((*tree).RefNode != NULL){
			if(ref_node(node) != NO_NODE){
				// tq: if((*tree).Parent != NULL){
				if(parent(node) != NO_NODE){
					// tq: printf("%d->",((*tree).Parent)->ser);
					printf("%d=>",ser(parent(node)));
				}
			}
			// tq: printf(":%s:%d",(*tree).Head,i);
			printf(":%s:%d",head(node),i);
			// tq: if((*tree).RefNode != NULL){
			if(ref_node(node) != NO_NODE){
				// tq: printf("->%d",((*tree).RefNode)->ser);
				printf("->%d",ser(ref_node(node)));
			}
			printf("]");
		}
		// tq: for(j=0;j<(*tree).NextCount;j++){
		for(j=0;j<child_count(node);j++){
			// tq: if(((*tree).Next[j])->ser == i){
			if(ser(child(node,j)) == i){
				// tq: printf("%d",((*tree).Next[j])->ser);
				printf("%d",ser(child(node,j)));
				break;
			// tq: }else if((*tree).Next[j]->RefNode != NULL){
			}else if(ref_node(child(node,j)) != NO_NODE){
				// tq: if((*tree).Next[j]->RefNode->ser == i){
				if(ser(ref_node(child(node,j))) == i){
					// tq: printf("%d",(*tree).Next[j]->RefNode->ser);
					printf("%d",ser(ref_node(child(node,j))));
				}
			}
		}
		printf(",");
	}
	printf("\n");
	return(nodes);
}
/** Conj */
// tq: struct Tree *Function_Print_Conj_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Conj_T(NODE node, struct function_options *_fopt, struct compile_options *_copt){
		DB(fprintf(stderr," before op : skip:%d:\n",(*_fopt).f_skipOnce);)
		if((((*_fopt).f_skipOnce)&1) == 1){
			(*_fopt).f_skipOnce = (*_fopt).f_skipOnce - 1;
			// tq: return(tree);
			return(node);
		}
		DB(fprintf(stderr," after op : skip:%d:\n",(*_fopt).f_skipOnce);)
		// tq: if((*tree).Conj == 1){
		if(conjugate(node) == 1){
			printf(",");
		// tq: }else if((*tree).NCself > 1 && (*tree).Conj == 0){	// for search
		}else if(child_no(node) > 1 && conjugate(node) == 0){	// for search
			printf(")(");
		}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Conj_S(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Conj_S(NODE node, struct function_options *_fopt, struct compile_options *_copt){
		// tq: if((*tree).NCself > 1 && (*tree).Conj != 1){
		if(child_no(node) > 1 && conjugate(node) != 1){
			printf(")");
		}
		// tq: if((*tree).LVself != 0 && strlen((*tree).Head) != 0){ 
		if(level(node) != 0 && strlen(head(node)) != 0){ 
			// tq: if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
			if((*_copt).c_counter > 0 && (extra_stat(node)&8) == 8){	// for unpack
				// tq: if(strlen((*tree).Head) > 3){
				if(strlen(head(node)) > 3){
					printf(",");
				}
			}else{
				printf(",");	//normal case
			}
		} 
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Conj_JS(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Conj_JS(NODE node, struct function_options *_fopt, struct compile_options *_copt){
		// tq: if((*tree).NCself > 1 && (*tree).Conj != 1){
		if(child_no(node) > 1 && conjugate(node) != 1){
			printf("]");
		}
		// tq: if((*tree).LVself != 0 && strlen((*tree).Head) != 0){ 
		if(level(node) != 0 && strlen(head(node)) != 0){ 
			// tq: if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
			if((*_copt).c_counter > 0 && (extra_stat(node)&8) == 8){	// for unpack
				// tq: if(strlen((*tree).Head) > 3){
				if(strlen(head(node)) > 3){
					printf(",");
				}
			}else{
				printf(",");	//normal case
			}
		} 
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Conj_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Conj_WL(NODE node, struct function_options *_fopt, struct compile_options *_copt){
		// tq: if((*tree).Conj == 1){
		if(conjugate(node) == 1){
			printf(",");
		// tq: }else if((*tree).NCself > 1){
		}else if(child_no(node) > 1){
			printf("][");
		}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Conj_C(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Conj_C(NODE node, struct function_options *_fopt, struct compile_options *_copt){
		// tq: if((*tree).Conj == 1){
		if(conjugate(node) == 1){
			printf(INDENT);
		// tq: }else if((*tree).NCself > 1){
		}else if(child_no(node) > 1){
			printf("\n");
			printf(INDENT);
		}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Conj_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Conj_X(NODE node, struct function_options *_fopt, struct compile_options *_copt){
		// tq: if((*tree).Conj == 1){
		if(conjugate(node) == 1){
			printf(" ");
		// tq: }else if((*tree).NCself > 1){
		}else if(child_no(node) > 1){
			printf("<c/>");
		}
	// tq: return(tree);
	return(node);
}
/** Bopen */
// tq: struct Tree *Function_Print_Bopen_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
NODE Function_Print_Bopen_T(NODE node, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){
		// tq: if((*tree).NextCount != 0){ 
		if(child_count(node) != 0){ 
			// tq: if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8 && ((*tree).extra_stat&1) != 1){	// for unpack
			if((*_copt).c_counter > 0 && (extra_stat(node)&8) == 8 && (extra_stat(node)&1) != 1){	// for unpack
				// tq: if(strlen((*tree).Head) > 3){
				if(strlen(head(node)) > 3){
					//printf(",");
				}
			}else{
				printf("(");	//normal case  : "must"
			}
		}
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Bopen_S(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
NODE Function_Print_Bopen_S(NODE node, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 0){
		int i;
		// tq: for(i=0;i<(*tree).NextCount;i++){
		for(i=0;i<child_count(node);i++){
			// tq: if((*tree).Next[i]->Conj == 0){ 
			if(conjugate(child(node,i)) == 0){ 
				// tq: if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
				if((*_copt).c_counter > 0 && (extra_stat(node)&8) == 8){	// for unpack
					// tq: if(strlen((*tree).Head) > 3){
					if(strlen(head(node)) > 3){
						;
					}
				}else{
					printf("(");	//normal case
				}
			}
		}
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Bopen_JS(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
NODE Function_Print_Bopen_JS(NODE node, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 0){
		int i;
		// tq: for(i=0;i<(*tree).NextCount;i++){
		for(i=0;i<child_count(node);i++){
			// tq: if((*tree).Next[i]->Conj == 0){ 
			if(conjugate(child(node,i)) == 0){ 
				// tq: if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
				if((*_copt).c_counter > 0 && (extra_stat(node)&8) == 8){	// for unpack
					// tq: if(strlen((*tree).Head) > 3){
					if(strlen(head(node)) > 3){
						;
					}
				}else{
					printf("[");	//normal case
				}
			}
		}
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Bopen_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
NODE Function_Print_Bopen_WL(NODE node, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){
		// tq: if((*tree).NextCount != 0){
		if(child_count(node) != 0){
			printf("[");
		}
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Bopen_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
NODE Function_Print_Bopen_X(NODE node, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){
		// tq: if((*tree).NextCount != 0){
		if(child_count(node) != 0){
			int sw = 0;
			int *dim_pos;
			int head_len = 0;
			char *head_str;
			if((dim_pos = calloc(2,sizeof(int))) == NULL){
				perror("[Fail]:calloc@Function_Print_Bopen_X.\n");
				exit(1);
			}
			// tq: sw = Detect_DimRegion((*tree).Head,dim_pos);
			sw = Detect_DimRegion(head(node),dim_pos);
			if(sw == 2){
				// tq: head_len = strlen((*tree).Head);
				head_len = strlen(head(node));
				if((head_str = malloc(sizeof(char) * (head_len+2))) == NULL){
					perror("[Fail]:calloc@Function_Print_Bopen_X.\n");
					exit(1);
				}
				// tq: strcpy(head_str,(*tree).Head);
				strcpy(head_str,head(node));
				head_str[dim_pos[0]] = '\0';
				head_str[head_len-1] = '\0';
				printf("<%s DIM=",head_str);
				printf("%s>",head_str+dim_pos[0]+1);
			}else{
				// tq: head_len = strlen((*tree).Head);
				head_len = strlen(head(node));
				if(head_len > 0){
					// tq: printf("<%s>",(*tree).Head);
					printf("<%s>",head(node));
				}else{
					;
				}
			}
		}
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Bopen_C(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt, int pos){
NODE Function_Print_Bopen_C(NODE node, struct function_options *_fopt, struct compile_options *_copt, int pos){
	if(pos == 1){
		// tq: if((*tree).NextCount != 0){
		if(child_count(node) != 0){
			printf(INDENT);
		}
	}
	// tq: return(tree);
	return(node);
}
/** Bclose */
// tq: struct Tree *Function_Print_Bclose_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Bclose_T(NODE node, struct function_options *_fopt, struct compile_options *_copt){
	// tq: if((*tree).NextCount != 0){
	if(child_count(node) != 0){
			// tq: if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
			if((*_copt).c_counter > 0 && (extra_stat(node)&8) == 8 && (extra_stat(node)&1) != 1){	// for unpack
				;
			}else{
				printf(")");	//normal case
			}
			// tq: if((*_copt).c_counter > 0 && ((*tree).extra_stat&4) == 4){	// for quating
			if((*_copt).c_counter > 0 && (extra_stat(node)&4) == 4){	// for quating
				printf("\"");
			}
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Bclose_S(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Bclose_S(NODE node, struct function_options *_fopt, struct compile_options *_copt){
	// tq: if((*tree).NextCount != 0){
	if(child_count(node) != 0){
			// tq: if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
			if((*_copt).c_counter > 0 && (extra_stat(node)&8) == 8){	// for unpack
				;
			}else{
				printf(")");	//normal case
			}
			// tq: if((*_copt).c_counter > 0 && ((*tree).extra_stat&4) == 4){	// for quating
			if((*_copt).c_counter > 0 && (extra_stat(node)&4) == 4){	// for quating
				printf("\"");
			}
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Bclose_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Bclose_WL(NODE node, struct function_options *_fopt, struct compile_options *_copt){
	// tq: if((*tree).NextCount != 0){
	if(child_count(node) != 0){
			// tq: if((*_copt).c_counter > 0 && ((*tree).extra_stat&8) == 8){	// for unpack
			if((*_copt).c_counter > 0 && (extra_stat(node)&8) == 8){	// for unpack
				;
			}else{
				printf("]");	//normal case
			}
			// tq: if((*_copt).c_counter > 0 && ((*tree).extra_stat&4) == 4){	// for quating
			if((*_copt).c_counter > 0 && (extra_stat(node)&4) == 4){	// for quating
				printf("\"");
			}
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Bclose_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Bclose_X(NODE node, struct function_options *_fopt, struct compile_options *_copt){
	if(child_count(node) != 0){
			int sw = 0;
			int *dim_pos;
			int head_len = 0;
			char *head_str;
			if((dim_pos = calloc(2,sizeof(int))) == NULL){
				perror("[Fail]:calloc@Function_Print_Bclose_X.\n");
				exit(1);
			}
			// tq: sw = Detect_DimRegion((*tree).Head,dim_pos);
			sw = Detect_DimRegion(head(node),dim_pos);
			if(sw == 2){
				// tq: head_len = strlen((*tree).Head);
				head_len = strlen(head(node));
				if((head_str = malloc(sizeof(char) * (head_len+2))) == NULL){
					perror("[Fail]:calloc@Function_Print_Bclose_X.\n");
					exit(1);
				}
				// tq: strcpy(head_str,(*tree).Head);
				strcpy(head_str,head(node));
				head_str[dim_pos[0]] = '\0';
				head_str[head_len-1] = '\0';
				printf("</%s>",head_str);
			}else{
				// tq: head_len = strlen((*tree).Head);
				head_len = strlen(head(node));
				if(head_len > 0){
					// tq: printf("</%s>",(*tree).Head);
					printf("</%s>",head(node));
				}else{
					;
				}
			}
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Bclose_C(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Bclose_C(NODE node, struct function_options *_fopt, struct compile_options *_copt){
	// tq: if((*tree).NextCount != 0){
	if(child_count(node) != 0){
		printf("\n");
	// tq: }
	}
	return(node);
}
/** val */
// tq: int Get_nvalMax(struct Tree *tree){
int Get_nvalMax(NODE node){
	int i;
	int MAX = 0;
	//Self
	// tq: MAX = max(MAX,(*tree).nval);
	MAX = max(MAX,value_count(node));
	//Ref
	// tq: if((*tree).RefNode != NULL){
	if(ref_node(node) != NO_NODE){
		// tq: MAX = max(MAX,(*tree).RefNode->nval);
		MAX = max(MAX,value_count(ref_node(node)));
	}
	// tq: for(i=0;i<(*tree).NextCount;i++){
	for(i=0;i<child_count(node);i++){
		// tq: MAX = max(MAX,Get_nvalMax((*tree).Next[i]));
		MAX = max(MAX,Get_nvalMax(child(node,i)));
	}
	return(MAX);
}
// tq: int Get_nvalList(struct Tree *tree, int *nvalList, int nval_start){
int Get_nvalList(NODE node, int *nvalList, int nval_start){
	int i;
	int nval = 0;
	int nval_count = nval_start;
	int tmp_head_len = 0;
	// tq: tmp_head_len = strlen((*tree).Head);
	tmp_head_len = strlen(head(node));
	// tq: if(tmp_head_len == 0 || (*tree).Head[tmp_head_len-1] != '@'){
	if(tmp_head_len == 0 || head(node)[tmp_head_len-1] != '@'){
		goto EXIT_pseudo;
	}
	// tq: nval = (*tree).NextCount;
	nval = child_count(node);
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
	// tq: nval = (*tree).nval;
	nval = value_count(node);
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
	// tq: if((*tree).RefNode != NULL){
	if(ref_node(node) != NO_NODE){
		// tq: nval = (*(*tree).RefNode).nval;
		nval = value_count(ref_node(node));
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
	// tq: for(i=0;i<(*tree).NextCount;i++){
	for(i=0;i<child_count(node);i++){
		// tq: nval_count = Get_nvalList((*tree).Next[i],nvalList,nval_count);
		nval_count = Get_nvalList(child(node,i),nvalList,nval_count);
	}
	return(nval_count);
}
int print_singleVal(char *str){
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
// tq: struct Tree *Print_nthVal(struct Tree *tree, int nth){
NODE Print_nthVal(NODE node, int nth){
	// nth : loop iterator
	int p = 0;
	// tq: if((*tree).valstr != NULL && (*tree).valPtr != NULL){
	if(values_str(node) != NULL && value_poses(node) != NULL){
		// tq: p = nth%(*tree).nval;
		p = nth%value_count(node);
		// tq: print_singleVal((*tree).valstr+(*tree).valPtr[p]);
		print_singleVal(values_str(node)+value_pos(node,p));
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Recursive_Print_nthVal(struct Tree *tree, int nth){ //%P
NODE Function_Recursive_Print_nthVal(NODE node, int nth, struct function_options *_fopt, struct compile_options *_copt){ //%P
	int i;
	int conjR = 0;
	// tq: if((*tree).NCself > 1){
	if(child_no(node) > 1){
		printf(",");
	}
	// tq: if((*tree).nval > 0){
	if(value_count(node) > 0){
		// tq: Print_nthVal(tree,nth);
		Print_nthVal(node,nth);
		conjR = 1;
	}
	// tq: if((*tree).RefNode == NULL && ((*tree).extra_stat&2) != 2){
	if(ref_node(node) == NO_NODE && (extra_stat(node)&2) != 2){
		int tmp_head_len = 0;
		// tq: tmp_head_len = strlen((*tree).Head);
		tmp_head_len = strlen(head(node));
		// tq: if(tmp_head_len == 0 || (*tree).Head[tmp_head_len-1] != '@'){
		if(tmp_head_len == 0 || head(node)[tmp_head_len-1] != '@'){
                        // tq: printf("%s",(*tree).Head+(*tree).IndicatorPtr);
                        printf("%s",head(node)+indicator_pos(node));
		}else{	//force-bind
			if(((*_fopt).f_skipOnce&1) != 1){
                                (*_fopt).f_skipOnce = (*_fopt).f_skipOnce + 1;
			}
			// tq: ExFunction_Recursive_Ser_MultiPrint((*tree).Next[nth%(*tree).NextCount], (struct Tree *(*)())Function_Print_Conj_T, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_T,  (struct Tree *(*)())Function_Print_Bclose_T,NULL,_fopt,_copt,0);
			ExFunction_Recursive_Ser_MultiPrint(child(node,nth%child_count(node)), (NODE(*)())Function_Print_Conj_T, (NODE(*)())Function_Print_Head, (NODE(*)())Function_Print_Bopen_T,  (NODE(*)())Function_Print_Bclose_T,NULL,_fopt,_copt,0);
			return(node);
		}
	}
	// tq: if((*tree).RefNode != NULL){
	if(ref_node(node) != NO_NODE){
		// tq: if((*tree).RefNode->nval > 0){
		if(value_count(ref_node(node)) > 0){
			if(conjR > 0){
				printf(",");
			}
			// tq: Print_nthVal((*tree).RefNode,nth);
			Print_nthVal(ref_node(node),nth);
		}
		// tq: if((*tree).RefNode->NextCount > 0){
		if(child_count(ref_node(node)) > 0){
			printf("(");
			// tq: for(i=0;i<(*tree).RefNode->NextCount;i++){
			for(i=0;i<child_count(ref_node(node));i++){
				// tq: Function_Recursive_Print_nthVal((*tree).RefNode->Next[i],nth);
				Function_Recursive_Print_nthVal(child(ref_node(node),i),nth,_fopt,_copt);
			}
			printf(")");
		}
	}
	// tq: if((*tree).NextCount > 0){
	if(child_count(node) > 0){
		printf("(");
		// tq: for(i=0;i<(*tree).NextCount;i++){
		for(i=0;i<child_count(node);i++){
			// tq: Function_Recursive_Print_nthVal((*tree).Next[i],nth);
			Function_Recursive_Print_nthVal(child(node,i),nth,_fopt,_copt);
		}
		printf(")");
	}
	// tq: return(tree);
	return(node);
}
/** Head */
// tq: struct Tree *Function_RecursiveCyclic_Print_IProductVal(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){ //%P
NODE Function_RecursiveCyclic_Print_IProductVal(NODE node, struct function_options *_fopt, struct compile_options *_copt){ //%P
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
	// tq: max_nval = Get_nvalMax(tree);
	max_nval = Get_nvalMax(node);
	// tq: nval_count = Get_nvalList(tree,nval_list,0);
	nval_count = Get_nvalList(node,nval_list,0);
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
		// tq: Function_Recursive_Print_nthVal(tree,i);
		Function_Recursive_Print_nthVal(node,i,_fopt,_copt);
	}
	for(i=0;i<nval_count-1;i++){
		printf(")");
	}
	//print後は子ノードを切る
	// tq: if(((*tree).extra_stat&2) != 2){
	if((extra_stat(node)&2) != 2){
		// tq: (*tree).extra_stat = (*tree).extra_stat + 2;
		set_extra_stat(node,extra_stat(node) + 2);
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Print_RecursiveSeq_Head(struct Tree *tree, int conj, int ind){
NODE Print_RecursiveSeq_Head(NODE node, int conj, int ind){
	int i;
	if(conj == 1){
		printf(",");
	}
	if(ind == 1){
		// tq: printf("%s",(*tree).Head+(*tree).IndicatorPtr);
		printf("%s",head(node)+indicator_pos(node));
	}else{
		// tq: printf("%s",(*tree).Head);
		printf("%s",head(node));
	}
	// tq: for(i=0;i<(*tree).NextCount;i++){
	for(i=0;i<child_count(node);i++){
		// tq: Print_RecursiveSeq_Head((*tree).Next[i],1,ind);
		Print_RecursiveSeq_Head(child(node,i),1,ind);
	}
	//print後は子ノードを切る
	// tq: if(((*tree).extra_stat&2) != 2){
	if((extra_stat(node)&2) != 2){
		// tq: (*tree).extra_stat = (*tree).extra_stat + 2;
		set_extra_stat(node,extra_stat(node) + 2);
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Head(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){ //%P
NODE Function_Print_Head(NODE node, struct function_options *_fopt, struct compile_options *_copt){ //%P
	/* 特殊型にFunction_Print_ProductValあり、上位関数で切り替え */
	//// tq: struct Tree *ins_head = NULL;
	//NODE ins_head = NO_NODE;
	char target_type = '\0';
	int target_label = -1;
	int prg = 0;
	/* print hierarchy */
	if((*_fopt).f_print_hierarchy == 1 && (*_fopt).f_print_self_stat == 1){
		int i;
		printf("\n");
		// tq: for(i=0;i<(*tree).LVself;i++){
		for(i=0;i<level(node);i++){
			printf(INDENT);
		}
		// tq: if((*tree).Conj == 1 && (*tree).NCself > 1){
		if(conjugate(node) == 1 && child_no(node) > 1){
			printf("+");
			// tq: printf("%d:",(*tree).ser);
			printf("%d:",ser(node));
		}else{
			printf("-");
			// tq: printf("%d:",(*tree).ser);
			printf("%d:",ser(node));
		}
	}
	/* interpret */
	char *tmp_str = NULL;
	// tq: tmp_str = Function_Interpret_Head(tree,_copt);
	tmp_str = Interpret_Head(node,_copt);
	/* print head */
	// tq: if(((*tree).extra_stat&1) == 1){
	if((extra_stat(node)&1) == 1){
		// tq: printf("%s",(*tree).Head);	//normal
		printf("%s",head(node));	//normal
	}else if((*_copt).c_counter > 0){
		printf("%s",tmp_str);
		free(tmp_str);
	}else{
		// tq: printf("%s",(*tree).Head);	//normal
		printf("%s",head(node));	//normal
	}

	/* if extra_stat&2 == 2 then return() */
	// tq: if(((*tree).extra_stat&2) == 2){
	if((extra_stat(node)&2) == 2){
		// tq: return(tree);
		return(node);
	}

	/* print bind mark (1) */
	// tq: if((*tree).valstr != NULL){
	if(values_str(node) != NULL){
		printf("@");
	}
	/* print ref node */
	// tq: prg = get_ref((*tree).Head+(*tree).IndicatorPtr,&target_type,&target_label);
	prg = get_ref(head(node)+indicator_pos(node),&target_type,&target_label);
	// tq: if((*tree).RefNode != NULL){
	if(ref_node(node) != NO_NODE){
		(*_fopt).f_print_self_stat = 0;
		/* switch 't' 'h' */
		// tq: if((*tree).RefNode->LabelType == 'h'){
		if(label_type(ref_node(node)) == 'h'){
			DB(fprintf(stderr," LT:h: <= TG:%c:\n",target_type);)
			printf("@");
			// tq: Function_Print_Head((*tree).RefNode,_fopt,_copt);
			Function_Print_Head(ref_node(node),_fopt,_copt);
		// tq: }else if((*tree).RefNode->LabelType == 't' && target_type == 't'){
		}else if(label_type(ref_node(node)) == 't' && target_type == 't'){
			DB(fprintf(stderr," LT:t:,TG:t:\n");)
			printf("@");
			if((((*_fopt).f_skipOnce)&1) == 0){	// skip print_conj
				(*_fopt).f_skipOnce = (*_fopt).f_skipOnce + 1;
			}
			DB(fprintf(stderr," print_head:skip:%d:\n",(*_fopt).f_skipOnce);)
			// tq: ExFunction_Recursive_Ser_MultiPrint((*tree).RefNode, (struct Tree *(*)())Function_Print_Conj_T, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_T,  (struct Tree *(*)())Function_Print_Bclose_T,NULL,_fopt,_copt,0);
			ExFunction_Recursive_Ser_MultiPrint(ref_node(node), (NODE (*)())Function_Print_Conj_T, (NODE (*)())Function_Print_Head, (NODE (*)())Function_Print_Bopen_T,  (NODE (*)())Function_Print_Bclose_T,NULL,_fopt,_copt,0);
		// tq: }else if((*tree).RefNode->LabelType == 't' && target_type == 'h'){
		}else if(label_type(ref_node(node)) == 't' && target_type == 'h'){
			DB(fprintf(stderr," LT:t:,TG:h:\n");)
			printf("@");
			// tq: Function_Print_Head((*tree).RefNode,_fopt,_copt);
			Function_Print_Head(ref_node(node),_fopt,_copt);
		}
	}
	/* progress IndicatorPtr -> not here */

	/* print binded data (1) */
	// tq: if((*tree).valstr != NULL){
	if(values_str(node) != NULL){
		// tq: printf("(%s)",(*tree).valstr);
		printf("(%s)",values_str(node));
	}
	/* comma for unpack */
	if((*_copt).c_counter > 0){
		// tq: if(((*tree).extra_stat&8) == 8 && ((*tree).extra_stat&1) != 1 && (*tree).NextCount > 0){
		if((extra_stat(node)&8) == 8 && (extra_stat(node)&1) != 1 && child_count(node)> 0){
			putchar(44);
		}
	}

	/* print hierarchy */
	if((*_fopt).f_print_hierarchy == 1 && (*_fopt).f_print_self_stat == 1){
		printf(":");
	}
	if((*_fopt).f_print_hierarchy == 1){
		(*_fopt).f_print_self_stat = 1;
	}

	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Head_JS(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){ //%I
NODE Function_Print_Head_JS(NODE node, struct function_options *_fopt, struct compile_options *_copt){ //%I
	int sw = 0;
	int *dim_pos;
	int head_len = 0;
	char *head_str;
	char *tmp_str;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]:calloc@Function_Print_Head_JS.\n");
		exit(1);
	}
	// tq: head_len = strlen((*tree).Head);
	head_len = strlen(head(node));
	if((tmp_str = malloc(sizeof(char) * (head_len+1))) == NULL){
		perror("[Fail]:malloc@Function_Print_Head_JS.\n");
		exit(1);
	}
	/* compile */
	if((*_copt).c_counter > 0){
		// tq: tmp_str = Interpret_Head(tree,_copt);
		tmp_str = Interpret_Head(node,_copt);
	}else{
		// tq: strcpy(tmp_str,(*tree).Head);
		strcpy(tmp_str,head(node));
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
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Head_WL(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){ //%I
NODE Function_Print_Head_WL(NODE node, struct function_options *_fopt, struct compile_options *_copt){ //%I
	int sw = 0;
	int *dim_pos;
	int head_len = 0;
	char *head_str;
	char *tmp_str;
	if((dim_pos = calloc(2,sizeof(int))) == NULL){
		perror("[Fail]:calloc@Function_Print_Head_WL.\n");
		exit(1);
	}
	// tq: head_len = strlen((*tree).Head);
	head_len = strlen(head(node));
	if((tmp_str = malloc(sizeof(char) * (head_len+1))) == NULL){
		perror("[Fail]:malloc@Function_Print_Head_WL.\n");
		exit(1);
	}
	/* compile */
	if((*_copt).c_counter > 0){
		// tq: tmp_str = Interpret_Head(tree,_copt);
		tmp_str = Interpret_Head(node,_copt);
	}else{
		// tq: strcpy(tmp_str,(*tree).Head);
		strcpy(tmp_str,head(node));
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
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Head_X(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){ //%I
NODE Function_Print_Head_X(NODE node, struct function_options *_fopt, struct compile_options *_copt){ //%I
	// tq: if((*tree).NextCount == 0){
	if(child_count(node) == 0){
		/* compile */
		if((*_copt).c_counter > 0){
			char *tmp_str;
			// tq: tmp_str = Interpret_Head(tree,_copt);
			tmp_str = Interpret_Head(node,_copt);
			printf("%s",tmp_str);
		}else{
			// tq: printf("%s",(*tree).Head);	//normal
			printf("%s",head(node));	//normal
		}
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *Function_Print_Head_SN(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
NODE Function_Print_Head_SN(NODE node, struct function_options *_fopt, struct compile_options *_copt){
	// tq: printf("%d",(*tree).ser);
	printf("%d",ser(node));
	// tq: return(tree);
	return(node);
}

/* recursive-apply-function */
/** Down tree */
// tq: struct Tree *ExFunction_Recursive_Set_Obj(struct Tree *tree, struct Tree *(*e_function)(struct Tree *tree, void *), void *obj){
NODE ExFunction_Recursive_Set_Obj(NODE node, NODE (*e_function)(NODE node, void *), void *obj){
	int i;
	(*e_function)(node,obj);
	// tq: for(i=0;i<(*tree).NextCount;i++){
	for(i=0;i<child_count(node);i++){
		// tq: ExFunction_Recursive_Set_Obj((*tree).Next[i],e_function,obj);
		ExFunction_Recursive_Set_Obj(child(node,i),e_function,obj);
	}
	// tq: return(tree);
	return(node);
}
// tq: struct Tree *ExFunction_Recursive(struct Tree *tree, struct Tree *(*e_function)(struct Tree *, struct options *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt){
NODE ExFunction_Recursive(NODE node, NODE (*e_function)(NODE , struct options *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt){
	int i;
	// tq: struct Tree *out = tree;
	NODE out = node;
	// tq: if(tree == NULL || e_function == NULL){
	if(node == NO_NODE || e_function == NULL){
		perror("NULL node detected -- exit.\n");
		exit(1);
	}
	// tq: (*e_function)(tree,_opt);
	(*e_function)(node,_opt);
	// tq: for(i=0;i<(*tree).NextCount;i++){
	for(i=0;i<child_count(node);i++){
		// tq: ExFunction_Recursive((*tree).Next[i],e_function,_opt,_fopt,_copt);
		ExFunction_Recursive(child(node,i),e_function,_opt,_fopt,_copt);
	}
	return(out);
}
// tq: struct Tree *ExFunction_Recursive_Ser(struct Tree *tree, struct Tree *(*e_function)(struct Tree *, int, struct options *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, int _ser, int exec){
NODE ExFunction_Recursive_Ser(NODE node, NODE (*e_function)(NODE , int, struct options *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, int _ser, int exec){
	if(exec == 0){
		return(NO_NODE);
	}
	int i;
	// tq: struct Tree *out = tree;
	NODE out = node;
	if(node == NO_NODE || e_function == NULL){
		perror("NULL node detected -- exit.\n");
		exit(1);
	}
	// tq: (*e_function)(tree,_ser,_opt);
	(*e_function)(node,_ser,_opt);
	// tq: for(i=0;i<(*tree).NextCount;i++){
	for(i=0;i<child_count(node);i++){
		// tq: ExFunction_Recursive_Ser((*tree).Next[i],e_function,_opt,_fopt,_copt,_ser,exec);
		ExFunction_Recursive_Ser(child(node,i),e_function,_opt,_fopt,_copt,_ser,exec);
	}
	return(out);
}
// tq: struct Tree *ExFunction_Recursive_Ser_MultiPrint(struct Tree *tree, struct Tree *(*conj_function)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*head_function)(struct Tree *, struct function_options *, struct compile_options *), struct Tree *(*bopen_function)(struct Tree *, struct function_options *, struct compile_options *, int),  struct Tree *(*bclose_function)(struct Tree *, struct function_options *, struct compile_options *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, int _ser){
NODE ExFunction_Recursive_Ser_MultiPrint(NODE node, NODE (*conj_function)(NODE , struct function_options *, struct compile_options *), NODE (*head_function)(NODE , struct function_options *, struct compile_options *), NODE (*bopen_function)(NODE , struct function_options *, struct compile_options *, int),  NODE (*bclose_function)(NODE , struct function_options *, struct compile_options *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, int _ser){
	int i;
	// tq: struct Tree *out = tree;
	NODE out = node;
	// tq: if(tree == NULL){
	if(node == NO_NODE){
		perror("NULL node detected -- exit.\n");
		exit(1);
	}
	/*print conj*/
	// tq: conj_function(tree,_fopt,_copt);
	conj_function(node,_fopt,_copt);
	/*print Bopen pre*/
	// tq: bopen_function(tree,_fopt,_copt,0);
	bopen_function(node,_fopt,_copt,0);
	/*print head*/
	// tq: head_function(tree,_fopt,_copt);
	head_function(node,_fopt,_copt);
	/*print Bopen post*/
	// tq: bopen_function(tree,_fopt,_copt,1);
	bopen_function(node,_fopt,_copt,1);
	// $UU$ : if Tree.extra_stat&2 == 2 then skip for-loop.
	// tq: if(((*tree).extra_stat&2) == 2 && (*_copt).c_counter > 0){
	if((extra_stat(node)&2) == 2 && (*_copt).c_counter > 0){
		// tq: Function_RecursiveCyclic_Print_IProductVal(tree,_fopt,_copt);
		Function_RecursiveCyclic_Print_IProductVal(node,_fopt,_copt);
	}else{
		// tq: for(i=0;i<(*tree).NextCount;i++){
		for(i=0;i<child_count(node);i++){
			// tq: ExFunction_Recursive_Ser_MultiPrint((*tree).Next[i],conj_function,head_function,bopen_function,bclose_function,_opt,_fopt,_copt,_ser);
			ExFunction_Recursive_Ser_MultiPrint(child(node,i),conj_function,head_function,bopen_function,bclose_function,_opt,_fopt,_copt,_ser);
		}
	}
	/*print Bclose*/
	// tq: bclose_function(tree,_fopt,_copt);
	bclose_function(node,_fopt,_copt);
	return(out);
}
/** Up tree */
// tq: struct Tree *ExFunction_UpRecursive(struct Tree *tree, struct Tree *(*e_function)(struct Tree *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, char *buff){
NODE ExFunction_UpRecursive(NODE node, NODE (*e_function)(NODE ), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, char *buff){
	// tq: struct Tree *parent;
	NODE par;
	// tq: parent = (*tree).Parent;
	par = parent(node);
	// tq: if((*tree).ser == -1 || (*parent).ser == -1 || e_function == NULL){
	if(ser(node) == -1 || ser(par) == -1 || e_function == NULL){
		// tq: return(NULL);
		return(NO_NODE);
	}
	// tq: ExFunction_UpRecursive(parent,e_function,_opt,_fopt,_copt,buff);
	ExFunction_UpRecursive(par,e_function,_opt,_fopt,_copt,buff);
	return(par);
}

// SAK   bind

#define TRUE	1
#define FALSE	0

#define ARRAY_INFINITY	-1

typedef int bool;

/*
bool empty_dim(char** str)
{
	return list[0] == -1;
}
*/
bool is_leaf(NODE node)
{
	return child_count(node) == 0 || strchr(head(node),'@') != NULL;	// SAK pending leaf '@'
}	
/*
int first(int* list)
{
	return list[0];
}

int* rest(int* list)
{
	return ++list;
}
*/

// [] / [,6] empty -> infinit
int scan_dim_number(char** str)
{
	bool bracket_beg = FALSE;
	int value = 0;

	while((**str) && !isdigit(**str) && !(bracket_beg && (**str) == ']')) {	// SAK pending escape
		if(**str == '[') {
			bracket_beg = TRUE;
		}
		(*str)++;
	}

	if(!(**str)) {				// end of string
		value = -1;
	} else if(isdigit(**str)) {		// number
		value = 0;			
		while(isdigit(**str)) {
			value = value*10 + ((**str)-'0');
			(*str)++;
		}
	} else {				// ']' with no numbers after opening '[' (e.g. [...])
		value = 0;
		(*str)++;
	}

	return value;
}

char* get_dim_str(char* str)
{
	// SAK pending escape
	while((*str) != '\0' && (*str) != '[') {	// skip to '['
		str++;
	}

	return str;
}

/*
void get_dim_list(char* str, int* dims)
{
	dims[0] = -1;				// termnator(end of list)

	// SAK pending escape
	while((*str) != '\0' && (*str) != '[') {	// skip to '['
		str++;
	}

	if((*str) == '\0') {			// '[' not detected ->non array
		return;
	} 

	int i=0;
	do {
		int value = 0;
		str++;				// skip '['

		read_number(&str, &value);
		dims[i++] = value;
		dims[i] = -1;			// terminator(end of list)

		while((*str) == ',') {
			str++;			// skip ','

			read_number(&str, &value);
			dims[i++] = value;
			dims[i] = -1;		// terminator(end of list)
		}

		if((*str) == ']') {
			str++;
		} else {
			dims[0] = -1;			// invalid dimension str
			return;
		}

	} while((*str) == '[');
}
*/
	
struct Stream {
	char ch;
	FILE* fp;
};

void initialize(struct Stream* in, FILE* fp)
{
	(*in).fp = fp;
	(*in).ch = fgetc((*in).fp);
}
	
void reset(struct Stream* in)
{
	fseek((*in).fp, 0, SEEK_SET);
	(*in).ch = fgetc((*in).fp);
}

char peek(struct Stream* in)
{
	return (*in).ch;
}

char get(struct Stream* in)
{
	(*in).ch = fgetc((*in).fp);
	return (*in).ch;
}

bool eos(struct Stream* in)
{
	return (*in).ch == EOF;
}

void skip_value(int* size, struct Stream* in)
{
	char ch = peek(in);

	if(*size > 0) {			// other than 1st data item
		(*size)++;		// for length of ','
	}

	while((ch != EOF) && (ch != DD) && (ch != '\n')) {	// SAK pending : escape
		(*size)++;
		ch = get(in);
	}
	if((ch == DD) || (ch == '\n')) {	// SAK pending : escape
		ch = get(in);
	}
}

void bind_data_1st_path(NODE node, struct Stream* in)
{
	int size = (int)(long)(values_str(node));		// bufer suze

	skip_value(&size, in);
	set_value_count(node, value_count(node)+1);	// increment value counter
	set_values_str_ptr(node, (char*)(long)(size));		// increment byte counter
}

void set_value(char* buff, int* s_pos, struct Stream* in)
{
	if(*s_pos>0) {			// other than 1st data item
		buff[(*s_pos)++] = DD;	// append ','
	}

	char ch = peek(in);
	int pos = *s_pos;
	while((ch != EOF) && (ch != DD) && (ch != '\n') ) {	// SAK pending : escape
		buff[pos++] = ch;
		ch = get(in);
	}
	buff[pos++] = '\0';
	if((ch == DD) || (ch == '\n')) {	// SAK pending : escape
		ch = get(in);
	}
}

void bind_data_2nd_path(NODE node, struct Stream* in)		// process next 1 data item
{
	if(value_poses(node) == NULL) {	// 1st data item
		if(set_value_poses_ptr(node, malloc(sizeof(int) * (value_count(node)+1))) == NULL) {
			perror("[]malloc@put_value2.\n");
			exit(1);
		} else {
			set_value_count(node, 0);	// reset value counter
		}
		if(set_values_str_ptr(node, malloc(sizeof(char) * ((long)values_str(node))+1)) == NULL) {
			perror("[]malloc@put_value2.\n");
			exit(1);
		} else {
			(values_str(node))[0] = '\0';
		}
	}

	int s_pos = strlen(values_str(node));			// /SAK pending  peformance

	set_value(values_str(node), &s_pos, in);
	set_value_pos(node, value_count(node), s_pos);
	set_value_count(node, value_count(node)+1);		// increment value counter
}

extern bool bind_node(NODE, struct Stream*, void (*)(NODE, struct Stream*));

bool bind_primitive_node(NODE node, struct Stream* in, void (*e_function)(NODE, struct Stream*))
{
	int eof=FALSE;

	if(is_leaf(node)) {		// leaf node
		eof = eos(in);
		if(!eof) {
			(*e_function)(node, in);
		}
	}

	int i;
	for(i=0; !eof && i<child_count(node); i++) {
		eof = bind_node(child(node,i), in, e_function);
	}

	return eof;
}

bool bind_dim_node(NODE node, char* dims, struct Stream* in, void (*e_function)(NODE, struct Stream*))
{
	bool eof = FALSE;
	int i;
	
	int num = scan_dim_number(&dims);
	
	if(num == -1) {		//  no dim number
		eof = bind_primitive_node(node, in, e_function);
	} else {
		for(i=0; !eof && (num == 0 || i< num); i++) {
			eof = bind_dim_node(node, dims, in, e_function);
		}
	}

	return eof;
}

bool bind_node(NODE node, struct Stream* in, void (*e_function)(NODE, struct Stream*))
{
	char* dims = get_dim_str(head(node));

	if(is_leaf(node) && !(*dims)) {		// non-array leaf node
		return FALSE;
	} else {
		return bind_dim_node(node, dims, in, e_function);
	}
}

void bind_data(NODE node, FILE* DATA)
{	
	struct Stream in;

	initialize(&in, DATA);
	bind_node(node, &in, bind_data_1st_path);

	reset(&in);
	bind_node(node, &in, bind_data_2nd_path);
}
