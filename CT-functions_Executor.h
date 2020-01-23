/* Executor */
NODE Executor(NODE top, NODE refTree, NODE null_node, int C, int SN, struct options *_opt, struct function_options *_fopt, struct compile_options *_copt, struct search_options *_sopt, FILE *DATA, int EXEC_FLAG){
		/* pre */
		/** bind data (for input-form) */
		if((EXEC_FLAG&1) == 1){
			// ExFunction_Recursive(top,(NODE (*)())Function_Detect_DimBlock,_opt,_fopt,_copt);	// SAK Inner Prouct
			if((*_opt).data != NULL){
				if(strlen((*_opt).data) > 0){
					// Function_Bind_Data(DATA,top,_opt,_fopt,_copt);		// SAK Inner Product
					bind_data(top, DATA);						// SAK Inner Product
				}
			}
		}
		/** bind self-ref (for input-form) */
		if((EXEC_FLAG&8) == 8){
			Function_Recursive_Bind_RefNode(top,top,_copt);
		}
		/** bind io-ref (for output-form) */
		if((EXEC_FLAG&4) == 4){
			Function_Recursive_Bind_RefNode(top,refTree,_copt);
		}
		/** inner product of binded data */
		if((EXEC_FLAG&16) == 16){
                        ExFunction_Recursive(top,(NODE (*)())Function_Assign_RefedValPtr,_opt,_fopt,_copt);
		}
		/** print */
		if((EXEC_FLAG&2) == 2){
			/*** search */
		        NODE hit_tree = top;
		        NODE hit_node = top;
			if(_sopt != NULL){
				if((*_sopt).s_counter > 0){
					hit_node = Function_Get_Node((*_sopt).pos,top);
					// t: if(hit_node == NULL){
					if(hit_node == NO_NODE){
						hit_tree = null_node;
					}else{
						hit_tree = hit_node;
					}
				}
			}else{
				hit_tree = top;
			}
			/**** edit hit_tree */
			// tq: int CONJ_ORG = (*hit_tree).Conj;
			int CONJ_ORG = conjugate(hit_tree);
			// tq: if((*hit_tree).Conj == 1){
			if(conjugate(hit_tree) == 1){
				// tq: (*hit_tree).Conj = CONJ_SW;
				set_conjugate(hit_tree,CONJ_SW);
			}

			/*** apply formated print */
			(*_fopt).f_print_self_stat = 1;
			if((*_fopt).f_print_N == 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (NODE (*)())Function_Print_Conj_T, (NODE (*)())Function_Print_Head_SN, (NODE (*)())Function_Print_Bopen_T, (NODE (*)())Function_Print_Bclose_T, _opt,_fopt,_copt,SN);
				if((*_copt).c_restrict == 1){
					printf(";");
				}
				printf("\n");
			}
			if((*_fopt).f_print_T == 1){
				if((*_fopt).f_print_hierarchy == 1){
					printf("====multiline====>");
				}
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (NODE (*)())Function_Print_Conj_T, (NODE (*)())Function_Print_Head, (NODE (*)())Function_Print_Bopen_T,  (NODE (*)())Function_Print_Bclose_T,_opt,_fopt,_copt,SN);
				if((*_copt).c_restrict == 1){
					printf(";");
				}
				printf("\n");
				if((*_fopt).f_print_hierarchy == 1){
					printf("<====multiline====\n");
				}
			}
			if((*_fopt).f_print_S == 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (NODE (*)())Function_Print_Conj_S, (NODE (*)())Function_Print_Head, (NODE (*)())Function_Print_Bopen_S, (NODE (*)())Function_Print_Bclose_S, _opt,_fopt,_copt,SN);
				if((*_copt).c_restrict == 1){
					printf(";");
				}
				printf("\n");
			}
			if((*_fopt).f_print_W >= 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (NODE (*)())Function_Print_Conj_WL, (NODE (*)())Function_Print_Head_WL, (NODE (*)())Function_Print_Bopen_WL, (NODE (*)())Function_Print_Bclose_WL, _opt,_fopt,_copt, SN);
				if((*_copt).c_restrict == 1){
					printf(";");
				}
				printf("\n");
			}
			if((*_fopt).f_print_X == 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (NODE (*)())Function_Print_Conj_X, (NODE (*)())Function_Print_Head_X, (NODE (*)())Function_Print_Bopen_X, (NODE (*)())Function_Print_Bclose_X, _opt,_fopt,_copt,SN);
				if((*_copt).c_restrict == 1){
					printf("<;/>");
				}
				printf("\n");
			}
			if((*_fopt).f_print_J == 1){
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (NODE (*)())Function_Print_Conj_JS, (NODE (*)())Function_Print_Head_JS, (NODE (*)())Function_Print_Bopen_JS, (NODE (*)())Function_Print_Bclose_WL, _opt,_fopt,_copt,SN);
				printf("\n");
			}

			if((*_fopt).f_print_C == 1){
				printf("====multiline====>\n");
				ExFunction_Recursive_Ser_MultiPrint(hit_tree, (NODE (*)())Function_Print_Conj_C, (NODE (*)())Function_Print_Head, (NODE (*)())Function_Print_Bopen_C, (NODE (*)())Function_Print_Bclose_C, _opt,_fopt,_copt,SN);
				printf("<====multiline====\n");
			}
			/*** apply status print */
                        if((*_fopt).f_print_status == 1){
				printf("====multiline====>\n");
				ExFunction_Recursive(hit_tree,(NODE (*)())Function_Print_Status,_opt,_fopt,_copt);
				printf("<====multiline====\n");
                        }
			/*** apply conjugation-table print */
                        if((*_fopt).f_print_Ma == 1){
				printf("====multiline====>\n");
				ExFunction_Recursive_Ser(hit_tree,(NODE (*)())Function_Print_Adj,_opt,_fopt,_copt,SN,1);
				printf("<====multiline====\n");
                        }

			/**** recover hit_tree */
			// tq if((*hit_tree).Conj == CONJ_SW){
			if(conjugate(hit_tree) == CONJ_SW){
				// tq: (*hit_tree).Conj = CONJ_ORG;
				set_conjugate(hit_tree,CONJ_ORG);
			}
		}
		/* test */
		return(top);
}
