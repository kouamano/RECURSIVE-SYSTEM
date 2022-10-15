void push_buff(struct options *opt, int C, char *BUFF, int counter){
	//TODO: size check
	BUFF[counter] = (char)C;

}
int read_x(struct options *opt, FILE *IN, struct Block *Bl, int start_Bl, int start_Nd, int start_Lv){
	int current_C = 0;
	int TS = 0;
	int TE = 0;
	int TI = 0;
	int BD = 0;
	int current_BlType = 0;
	int current_Bl = start_Bl;
	int current_Nd = start_Nd;
	int current_Lv = start_Lv;
	int start_CDATA = 0;
	int end_CDATA = 0;
	int in_cdata = 0;
	char *BUFF = NULL;
	int BUFF_counter = 0;
	if((BUFF = malloc(sizeof(char) * (*opt).blocks)) == NULL){
		perror("malloc() for BUFF\n");
		exit(1);
	}
	BUFF[0] = '\0';
	int in_tag = 0;
	while((current_C = fgetc(IN))){
		if(current_C == EOF){
			BUFF[BUFF_counter] = '\0';
			if(strlen(BUFF) > 0 && (*opt).pt == 1){
				//printf("%s",BUFF);
				printf("%s#(Lv%d:tag%d)\n",BUFF,current_Lv,in_tag);	//createの代わり
			}
			break;
		}
		push_buff(opt,current_C,BUFF,BUFF_counter);
		BUFF_counter++;
		if(current_C == '<'){
			//'<'はタグにのみ含まれるので問答無用で以下
			in_tag = 1;
			//CDATAセクションは開始か
			start_CDATA = start_cdata(BUFF,BUFF_counter,in_cdata);
			in_cdata = start_CDATA;

			printf("{<@tag:%d:}",in_tag);
		}
		if(current_C == '>'){
			//'>'はCDATAタグに含まれる可能性があるので判定が必要
			//とはいえ、tagはとりあえずセットする
			in_tag = -1;
			//CDATAセクションは開始か
			start_CDATA = start_cdata(BUFF,BUFF_counter,in_cdata);
			in_cdata = start_CDATA;
			//CDATAセクションは終わりか
			end_CDATA = end_cdata(BUFF,BUFF_counter,in_cdata);
			if(in_cdata == 1 && end_CDATA == 1){
				in_cdata = 0;
			}
			
			printf("{<@tag:%d:}",in_tag);
		}
		if(in_tag == 0){
			//予備
		}
		if(in_tag == 1 && in_cdata == 0){
			//BODYのprint
			if(current_C == '<'){
				if(BUFF_counter < 2){
					;
				}else{
					//body Blのcreate
					BUFF[BUFF_counter - 1] = '\0';
					printf("%s$(Lv%d:tag%d)\n",BUFF,current_Lv,in_tag);	//createの代わり
					//BUFFクリア、BUFF_counter クリア
					BUFF[0] = '<';
					BUFF_counter = 1;
				}
			}
		}
		if(in_tag == -1 && in_cdata == 0){
			//TAGのprint
			if(current_C == '>'){ //CDATAの途中ではprintしない
				//tag Blのcreate
				BUFF[BUFF_counter] = '\0';
				printf("%s#(Lv%d:tag%d)\n",BUFF,current_Lv,in_tag);	//createの代わり
				//BUFFクリア、BUFF_counterクリア
				BUFF[0] = '\0';
				BUFF_counter = 0;
				//TS/TE/TI判定
				//if tag == TS then Lv++; node生成
				//if tag == TE then Lv--;
				in_tag = 1;
			}
		}
	}
	return(0);
}
