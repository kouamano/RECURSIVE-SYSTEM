void read_tag(int C){
	putchar(C);
}
void read_body(){
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
		if(current_C == '<'){
			in_tag = 1;
		}
		if(current_C == '>'){
			in_tag = 0;
		}
		if(in_tag == 1){
		}
		if(in_tag == 0){
		}
		if(in_tag == -1){
		}
	}
	return(0);
}
