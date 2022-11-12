int sw_esc(int *esc){
	if(*esc == 0){
		*esc = 1;
	}else{
		*esc = 0;
	}
	return(*esc);
}
void read_json(struct options *opt, FILE *IN){
	int current_C = 0;
	int current_Lv = 0;
	int current_Nd = 0;
	int current_NdType = -1;
	int DQ_ESC = 0;
	int BS_ESC = 0;
	char *BUFF = NULL;
	while((current_C = fgetc(IN))){
	}
}
