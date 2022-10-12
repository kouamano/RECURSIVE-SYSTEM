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

void check_extend(char *BUFF, int *tag, int *in_cdata, const int counter){
	printf("[in check]");
	BUFF[counter] = '\0';
	if(strncmp(BUFF,THead_CDATA,strlen(THead_CDATA)) == 0){
		if(strncmp(BUFF+strlen(BUFF)-strlen(TTail_CDATA),TTail_CDATA,strlen(TTail_CDATA)) == 0){
			printf("HOGE");
			*tag = -1;
		}else{
			*tag = 0;
			*in_cdata = 1;
		}
	}else{
			*tag = -1;
	}
}

int check_Block_type(char *BUFF, int *type){
	int head_match;
	int tail_match;
	int ext_out = 1;
	head_match = strncmp(BUFF,THead_CDATA,strlen(THead_CDATA));
	tail_match = strncmp(BUFF+strlen(BUFF)-strlen(TTail_CDATA),TTail_CDATA,strlen(TTail_CDATA));
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
	if(head_match == 0 && tail_match == 0){
		*type = BType_iTag;
		ext_out = -1;
		printf("ext_out:%d:",ext_out);
	}
	//comment
	/*
	else if(strncmp(BUFF,THead_comment,strlen(THead_comment)) == 0){
		*type = BType_iTag;
		ext_out = 0;
	}
	*/
	//proc
	//other
	//normal-start
	//normal-end
	//body
	//return(-1);
	return(ext_out);
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
