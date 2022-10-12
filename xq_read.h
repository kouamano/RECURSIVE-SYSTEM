void push_buff(struct options *opt, int C, char *BUFF, int counter){
	//putchar(C);
	//TODO: size check
	BUFF[counter] = (char)C;

}
int read_x(struct options *opt, FILE *IN, struct Block *Bl, int start_Bl, int start_Nd, int start_Lv){
	int current_C = 0;
	int in_tag = 0;
	int TS = 0;
	int TE = 0;
	int TI = 0;
	int BD = 0;
	int ext_cont = 0;
	int current_BlType = 0;
	int current_Bl = start_Bl;
	int current_Nd = start_Nd;
	int current_Lv = start_Lv;
	char *BUFF = NULL;
	int BUFF_counter = 0;
	if((BUFF = malloc(sizeof(char) * (*opt).blocks)) == NULL){
		perror("malloc() for BUFF\n");
		exit(1);
	}
	BUFF[0] = '\0';
	while((current_C = fgetc(IN))){
		if(current_C == EOF){
			BUFF[BUFF_counter] = '\0';
			printf("%s",BUFF);
			break;
		}
		push_buff(opt,current_C,BUFF,BUFF_counter);
		BUFF_counter++;
		if(current_C == '<'){
			if(in_tag == -1){
				in_tag = 1;
			}
		}
		if(current_C == '>'){
			in_tag = 0;
		}
		if(in_tag == 1){
			//if current_C == '<' && BUFF != 0 then create body block
			if(current_C == '<'){
				if(BUFF_counter < 2){
					;
				}else{
					//bodyのcreate
					BUFF[BUFF_counter - 1] = '\0';
					printf("%s$:Lv%d:tag%d\n",BUFF,current_Lv,in_tag);	//createの代わり
					//BUFFクリア、BUFF_counter クリア
					BUFF[0] = '<';
					BUFF_counter = 1;
				}
			}
		}
		if(in_tag == 0){
			in_tag = check_extend(BUFF,&ext_cont);
			//in_tag = -1;
		}
		if(in_tag == -1){
			//if current_C == '>' && BUFF != 0 then create tag block 、タグ種別判定
			//TS/TE/TIが決まる
			if(current_C == '>'){
				//TS/TE/TIを判定
				//TS/TE/TIをBlにset
				//tag Blのcreate
				BUFF[BUFF_counter] = '\0';
				printf("%s#:Lv%d:tag%d\n",BUFF,current_Lv,in_tag);	//createの代わり
				//BUFFクリア、BUFF_counterクリア
				BUFF[0] = '\0';
				BUFF_counter = 0;
				//if tag == TS then Lv++; node生成
				//if tag == TE then Lv--;
				//TS/TE/TIをクリア
			}
		}
		//push_buff(current_C,BUFF,BUFF_counter);
		//BUFF_counter++;
	}
	return(0);
}
