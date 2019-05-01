/* include into T-functions_imex.h */
void Executor(struct Tree *top, struct Tree *null_node, int C, int SN, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, struct search_options *_sopt, int *t_array_count, struct Tree **TA, FILE *DATA, int EXEC_FLAG){
		/* pre */
		//* bind data (for input-form) */
		//printf(":EXEC=%d:",EXEC_FLAG);
		if((EXEC_FLAG&1) == 1){
			ExFunction_Recursive_Ser(top,(struct Tree *(*)())Detect_DimBlock,_fopt,_copt,SN,1);
			if((*_opt).data != NULL){
				if(strlen((*_opt).data) > 0){
					bind_data(DATA,top,_fopt,_copt);
				}
			}
		}
		//* bind ref-node (for output-form) */
		if((EXEC_FLAG&4) == 4){
		}

		/* print */
		if((EXEC_FLAG&2) == 2){
			/* for search */
		        struct Tree *hit_tree;
		        struct Tree *hit_node;
			if((*_sopt).s_counter > 0){
				hit_node = get_node((*_sopt).pos,top);
				if(hit_node == NULL){
					hit_tree = null_node;
				}else{
					hit_tree = hit_node;
				}
			}else{
				hit_tree = top;
			}
			/* apply formated print */
			if((*_fopt).f_print_N == 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (struct Tree *(*)())Function_Print_Conj_T, (struct Tree *(*)())Function_Print_Head_SN, (struct Tree *(*)())Function_Print_Bopen_T,  (struct Tree *(*)())Function_Print_Bclose_T,  _fopt, _copt, SN);
				if(C == LF && (*_copt).c_restrict == 1){
					printf(";");
				}
				if(C == LF || C == TAB){
					printf("%c",C);
				}
				printf("\n");
			}
			if((*_fopt).f_print_T == 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (struct Tree *(*)())Function_Print_Conj_T, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_T,  (struct Tree *(*)())Function_Print_Bclose_T,  _fopt, _copt, SN);
				if(C == LF && (*_copt).c_restrict == 1){
					printf(";");
				}
				if(C == LF || C == TAB){
					printf("%c",C);
				}
				printf("\n");
			}
			if((*_fopt).f_print_S == 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (struct Tree *(*)())Function_Print_Conj_S, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_S,  (struct Tree *(*)())Function_Print_Bclose_S,  _fopt, _copt, SN);
				if(C == LF && (*_copt).c_restrict == 1){
					printf(";");
				}
				if(C == LF || C == TAB){
					printf("%c",C);
				}
				printf("\n");
			}
			if((*_fopt).f_print_C == 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (struct Tree *(*)())Function_Print_Conj_C, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_C,  (struct Tree *(*)())Function_Print_Bclose_C,  _fopt, _copt, SN);
				if(C == LF && (*_copt).c_restrict == 1){
					printf(";");
				}
				if(C == LF || C == TAB){
					printf("%c",C);
				}
				printf("\n");
			}
			if((*_fopt).f_print_W == 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (struct Tree *(*)())Function_Print_Conj_WL, (struct Tree *(*)())Function_Print_Head_WL, (struct Tree *(*)())Function_Print_Bopen_WL,  (struct Tree *(*)())Function_Print_Bclose_WL,  _fopt, _copt, SN);
				if(C == LF && (*_copt).c_restrict == 1){
					printf(";");
				}
				if(C == LF || C == TAB){
					printf("%c",C);
				}
				printf("\n");
			}
			if((*_fopt).f_print_X == 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (struct Tree *(*)())Function_Print_Conj_X, (struct Tree *(*)())Function_Print_Head_X, (struct Tree *(*)())Function_Print_Bopen_X,  (struct Tree *(*)())Function_Print_Bclose_X, _fopt, _copt, SN);
				if(C == LF && (*_copt).c_restrict == 1){
					//printf("");
				}
				if(C == LF || C == TAB){
					printf("%c",C);
				}
				printf("\n");
			}
			if((*_fopt).f_print_J == 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (struct Tree *(*)())Function_Print_Conj_JS, (struct Tree *(*)())Function_Print_Head_JS, (struct Tree *(*)())Function_Print_Bopen_JS,  (struct Tree *(*)())Function_Print_Bclose_WL,  _fopt, _copt, SN);
				if(C == LF || C == TAB){
					printf("%c",C);
				}
				printf("\n");
			}

			/* apply status print */
                        if((*_fopt).f_print_status == 1){
				ExFunction_Recursive(hit_tree,(struct Tree *(*)())Function_Print_Status,_fopt,_copt);
				printf("\n");
                        }
                        if((*_fopt).f_print_hierarchy == 1){
				ExFunction_Recursive(hit_tree,(struct Tree *(*)())Function_Print_HeadHierarchy,_fopt,_copt);
				printf("\n");
                        }
                        if((*_fopt).f_print_hierarchy_status == 1){
				ExFunction_Recursive(hit_tree,(struct Tree *(*)())Function_Print_HeadHierarchyStatus,_fopt,_copt);
				printf("\n");
                        }

			/* apply conjugation-table print */
                        if((*_fopt).f_print_Ma == 1){
				ExFunction_Recursive_Ser(hit_tree,(struct Tree *(*)())Function_Print_Adj,_fopt,_copt,SN,1);
				printf("\n");
                        }
		}
			/* test */
			//exit(0);
}

