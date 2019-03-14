			/* apply compiler */
			if((*_copt).c_clear == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Clear_Head,_fopt,_copt);
			}else if((*_copt).c_dot){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Dot_Head,_fopt,_copt);
			}
			if((*_copt).c_counter > 0){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Compile_Head,_fopt,_copt);
			}


			/* apply formated print */
			if((*_fopt).f_print_N == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Seq,_fopt,_copt);
				if(C == LF && (*_copt).c_restrict == 1){
					printf(";");
				}
				if(C == LF || C == TAB){
					printf("%c",C);
				}
			}
			if((*_fopt).f_print_T == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_T,_fopt,_copt);
				if(C == LF && (*_copt).c_restrict == 1){
					printf(";");
				}
				if(C == LF || C == TAB){
					printf("%c",C);
				}
	                        if((*_fopt).f_print_test == 1){
					printf("\\/ TEST\n");
					ExFunction_Recursive_Ser_MultiPrint(top, (struct Tree *(*)())Function_Print_Conj_T, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_T,  (struct Tree *(*)())Function_Print_Bclose,  _fopt, _copt, SN);
					if(C == LF && (*_copt).c_restrict == 1){
						printf(";");
					}
					if(C == LF || C == TAB){
						printf("%c",C);
					}
					printf("\n");
	                        }

			}
			if((*_fopt).f_print_C == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_C,_fopt,_copt);
				if(C == LF && (*_copt).c_restrict == 1){
					printf(";");
				}
				if(C == LF || C == TAB){
					printf("%c",C);
				}
			}
			if((*_fopt).f_print_W == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_W,_fopt,_copt);
				if(C == LF && (*_copt).c_restrict == 1){
					printf(";");
				}
				if(C == LF || C == TAB){
					printf("%c",C);
				}
			}
			if((*_fopt).f_print_S == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_S,_fopt,_copt);
				if(C == LF || C == TAB){
					printf("%c",C);
				}
	                        if((*_fopt).f_print_test == 1){
					printf("\\/ TEST\n");
					ExFunction_Recursive_Ser_MultiPrint(top, (struct Tree *(*)())Function_Print_Conj_S, (struct Tree *(*)())Function_Print_Head, (struct Tree *(*)())Function_Print_Bopen_S,  (struct Tree *(*)())Function_Print_Bclose,  _fopt, _copt, SN);
					if(C == LF && (*_copt).c_restrict == 1){
						printf(";");
					}
					if(C == LF || C == TAB){
						printf("%c",C);
					}
					printf("\n");
	                        }


			}
			if((*_fopt).f_print_J == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_J,_fopt,_copt);
				if(C == LF || C == TAB){
					printf("%c",C);
				}

			}


			/* apply formated print */
                        if((*_fopt).f_print_status == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Status,_fopt,_copt);
				printf("\n");
                        }
                        if((*_fopt).f_print_hierarchy == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_HeadHierarchy,_fopt,_copt);
				printf("\n");
                        }
                        if((*_fopt).f_print_hierarchy_status == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_HeadHierarchyStatus,_fopt,_copt);
				printf("\n");
                        }


			/* apply conjugation-table print */
                        if((*_fopt).f_print_Ma == 1){
				ExFunction_Recursive_Ser(top,(struct Tree *(*)())Function_Print_Adj,_fopt,_copt,SN);
				printf("\n");
                        }

