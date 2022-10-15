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

struct Bl_create_opt {
	int strsize;
	//子ノードを初期に確保、子ノード追加ごとに余裕をチェック、余裕がなければallocする
	int childnodes;
};

/* functions */
struct Block *alloc_Block_arr(int size){
	struct Block *p;
	if((p = malloc(sizeof(struct Block) * size)) == NULL){
		perror("alloc_Block()\n");
		exit(1);
	}
	return(p);
}

int create_Nd(struct Block *Bl, int No, struct Bl_create_opt create_opt){
	Bl[No].ser = 0;
	Bl[No].Lv = 0;
	Bl[No].Bltype = 0;
	Bl[No].parent = -1;
	if((Bl[No].str = malloc(sizeof(char) * create_opt.strsize)) == NULL){
		perror("create_top_Nd");
		exit(1);
	}
	Bl[No].str[0] = '\0';
	return(No);
}

int start_cdata(char *BUFF, const int counter, int in_cdata){
	int start = 0;
	BUFF[counter] = '\0';
	if(strncmp(BUFF,THead_CDATA,strlen(THead_CDATA)) == 0){
		start = 1;
		printf("startCDATA");
	}
	return(start);
}

int end_cdata(char *BUFF, const int counter, int in_cdata){
	int end = 0;
	BUFF[counter] = '\0';
	//if(strncmp(BUFF,THead_CDATA,strlen(THead_CDATA)) == 0){
	if(strncmp(BUFF+strlen(BUFF)-strlen(TTail_CDATA),TTail_CDATA,strlen(TTail_CDATA)) == 0){
		end = 1;
		printf("endCDATA");
	}
	return(end);
}

int check_Block_type(char *BUFF){
	int out = 0;
	//CDATA
	/*
	printf("{{{\n");
	printf(":%s:",BUFF);
	printf(":%s:",THead_CDATA);
	printf(":%s:",BUFF+strlen(BUFF)-strlen(TTail_CDATA));
	printf(":%s:",TTail_CDATA);
	printf(":%d,%d:\n",head_match,tail_match);
	printf("}}}\n");
	*/
	//proc
	//other
	//normal-start
	//normal-end
	//body
	return(out);
}

int set_Block_type(struct Block *Bl, int target_Bl, int type){
	int rt = 0;
	if(((Bl[target_Bl].Bltype)&type) != type){
		Bl[target_Bl].Bltype += type;
		rt = type;
	}
	return(rt);
}


