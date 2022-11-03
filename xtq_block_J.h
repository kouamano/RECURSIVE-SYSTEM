#define STAG_topJJ "["
#define ETAG_topJJ "]"
#define STAG_J "{"
#define ETAG_J "}"
void put_strSTag_J(char *buff){
	int i;
	int len = 0;
	len = strlen(buff);
	putc('"',stdout);
	for(i=0;i<len;i++){
		if(*(buff+i) == '"'){
			putc('\\',stdout);
		}
		putc(*(buff+i),stdout);
	}
	putc('"',stdout);
	putc(':',stdout);
}
void put_strITag_J(char *buff){
	int i;
	int len = 0;
	len = strlen(buff);
	putc('"',stdout);
	for(i=0;i<len;i++){
		if(*(buff+i) == '"'){
			putc('\\',stdout);
		}
		putc(*(buff+i),stdout);
	}
	putc('"',stdout);
	printf("%s",":{}");
}
void put_strBody_J(char *buff){
	int i;
	int len = 0;
	len = strlen(buff);
	putc('"',stdout);
	for(i=0;i<len;i++){
		if(*(buff+i) == '"'){
			putc('\\',stdout);
			putc(*(buff+i),stdout);
		}else if(*(buff)+i == '\n'){
			putc(' ',stdout);
			//putc(*(buff+i),stdout);
		}else{
			putc(*(buff+i),stdout);
		}
	}
	putc('"',stdout);
	printf("%s",":[]");
}
void ExPrint_seq_Bl_JJ(struct Block *Bl, int target, struct options opt, struct Bl_tree_report report){
	int i;
	//start Node
	printf("%s",STAG_topJJ);
        for(i=target;i<report.Bls;i++){
		//Node = sTag:
		if((Bl[i].Bltype&BType_Node) == BType_Node){
			//print conj
			if(i > 0 && (Bl[i-1].Bltype&BType_Node) != BType_Node){
				printf("%s",",");
			}
			//print str
			put_strSTag_J(Bl[i].str);
			//print open blacket
			printf("%s",STAG_J);
		}
		//eTag
		if((Bl[i].Bltype&BType_eTag) == BType_eTag){
			//print close blacket
			printf("%s",ETAG_J);
		}
		//iTag
		if((Bl[i].Bltype&BType_iTag) == BType_iTag){
			//print conj
			if((Bl[i-1].Bltype&BType_sTag) != BType_sTag && (Bl[i-1].Bltype) != 0){
				printf("%s",",");
			}
			//print str
			put_strITag_J(Bl[i].str);
		}
		//Body
		if((Bl[i].Bltype&BType_Body) == BType_Body){
			//print conj
			if((Bl[i-1].Bltype&BType_sTag) != BType_sTag){
				printf("%s",",");
			}
			//print str
			put_strBody_J(Bl[i].str);
		}

	}
	//last Node
	printf("%s",ETAG_J);
}
void ExPrint_seq_Bl_J(struct Block *Bl, int target, struct options opt, struct Bl_tree_report report){
	int i;
	//start Node
	printf("%s",STAG_topJJ);
        for(i=target;i<report.Bls;i++){
		//Node = sTag:
		if((Bl[i].Bltype&BType_Node) == BType_Node){
			//print conj
			if(i > 0 && (Bl[i-1].Bltype&BType_Node) != BType_Node){
				printf("%s",",");
			}
			//print str
			put_strSTag_J(Bl[i].str);
			//print open blacket
			printf("%s",STAG_J);
		}
		//eTag
		if((Bl[i].Bltype&BType_eTag) == BType_eTag){
			//print close blacket
			printf("%s",ETAG_J);
		}
		//iTag
		if((Bl[i].Bltype&BType_iTag) == BType_iTag){
			//print conj
			if((Bl[i-1].Bltype&BType_sTag) != BType_sTag && (Bl[i-1].Bltype) != 0){
				printf("%s",",");
			}
			//print str
			put_strITag_J(Bl[i].str);
		}
		//Body
		if((Bl[i].Bltype&BType_Body) == BType_Body){
			//print conj
			if((Bl[i-1].Bltype&BType_sTag) != BType_sTag){
				printf("%s",",");
			}
			//print str
			put_strBody_J(Bl[i].str);
		}

	}
	//last Node
	printf("%s",ETAG_topJJ);
}
