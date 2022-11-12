int sw_esc(int *esc){
	if(*esc == 0){
		*esc = 1;
	}else{
		*esc = 0;
	}
	return(*esc);
}
char *alloc_BUFF(int size){
	char *p;
	if((p = malloc(sizeof(char) * (size+1))) == NULL){
		perror("alloc buff");
		exit(1);
	}
	return p;
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
		//status
		if(current_C == '\\'){
			BS_ESC = 1;
		}else{
			BS_ESC = 0;
		}
		if(current_C == '"' && BS_ESC == 0){
			sw_esc(&DQ_ESC);
		}
		//check
	}
}
