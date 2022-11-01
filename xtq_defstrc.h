#define LEN 1024

/* Block type */
int BType_Unuse = -1;
int BType_Node = 1;
int BType_sTag = 2;
int BType_eTag = 4;
int BType_iTag = 8;
int BType_Body = 16;

/* tag head and tail */
char THead_CDATA[] = "<![CDATA[";
char TTail_CDATA[] = "]]>";
char THead_comment[] = "<!--";
char TTail_comment[] = "-->";
char THead_proc[] = "<?";
char TTail_proc[] = "?>";
char THead_other[] = "<!";
char TTail_other[] = ">";
char THead_emp[] = "<";
char TTail_emp[] = "/>";
char THead_start[] = "<";
char TTail_start[] = ">";
char THead_end[] = "</";
char TTail_end[] = ">";

/* structure */
struct options {
        int help;
        int stat;
        int check;
        char *file;
        int buff;
        int blocks;
        //printt option
        int pt;
        int pn;
        int pb;
        int pbs;
        int ptf;
        int pjf;
        int pyf;
        char *pf;
	char *BH;
	char *BF;
	char *SH;
	char *SF;
};

struct Block {
        //int ser;
        int Lv;
        int Bltype;
        int parent;
        char *str;
        int nexts;
        int *next_Bl;
};

struct Bl_create_opt {
        int str_size;
        int next_nodes;
                //ノードブロックの場合のみ：子ノード追加ごとにreallocする
};

struct Bl_tree_report {
        int Bls;
        int Nds;
        int Chrs;
};

