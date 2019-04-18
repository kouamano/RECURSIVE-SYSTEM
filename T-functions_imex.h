//import tree script
int import_Tree(FILE *IN, struct Tree *top, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, struct search_options *_sopt, int *ncount, int EXEC_FLAG, int *t_array_count, struct Tree **TA){
	int WAR;
	int C;
	int DLM_ACC = 1;
	char *BUFF;
	int buf_ptr = 0;
	struct Tree *current;
	struct Tree *next;
	int close = 0;
	int ESC = 0;
	int SN = 1;
	/* for search function */
        struct Tree *null_node;
	null_node = Create_Node(-1,(*_opt).buff);
	strcpy((*null_node).Head,"$NULL$");
	(*null_node).LVself = -1;
	(*null_node).NCself = 1;

	WAR = (*_opt).war;
	current = top;
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
			if(close == 0){
				strcpy((*current).Head,BUFF);
				AnalyzeHead(current);
			}
			/* check */
			if(WAR > 0){
				print_war(C,current,WAR);
			}
			/* create next */
			next = Create_Node(SN,(*_opt).buff);
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
			if(close == 0){
				strcpy((*current).Head,BUFF);
				AnalyzeHead(current);
			}
			/* check */
			if(WAR > 0){
				print_war(C,current,WAR);
			}
			/* create next */
			next = Create_Node(SN,(*_opt).buff);
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
			if(close == 0){
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
		}else if(C == LF || C == TAB){
			/* 0:single / 1:multi / 2:individual */
			if(EXEC_FLAG == 0){
			if((*_opt).in_form == 0){
				; // executed bellow
			}else if((*_opt).in_form == 1){
				; // under construction
			}else if((*_opt).in_form == 2){
				/* copy BUFF */
				BUFF[buf_ptr] = '\0';
				if(close == 0){
					strcpy((*current).Head,BUFF);
					AnalyzeHead(current);
				}
				/* clear BUFF */
				BUFF[0] = '\0';
				buf_ptr = 0;
				close = 0;
				/* apply functions */
				Executor(top, null_node, C, SN, _opt, _fopt, _copt, _sopt);
				/* clear tree */
				Function_Recursive_FreeForce_Tree(top);
				free(top);
				top = Create_Node(SN,(*_opt).buff);
				SN++;
				*ncount = SN;
				ESC = 0;
			}
			}else if(EXEC_FLAG == 1){
			if((*_opt).in_form == 0){
				; // executed bellow
			}else if((*_opt).in_form == 1){
				; // under construction
			}else if((*_opt).in_form == 2){
				/* copy BUFF */
				BUFF[buf_ptr] = '\0';
				if(close == 0){
					strcpy((*current).Head,BUFF);
					AnalyzeHead(current);
				}
				/* clear BUFF */
				BUFF[0] = '\0';
				buf_ptr = 0;
				close = 0;
				/* apply functions */
				Executor(top, null_node, C, SN, _opt, _fopt, _copt, _sopt);
				/* clear tree */
				Function_Recursive_FreeForce_Tree(top);
				free(top);
				top = Create_Node(SN,(*_opt).buff);
				SN++;
				*ncount = SN;
				ESC = 0;
			}
			}
		}else if(C == EOF){
			close = 0;
			ESC = 0;
			if(EXEC_FLAG == 0){
			if((*_opt).in_form == 0){
				Executor(top, null_node, C, SN, _opt, _fopt, _copt, _sopt);
				printf("\n");
			}
			}else if(EXEC_FLAG == 1){
			if((*_opt).in_form == 0){
				Executor(top, null_node, C, SN, _opt, _fopt, _copt, _sopt);
				printf("\n");
			}
			}
			return(C);
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
	return(C);
}

/* data bind*/
int bind_data(FILE *IN, struct Tree *tree, struct function_options *_fopt, struct compile_options *_copt){
	int C;
	int bn_count = 0;
	int delim_count = 0;
	struct Tree **bn_table = NULL;
	printf(":tree=%ld:",tree);
	Function_Recursive_Search_BindNode(tree,&bn_count,bn_table);
	printf(":bncount=%d:\n",bn_count);
	//* search bind node */
	while((C = fgetc(IN))){
		if(C == EOF){
			return(0);
		}else{
			putchar(C);
		}
	}
	return(0);
}
