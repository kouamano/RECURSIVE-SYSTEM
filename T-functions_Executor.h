/* Executor */
struct Tree *Executor(struct Tree *top, struct Tree *refTree, struct Tree *null_node, int C, int SN, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, struct search_options *_sopt, FILE *DATA, int EXEC_FLAG){
		FC(fprintf(stderr,">Executor(F:%d:)<\n",EXEC_FLAG);)
		/* pre */
		/** bind data (for input-form) */
		if((EXEC_FLAG&1) == 1){
			ExFunction_Recursive(top,(struct Tree *(*)())Function_Detect_DimBlock,_opt,_fopt,_copt);
			if((*_opt).data != NULL){
				if(strlen((*_opt).data) > 0){
					ExFunction_Bind_Data(DATA,top,_opt,_fopt,_copt);
				}
			}
		}
		/** bind self-ref (for input-form) */
		if((EXEC_FLAG&8) == 8){
			ExFunction_Recursive_Bind_RefNode(top,top,_copt);
		}
		/** bind io-ref (for output-form) */
		if((EXEC_FLAG&4) == 4){
			ExFunction_Recursive_Bind_RefNode(top,refTree,_copt);
		}
		/** inner product of binded data */
		if((EXEC_FLAG&16) == 16){
                        ExFunction_Recursive(top,(struct Tree *(*)())Function_Assign_RefedValPtr,_opt,_fopt,_copt);
		}
		/** print */
		if((EXEC_FLAG&2) == 2){
			/*** search */
		        struct Tree *hit_tree = top;
		        struct Tree *hit_node = top;
			if(_sopt != NULL){
				if((*_sopt).s_counter > 0){
					hit_node = ExFunction_Get_Node((*_sopt).pos,top);
					if(hit_node == NULL){
						hit_tree = null_node;
					}else{
						hit_tree = hit_node;
					}
				}
			}else{
				hit_tree = top;
			}
			/*** apply formated print */
			(*_fopt).f_print_self_stat = 1;
			if((*_fopt).f_print_N == 1){
				ExFunction_Recursive_Print_Tree(hit_tree, (struct Tree *(*)())Function_Print_Conj_T, (struct Tree *(*)())Function_Print_Head_SN, (struct Tree *(*)())Function_Print_Bopen_T, (struct Tree *(*)())Function_Print_Bclose_T, _opt,_fopt,_copt,NULL,SN);
				if((*_copt).c_restrict == 1){
					printf(";");
				}
				printf("\n");
			}
			if((*_fopt).f_print_T == 1){
				if((*_fopt).f_print_hierarchy == 1){
					printf("====multiline====>");
				}
				ExFunction_Recursive_Print_Tree(hit_tree, (struct Tree *(*)())Function_Print_Conj_T, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_T,  (struct Tree *(*)())Function_Print_Bclose_T,_opt,_fopt,_copt,NULL,SN);
				if((*_copt).c_restrict == 1){
					printf(";");
				}
				printf("\n");
				if((*_fopt).f_print_hierarchy == 1){
					printf("<====multiline====\n");
				}
			}
			if((*_fopt).f_print_S == 1){
				ExFunction_Recursive_Print_Tree(hit_tree, (struct Tree *(*)())Function_Print_Conj_S, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_S, (struct Tree *(*)())Function_Print_Bclose_S, _opt,_fopt,_copt,NULL,SN);
				if((*_copt).c_restrict == 1){
					printf(";");
				}
				printf("\n");
			}
			if((*_fopt).f_print_W >= 1){
				ExFunction_Recursive_Print_Tree(hit_tree, (struct Tree *(*)())Function_Print_Conj_WL, (struct Tree *(*)())Function_Print_Head_WL, (struct Tree *(*)())Function_Print_Bopen_WL, (struct Tree *(*)())Function_Print_Bclose_WL,_opt,_fopt,_copt,NULL,SN);
				if((*_copt).c_restrict == 1){
					printf(";");
				}
				printf("\n");
			}
			if((*_fopt).f_print_X == 1){
				ExFunction_Recursive_Print_Tree(hit_tree, (struct Tree *(*)())Function_Print_Conj_X, (struct Tree *(*)())Function_Print_Head_X, (struct Tree *(*)())Function_Print_Bopen_X, (struct Tree *(*)())Function_Print_Bclose_X,_opt,_fopt,_copt,NULL,SN);
				if((*_copt).c_restrict == 1){
					printf("<;/>");
				}
				printf("\n");
			}
			if((*_fopt).f_print_J == 1){
				ExFunction_Recursive_Print_Tree(hit_tree, (struct Tree *(*)())Function_Print_Conj_JS, (struct Tree *(*)())Function_Print_Head_JS, (struct Tree *(*)())Function_Print_Bopen_JS, (struct Tree *(*)())Function_Print_Bclose_WL,_opt,_fopt,_copt,NULL,SN);
				printf("\n");
			}
			if((*_fopt).f_print_C == 1){
				printf("====multiline====>\n");
				ExFunction_Recursive_Print_Tree(hit_tree, (struct Tree *(*)())Function_Print_Conj_C, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_C, (struct Tree *(*)())Function_Print_Bclose_C,_opt,_fopt,_copt,NULL,SN);
				printf("<====multiline====\n");
			}
			/*** apply status print */
                        if((*_fopt).f_print_status == 1){
				printf("====multiline====>\n");
				ExFunction_Recursive_Ser(hit_tree,(struct Tree *(*)())Function_Print_Status,_opt,_fopt,_copt,SN,1);
				printf("<====multiline====\n");
                        }
			/*** apply conjugation-table print */
                        if((*_fopt).f_print_Ma == 1){
				printf("====multiline====>\n");
				ExFunction_Recursive_Ser(hit_tree,(struct Tree *(*)())Function_Print_Adj,_opt,_fopt,_copt,SN,1);
				printf("<====multiline====\n");
                        }
			/*** apply linkage print */
                        if((*_fopt).f_print_Ln == 1){
				printf("====multiline====>\n");
				ExFunction_Recursive_Ser(hit_tree,(struct Tree *(*)())Function_Print_Linkage,_opt,_fopt,_copt,SN,1);
				printf("<====multiline====\n");
                        }
		}
		/* test */
		return(top);
}
