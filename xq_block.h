/* Block type */
int BType_Node = 1;
int BType_sTag = 2;
int BType_eTag = 4;
int BType_iTag = 8;
int BType_Body = 16;

/* tag head and tail */
char THead_CDATA[] = "<![CDATA[";
int Textend_CDATA = 1;
char TTail_CDATA[] = "]]>";
char THead_comment[] = "<!--";
int Textend_comment = 1;
char TTail_comment[] = "-->";
char THead_proc[] = "<?";
int Textend_proc = 1;
char TTail_proc[] = "?>";
char THead_other[] = "<!";
int Textend_other = 1;
char TTail_other[] = "!>";

/* structure */
struct Block {
	int ser;
	int Lv;
	int Bltype;
	int parent;
	char *str;
	int *next_Bl;
};

/* functions */
struct Block *alloc_Block(int size){
	struct Block *p;
	if((p = malloc(sizeof(struct Block) * size)) == NULL){
		perror("alloc_Block()\n");
		exit(1);
	}
	return(p);
}

int check_Block_type(char *BUFF){
	return(0);
}

int set_Block_type(struct Block *Bl, int target_Bl, int type){
	int rt = 0;
	if(((Bl[target_Bl].Bltype)&type) != type){
		Bl[target_Bl].Bltype += type;
		rt = type;
	}
	return(rt);
}

int create_top_Nd(struct Block *Bl){
	Bl[0].ser = 0;
	Bl[0].Lv = 0;
	return(0);
}
