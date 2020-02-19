#include <string.h>

static struct LinkTable* LT;

struct LinkTable *Alloc_Link_V(struct LinkTable *LT){
	unsigned int size = (*LT).node_count;		// SAK(uint)
	(*LT).head = realloc((*LT).head, sizeof(*(*LT).head) * (size + 1));
	if((*LT).head == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}
#ifdef MEM_LEVEL
	(*LT).level = realloc((*LT).level, sizeof(*(*LT).level) * (size + 1));	// SAK
	if((*LT).level == NULL){							// SAK
		perror("[Fail]:realloc@Alloc_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
#endif

#ifdef MEM_CHILD_NO
	(*LT).child_no = realloc((*LT).child_no, sizeof(*(*LT).child_no) * (size + 1));		// SAK
	if((*LT).child_no == NULL){							// SAK
		perror("[Fail]:realloc@Alloc_Link_V.^\n");			// SAK
		exit(1);							// SAK
	}									// SAK
#endif

	(*LT).conjugate = realloc((*LT).conjugate, sizeof(*(*LT).conjugate) * (size + 1));
	if((*LT).conjugate == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.^\n");
		exit(1);
	}

#ifdef MEM_LABEL_TYPE
	(*LT).label_type = realloc((*LT).label_type, sizeof(*(*LT).label_type) * (size + 1));	// SAK
	if((*LT).label_type == NULL)							{	// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");					// SAK
		exit(1);									// SAK
	}											// SAK
	(*LT).label_type[0] = ' ';								// SAK
#endif

#ifdef MEM_LABEL
	(*LT).label = realloc((*LT).label, sizeof(*(*LT).label) * (size + 1));			// SAK
	if((*LT).label == NULL)							{		// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");					// SAK
		exit(1);									// SAK
	}											// SAK
#endif

#ifdef MEM_INDICATOR_POS
	(*LT).indicator_pos = realloc((*LT).indicator_pos, sizeof(*(*LT).indicator_pos) * (size + 1));	// SAK
	if((*LT).indicator_pos == NULL)							{	// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");					// SAK
		exit(1);									// SAK
	}											// SAK
#endif

	(*LT).child_count = realloc((*LT).child_count, sizeof(*(*LT).child_count) * (size + 1));
	if((*LT).child_count == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.\n");
		exit(1);
	}
        (*LT).child_count[0] = 0;

	(*LT).children = realloc((*LT).children, sizeof(*(*LT).children) * (size + 1));
	if((*LT).children == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.\n");
		exit(1);
	}

	(*LT).children[(*LT).node_count] = NULL;

#ifdef MEM_DIMENSION_STR
	(*LT).dimension_str = realloc((*LT).dimension_str, sizeof(*(*LT).dimension_str) * (size + 1));	// SAK
	if((*LT).dimension_str == NULL){							// SAK
		perror("[Fail]:realloc@Alloc_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
#endif

#ifdef MEM_VALUE_COUNT
	(*LT).value_count = realloc((*LT).value_count, sizeof(*(*LT).value_count) * (size + 1));		// SAK
	if((*LT).value_count == NULL){								// SAK
		perror("[Fail]:realloc@Alloc_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
#endif

	(*LT).value_poses = realloc((*LT).value_poses, sizeof(*(*LT).value_poses) * (size + 1));	// SAK
	if((*LT).value_poses == NULL){									// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");						// SAK
		exit(1);										// SAK
	}												// SAK
													// SAK
	(*LT).value_poses[(*LT).node_count] = NULL;							// SAK

	(*LT).values_str = realloc((*LT).values_str, sizeof(*(*LT).values_str) * (size + 1));	// SAK 
	if((*LT).values_str == NULL){							// SAK 
		perror("[Fail]:realloc@Alloc_Link_V.^\n");				// SAK 
		exit(1);								// SAK 
	}										// SAK

	(*LT).parent = realloc((*LT).parent, sizeof(*(*LT).parent) * (size + 1));
	if((*LT).parent == NULL){
		perror("[Fail]:realloc@Alloc_Link_V.\n");
		exit(1);
	}

	(*LT).ref_node = realloc((*LT).ref_node, sizeof(*(*LT).ref_node) * (size + 1));	// SAK
	if((*LT).ref_node == NULL){							// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");				// SAK
		exit(1);								// SAK
	}										// SAK

	(*LT).extra_stat = realloc((*LT).extra_stat, sizeof(*(*LT).extra_stat) * (size + 1));	// SAK
	if((*LT).extra_stat == NULL){							// SAK
		perror("[Fail]:realloc@Alloc_Link_V.\n");				// SAK
		exit(1);								// SAK
	}										// SAK

	return(LT);
}

NODE Add_Link_V(struct LinkTable *LT, NODE _parent){				// SAK(uint)
	// int size = (*LT).SN;		SAK pending -> close
	unsigned int size = (*LT).node_count;		// SAK			// SAK(uint)
	// int bulk = (*opt).bulk_size;		// SAK pending
	int bulk = 1000000;

	if((*LT).node_count % bulk == 0) {
#ifdef MEM_SER
	(*LT).ser = realloc((*LT).ser, sizeof(*(*LT).ser) * (size + bulk));	// SAK
	if((*LT).ser == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.^\n");			// SAK
		exit(1);							// SAK
	}									// SAK
	(*LT).ser[size] = 0;							// SAK
#endif

	(*LT).head = realloc((*LT).head, sizeof(*(*LT).head) * (size + bulk));
	if((*LT).head == NULL){
		perror("[Fail]:realloc@Add_Link_V.^\n");
		exit(1);
	}
	(*LT).head[size] = NULL;

	(*LT).parent = realloc((*LT).parent, sizeof(*(*LT).parent) * (size + bulk));
	if((*LT).parent == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).parent[size] = (*LT).node_count;

#ifdef MEM_LEVEL
	(*LT).level = realloc((*LT).level, sizeof(*(*LT).level) * (size + bulk));	// SAK
	if((*LT).level == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).level[size] = -1;							// SAK
#endif

#ifdef MEM_CHILD_NO
	(*LT).child_no = realloc((*LT).child_no, sizeof(*(*LT).child_no) * (size + bulk));	// SAK
	if((*LT).child_no == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).child_no[size] = 1;							// SAK
#endif

	(*LT).conjugate = realloc((*LT).conjugate, sizeof(*(*LT).conjugate) * (size + bulk));
	if((*LT).conjugate == NULL){
		perror("[Fail]:realloc@AddLink_V.^\n");
		exit(1);
	}
	(*LT).conjugate[size] = 0;

#ifdef MEM_LABEL_TYPE
	(*LT).label_type = realloc((*LT).label_type, sizeof(*(*LT).label_type) * (size + bulk));	// SAK
	if((*LT).label_type == NULL){								// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");						// SAK
		exit(1);									// SAK
	}											// SAK
	(*LT).label_type[size] = ' ';								// SAK
#endif

#ifdef MEM_LABEL
	(*LT).label = realloc((*LT).label, sizeof(*(*LT).label) * (size + bulk));			// SAK
	if((*LT).label == NULL){								// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");						// SAK
		exit(1);									// SAK
	}											// SAK
	(*LT).label[size] = 0;								// SAK
#endif

#ifdef MEM_INDICATOR_POS
	(*LT).indicator_pos = realloc((*LT).indicator_pos, sizeof(*(*LT).indicator_pos) * (size + bulk));	// SAK
	if((*LT).indicator_pos == NULL){								// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");						// SAK
		exit(1);									// SAK
	}											// SAK
	(*LT).indicator_pos[size] = 0;								// SAK
#endif

	(*LT).child_count = realloc((*LT).child_count, sizeof(*(*LT).child_count) * (size + bulk));
	if((*LT).child_count == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).child_count[size] = 0;

	(*LT).children = realloc((*LT).children, sizeof(*(*LT).children) * (size + bulk));
	if((*LT).children == NULL){
		perror("[Fail]:realloc@Add_Link_V.\n");
		exit(1);
	}
	(*LT).children[size] = NULL;

#ifdef MEM_DIMENSION_STR
	(*LT).dimension_str = realloc((*LT).dimension_str, sizeof(*(*LT).dimension_str) * (size + bulk));		// SAK
	if((*LT).dimension_str == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).dimension_str[size] = NULL;							// SAK
#endif

#ifdef MEM_VALUE_COUNT
	(*LT).value_count = realloc((*LT).value_count, sizeof(*(*LT).value_count) * (size + bulk));		// SAK
	if((*LT).value_count == NULL){								// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");					// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).value_count[size] = 0;								// SAK
#endif

	(*LT).value_poses = realloc((*LT).value_poses, sizeof(*(*LT).value_poses) * (size + bulk));	// SAK
	if((*LT).value_poses == NULL){									// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");							// SAK
		exit(1);										// SAK
	}												// SAK
	(*LT).value_poses[size] = NULL;									// SAK

	(*LT).values_str = realloc((*LT).values_str, sizeof(*(*LT).values_str) * (size + bulk));		// SAK
	if((*LT).values_str == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.^\n");				// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).values_str[size] = NULL;							// SAK

	(*LT).ref_node = realloc((*LT).ref_node, sizeof(*(*LT).ref_node) * (size + bulk));	// SAK
	if((*LT).ref_node == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");					// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).ref_node[size] = NO_NODE;							// SAK

	(*LT).extra_stat = realloc((*LT).extra_stat, sizeof(*(*LT).extra_stat) * (size + bulk));	// SAK
	if((*LT).extra_stat == NULL){							// SAK
		perror("[Fail]:realloc@Add_Link_V.\n");					// SAK
		exit(1);								// SAK
	}										// SAK
	(*LT).extra_stat[size] = 0;							// SAK

	}

	(*LT).node_count++;

	// return(0);									// SAK
	return(size);									// SAK
}

int Add_Link_Memb(struct LinkTable *LT, NODE _parent, int _node_count){
	(*LT).child_count[_parent]++;
	(*LT).children[_parent] = realloc((*LT).children[_parent], sizeof(**(*LT).children) * (*LT).child_count[_parent] );
	(*LT).children[_parent][(*LT).child_count[_parent] -1] = _node_count;	// **SAK**
	return(0);
}

struct LinkTable *Create_LinkTable(int _offset){
	// under construction
	struct LinkTable *LT;
	LT = malloc(sizeof(struct LinkTable) * 1);
	if(LT == NULL){
		perror("[Fail]:malloc@Create_LinkTable.\n");
		exit(1);
	}
/* SAK
	if(((*LT).parent = malloc(sizeof(int) * 1)) == NULL){
		perror("[Fail]:malloc@Create_LinkTable");
		exit(1);
	}
	if(((*LT).Lv = malloc(sizeof(int) * 1)) == NULL){
		perror("[Fail]:malloc@Create_LinkTable");
		exit(1);
	}
*/

	(*LT).offset = _offset;
	(*LT).node_count = 0;
#ifdef MEM_SER
	(*LT).ser = NULL;		// SAK
#endif
	// (*LT).parent[0] = -1;	// SAK
	(*LT).parent = NULL;		// SAK
#ifdef MEM_LEVEL
	// (*LT).Lv[0] = 0;		// SAK
	(*LT).level = NULL;		// SAK
#endif
#ifdef MEM_CHILD_NO
	(*LT).child_no = NULL;		// SAK
#endif
	(*LT).head = NULL;
	(*LT).conjugate = NULL;
#ifdef MEM_LABEL_TYPE
	(*LT).label_type = NULL;		// SAK
#endif
#ifdef MEM_LABEL
	(*LT).label = NULL;		// SAK
#endif
#ifdef MEM_INDICATOR_POS
	(*LT).indicator_pos = NULL;	// SAK
#endif
#ifdef MEM_DIMENSION_STR
	(*LT).dimension_str = NULL;		// SAK
#endif
#ifdef MEM_VALUE_COUNT
	(*LT).value_count = NULL;		// SAK
#endif
	(*LT).value_poses = NULL;		// SAK
	(*LT).values_str = NULL;		// SAK
	(*LT).child_count = NULL;
	(*LT).children = NULL;
	(*LT).ref_node = NULL;		// SAK
	(*LT).extra_stat = NULL;		// SAK
	


	// Alloc_Link_V(LT);		// SAK pending  ->close

	return(LT);
}

// initialize
//
void init_tree()
{
	LT = Create_LinkTable(0);

	if(LT == NULL) {
		perror("[Fail]:Create_LinkTable@init_table.\n");
		exit(1);
	}
}

//
// node creaion
//
NODE create_node()
{
	return Add_Link_V(LT, -1);      // no parent(link to parent later)
}

//
// accessors
//

//
//void setLinkTablePtr(struct LinkTable* lt)
//{
//	LT = lt;
//}

unsigned int node_count()			// SAK(uint)
{
	return (*LT).node_count;
}

unsigned int ser(NODE node)			// SAK(uint)
{
#ifdef MEM_SER
	return ((*LT).ser)[node];
#else
	return node-1;
#endif
}

void set_ser(NODE node, unsigned int ser)	// SAK(uint)
{
#ifdef MEM_SER
	((*LT).ser)[node] = ser;
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

void add_child(NODE parent, NODE child)	// add child to node parent
{
	Add_Link_Memb(LT, parent, child);

	set_parent(child, parent);
	set_child_no(child, child_count(parent));
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
			perror("[Fail]malloc@Head-allocation.\n");
			exit(1);
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
			perror("[Fail]malloc@set_dimension_str.\n");
			exit(1);
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
	int len = strlen(head(node));
	if((len > 0) && (head(node)[len-1] == '@')) {
		return child_count(node);
	} else {
		return ((*LT).value_count)[node];
	}
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
			perror("[Fail]:malloc@set_values_str.^\n");
			exit(1);
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

int Function_Print_LinkTable(struct LinkTable *LT){
	unsigned int i;							// SAK(uint)
	int j;								// SAK(uint)
	printf("Global.offset_SN:%d:\n",(*LT).offset);
	// tq: printf("Global.SN:%d:\n",(*LT).node_count);
	printf("Global.SN:%u:\n",(*LT).node_count);			// SAK(uint)
	// tq: for(i=0;i<(*LT).node_count;i++){
	for(i=0;i<(*LT).node_count;i++){
		// tq: printf("Each[%d].:H=%s:",i,(*LT).head[i]);
		printf("Each[%u].:H=%s:",i,head(i));			// SAK(uint)
		// tq: printf(":Pa=%d:",(*LT).parent[i]);
		printf(":Pa=%u:",parent(i));				// SAK(uint)
		// printf(":Lv=%d:",(*LT).Lv[i]);	// SAK
		// tq: printf(":Lv=%d:",(*LT).level[i]);	// SAK
		printf(":Lv=%d:",level(i));	// SAK
		// tq: printf(":Cj=%d:",(*LT).conjugate[i]);
		printf(":Cj=%d:",conjugate(i));
		// tq: printf(":VC=%d:",(*LT).child_count[i]);
		printf(":VC=%d:",child_count(i));
		printf(":V");
		// tq: for(j=0;j<(*LT).child_count[i];j++){
		for(j=0;j<child_count(i);j++){
			// tq: printf(",%d",(*LT).children[i][j]);
			printf(",%u",child(i,j));			// SAK(uint)
		}
		printf(":\n");
	}
	return(0);
}

/* SAK pending -> closed */
int Free_LinkTable(struct LinkTable *LT){	// SAK pending
	unsigned int i;					// SAK(uint)
	for(i=0;i<(*LT).node_count;i++){
		free((*LT).head[i]);
		//free((*LT).parent);
		//free((*LT).Lv);
		//free((*LT).conjugate);
		//free((*LT).child_count);
		free((*LT).children[i]);
#ifdef MEM_DIMENSION_STR
		free((*LT).dimension_str[i]);
#endif
		free((*LT).value_poses[i]);
		free((*LT).values_str[i]);
	}

#ifdef MEM_SER
	free((*LT).ser);
#endif
	free((*LT).parent);
	// free((*LT).Lv);	// SAK
#ifdef MEM_LEVEL
	free((*LT).level);	// SAK
#endif
#ifdef MEM_CHILD_NO
	free((*LT).child_no);
#endif
	free((*LT).conjugate);
#ifdef MEM_LABEL_TYPE
	free((*LT).label_type);       // SAK rename   t -> tree, h -> head
#endif
#ifdef MEM_LABEL
	free((*LT).label);             // SAK rename
#endif
#ifdef MEM_INDICATOR_POS
	free((*LT).indicator_pos);     // SAK rename
#endif
#ifdef MEM_DIMENSION_STR
	free((*LT).dimension_str);   // SAK rename
#endif
#ifdef MEM_VALUE_COUNT
	free((*LT).value_count);       // SAK rename
#endif
	free((*LT).value_poses);
	free((*LT).values_str);      // SAK rename
	free((*LT).child_count);
	free((*LT).head);
	free((*LT).children);
	free((*LT).ref_node);		// SAK
	free((*LT).extra_stat);		// SAK

	(*LT).offset = 0;
	(*LT).node_count = 0;
	(*LT).parent = NULL;
        // (*LT).Lv = NULL;     // SAK
        // (*LT).level = NULL;  // SAK
	(*LT).conjugate = NULL;
	(*LT).child_count = NULL;
	(*LT).head = NULL;
	(*LT).children = NULL;

	return(0);
}

