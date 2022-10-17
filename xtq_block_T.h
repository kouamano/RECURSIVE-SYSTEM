void ExPrint_seq_Bl_T(struct Block *Bl, int target, struct options opt, struct Bl_tree_report report){
	int i;
        for(i=target;i<report.Bls;i++){
		//Node = sTag:
		if((Bl[i].Bltype&BType_Node) == BType_Node){
			//print conj
			if(i > 0 && (Bl[i].Bltype&BType_Node) != BType_Node){
				printf("%s",",");
			}
			//print str
			printf(opt.pf,Bl[i].str);
			//print open blacket
			printf("%s","(");
		}
		//eTag
		if((Bl[i].Bltype&BType_eTag) == BType_eTag){
			printf("%s",")");
		}
	}
}
