void Executer(struct Block *Bl, int target_Bl, struct options opt, struct Bl_tree_report report){
	int output = 0;
	if(opt.pbs == 1){
		ExPrint_seq_BlSt(Bl, target_Bl, opt, report);
		int output = 1;
	}
	if(output > 0){
		printf("\n==== ==== ==== ====\n");
	}
	if(opt.pb == 1){
		ExPrint_seq_Bl(Bl,target_Bl,opt,report);
		int output = 1;
	}
	if(output > 0){
		printf("\n==== ==== ==== ====\n");
	}
	if(opt.ptf == 1){
		ExPrint_seq_Bl_T(Bl, target_Bl, opt, report);
		int output = 1;
	}
}
