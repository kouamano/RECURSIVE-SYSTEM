			/* apply compiler @ T-basic_functions.h */
			if((*_copt).c_clear == 1){
				//printf("hoge");
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Clear_Head,_copt);
			}else if((*_copt).c_dot){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Dot_Head,_copt);
			}
			if((*_copt).c_counter == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Compile_Head,_copt);
			}
			/* apply functions @ T-basic_functions.h */
			if((*_fopt).f_print_T == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head,_copt);
				if(C == LF || C == TAB){
					printf("%c",C);
				}
			}
			if((*_fopt).f_print_W == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_W,_copt);
				if(C == LF || C == TAB){
					printf("%c",C);
				}
			}
			if((*_fopt).f_print_S == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_S,_copt);
				if(C == LF || C == TAB){
					printf("%c",C);
				}

			}
			if((*_fopt).f_print_J == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_J,_copt);
				if(C == LF || C == TAB){
					printf("%c",C);
				}

			}


                        if((*_fopt).f_print_status == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Status,_copt);
                        }
                        if((*_fopt).f_print_hierarchy == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_HeadHierarchy,_copt);
                        }
                        if((*_fopt).f_print_hierarchy_status == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_HeadHierarchyStatus,_copt);
                        }

