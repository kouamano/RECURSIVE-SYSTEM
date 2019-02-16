			/* apply functions @ T-basic_functions.h */
			//extern int EC; // compile error
                        if((*_fopt).f_print_T == 1){
                        ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head);
                        printf("\n");
                        }
                        if((*_fopt).f_print_S == 1){
                        ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_S);
                        printf("\n");
                        }
                        if((*_fopt).f_print_J == 1){
                        ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_J);
                        printf("\n");
                        }
                        if((*_fopt).f_print_W == 1){
                        ExFunction_Recursive(top,(struct Tree *(*)())Function_Print_Head_W);
                        printf("\n");
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
