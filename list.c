#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int main(void){
	int i;
	int TAS;
	int VAS;
	float v[5] = {1,2,3,7,5};
	struct List precell;
	struct List *cell;
	struct List *lastcell;
	//TAS = 0;
	//VAS = 5;

	init_List_Head(&precell,256);
	precell.NextCount = 0;
	//precell.NextCount = 5;
	//precell.Next = malloc(sizeof(struct List) * 5);
	//sprintf(precell.Head,"%s","FLOAT");

	cell = malloc(sizeof(struct List) * 5);
	if(cell == NULL){printf("[Err] malloc() @ main .\n");exit(1);}

	for(i=0;i<5;i++){
		//printf(":%f:\n",v[i]);
		init_List_zero(&cell[i]);
		cell[i].Head = malloc(sizeof(char)*256);
		sprintf(cell[i].Head,"%s","FLOAT");
		cell[i].function = NULL;
		cell[i].Val = v[i];
		cell[i].function = &Function_Print_Head;
		//cell[i].v_function = NULL;
		//precell.Next[i] = &cell[i];
		//cell[i].LVself = precell.LVself+1;
		Function_Add_Next(&precell,&cell[i]);
	}
	//printf("%s\n",precell.Head);
	//Function_Print_Head(&precell);

	//ExFunction_Recursive_List(&precell, (struct List *(*)())Function_Print_Status);
	printf("\n=====\n");
	ExFunction_Recursive_Tree_Print(&precell, (struct List *(*)())Function_Print_Status_Tree,1);
	//ExFunction_Recursive_Tree_Print(&precell, (struct List *(*)())Function_Print_Status_Tree,0);
	printf("\n");
	printf("\n=====\n");
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
