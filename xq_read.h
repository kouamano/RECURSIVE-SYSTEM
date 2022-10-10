int read_x(struct options *opt, FILE *IN, struct Block *Bl, int start_Bl, int start_Nd, int start_Lv){
	int current_C = 0;
	int in_tag = 0;
	int TO = 0;
	int TC = 0;
	int TI = 0;
	int BD = 0;
	int current_Bl = start_Bl;
	int current_Nd = start_Nd;
	int current_Lv = start_Lv;
	char *BUFF = NULL;
	if((BUFF = malloc(sizeof(char) * (*opt).blocks)) == NULL){
		perror("malloc() for BUFF\n");
		exit(1);
	}
	while((current_C = fgetc(IN))){
		if(current_C == EOF){
			break;
		}
	}
	return(0);
}
