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

			/* apply compiler @ T-compiler.h */
