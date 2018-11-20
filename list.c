#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int main(void){
	int i;
	int TAS;
	int VAS;
	float v[5] = {1,2,3,7,5};
	struct List cell[5];
	struct List precell;
	struct List *lastcell;
	TAS = 0;
	VAS = 5;
	for(i=0;i<5;i++){
		cell[i].Head = malloc(sizeof(char)*256);
		sprintf(cell[i].Head,"%s","FLOAT");
		cell[i].function = NULL;
		cell[i].Val = v[i];
		cell[i].function = &Function_Print_Head;
		//cell[i].v_function = NULL;
		cell[i].Next = NULL;
	}
	init_List_Head(&precell,256);
	sprintf(precell.Head,"%s","FLOAT");
	printf("%s\n",precell.Head);
	//precell.function = &Function_Print_Head;
	//precell.Val = v[0];
	//precell.function = &Function_Print_Val;
	//precell.Next = NULL;
	//precell.Next[0] = &cell[4];
	//cell[4].Next[0] = &cell[1];
	//cell[1].Next[0] = &cell[3];
	//cell[3].Next[0] = &cell[2];
	//lastcell = ExFunction_Recursive_List(&precell, (struct List *(*)())precell.function);
	//lastcell = FunctionExternal_Recursive_Liposome(&precell, (struct Liposome *(*)())&Function_PrintAdd_Value, (struct Liposome *(*)())&Function_PrintAdd_Value);
	//lastcell = FunctionExternal_Recursive_Liposome(&precell, NULL, (struct Liposome *(*)())precell.v_function);
	//lastcell = FunctionExternal_Recursive_Liposome(&precell, (struct Liposome *(*)())precell.t_function, (struct Liposome *(*)())precell.v_function);
	//lastcell = Function_Recursive_Liposome(&precell);
	//Function_PrintAdd_Value(lastcell);
	return(0);
}
