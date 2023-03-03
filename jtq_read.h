int sw_esc(int *esc){
	if(*esc == 0){
		*esc = 1;
	}else{
		*esc = 0;
	}
	return(*esc);
}
struct NdReport *read_json(struct options *opt, FILE *IN, struct Nd *NdArr, int idx){
	struct NdReport *report;
	report = malloc(sizeof(struct NdReport) * 1);
	if(report == NULL){
		perror("malloc:report");
		exit(1);
	}
	int current_C = 0;
	int prev_C = 0;
	int current_CjC = 0;
	int prev_CjC = 0;
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
			//BUFF to Head & //Node set
			BUFF[BUFF_counter] = '\0';
			BUFF_counter = 0;

			//Parent tune
			tuned_Pa = -1;

			set_Nd(opt,NdArr,current_Nd,-1,-1,current_Lv,tuned_Pa,BUFF);
			print_NdStat(opt,NdArr,current_Nd,current_Nd,tuned_Pa);

			//Node progress
			current_Nd++;

			break;
		}

		//check
		// //Illegal char
		if(prev_C == ']' || prev_C == '}'){
			if(current_C == ']' || current_C == '}' || current_C == '[' || current_C == '{' || current_C == ',' || current_C == '\n'){
			}else{
				printf(":IC:");
			}
		}

		// //Nd count

		// //BUFF count

		// //Status print
		printf(":<%c><%c><N%dD%dB%dP%d>:",prev_C,current_C,current_Nd,DQ_ESC,BS_ESC,current_Pa);

		//BUFF operation AND Node set directive
		if((current_C == '[' || current_C == '{') && (DQ_ESC == 0 && BS_ESC == 0)){
			//Conj char
			prev_CjC = current_CjC;
			current_CjC = current_C;

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
			//Conj char
			prev_CjC = current_CjC;
			current_CjC = current_C;

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
			//Conj char
			prev_CjC = current_CjC;
			current_CjC = current_C;

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

	//Report
	(*report).Nds = current_Nd;
	(*report).chars = C_counter;
	return(report);
}
void print_report(struct NdReport *report){
	fprintf(stderr,"Nd:%d\n",(*report).Nds);
	fprintf(stderr,"Ch:%d\n",(*report).chars);
}
void print_node(struct options *opt, struct Nd *node, int idx_start, int idx_end){
	printf("==IN:print_node==\n");
	int i;
	for(i=0;i<idx_end;i++){
		printf("%d<%s><%d><%d><%d>\n",i,node[i].head,node[i].Pa,node[i].Lv,node[i].Ty);
	}
}
void print_json(struct options *opt, struct Nd *node, int idx_start, int idx_end){
	printf("==IN:print_json==\n");
	int i;
	for(i=0;i<idx_end;i++){
		printf("<%d:%s>\n",i,node[i].head);
	}
}

