/* structures */
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
	char *valstr;
	int NextCount;
	struct Tree **Next;
	struct Tree *Parent;	// must not free !!
	struct Tree *RefNode;
};

struct options {
        int help;
        int stat;
        int check;
        int buff;
        int war;
        char *in;
        char *out;
	char *data;
	int data_buff;
	int Pin;
	int Pout;
        int hF;
        int hC;
        int hS;
        int hD;
};

struct function_options {
        int f_counter;
        int f_print_T;
        int f_print_S;
        int f_print_J;
        int f_print_W;
        int f_print_X;
        int f_print_C;
        int f_print_N;
        int f_print_Ma;
        int f_print_status;
        int f_print_hierarchy;
        int f_print_hierarchy_status;
        int f_print_test;
	int f_print_self_stat;
};

struct compile_options {
	int c_counter;
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

