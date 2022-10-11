void push_buff(int C, char *BUFF, int counter){
	//putchar(C);
	BUFF[counter] = (char)C;

}
int read_x(struct options *opt, FILE *IN, struct Block *Bl, int start_Bl, int start_Nd, int start_Lv){
	int current_C = 0;
	int in_tag = 0;
	int TS = 0;
	int TE = 0;
	int TI = 0;
	int BD = 0;
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
			break;
		}
		push_buff(current_C,BUFF,BUFF_counter);
		BUFF_counter++;
		if(current_C == '<'){
			in_tag = 1;
		}
		if(current_C == '>'){
			in_tag = 0;
		}
		if(in_tag == 1){
			if(current_C == '<'){
			//bodyのcreate
			//if current_C == '<' && BUFF != 0 then create body block
			}
		}
		if(in_tag == 0){
			//extend check
				//タグ種別ごとに
			//extendあり: 最後まで読み込む; in_tag = -1
			//extendなし: in_tag = -1
			//TS/TE/TIが決まる
		}
		if(in_tag == -1){
			if(current_C == '>'){
			//tagのcreate
			//if current_C == '>' && BUFF != 0 then create tag block 、タグ種別判定
				//if tag == TS then Lv++; node生成
				//if tag == TE then Lv--;
			//TS/TE/TIをクリア
			}
		}
	}
	return(0);
}
//TODO: BUFF_counterの扱い
