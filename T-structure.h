//structure
struct Tree {
	int numIDX;
	int *IDX;
	int LVself;
	int NCself;
	int Conj;
	int Bopen;
	char *Head;
	int Bclose;
	int NextCount;
	struct Tree **Next;
	struct Tree *Parent;	// must not free !!
};

struct options {
        int help;
        int stat;
        int check;
        int buff;
        int war;
        char *in;
	int form;
        int hF;
        int hC;
};

struct function_options {
        int f_counter;
        int f_print_T;
        int f_print_S;
        int f_print_J;
        int f_print_W;
        int f_print_Ma;
        int f_print_status;
        int f_print_hierarchy;
        int f_print_hierarchy_status;
};

struct compile_options {
	int c_counter;
        int c_wolfram;
};

