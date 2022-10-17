void Executer(struct Block *Bl, int target_Bl, struct options opt, struct Bl_tree_report report){
	if(opt.pbs == 1){
		ExPrint_seq_BlSt(Bl, target_Bl, opt, report);
	}
	if(opt.pb == 1){
		ExPrint_seq_Bl(Bl,target_Bl,opt,report);
	}
	ExPrint_seq_Bl_T(Bl, target_Bl, opt, report);

}
