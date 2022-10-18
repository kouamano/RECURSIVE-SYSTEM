/* functions */
/** alloc **/
struct Block *alloc_Bl_arr(int size){
	struct Block *p;
	if((p = malloc(sizeof(struct Block) * size)) == NULL){
		perror("alloc_Block()\n");
		exit(1);
	}
	return(p);
}

struct Bl_tree_report *alloc_Bl_tree_report(void){
	struct Bl_tree_report *p;
	if((p = malloc(sizeof(struct Bl_tree_report) * 1)) == NULL){
		perror("alloc_Bl_tree_report");
		exit(1);
	}
	return(p);
}

/** create, edit, test **/
int create_Nd(struct Block *Bl, int No, struct Bl_create_opt create_opt){
	//Bl[No].ser = 0;
	Bl[No].Lv = 0;
	Bl[No].Bltype = 0;
	Bl[No].parent = -1;
	if((Bl[No].str = malloc(sizeof(char) * create_opt.str_size)) == NULL){
		perror("create_Nd");
		exit(1);
	}
	Bl[No].str[0] = '\0';
	Bl[No].nexts = 0;
	Bl[No].next_Bl = NULL;
	return(No);
}

int start_cdata(char *BUFF, const int counter, int in_cdata){
	int start = 0;
	BUFF[counter] = '\0';
	if(strncmp(BUFF,THead_CDATA,strlen(THead_CDATA)) == 0){
		start = 1;
		//debug
		//printf("{startCDATA}");
	}
	return(start);
}

int end_cdata(char *BUFF, const int counter, int in_cdata){
	int end = 0;
	BUFF[counter] = '\0';
	if(strncmp(BUFF+strlen(BUFF)-strlen(TTail_CDATA),TTail_CDATA,strlen(TTail_CDATA)) == 0){
		end = 1;
		//debug
		//printf("{endCDATA}");
	}
	return(end);
}

int check_Bl_type(char *BUFF, const int current){
	int out = current;
	//CDATA
	if(strncmp(BUFF,THead_CDATA,strlen(THead_CDATA)) == 0){
		if((out&BType_iTag) != BType_iTag){
			out = BType_iTag;
		}
	}
	//comment itag
	else if((strncmp(BUFF,THead_comment,strlen(THead_comment)) == 0) && (strncmp(BUFF+strlen(BUFF)-strlen(TTail_comment),TTail_comment,strlen(TTail_comment)) == 0)){
		//debug
		//printf("{in_coment}");
		if((out&BType_iTag) != BType_iTag){
			out = BType_iTag;
		}
	}
	//proc itag
	else if((strncmp(BUFF,THead_proc,strlen(THead_proc)) == 0) && (strncmp(BUFF+strlen(BUFF)-strlen(TTail_proc),TTail_proc,strlen(TTail_proc)) == 0)){
		//debug
		//printf("{in_proc}");
		if((out&BType_iTag) != BType_iTag){
			out = BType_iTag;
		}
	}
	//other itag
	else if((strncmp(BUFF,THead_other,strlen(THead_other)) == 0) && (strncmp(BUFF+strlen(BUFF)-strlen(TTail_other),TTail_other,strlen(TTail_other)) == 0)){
		//debug
		//printf("{in_ot}");
		if((out&BType_iTag) != BType_iTag){
			out = BType_iTag;
		}
	}
	//emp itag
	else if((strncmp(BUFF,THead_emp,strlen(THead_emp)) == 0) && (strncmp(BUFF+strlen(BUFF)-strlen(TTail_emp),TTail_emp,strlen(TTail_emp)) == 0)){
		//debug
		//printf("{in_emp}");
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

void set_Block(struct Block *Bl, int No, int type, int lv, int pn, char *buff){
	int len = 0;
	len = strlen(buff);
	if((Bl[No].str = malloc(sizeof(char) * (len+1))) == NULL){
		perror("set_Block\n");
		exit(1);
	}
	strcpy(Bl[No].str,buff);
	Bl[No].Lv = lv;
	Bl[No].Bltype = type;
	Bl[No].parent = pn;
}

/** print **/
void print_tree_report(struct Bl_tree_report *report){
	fprintf(stderr,"==== ==== ==== ==== ====\n");
	fprintf(stderr,"followings were operated:\n");
	fprintf(stderr,"Bls:%d\n",(*report).Bls);
	fprintf(stderr,"Nds:%d\n",(*report).Nds);
	fprintf(stderr,"Chrs:%d\n",(*report).Chrs);
	fprintf(stderr,"==== ==== ==== ==== ====\n");
}

void ExPrint_seq_Bl(struct Block *Bl, int target, struct options opt, struct Bl_tree_report report){
	int i;
	for(i=target;i<report.Bls;i++){
		printf(opt.pf,Bl[i].str);
		if(opt.pn == 1){
			printf("\n");
		}
	}
}

void ExPrint_seq_BlSt(struct Block *Bl, int target, struct options opt, struct Bl_tree_report report){
	int i;
	for(i=target;i<report.Bls;i++){
		printf("%s",opt.SH);
		printf("Bl%d,Ty%d,Lv%d,Pa%d",i,Bl[i].Bltype,Bl[i].Lv,Bl[i].parent);
		printf("%s",opt.SF);
		printf(opt.pf,Bl[i].str);
		if(opt.pn == 1){
			printf("\n");
		}
	}
}

