			/* apply compiler @ T-basic_functions.h */
			if((*_copt).c_clear == 1){
				//printf("hoge");
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Clear_Head);
			}else if((*_copt).c_dot){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Dot_Head);
			}
			if((*_copt).c_counter == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Compile_Head);
			}
			/* apply functions @ T-basic_functions.h */
			if((*_fopt).f_print_T == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head);
				if(C == LF || C == TAB){
					printf("%c",C);
				}
			}
			if((*_fopt).f_print_W == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_W);
				if(C == LF || C == TAB){
					printf("%c",C);
				}
			}
			if((*_fopt).f_print_S == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_S);
				if(C == LF || C == TAB){
					printf("%c",C);
				}

			}
			if((*_fopt).f_print_J == 1){
				ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_J);
				if(C == LF || C == TAB){
					printf("%c",C);
				}

			}


                        if((*_fopt).f_print_status == 1){
                        ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Status);
                        }
                        if((*_fopt).f_print_hierarchy == 1){
                        ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_HeadHierarchy);
                        }
                        if((*_fopt).f_print_hierarchy_status == 1){
                        ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_HeadHierarchyStatus);
                        }

