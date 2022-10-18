void push_buff(struct options *opt, int C, char *BUFF, int counter){
	//サイズチェックはwhile loop内で行っている
	BUFF[counter] = (char)C;

}
struct Bl_tree_report *read_x(struct options *opt, FILE *IN, struct Block *Bl, int start_Bl, int start_Nd, int start_Lv, int start_PNd, struct Bl_tree_report *report){
	int current_C = 0;
	int C_counter = 0;
	int Nd_counter = 0;
	int current_BType = 0;
	int current_Bl = start_Bl;
	//int current_Nd = start_Nd;
	int current_Lv = start_Lv;
	int current_PNd = start_PNd;
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
		C_counter++;
		if(current_C == EOF){
			if(strlen(BUFF) > 0 && (*opt).pt == 1){
				//debug
				//printf("{<@tag:%d:}",in_tag);
				//printf("%s$(Bl%d:Ty%d:Lv%d:PN%d)\n",BUFF,current_Bl,current_BType,current_Lv,current_PNd);	//createの代わり
				current_Bl++;
				BUFF[BUFF_counter] = '\0';
				current_BType = check_Bl_type(BUFF,current_BType);
				set_Block(Bl,current_Bl,current_BType,current_Lv,current_PNd,BUFF);
			}
			break;
		}
		//Block count check
		if(current_Bl == (*opt).blocks){
			perror("Block creation error.\n");
			exit(1);
		}
		//BUFF size check
		if(BUFF_counter == (*opt).buff){
			perror("BUFF size error.\n");
			exit(1);
		}
		push_buff(opt,current_C,BUFF,BUFF_counter);
		BUFF_counter++;
		if(current_C == '<'){
			//'<'はタグにのみ含まれるので問答無用で以下
			in_tag = 1;
			//CDATAセクションは開始か
			start_CDATA = start_cdata(BUFF,BUFF_counter,in_cdata);
			in_cdata = start_CDATA;
			//debug
			//printf("{<@tag:%d:}",in_tag);
		}
		if(current_C == '>'){
			//'>'はCDATAタグだけでなく含まれる可能性があるので判定が必要
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
			//debug
			//printf("{<@tag:%d:}",in_tag);
		}
		if(in_tag == 0){
			//予備
		}
		if(in_tag == 1 && in_cdata == 0){
			//BODYの処理
			if(current_C == '<'){
				if(BUFF_counter < 2){
					;
				}else{
					current_Bl++;
					//body Blのcreate
					BUFF[BUFF_counter - 1] = '\0';
					//create Bl
					current_BType = check_Bl_type(BUFF,current_BType);
					//debug
					//printf("%s$(Bl%d:Ty%d:Lv%d:PN%d)\n",BUFF,current_Bl,current_BType,current_Lv,current_PNd);	//createの代わり
					set_Block(Bl,current_Bl,current_BType,current_Lv,current_PNd,BUFF);
					//BUFFクリア、BUFF_counter クリア
					BUFF[0] = '<';
					BUFF_counter = 1;
				}
			}
		}
		if(in_tag == -1 && in_cdata == 0){
			//TAGの処理
			if(current_C == '>'){ //CDATAの途中ではprintしない
				current_Bl++;
				//tag Blのcreate
				BUFF[BUFF_counter] = '\0';
				current_BType = check_Bl_type(BUFF,current_BType);
				//debug
				//printf("%s#(Bl%d:Ty%d:Lv%d:PN%d)\n",BUFF,current_Bl,current_BType,current_Lv,current_PNd);	//createの代わり
				set_Block(Bl,current_Bl,current_BType,current_Lv,current_PNd,BUFF);
				//current_LvをセットしたのちにLv up
				if((current_BType&BType_sTag) == BType_sTag){
					current_Lv++;
					current_PNd = current_Bl;
				}
				if((current_BType&BType_eTag) == BType_eTag){
					current_Lv--;
					//current_PNd
					current_PNd = Bl[(Bl[current_Bl].parent)].parent;
				}
				if((current_BType&BType_Node) == BType_Node){
					Nd_counter++;
				}
				//BUFFクリア、BUFF_counterクリア
				BUFF[0] = '\0';
				BUFF_counter = 0;
				in_tag = 1;
			}
		}
	}
	(*report).Bls = current_Bl+1;	//topノードを足す
	(*report).Nds = Nd_counter+1;	//topノードを足す
	(*report).Chrs = C_counter;
	return(report);
}
