/* structures */

/*							// SAK
struct Tree {
	int ser;
	int LVself;
	int NCself;
	int Conj;
	char LabelType;		//t -> tree, h -> head
	int Label;
	int IndicatorPtr;
	char *Head;
	char *dimstr;
	int nval;
	int *valPtr;
	char *valstr;
	int NextCount;
	struct Tree **Next;
	struct Tree *Parent;	// must not free !!
	struct Tree *RefNode;
	int extra_stat;
		//1: $~~,$~ -> avoid compile;	2: $PI$ -> skip Next
		//4: $`` -> quating tree;	8: $U$
		//16: $UU$
};
*/

//typedefs
typedef unsigned int NODE;			// SAK (uint)

#define	NO_NODE 0				// SAK (uint) -1 -> 0

//structure
//// Conj-table
struct LinkTable {
	// global
	int offset;		// SAK rename
	unsigned int node_count;		// SAK rename	// SAK (uint)
	// each node
#ifdef MEM_SER
	unsigned int *ser;		// SAK rename			// SAK (uint)
#endif
	NODE *parent;		// SAK NODE rename
#ifdef MEM_LEVEL
	int *level;		// SAK rename
#endif
#ifdef MEM_CHILD_NO
	int *child_no;		// SAK rename
#endif
	char **head;		// SAK rename
	int *conjugate;		// SAK rename
#ifdef MEM_LABEL_TYPE
	char *label_type;	// SAK rename	t -> tree, h -> head
#endif
#ifdef MEM_LABEL
	int *label;		// SAK rename
#endif
#ifdef MEM_INDICATOR_POS
	int *indicator_pos;	// SAK rename
#endif
#ifdef MEM_DIMENSION_STR
	char **dimension_str;	// SAK rename
#endif
#ifdef MEM_VALUE_COUNT
	int *value_count;	// SAK rename
#endif
	int **value_poses;	// SAK rename
	char **values_str;	// SAK rename
	int *child_count;	// SAK rename
	NODE **children;	// SAK NODE rename
	NODE *ref_node;		// SAK NODE rename
        int *extra_stat;
		//1: $~~$,$~$ -> avoid compile;   2: $PI$ ; skipNext 兼用
		//4: $``$ -> quating tree;	8: $U$, $UU$
};

#if 0		// extern -> not needed
extern void init_tree();

//
// accessors
//
extern NODE create_node();

extern int node_count();

extern int ser(NODE n);
extern void set_ser(NODE n, int ser);

extern int level(NODE n);
extern void set_level(NODE n, int level);

extern int child_no(NODE n);
extern void set_child_no(NODE n, int no);

extern NODE parent(NODE n);			// parent of node n
extern void set_parent(NODE n, NODE parent);
	
extern char* head(NODE n);			// head string of node n
extern char* set_head(NODE n, char* head);	// set head string of node n
extern char* set_head_ptr(NODE n, char* head);	// set head string of node n

extern int conjugate(NODE n);			// conj flag of node n  (0: fist node, 1: other nodes)
extern void set_conjugate(NODE n, int conj);	// conj flag of node n  (0: fist node, 1: other nodes)

extern int child_count(NODE n);			// number of children of node n
extern int set_child_count(NODE n, int count);	// number of children of node n

extern NODE* children(NODE n);			// children of node n
extern NODE child(NODE n, int i);		// ith child of node n
extern void set_child(NODE n, int i, NODE child);		// ith child of node n
extern void add_child(NODE parent, NODE child);	// add child to node parent

extern char label_type(NODE n);			// label type of node n
extern void set_label_type(NODE n, char type);	// label type o noe n

extern int label(NODE n);
extern void set_label(NODE n, int label);

extern int indicator_pos(NODE n);
extern void set_indicator_pos(NODE n, int pos);

extern char* dimension_str(NODE n);
extern char* set_dimension_str(NODE n, char* str);
extern char* set_dimension_str_ptr(NODE n, char* str);

extern int value_count(NODE n);
extern void set_value_count(NODE n, int count);

extern int* value_poses(NODE n);
extern int* set_value_poses_ptr(NODE n, int* poses);
extern int value_pos(NODE n, int i);
extern void set_value_pos(NODE n, int i, int pos);

extern char* values_str(NODE n);
extern char* set_values_str(NODE n, char* str);
extern char* set_values_str_ptr(NODE n, char* str);

extern NODE ref_node(NODE n);			// ref node of node n
extern void set_ref_node(NODE n, NODE ref);	// set ref node of node n

extern int extra_stat(NODE n);
extern void set_extra_stat(NODE n, int stat);

extern NODE alloc_node();
#endif
struct options {
        int help;
        int stat;
        int check;
        int war;
	int test;
        char *in;
        char *out;
	char *data;
        int buff;
	int data_buff;
	int Pin;
	int Pout;
	int Pprod;
        int hF;
        int hC;
        int hS;
        int hD;
	int hE;
};

struct function_options {
        int f_counter;
        int f_print_T;
        int f_print_S;
        int f_print_J;
        int f_print_W;
		// 1 : normal,	2 : fill "List" when head is null str.
        int f_print_X;
        int f_print_C;
        int f_print_N;
        int f_print_Ma;
        int f_print_production;
        int f_print_status;
        int f_print_hierarchy;
        // int f_print_hierarchy_status;
        int f_print_test;
	int f_print_self_stat;

	int f_skipOnce;
		// 1 : Function_Print_Conj_T
};

struct compile_options {
	int c_counter;
	int c_list;
	int c_restrict;
	int c_clear;
	int c_dot;
};

struct search_options {
	int s_counter;
	char *pos;
	char *head;
};

struct data_options {
	int d_counter;
	char dd;
};

struct reform_options {
	int r_counter;
};

