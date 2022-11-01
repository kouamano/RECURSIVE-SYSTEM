void put_strSTag_Y(char *buff){
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
void put_strITag_Y(char *buff){
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
void put_strBody_Y(char *buff){
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
void ExPrint_seq_Bl_Y(struct Block *Bl, int target, struct options opt, struct Bl_tree_report report){
	int i;
	int j;
	//start Node
        for(i=target;i<report.Bls;i++){
		//Node = sTag:
		//printf("%d",Bl[i].Lv);
		if((Bl[i].Bltype&BType_Node) == BType_Node){
			for(j=1;j<Bl[i].Lv;j++){
				printf(" ");
			}

			//print conj
			if(i > 0 && (Bl[i-1].Bltype&BType_Node) != BType_Node){
				//printf("%s",",");
			}
			//print str
			put_strSTag_Y(Bl[i].str);
			//print open blacket
			printf("\n");
		}
		//eTag
		if((Bl[i].Bltype&BType_eTag) == BType_eTag){
			//print close blacket
			//printf("%s",ETAG_J);
			//printf("\n");
		}
		//iTag
		if((Bl[i].Bltype&BType_iTag) == BType_iTag){
			for(j=1;j<Bl[i].Lv;j++){
				printf(" ");
			}

			//print conj
			if((Bl[i-1].Bltype&BType_sTag) != BType_sTag && (Bl[i-1].Bltype) != 0){
				//printf("%s",",");
			}
			//print str
			put_strITag_Y(Bl[i].str);
			printf("\n");
		}
		//Body
		if((Bl[i].Bltype&BType_Body) == BType_Body){
			for(j=1;j<Bl[i].Lv;j++){
				printf(" ");
			}

			//print conj
			if((Bl[i-1].Bltype&BType_sTag) != BType_sTag){
				//printf("%s",",");
			}
			//print str
			put_strBody_Y(Bl[i].str);
			printf("\n");
		}

	}
	//last Node
	//printf("\n");
}
