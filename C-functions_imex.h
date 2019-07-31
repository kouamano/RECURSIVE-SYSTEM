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

// struct LinkTable*	LT;

int SN;			// node count (excluding null node)

char	ch;		// next char of current token
TOKEN	token;		// current token

char*	BUFF;		// string for current token
int	buf_ptr;	// 

struct options *opt;	// pending

void error(char* msg)
{
	perror("[Fail]:syntax error.\n");
	exit(1);
}

//char* alloc_buff()
//{
//	char* bf = malloc(sizeof(char) * BUFF_LEN);
//
//	if(bf == NULL) {
//		error("allloc");
//	} else {
//		return bf;
//	}
//}
	
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

//NODE create_node()
//{
//	return Add_Link_V(LT, -1);	// no parent(link to parent later)
//}

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
/*
bool ident_char(char ch)
{
	return isalnum(ch) || ch == '$' || ch == '#' || ch == '~'|| ch == '`'|| ch == '@';
}
*/

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
	if(token == EOF) {
		error("syntax error");
	}

	clear_buff();

	// skip fist LF/TAB
	while(ch != EOF && (/* ch == ' ' || */ ch == LF || ch ==TAB)) {
		next_char();
	}

	switch(ch) {
	case '(' :
	case ')' :
	case ',' :
	case '@' :
		token = ch;
		append_char(ch);	// append char to BUFF

		next_char();		// get next char
		break;
	case EOF :
		token = ch;
		break;
	default :
		token = 'I';		// identifier

		do {
			switch(ch) {
			case '"' :
				skip_double_quote();	// skip to closing '"'
				break;
			case '[':
				skip_dim();		// skip to closing ']'
				break;
			case LF :			// ignore LF, TAB
			case TAB :
				next_char();
				break;
			default :
				append_char(ch);	// append to header
				next_char();
				break;
			}
		} while(ch != EOF && ch != '(' && ch != ')' && ch != ',' && ch !='@');

		break;
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

#if 0
void next_token()
{
	int DLM_ACC = 1;

	clear_buff();

	// skip blank, etc.
	while(ch != EOF && (ch == ' ' || /* ch == CR ||*/ ch == LF || ch ==TAB)) {
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
#endif

void skip(TOKEN tk)
{
	if(tk == token) {
		next_token();
	} else {
		error("syntax error");
	}
}

void put_value(char* buff, char* value)
{
	int len = strlen(buff);
	buff[len] = ',';
	strcpy(buff+len, value);
}

void parse_bind_values(NODE node)
{
	if(token == '@') {
		int value_count = 0;
		char* data_buff;

		if((data_buff = malloc(sizeof(char) * (*opt).data_buff)) == NULL){
			perror("[]malloc@parse_bind_data.\n");
			exit(1);
		}

		skip('@');
		skip('(');
		
		if(token == 'I') {
			put_value(data_buff, BUFF);
			value_count++;
			skip('I');
		}
		while(token == ',') {
			skip(',');
			if(token == 'I') {
				put_value(data_buff, ",");
				put_value(data_buff, BUFF);
				value_count++;
				skip('I');
			}
		}

		skip(')');	

		set_value_count(node, value_count);
		if(value_count > 0) {
			set_values_str(node, data_buff);
		}

		free(data_buff);
	}

}

//
// return tree for <header>
//
NODE parse_header(int level)
{
	NODE node = alloc_node();	// allocate node for this <header>
	set_level(node, level);		// set buff to <header> node

	if(token != 'I') {		// null node	20190731
		set_head(node, "");
	} else {
		set_head(node, BUFF);	// set buff to <header> node
		Analyze_HeadLabel(node);// SAK Analyze_Head -> Analyze_HeadLabel
		skip('I');		// skip idenifier token
	}				

	if(token=='@') {		// bind operator
		parse_bind_values(node);
	}

	return node;
}

//
// return tree for <T-exp>
//
NODE parseT(int level)
{
	NODE root;	// root node of tree for this <T-exp>
	NODE child;	// child node of root

	root = parse_header(level);	// node for <header>

	// child nodes
	while(token == '(') {
		skip('(');	// skip '('

		child = parseT(level+1);	// 1st child after 	'('

		add_child(root, child);	// add child to root 
		set_conjugate(child, OFF);	// mark as 1st child

		while(token == ',') {
			skip(',');		// skip ','

			child = parseT(level+1);	// 2nd child

			add_child(root, child);		// add child to root 
			set_conjugate(child, ON);	// mark as 2nd child
		}

		skip(')');		// skip ')'
	}

	return root;		// root node of this T-exp
#if 0
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

		// if(token == ')') {		// 20190730
		if(token != 'I') {		// 20190730
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

			if(token != 'I') {		// 20190730
				child = alloc_node();	// 20190730(null node)
				set_head(child, "");	// 20190730
				set_level(child, level+1);	// 20190730
			} else {				// 20190730
				child = parseT(level+1);	// 2nd child
			}					// 20190730

			add_child(root, child);		// add child to root 
			set_conjugate(child, ON);	// mark as 2nd child
		}

		skip(')');		// skip ')'
	}

	return root;		// root node of this T-exp
#endif
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
NODE import_LinkTable(FILE *_IN, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, struct search_options *_sopt, int *ncount, int EXEC_FLAG, FILE *DATA)
{

#ifdef DEBUG
	printf("*** import_linkTable\n");
#endif

	NODE	root;

	// set global ptrs
	IN = _IN;		// input file

	// LT = _LT;		// link table

	SN = *ncount;		// node count (excluding null node)

	opt = _opt;		// options

	// initialize buf
	if((BUFF = malloc(sizeof(char) * (*_opt).buff)) == NULL){
		printf("[Fail] malloc.\n");
		exit(1);
	}
	clear_buff();

	ch =' ';
	next_char();		// ch <- first char
	token = ' ';

	next_token();
	// while(token != EOF) {	// single T-exp allowed
	root = parseT(0);	// parse with level 0
	// skip(LF);
#ifdef DEBUG
	dump_tree(root, 0);
	printf("\n\n");
#endif
	*ncount = SN;

	//}
	
	if(token != EOF) {	// more than one T-exps 
		error("*** syntax error ***\n");
	}

	return root;
}

