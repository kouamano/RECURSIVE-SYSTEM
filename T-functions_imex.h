//import tree script
struct Tree *import_Tree(FILE *IN, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, struct search_options *_sopt, int *ncount, int EXEC_FLAG, FILE *DATA){
	int WAR;
	int C;
	int DLM_ACC = 1;
	char *BUFF;
	int buf_ptr = 0;
	int buff_size = 0;
	struct Tree *io_top;
	struct Tree *current;
	struct Tree *next;
	int close = 0;
	int ESC = 0;
	int SN = *ncount;
	io_top = Create_Node(SN,0);
	SN++;
	*ncount = SN;

	WAR = (*_opt).war;
	current = io_top;
	next = NULL;
	if((BUFF = malloc(sizeof(char) * (*_opt).buff)) == NULL){
		printf("[Fail] malloc.\n");
		exit(1);
	}
	while((C = fgetc(IN))){
		/* check chars */
		if(WAR > 0){
			print_war(C,current,WAR);
		}
		/* set conditions */
		if(C == '[' && ESC == 0){
			DLM_ACC--;
		}
		if(C == ']' && ESC == 0){
			DLM_ACC++;
		}
		if(C == '\\'){
			ESC = 1;
		}
		/* function code */
		if(C == '(' && ESC == 0){
			/* confirm current */
			BUFF[buf_ptr] = '\0';
			buff_size = 0;
			buff_size = strlen(BUFF);
			//printf(";%d;",buff_size);
			if(close == 0){
				if(((*current).Head = malloc(sizeof(char) * (buff_size + 1))) == NULL){
					perror("[Fail]malloc@Head-allocation.\n");
					exit(1);
				}
				strcpy((*current).Head,BUFF);
				AnalyzeHead(current);
			}
			/* check */
			if(WAR > 0){
				print_war(C,current,WAR);
			}
			/* create next */
			next = Create_Node(SN,0);
			SN++;
			*ncount = SN;
			/* add next to current / current.NextCount / next.LVself, NCself */
			Add_Next(current,next);
			/* set properties of next */
			(*next).Conj = 0;
			/* clear BUFF */
			BUFF[0] = '\0';
			buf_ptr = 0;
			/* set node_parent */
			//parent = current;
			/* set node_current */
			current = next;
			close = 0;
		}else if(C == ',' && DLM_ACC > 0 && ESC == 0){
			/* confirm current */
			BUFF[buf_ptr] = '\0';
			buff_size = 0;
			buff_size = strlen(BUFF);
			if(close == 0){
				if(((*current).Head = malloc(sizeof(char) * (buff_size + 1))) == NULL){
					perror("[Fail]malloc@Head-allocation.\n");
					exit(1);
				}
				strcpy((*current).Head,BUFF);
				AnalyzeHead(current);
			}
			/* check */
			if(WAR > 0){
				print_war(C,current,WAR);
			}
			/* create next */
			next = Create_Node(SN,0);
			SN++;
			*ncount = SN;
			/* add next */
			Add_Next((*current).Parent,next);
			/* set properties of next */
			(*next).Conj = 1;
			/* clear BUFF */
			BUFF[0] = '\0';
			buf_ptr = 0;
			/* set node_parent */
			// parent = parent;
			/* set node_current */
			current = next;
			close = 0;
		}else if(C == ')' && ESC == 0){
			/* confirm current */
			BUFF[buf_ptr] = '\0';
			buff_size = 0;
			buff_size = strlen(BUFF);
			if(close == 0){
				if(((*current).Head = malloc(sizeof(char) * (buff_size + 1))) == NULL){
					perror("[Fail]malloc@Head-allocation.\n");
					exit(1);
				}
				strcpy((*current).Head,BUFF);
				AnalyzeHead(current);
			}
			/* check */
			if(WAR > 0){
				print_war(C,current,WAR);
			}
			/* clear BUFF */
			BUFF[0] = '\0';
			buf_ptr = 0;
			/* set node_parent */
			// parent = parent;
			/* set node_current */
			if((*current).Parent != NULL){
				current = (*current).Parent;
			}
			close++;
		}else if(C == LF || C == TAB){	//ignore chars 
			;
		}else if(C == EOF){
			BUFF[buf_ptr] = '\0';
			buff_size = 0;
			buff_size = strlen(BUFF);
			if(close == 0){
				if(((*current).Head = malloc(sizeof(char) * (buff_size + 1))) == NULL){
					perror("[Fail]malloc@Head-allocation.\n");
					exit(1);
				}
				strcpy((*current).Head,BUFF);
				AnalyzeHead(current);
			}
			close = 0;
			ESC = 0;
			return(io_top);
		}else{
			/* buffering */
			BUFF[buf_ptr] = C;
			BUFF[buf_ptr+1] = '\0';
			buf_ptr++;
			close = 0;
			if(C == '\\'){
				ESC = 1;
			}else{
				ESC = 0;
			}
		}
	}
	return(io_top);
}


