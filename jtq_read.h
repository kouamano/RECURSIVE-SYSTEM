int sw_esc(int *esc){
	if(*esc == 0){
		*esc = 1;
	}else{
		*esc = 0;
	}
	return(*esc);
}
void read_json(struct options *opt, FILE *IN, struct Nd *NdArr, int idx){
	int current_C = 0;
	int prev_C = 0;
	int current_Cj = 0;
	int prev_Cj = 0;

	int current_CjType = 0;
	int current_NdType = 0;
	int current_Lv = 0;
	int current_Pa = -1;
	int tuned_Pa = -1;
	int prev_Pa = -2;
	int current_Nd = 0;

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
		// //Illegal char
		if((current_C == ']' || current_C == '}' || current_C == '[' || current_C == '{' || current_C == ',') && (DQ_ESC == 0 && BS_ESC == 0) && (prev_C == ']' || prev_C == '}')){
		}else{
		}

		// //Nd count

		// //BUFF count

		// //Status print
		printf(":<%c><%c><D%dB%dP%d>:",prev_C,current_C,DQ_ESC,BS_ESC,current_Pa);

		//BUFF operation AND Node set directive
		if((current_C == '[' || current_C == '{') && (DQ_ESC == 0 && BS_ESC == 0)){
			//BUFF to Head & //Node set
			BUFF[BUFF_counter] = '\0';
			BUFF_counter = 0;
			if(prev_C != ']' && prev_C != '}'){
				//Node type
	
				//Parent tune
				tuned_Pa = current_Pa;
	
				//Set Node
				printf("\n<<<%s|N%dP%dL%d>>>\n",BUFF,current_Nd,tuned_Pa,current_Lv);
				set_Nd(opt,NdArr,current_Nd,-1,-1,current_Lv,tuned_Pa,BUFF);
				print_NdStat(opt,NdArr,current_Nd,current_Nd,current_Pa);
	
				//Lv
				current_Lv++;
	
				//Parent operation
				current_Pa = current_Nd;
	
				//Node progress
				current_Nd++;
			}else{
				//Lv
				current_Lv++;

				//Parent operation
				current_Pa = NdArr[current_Nd-1].Pa;
			}
		}
		else if((current_C == ',') && (DQ_ESC == 0 && BS_ESC == 0)){
			//BUFF to Head & //Node set
			BUFF[BUFF_counter] = '\0';
			BUFF_counter = 0;
			if(prev_C != ']' && prev_C != '}'){
				//Node type

				//Set Node
				printf("\n<<<%s|N%dP%dL%d>>>\n",BUFF,current_Nd,current_Pa,current_Lv);
				set_Nd(opt,NdArr,current_Nd,-1,-1,current_Lv,current_Pa,BUFF);
				print_NdStat(opt,NdArr,current_Nd,current_Nd,current_Pa);
				//printf("\n<<<<%s|N%dP%dL%d>>>>\n",NdArr[current_Nd].head,current_Nd,NdArr[current_Nd].Pa,NdArr[current_Nd].Lv);


				//Parent operation
				//-nothing-

				//Node progress
				current_Nd++;

				//Cj operation
				prev_Cj = current_Cj;
				current_Cj = current_C;
			}
		}
		else if((current_C == ']' || current_C == '}') && (DQ_ESC == 0 && BS_ESC == 0)){
			//BUFF to Head & //Node set
			BUFF[BUFF_counter] = '\0';
			BUFF_counter = 0;
			if(prev_C != ']' && prev_C != '}'){
				//Node type
	
				//Set node
				printf("\n<<<%s|N%dP%dL%d>>>\n",BUFF,current_Nd,current_Pa,current_Lv);
				set_Nd(opt,NdArr,current_Nd,-1,-1,current_Lv,current_Pa,BUFF);
				print_NdStat(opt,NdArr,current_Nd,current_Nd,current_Pa);
	
				//Lv
				current_Lv--;
	
				//Parent operation
				current_Pa = NdArr[NdArr[current_Nd].Pa].Pa;
	
				//Node progress
				current_Nd++;
	
				//Cj operation
				prev_Cj = current_Cj;
				current_Cj = current_C;
			}else{
				//Lv
				current_Lv--;

				//Parent operation
				current_Pa = NdArr[current_Nd].Pa;
			}
		}
		else {
			//if(prev_C != ']' && prev_C != '}'){
				BUFF[BUFF_counter] = current_C;
				BUFF_counter++;
			//}
		}

		//Escape status
		if(current_C == '\\'){
			BS_ESC = 1;
		}else{
			BS_ESC = 0;
		}
		if(current_C == '"' && BS_ESC == 0){
			sw_esc(&DQ_ESC);
		}

		//Prev status
		prev_C = current_C;
	}
}
void print_json(struct options *opt, struct Nd *node, int idx_start, int idx_end){
}
