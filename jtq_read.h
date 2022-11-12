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
void read_json(struct options *opt, FILE *IN, struct Nd *NdArr){
	int current_C = 0;
	int prev_C = 0;
	int current_Lv = 0;
	int current_Nd = 0;
	int current_NdType = 0;
	int current_CjType = 0;
	int DQ_ESC = 0;
	int BS_ESC = 0;
	char *BUFF = NULL;
	BUFF = alloc_BUFF((*opt).buff);
	BUFF[0] = '\0';
	int C_counter = 0;
	int BUFF_counter = 0;
	while((current_C = fgetc(IN))){
		//counter up
		C_counter++;

		//EOF
		if(current_C == EOF){
			break;
		}

		//check
		// //Nd count
		// //BUFF count
		printf(":<%c><%c>D%dB%d",prev_C,current_C,DQ_ESC,BS_ESC);

		//BUFF operation AND node set
		if((current_C == '[' || current_C == '{') && (DQ_ESC == 0 && BS_ESC == 0)){
			current_Lv++;
			current_Nd++;
		}
		else if((current_C == ',') && (DQ_ESC == 0 && BS_ESC == 0)){
			current_Nd++;
		}
		else if((current_C == ']' || current_C == '}') && (DQ_ESC == 0 && BS_ESC == 0)){
			current_Lv--;
		}
		else {
			BUFF_counter++;
		}

		//current status
		if(current_C == '\\'){
			BS_ESC = 1;
		}else{
			BS_ESC = 0;
		}
		if(current_C == '"' && BS_ESC == 0){
			sw_esc(&DQ_ESC);
		}

		//prev status
		prev_C = current_C;
	}
}
