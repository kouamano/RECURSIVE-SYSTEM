/* Block type */
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
struct Block {
	int ser;
	int Lv;
	int Bltype;
	int parent;
	char *str;
	int *next_Bl;
};

struct Bl_create_opt {
	int str_size;
	int next_nodes;
		//ノードブロックの場合のみ：子ノードを初期に確保、子ノード追加ごとに余裕をチェック、余裕がなければallocする
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
	if((Bl[No].str = malloc(sizeof(char) * create_opt.str_size)) == NULL){
		perror("create_Nd");
		exit(1);
	}
	Bl[No].str[0] = '\0';
	if((Bl[No].next_Bl = malloc(sizeof(int) * create_opt.next_nodes)) == NULL){
		perror("create_Nd");
		exit(1);
	}
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

int check_Block_type(char *BUFF, const int current){
	int out = current;
	//CDATA
	if(strncmp(BUFF,THead_CDATA,strlen(THead_CDATA)) == 0){
		if((out&BType_iTag) != BType_iTag){
			out = BType_iTag;
		}
	}
	//comment itag
	else if((strncmp(BUFF,THead_comment,strlen(THead_comment)) == 0) && (strncmp(BUFF+strlen(BUFF)-strlen(TTail_comment),TTail_comment,strlen(TTail_comment)) == 0)){
		printf("in_coment");
		if((out&BType_iTag) != BType_iTag){
			out = BType_iTag;
		}
	}
	//proc itag
	else if((strncmp(BUFF,THead_proc,strlen(THead_proc)) == 0) && (strncmp(BUFF+strlen(BUFF)-strlen(TTail_proc),TTail_proc,strlen(TTail_proc)) == 0)){
		printf("in_proc");
		if((out&BType_iTag) != BType_iTag){
			out = BType_iTag;
		}
	}
	//other itag
	else if((strncmp(BUFF,THead_other,strlen(THead_other)) == 0) && (strncmp(BUFF+strlen(BUFF)-strlen(TTail_other),TTail_other,strlen(TTail_other)) == 0)){
		printf("in_ot");
		if((out&BType_iTag) != BType_iTag){
			out = BType_iTag;
		}
	}
	//emp itag
	else if((strncmp(BUFF,THead_emp,strlen(THead_emp)) == 0) && (strncmp(BUFF+strlen(BUFF)-strlen(TTail_emp),TTail_emp,strlen(TTail_emp)) == 0)){
		printf("in_emp");
		if((out&BType_iTag) != BType_iTag){
			out = BType_iTag;
		}
	}
	//end tag
	else if((strncmp(BUFF,THead_end,strlen(THead_end)) == 0) && (strncmp(BUFF+strlen(BUFF)-strlen(TTail_end),TTail_end,strlen(TTail_end)) == 0)){
		if((out&BType_eTag) != BType_eTag){
			out = BType_eTag;
		}
	}
	//start tag
	else if((strncmp(BUFF,THead_start,strlen(THead_start)) == 0) && (strncmp(BUFF+strlen(BUFF)-strlen(TTail_start),TTail_start,strlen(TTail_start)) == 0)){
		if((out&BType_sTag) != BType_sTag){
			out = BType_sTag+BType_Node;
		}
	}
	//body
	else{
		if((out&BType_Body) != BType_Body){
			out = BType_Body;
		}
	}

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


