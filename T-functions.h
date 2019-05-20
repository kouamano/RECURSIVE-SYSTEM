/* prottype */

/* meta functions */
void null_func(void){
}

/* analyzers */
int AnalyzeHead(struct Tree *tree){
	int i = 0;
	int labelreadprt = 0;
	int labelnumlen = 0;
	char *labelnumstr;
	int headlen = 0;
	int labeled = 0;
	/* label type */
	if((*tree).Head[0] == '#' && (*tree).Head[1] == '#'){
		(*tree).LabelType = 't';
		labelreadprt = 2;
		labeled++;
	}else if((*tree).Head[0] == '#' && (*tree).Head[1] != '#'){
		(*tree).LabelType = 'h';
		labelreadprt = 1;
		labeled++;
	}
	/* label */
	if((*tree).LabelType != '\0'){
		/* check num char */
		for(i=labelreadprt; ((*tree).Head[i] >= 0x30) && ((*tree).Head[i] <= 0x39);i++){	//Hex
			labelnumlen++;
		}
		if((labelnumstr = malloc(sizeof(char) * (labelnumlen + 1))) == NULL){
			perror("[Fail]malloc@AnalyzeHead\n");
			exit(1);
		}
		strncpy(labelnumstr,(*tree).Head+labelreadprt,labelnumlen);
		sscanf(labelnumstr,"%d",&(*tree).Label);
		free(labelnumstr);
		labeled++;
	}
	/* IndicatorPtr */
	headlen = strlen((*tree).Head);
	for(i=labelnumlen;i<headlen;i++){
		if((*tree).Head[i] < 0x30 || (*tree).Head[i] > 0x39){
			(*tree).IndicatorPtr = i;
			break;
		}
	}
	//fprintf(stderr,"labeled:%d.\n",labeled);
	return(0);
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
int Detect_DimRegion(const char *head, int *pos){
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

/* reference analysis */
struct Tree *Function_Recursive_FindBind_LabelNode(struct Tree *tree, char type, int label, struct Tree *binded){	//for referred
	int i;
	if(tree == NULL){
		return(NULL);
	}
	if((*tree).LabelType == type && (*tree).Label == label){
		(*binded).RefNode = tree;	//bind
	}
	for(i=0;i<(*tree).NextCount;i++){
		Function_Recursive_FindBind_LabelNode((*tree).Next[i],type,label,binded);
	}
	return(NULL);
}
int get_ref(char *head, char *type, int *label){	//for binded
	int len;
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
		return(1);
	}
	if(len > 3){
		if(head[2] == '#' && head[3] >= 0x30 && head[3] <= 0x39){
			//sscanf(head+2,"%d",label);
			sscanf(head+3,"%d",label);
			*type = 't';
			return(1);
		}
	}
	return(0);
}

/* restructure functions */
void Function_Recursive_Bind_RefNode(struct Tree *binded, struct Tree *referred){
	int i;
	char target_type;
	int target_label;
	int stat;
	//stat = get_ref((*binded).Head,&target_type,&target_label);
	stat = get_ref((*binded).Head+(*binded).IndicatorPtr,&target_type,&target_label);
	if(stat == 1){
		struct Tree *addr;
		addr = Function_Recursive_FindBind_LabelNode(referred,target_type,target_label,binded);
	}
	for(i=0;i<(*binded).NextCount;i++){
		Function_Recursive_Bind_RefNode((*binded).Next[i],referred);
	}
}

int Add_DimStr(struct Tree *tree, int *dim_pos, char *buff){
	int len;
	len = strlen(buff);
	snprintf(buff+len,dim_pos[1]-dim_pos[0]+1,"%s",(*tree).Head+dim_pos[0]);
	return(len);
}
int Ins_DimStr(struct Tree *tree, int *dim_pos, char *buff){
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
int Print_UpR_Head(struct Tree *tree, char *buff){
	int sw;
	int dim_pos[2];
	int len;
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
		Print_UpR_Head((*tree).Parent,buff);
	}
	len = strlen(buff);
	return(len);
}
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
//struct Tree *Detect_DimBlock(struct Tree *tree, int dummy, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt){
struct Tree *Detect_DimBlock(struct Tree *tree, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt){
	int sw = 0;
	int dim_pos[2];
	char *buff;
	int len = 0;
	if((*tree).NextCount != 0){
		return(NULL);
	}
	sw = Detect_DimRegion((*tree).Head,dim_pos);
	if(sw != 2){
		return(NULL);
	}
	//if((buff = malloc(sizeof(char) * BUFF_LEN)) == NULL){
	if((buff = malloc(sizeof(char) * (*_opt).buff)) == NULL){
		perror("[Fail]malloc@Detect_DimBlock.\n");
		exit(1);
	}
	buff[0] = '\0';
	/* tmp -> dim */	
	len = Print_UpR_Head(tree,buff);
	if(((*tree).dimstr = malloc(sizeof(char) * (len + 1))) == NULL){
		perror("[Fail]malloc@Detect_DimBlock.\n");
		exit(1);
	}
	strcpy((*tree).dimstr,buff);
	(*tree).nval = get_nval(buff);
	free(buff);
	
	return(tree);
}
struct Tree *Function_Recursive_Search_BindNode(struct Tree *top, int *node_count, struct Tree **node_table){
	int i;
	struct Tree *current;
	current = top;
	if((*current).nval > 0){
		node_table = realloc(node_table,(sizeof(struct Tree *) * (*node_count + 2)));
		if(node_table == NULL){
			perror("[Fail]realloc@Function_Recursive_Search_BindNode");
			exit(1);
		}
		node_table[(*node_count)] = current;
		(*node_count)++;
	}
	for(i=0;i<(*current).NextCount;i++){
		Function_Recursive_Search_BindNode((*current).Next[i],node_count,node_table);
	}
	return(NULL);
}
int bind_data(FILE *DATA, struct Tree *tree, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt){
	int i;
        int C;
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
			//* escape */
			/*
                        if(C == '\\' && ESC == 0){
                                ESC = 1;
                        }else if(C == '\\' && ESC == 1){
                                ESC = 0;
                        }else{
                                ESC = 0;
                        }
			*/
			#include "escape_sw.c"

                }
        }
	free(buff);
        return(0);
}
struct Tree *Create_Node(int _ser, int H_size){
	struct Tree *tree;
	if((tree = malloc(sizeof(struct Tree) * 1)) == NULL){
		perror("[Fail]:malloc@Create_Node.\n");
		exit(1);
	}
	(*tree).ser=_ser;
	(*tree).LVself=0;
	(*tree).NCself=1;
	(*tree).Conj=0;
	(*tree).LabelType='\0';
	(*tree).Label=-1;
	(*tree).IndicatorPtr=0;
	if(H_size < 1){
		(*tree).Head = NULL;
	}else{
		if(((*tree).Head = malloc(sizeof(char) * H_size)) == NULL){
			perror("[Fail]:malloc@Create_Node.\n");
			exit(1);
		}
	}
	(*tree).NextCount=0;
	if(((*tree).Next = malloc((size_t)sizeof(struct Tree *) * 1)) == NULL){
		perror("[Fail]:malloc@Create_Node.\n");
		exit(1);
	}
	(*tree).dimstr = NULL;
	(*tree).nval = 0;
	(*tree).valstr = NULL;
	(*tree).Parent=NULL;
	(*tree).RefNode=NULL;
	return(tree);
}
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

/* compile functions */
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
char *Function_Compile(struct Tree *tree, struct compile_options *_copt){
	char *tmp_head;
	char *out_head;
	int compiled = 0;
	int len = 0;
	len = strlen((*tree).Head);
	if((tmp_head = malloc(sizeof(char) * (len+1))) == NULL){
		perror("[Fail]:malloc@Function_Compile.\n");
		exit(1);
	}
	if((out_head = malloc(sizeof(char) * (len+1))) == NULL){
		perror("[Fail]:malloc@Function_Compile.\n");
		exit(1);
	}

	strcpy(tmp_head,(*tree).Head+(*tree).IndicatorPtr);

	if((*_copt).c_clear > 0){
		tmp_head = Function_Clear_Head(tree);
	}else if((*_copt).c_dot > 0){
		tmp_head = Function_Dot_Head(tree);
	}else if(strncmp(tmp_head,"$NULL$",6) == 0){
	}else if(strncmp(tmp_head+(*tree).IndicatorPtr,"$PI$",4) == 0){	// Inner Product
		strcpy(out_head,tmp_head+(*tree).IndicatorPtr+4);
		strcpy(tmp_head,out_head);
		compiled++;
		//Under construction
	}else if(strncmp(tmp_head+(*tree).IndicatorPtr,"$X$",3) == 0){
		strcpy(out_head,tmp_head+(*tree).IndicatorPtr+3);
		strcpy(tmp_head,out_head);
		compiled++;
	}else if(strncmp(tmp_head+(*tree).IndicatorPtr,"$M$",3) == 0){
		strcpy(out_head,tmp_head+(*tree).IndicatorPtr+3);
		strcpy(tmp_head,out_head);
		compiled++;
	}else if(strncmp(tmp_head+(*tree).IndicatorPtr,"$U$",3) == 0){
		strcpy(out_head,tmp_head+(*tree).IndicatorPtr+3);
		strcpy(tmp_head,out_head);
		compiled++;
	}else if(strncmp(tmp_head,"$``",3) == 0){ //quating tree
		out_head = realloc(out_head, (sizeof(char) * (len+1)));
		if(out_head == NULL){
			perror("[Fail]:realloc@Function_Compile.\n");
			exit(1);
		}
		out_head[0]='"';
		if((*tree).NextCount == 0){
			strcpy(out_head+1,tmp_head+3);
			out_head[len-2]='"';
			out_head[len-1]='\0';
		}else{
			strcpy(out_head+1,tmp_head+3);
			out_head[len-1]='\0';
		}
		strcpy(tmp_head,out_head);
		compiled++;
	}else if(strncmp(tmp_head,"$~",2) == 0){
		strcpy(out_head,tmp_head+2);
		strcpy(tmp_head,out_head);
		compiled++;
	}else if(strncmp(tmp_head,"$`",2) == 0){ //quating Head
		out_head = realloc(out_head, (sizeof(char) * (len+1)));
		if(out_head == NULL){
			perror("[Fail]:realloc@Function_Compile_Head.\n");
			exit(1);
		}
		out_head[0]='"';
		strcpy(out_head+1,tmp_head+2);
		out_head[len-1]='"';
		out_head[len]='\0';
		strcpy(tmp_head,out_head);
		compiled++;
	}
	free(out_head);
	//fprintf(stderr,"Compiled:%d.\n",compiled);
	return(tmp_head);
}

/* print functions */
//* status */
void Function_Print_Smems(struct Tree *tree){
	//struct Tree *parent = (*tree).Parent;
	printf(":SN=%d:",(*tree).ser);
	printf(":LVs=%d:",(*tree).LVself);
	printf(":Adr=%ld:",(long int)tree);
	printf(":PaAdr=%ld:",(long int)(*tree).Parent);
	printf(":Ref=%ld:",(long int)(*tree).RefNode);
	printf(":LT=%c:",(*tree).LabelType);
	printf(":Lb=%d:",(*tree).Label);
	printf(":Hi=%d:",(*tree).IndicatorPtr);
	printf(":H=%s:",(*tree).Head);
	printf(":D=%s:",(*tree).dimstr);
	printf(":nval=%d:",(*tree).nval);
	printf(":vstr=%s:",(*tree).valstr);
	printf(":Cj=%d:",(*tree).Conj);
	printf(":NCs=%d:",(*tree).NCself);
	printf(":NC=%d:",(*tree).NextCount);
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
			printf("[%d",i);
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
				//printf("NotNULL");
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

/* formated print primitives */
//* Conj */
struct Tree *Function_Print_Conj_T(struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
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
			/* for unpack */
			if((*_copt).c_counter > 0 && strncmp((*tree).Head+(*tree).IndicatorPtr,"$U$",3) == 0){
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
			if((*_copt).c_counter > 0 && strncmp((*tree).Head+(*tree).IndicatorPtr,"$U$",3) == 0){
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
	struct Tree *ins_head = NULL;
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
	/* print head */
	if((*_copt).c_counter > 0){
		//* compile */
		char *tmp_str;
		tmp_str = Function_Compile(tree,_copt);
		printf("%s",tmp_str);
		free(tmp_str);	//test
	}else{
		printf("%s",(*tree).Head);	//normal
	}
	/* print ref node */
	if((*tree).RefNode != NULL){
		printf("@");
		(*_fopt).f_print_self_stat = 0;
		//* レファレンスされるノードのLTが't'/'h'により切り替え
		//* LT:'h' */
		ins_head = Function_Print_Head((*tree).RefNode,_fopt,_copt);
		//* LT:'t' */
	}
	if((*_fopt).f_print_hierarchy == 1){
		(*_fopt).f_print_self_stat = 1;
	}
	/* print binded data */
	// testing
	if((*tree).valstr != NULL){
		// the bind mark "@" print
		if(ins_head != NULL){
			if((*ins_head).valstr == NULL){
				printf("@");
			}
		}else{
			printf("@");
		}
		//printf("@(%s)",(*tree).valstr);
		printf("(%s)",(*tree).valstr);
	}
	/* print hierarchy */
	if((*_fopt).f_print_hierarchy == 1 && (*_fopt).f_print_self_stat == 1){
		printf(":");
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
		tmp_str = Function_Compile(tree,_copt);
	}else{
		strcpy(tmp_str,(*tree).Head);
	}
	/* conversion */
	sw = Detect_DimRegion(tmp_str,dim_pos);
	if(sw == 2){
		head_len = strlen(tmp_str);
		if((head_str = malloc(sizeof(char) * (head_len+1))) == NULL){
			perror("[Fail]:calloc@Function_Print_Head_W.\n");
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
		tmp_str = Function_Compile(tree,_copt);
	}else{
		strcpy(tmp_str,(*tree).Head);
	}
	/* conversion */
	sw = Detect_DimRegion(tmp_str,dim_pos);
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
			tmp_str = Function_Compile(tree,_copt);
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
			if((*_copt).c_counter > 0 && strncmp((*tree).Head+(*tree).IndicatorPtr,"$U$",3) == 0){
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
				if((*_copt).c_counter > 0 && strncmp((*tree).Head+(*tree).IndicatorPtr,"$U$",3) == 0){
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
				if((*_copt).c_counter > 0 && strncmp((*tree).Head+(*tree).IndicatorPtr,"$U$",3) == 0){
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
			sw = Detect_DimRegion((*tree).Head,dim_pos);
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
			if((*_copt).c_counter > 0 && strncmp((*tree).Head+(*tree).IndicatorPtr,"$U$",3) == 0){
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
			if((*_copt).c_counter > 0 && strncmp((*tree).Head+(*tree).IndicatorPtr,"$U$",3) == 0){
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
			if((*_copt).c_counter > 0 && strncmp((*tree).Head+(*tree).IndicatorPtr,"$U$",3) == 0){
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
			sw = Detect_DimRegion((*tree).Head,dim_pos);
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
//* Down tree */
struct Tree *ExFunction_Recursive(struct Tree *tree, struct Tree *(*e_function)(struct Tree *, struct options *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt){
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
	for(i=0;i<(*tree).NextCount;i++){
		ExFunction_Recursive_Ser_MultiPrint((*tree).Next[i],conj_function,head_function,bopen_function,bclose_function,_opt,_fopt,_copt,_ser);
	}
	/*print Bclose*/
	bclose_function(tree,_fopt,_copt);
	return(out);
}
//* Up tree */
struct Tree *ExFunction_UpRecursive(struct Tree *tree, struct Tree *(*e_function)(struct Tree *), struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, char *buff){
	struct Tree *parent;
	parent = (*tree).Parent;
	if((*tree).ser == -1 || (*parent).ser == -1 || e_function == NULL){
		return(NULL);
	}
	ExFunction_UpRecursive(parent,e_function,_opt,_fopt,_copt,buff);
	return(parent);
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

	//free((*tree).Category);
	//(*tree).Category = NULL;

	free((*tree).Head);
	(*tree).Head = NULL;
	free((*tree).dimstr);
	(*tree).dimstr = NULL;
	free((*tree).valstr);
	(*tree).valstr = NULL;

	return(0);
}
