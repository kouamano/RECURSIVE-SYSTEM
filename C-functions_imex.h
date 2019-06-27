#if 0
//import tree script
int import_LinkTable(FILE *_IN, struct Tree *top, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, int *ncount, struct LinkTable *_LT){
	int WAR;
	int C;
	int DLM_ACC = 1;
	char *BUFF;
	int buf_ptr = 0;
	//struct Tree *current;
	//struct Tree *next;
	int close = 0;
	int ESC = 0;
	//int SN = 1;
	// CQ(
	int vSN = 1;
	int current_SN = vSN;
	int parent_SN = vSN-1;
	int next_SN = vSN+1;
	// )
	WAR = (*_opt).war;
	//current = top;
	//next = NULL;
	if((BUFF = malloc(sizeof(char) * BUFF_LEN)) == NULL){
		printf("[Fail] malloc.\n");
		exit(1);
	}
	whil((C = fgetc(_IN))){
		/* check chars */
		if(WAR > 0){
			//print_war(C,current,WAR);
		}
		/* set conditions */
		if(C == '[' && ESC == 0){
			DLM_ACC--;
		}
		if(C == ']' && ESC == 0){
			DLM_ACC++;
		}
		if(C == '\\'){
			ESC = 1;
		}
		/* function code */
		if(C == '(' && ESC == 0){
			// CQ
			Add_Link_V(_LT,vSN);
			vSN++;

			/* confirm current */
			BUFF[buf_ptr] = '\0';
			if(close == 0){
				//strcpy((*current).Head,BUFF);
			}
			//(*current).Bclose = 0;
			/* check */
			if(WAR > 0){
				//print_war(C,current,WAR);
			}
			/* create next */
			//next = Create_Node(SN,BUFF_LEN);
			//SN++;
			//*ncount = SN;
			/* add next to current / current.NextCount / next.LVself, NCself */
			//Add_Next(current,next);
			/* set properties of next */
			//(*next).Bclose = 0;
			//(*next).Bopen = 1;
			//(*next).Conj = 0;
			/* clear BUFF */
			BUFF[0] = '\0';
			buf_ptr = 0;
			/* set node_parent */
			//parent = current;
			/* set node_current */
			//current = next;
			close = 0;
		}else if(C == ',' && DLM_ACC > 0 && ESC == 0){
			// CQ
			Add_Link_V(_LT,vSN);
			vSN++;

			/* confirm current */
			BUFF[buf_ptr] = '\0';
			if(close == 0){
				//strcpy((*current).Head,BUFF);
			}
			//(*current).Bclose = 0;
			/* check */
			if(WAR > 0){
				//print_war(C,current,WAR);
			}
			/* create next */
			//next = Create_Node(SN,BUFF_LEN);
			//SN++;
			//*ncount = SN;
			/* add next */
			//Add_Next((*current).Parent,next);
			/* set properties of next */
			//(*next).Bclose = 0;
			//(*next).Bopen = 0;
			//(*next).Conj = 1;
			/* clear BUFF */
			BUFF[0] = '\0';
			buf_ptr = 0;
			/* set node_parent */
			// parent = parent;
			/* set node_current */
			//current = next;
			close = 0;
		}else if(C == ')' && ESC == 0){
			/* confirm current */
			BUFF[buf_ptr] = '\0';
			/* Bclose transfar */
			//再帰呼び出し関数ではかっこをprintしないので、
			//かっこのprint情報を子に移す。
			if(close == 0){
				//strcpy((*current).Head,BUFF);
				//(*current).Bclose = 1;
			}else{
				//Add_Bclose_To_Next(current);
			}
			/* check */
			if(WAR > 0){
				//print_war(C,current,WAR);
			}
			/* clear BUFF */
			BUFF[0] = '\0';
			buf_ptr = 0;
			/* set node_parent */
			// parent = parent;
			/* set node_current */
			//if((*current).Parent != NULL){
			//	current = (*current).Parent;
			//}
			close++;
		}else if(C == LF || C == TAB){
			/* 0 single/1 multi/2 individual */
			if((*_opt).form == 0){
				; // executed bellow
			}else if((*_opt).form == 1){
				; // under construction
			}else if((*_opt).form == 2){
				// CQ
				Add_Link_V(_LT,vSN);
				vSN++;
				Function_Print_LinkTable(_LT);

				/* copy BUFF */
				BUFF[buf_ptr] = '\0';
				if(close == 0){
					//strcpy((*current).Head,BUFF);
				}
				/* clear BUFF */
				BUFF[0] = '\0';
				buf_ptr = 0;
				close = 0;
				/* apply functions */
				//#include "T-convFunctions_imex-branch.h"
				/* clear tree */
				//Function_Recursive_FreeForce_Tree(top);
				//free(top);
				//top = Create_Node(SN,BUFF_LEN);
				//SN++;
				//*ncount = SN;
				ESC = 0;
			}
		}else if(C == EOF){
			close = 0;
			ESC = 0;
			if((*_opt).form == 0){
				// CQ
				Add_Link_V(_LT,vSN);
				Function_Print_LinkTable(_LT);

				//#include "T-convFunctions_imex-branch.h"
			}
			return(C);
		}else{
			/* buffering */
			BUFF[buf_ptr] = C;
			BUFF[buf_ptr+1] = '\0';
			buf_ptr++;
			close = 0;
			if(C == '\\'){
				ESC = 1;
			}else{
				ESC = 0;
			}
		}
	}
	return(C);
}
#endif

#define ON		1
#define OFF		0

#define TRUE		1
#define FALSE		0

// typedef int NODE;
typedef char TOKEN;
typedef int bool;

FILE*	IN;

struct LinkTable*	LT;

int SN;			// node count (excluding null node)

char	ch;		// next char of current token
TOKEN	token;		// current token

char*	BUFF;		// string for current token
int	buf_ptr;	// 

void error(char* msg)
{

	printf("msg\n");
	exit(1);
}

char* alloc_buff()
{
	char* bf = malloc(sizeof(char) * BUFF_LEN);

	if(bf == NULL) {
		error("allloc");
	} else {
		return bf;
	}
}
	
void clear_buff()
{
	buf_ptr = 0;
	BUFF[buf_ptr]='\0';
}

void append_char(char ch)
{
	BUFF[buf_ptr] = ch;
	buf_ptr++;
	BUFF[buf_ptr] = '\0';
}	

//
// accessors
//

void setLinkTablePtr(struct LinkTable* lt)
{
	LT = lt;
}

int node_count()
{
	return (*LT).node_count;
}

int ser(NODE node)
{
#ifdef MEM_SER
	return ((*LT).ser)[node];
#else
	return node-1;
#endif
}

void set_ser(NODE node, int ser)
{
#ifdef MEM_SER
	((*LT).ser)[node] = ser;
#endif
}

int level(NODE node)
{
#ifdef MEM_LEVEL
	return ((*LT).level)[node];
#else
	int i=0;
	while(parent(node) != NO_NODE) {
		node=parent(node);
		i++;
	}
	return i;
#endif
}

void set_level(NODE node, int level)
{
#ifdef MEM_LEVEL
	((*LT).level)[node] = level;
#endif
}

int child_no(NODE node)
{
#ifdef MEM_CHILD_NO
	return (LT->child_no)[node];
#else
	NODE p = parent(node);
	if(p==NO_NODE) {
		return 1;       // rot node
	}
	int i;
	for(i=0;i<child_count(p);i++) {
		if(child(p,i) == node)
			return i+1;
	}
	return 1;
#endif
}

void set_child_no(NODE n, int no)
{
#ifdef MEM_CHILD_NO
	(LT->child_no)[n] = no;
#endif
}

NODE parent(NODE n)			// parent of node n
{
	return (LT->parent)[n];
}

void set_parent(NODE n, NODE parent)
{
	(LT->parent)[n] = parent;
}
	

char* head(NODE n)			// head string of node n
{
	return ((*LT).head)[n];
}

char* set_head(NODE n, char* head)	// set head string of node n
{
	char* ptr;

	if(head == NULL) {
		ptr = NULL;
	} else {
		ptr = malloc(sizeof(char) * (strlen(head)+1));

		if(ptr == NULL) {
			error("");
		} else {
			strcpy(ptr, head);
		}

	}

	((*LT).head)[n] = ptr;

	return ptr;
}

char* set_head_ptr(NODE n, char* head)	// set head ptr of node n
{
	((*LT).head)[n] = head;
	return head;
}

int conjugate(NODE n)			// conj flag of node n  (0: fist node, 1: other nodes)
{
	return (LT->conjugate)[n];
}

void set_conjugate(NODE n, int conj)		// conj flag of node n  (0: fist node, 1: other nodes)
{
	(LT->conjugate[n]) = conj;
}

int child_count(NODE n)			// number of children of node n
{
	return (LT->child_count)[n];
}

int set_child_count(NODE n, int count)			// number of children of node n
{
	return (LT->child_count)[n] = count;
}

NODE* children(NODE n)			// children of node n
{
	return (LT->children)[n];
}

NODE child(NODE n, int i)		// ith child of node n
{
	return (LT->children[n])[i];
}

void set_child(NODE n, int i, NODE child)	// set ith child of node n
{
	(LT->children[n])[i]=child;
}

void add_child(NODE parent, NODE child)	// add child to node parent
{
	Add_Link_Memb(LT, parent, child);

	set_parent(child, parent);
	set_child_no(child, child_count(parent));
}

char label_type(NODE node)
{
#ifdef MEM_LABEL_TYPE
	return ((*LT).label_type)[node];
#else
	if(head(node)[0] == '#' && head(node)[1] == '#') {
		return 't';
	} else if(head(node)[0] == '#' && head(node)[1] != '#') {
		return 'h';
	} else {
		return '\0';
	}
#endif
}

void set_label_type(NODE n, char type)
{
#ifdef MEM_LABEL_TYPE
	((*LT).label_type)[n] = type;
#endif
}

int label(NODE node)
{
#ifdef MEM_LABEL
	return ((*LT).label)[node];
#else
	int labelreadprt = 0;
	int labelnumlen = 0;
	int i;
	char *labelnumstr;
	if(head(node)[0] == '#' && head(node)[1] == '#') {
		labelreadprt = 2;
	} else if(head(node)[0] == '#' && head(node)[1] != '#') {
		labelreadprt = 1;
	} else {
		return -1;
	}

	for(i=labelreadprt; (head(node)[i] >= 0x30) && (head(node)[i] <= 0x39);i++){    //Hex
		labelnumlen++;
	}
	if((labelnumstr = malloc(sizeof(char) * (labelnumlen + 1))) == NULL){
		perror("[Fail]malloc@AnalyzeHead\n");
		exit(1);
	}
	strncpy(labelnumstr,head(node)+labelreadprt,labelnumlen);
	labelnumstr[labelnumlen] = '\0';						// SAK
	int wk;
	sscanf(labelnumstr,"%d",&wk);
	free(labelnumstr);
	return wk;
#endif
}

void set_label(NODE node, int label)
{
#ifdef MEM_LABEL
	((*LT).label)[node] = label;
#endif
}

int indicator_pos(NODE node)
{
#ifdef MEM_INDICATOR_POS
	return ((*LT).indicator_pos)[node];
#else
	int labelreadprt=0;
	int i;
	if(head(node)[0] == '#' && head(node)[1] == '#') {
		labelreadprt = 2;
	} else if(head(node)[0] == '#' && head(node)[1] != '#') {
		labelreadprt = 1;
	}

	for(i=labelreadprt; ((i<strlen(head(node))) && (head(node)[i] >= 0x30) && (head(node)[i] <= 0x39));i++){    //Hex
		//i++;
	}
	if(i<strlen(head(node))) {
		return i;
	} else {
		return 0;
	}
#endif
}
	
void set_indicator_pos(NODE node, int pos)
{
#ifdef MEM_INDICATOR_POS
	((*LT).indicator_pos)[node] = pos;
#endif
}

char* dimension_str(NODE node)
{
#ifdef MEM_DIMENSION_STR
	return ((*LT).dimension_str)[node];
#else
	int sw = 0;
	int dim_pos[2];
	char *buff;
	int len = 0;
	if(child_count(node) != 0){			// SAK pending
		return(NULL);
	}
	sw = Detect_DimRegion(head(node),dim_pos);
	if(sw != 2){
		return(NULL);
	}

	// if((buff = malloc(sizeof(char) * (*_opt).buff)) == NULL){
	if((buff = malloc(sizeof(char) * BUFF_LEN))== NULL){
		perror("[Fail]malloc@Detect_DimBlock.\n");
		exit(1);
	}
	buff[0] = '\0';

	len = Print_UpR_Head(node,buff);

	return buff;
#endif
}

char* set_dimension_str(NODE node, char* str)
{ 
#ifdef MEM_DIMENSION_STR
	char* ptr;

	if(str == NULL) {
		ptr = NULL;
	} else {
		ptr = malloc(sizeof(char) * (strlen(str)+1));

		if(ptr == NULL) {
			error("");
		} else {
			strcpy(ptr, str);
		}

	}

	((*LT).dimension_str)[node] = ptr;

	return ptr;
#else
	return NULL;
#endif
}

char* set_dimension_str_ptr(NODE node, char* str)
{
#ifdef MEM_DIMENSION_STR
	((*LT).dimension_str)[node] = str;
	return str;
#else
	return NULL;
#endif
}

int value_count(NODE node)
{
#ifdef MEM_VALUE_COUNT
	return ((*LT).value_count)[node];
#else
	int sw = 0;
	int dim_pos[2];
	char *buff;
	int len = 0;
	if(child_count(node) != 0){
		return(0);
	}
	sw = Detect_DimRegion(head(node),dim_pos);
	if(sw != 2){
		return(0);
	}
	if((buff = malloc(sizeof(char) * BUFF_LEN)) == NULL){
		perror("[Fail]malloc@Detect_DimBlock.\n");
		exit(1);
	}
	buff[0] = '\0';

	len = Print_UpR_Head(node,buff);
	int nval = get_nval(buff);
	free(buff);
	return nval;
#endif
}

void set_value_count(NODE node, int count)
{
#ifdef MEM_VALUE_COUNT
	((*LT).value_count)[node] = count;
#endif
}

int value_pos(NODE node, int i)
{
	return ((*LT).value_poses)[node][i];
}

int* value_poses(NODE node)
{
	return ((*LT).value_poses)[node];
}

int* set_value_poses_ptr(NODE node, int* poses)
{
	((*LT).value_poses)[node] = poses;
	return poses;
}

void set_value_pos(NODE node, int i, int pos)
{
	((*LT).value_poses)[node][i] = pos;
}

char* values_str(NODE node)
{
	return ((*LT).values_str)[node];
}

char* set_values_str(NODE node, char* str)
{
	char* ptr;

	if(str == NULL) {
		ptr = NULL;
	} else {
		ptr = malloc(sizeof(char) * (strlen(str)+1));

		if(ptr == NULL) {
			error("");
		} else {
			strcpy(ptr, str);
		}

	}

	((*LT).values_str)[node] = ptr;

	return ptr;
}

char* set_values_str_ptr(NODE node, char* str)
{
	((*LT).values_str)[node] = str;
	return str;
}

NODE ref_node(NODE node)			// ref node of node n
{
	return ((*LT).ref_node)[node];
}

void set_ref_node(NODE node, NODE ref)	// set ref node of node n
{
	((*LT).ref_node)[node] = ref;
}

int extra_stat(NODE node)
{
	return ((*LT).extra_stat)[node];
}

void set_extra_stat(NODE node, int stat)
{
	((*LT).extra_stat)[node] = stat;
}

NODE create_node()
{
	return Add_Link_V(LT, -1);	// no parent(link to parent later)
}

NODE alloc_node()
{
	// NODE n = LT->node_count;

	// Add_Link_V(LT, -1);	// no parent(link to parent later)

	// set_parent(n, -1);
	// set_child_count(n, 0);
	// set_level(n, 0);
	// set_child_no(n, 1);

	NODE n;
	n = Create_Node(SN, 0);

	SN++;				// node count

	return n;
}

bool ident_char(char ch)
{
	return isalnum(ch) || ch == '$' || ch == '#' || ch == '~'|| ch == '`'|| ch == '@';
}

void next_char()
{
	if(ch == EOF) {
		error("syntax error");
	} else {
		ch = fgetc(IN);
	}
}		

void skip_blank()
{
	while(ch==' ') {
		next_char();
	}
}

void skip_double_quote()
{
	do {
		append_char(ch);			// '"'
		next_char();
		while(ch != EOF && ch != '"') {
			append_char(ch);
			next_char();
		}
		if(ch != EOF) {
			append_char(ch);
			next_char();
		}
	} while(ch == '"');
}

void skip_dim()
{
	int DLM_ACC;

	do {
		append_char(ch);			// '['
		next_char();

		DLM_ACC = 1;

		while(ch != EOF && DLM_ACC > 0) {
			if(ch == '"') {
				skip_double_quote();
			} else {
				switch(ch) {
				case '[':
					DLM_ACC++;
					break;
				case ']':
					DLM_ACC--;
					break;
				// case '\\':
				// 	append_char(ch);
				// 	next_char();
				// 	break;
				default:
					break;
				}

				append_char(ch);
				next_char();
			}
		}
		if(DLM_ACC > 0) {
			error("syntax error");		// EOF before closing ']'
		}
	} while(ch == '[');
}

void next_token()
{
	int DLM_ACC = 1;

	clear_buff();

	// skip blank, etc.
	while(ch != EOF & (ch == ' ' || /* ch == CR ||*/ ch == LF || ch ==TAB)) {
		next_char();
	}

	if(ident_char(ch) || ch == '\\' || ch == '"') {	// identifier
		token = 'I';		

		if(ch == '"') {
			skip_double_quote();
		} else {
			// if(ch == '\\') {
			// 	append_char(ch);
			// 	next_char();
			// }
			append_char(ch);
			next_char();
		}

		while(ident_char(ch) || ch == '\\' || ch == '"' || ch == '[') {
			
			if(ch == '"') {
				skip_double_quote();	// skip to closing '"'
			} else {
				if(ch == '[') {
					skip_dim();		// skip to closing ']'
				} else {
					// if(ch == '\\') {	// skip escape
					//	append_char(ch);
					//	next_char();
					//}
					append_char(ch);	// append char to BUFF
					next_char();
				}
			}
		}
			
	} else {
		switch(ch) {
		case '(' :
		case ')' :
		case ',' :
	//	case CR  : 
	//	case LF  :
			token = ch;
			append_char(ch);	// append char to BUFF

			next_char();		// get next char
		break;
		case EOF :
			token = ch;
			break;
		default :
			error("syntax error");
		}
	}

#ifdef DEBUG
	{
		char tk=token;
		char* bf=BUFF;	

		char wk[1];
		wk[0]='\0';

		switch(tk) {
		case EOF:
			tk = 'E';
			bf = wk;
			break;
		case LF:
			tk = 'L';
			bf = wk;
			break;
		default:
			break;
		}
		printf("token : \'%c\'      \"%s\"\n", tk, bf);
	}
#endif
}

void skip(TOKEN tk)
{
	if(tk == token) {
		next_token();
	} else {
		error("syntax error");
	}
}

//
// return tree for <header>
//
NODE parse_header(int level)
{
	NODE root = alloc_node();	// allocate node for this <header>
	set_head(root, BUFF);		// set buff to <header> node
	set_level(root, level);		// set buff to <header> node

	Analyze_HeadLabel(root);	// SAK Analyze_Head -> Analyze_HeadLabel

	next_token();			// get next token

	return root;
}

//
// return tree for <T-exp>
//
NODE parseT(int level)
{
	NODE root;	// root node of tree for this <T-exp>
	NODE child;	// child node of root

	// root node
	if(token == '(') {
		root = alloc_node();			// null node
		set_head(root, "");
		set_level(root, level);
	} else {
		root = parse_header(level);	// node for <header>
	}

	// child nodes
	while(token == '(') {
		skip('(');	// skip '('

		if(token == ')') {
			child = alloc_node();	// null node
			set_head(child, "");
			set_level(child, level+1);
		} else {
			child = parseT(level+1);	// 1st child after '('
		}

		add_child(root, child);	// add child to root 
		set_conjugate(child, OFF);	// mark as 1st child

		while(token == ',') {
			skip(',');		// skip ','

			child = parseT(level+1);	// 2nd child

			add_child(root, child);	// add child to root 
			set_conjugate(child, ON);	// mark as 2nd child
		}

		skip(')');		// skip ')'
	}

	return root;		// root node of this T-exp
}

#ifdef DEBUG
void dump_node(NODE node)
{

	char cj = (conjugate(node) > 0? '+': '-');

	printf("%c%s               node#:%5d, parent:%5d, child_count:%3d, level:%3d, child_no:%3d\n",
		cj, head(node), node, parent(node), child_count(node), level(node), child_no(node));
}
	
void dump_tree(NODE root, int indent)
{
	int i, c;

	for(i= 0; i<4*indent; i++) {
		printf("%c", ' ');
	}
	
	dump_node(root);
	for(c = 0; c<child_count(root); c++) {
		dump_tree(child(root, c), indent+1);
	}
}
#endif

//import tree script
// NODE import_LinkTable(FILE *_IN, struct Tree *top, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, int *ncount, struct LinkTable *_LT)
NODE import_LinkTable(FILE *_IN, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, struct search_options *_sopt, int *ncount, int EXEC_FLAG, FILE *DATA, struct LinkTable *_LT)
{

#ifdef DEBUG
	printf("*** import_linkTable\n");
#endif

	NODE	root;

	// set global ptrs
	IN = _IN;		// input file

	LT = _LT;		// link table

	SN = *ncount;		// node count (excluding null node)

	// initialize buf
	BUFF = alloc_buff();
	clear_buff();

	ch =' ';

	next_token();
	while(token != EOF) {
	root = parseT(0);	// parse with level 0
	// skip(LF);
#ifdef DEBUG
	dump_tree(root, 0);
	printf("\n\n");
#endif
	*ncount = SN;

	}

	return root;
}

