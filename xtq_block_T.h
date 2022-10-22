void put_str_T(char *buff){
	int i;
	int len = 0;
	len = strlen(buff);
	putc('"',stdout);
	for(i=0;i<len;i++){
		if(*(buff+i) == '"'){
			putc('"',stdout);
		}
		putc(*(buff+i),stdout);
	}
	putc('"',stdout);
}
void ExPrint_seq_Bl_T(struct Block *Bl, int target, struct options opt, struct Bl_tree_report report){
	int i;
	//start Node
	printf("%s","(");
        for(i=target;i<report.Bls;i++){
		//Node = sTag:
		if((Bl[i].Bltype&BType_Node) == BType_Node){
			//print conj
			if(i > 0 && (Bl[i-1].Bltype&BType_Node) != BType_Node){
				printf("%s",",");
			}
			//print str
			printf(opt.pf,Bl[i].str);
			//print open blacket
			printf("%s","(");
		}
		//eTag
		if((Bl[i].Bltype&BType_eTag) == BType_eTag){
			//print close blacket
			printf("%s",")");
		}
		//iTag
		if((Bl[i].Bltype&BType_iTag) == BType_iTag){
			//print conj
			if((Bl[i-1].Bltype&BType_sTag) != BType_sTag && (Bl[i-1].Bltype) != 0){
				printf("%s",",");
			}
			//print str
			printf(opt.pf,Bl[i].str);
		}
		//Body
		if((Bl[i].Bltype&BType_Body) == BType_Body){
			//print conj
			if((Bl[i-1].Bltype&BType_sTag) != BType_sTag){
				printf("%s",",");
			}
			//print str
			put_str_T(Bl[i].str);
			//printf(opt.pf,Bl[i].str);
		}

	}
	//last Node
	printf("%s",")");
}
