#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int main(void){
	int i;
	int TAS;
	int VAS;
	float v[5] = {1,2,3,7,5};
	struct Liposome cell[5];
	struct Liposome precell;
	struct Liposome *lastcell;
	TAS = 0;
	VAS = 5;
	for(i=0;i<5;i++){
		cell[i].Head = malloc(sizeof(char)*256);
		sprintf(cell[i].Head,"%s","FLOAT");
		cell[i].TimeArraySize = &TAS;
		cell[i].Time = NULL;
		cell[i].t_function = NULL;
		cell[i].ValueArraySize = &VAS;
		cell[i].Value = v;
		cell[i].v_function = &Function_PrintAdd_Value;
		//cell[i].v_function = NULL;
		cell[i].Next = NULL;
	}
	//sprintf(precell.Head,"%s","NEST");
	precell.Head = malloc(sizeof(char)*256);
	sprintf(precell.Head,"%s","FLOAT");
	precell.TimeArraySize = &TAS;
	precell.Time = NULL;
	//precell.t_function = NULL;
	precell.t_function = &Function_PrintAdd_Value;
	precell.ValueArraySize = &VAS;
	precell.Value = v;
	precell.v_function = &Function_PrintAdd_Value;
	//precell.Next = NULL;
	precell.Next = &cell[4];
	cell[4].Next = &cell[1];
	cell[1].Next = &cell[3];
	cell[3].Next = &cell[2];
	lastcell = FunctionExternal_Recursive_Liposome(&precell, NULL, (struct Liposome *(*)())precell.v_function);
	lastcell = FunctionExternal_Recursive_Liposome(&precell, (struct Liposome *(*)())&Function_PrintAdd_Value, (struct Liposome *(*)())&Function_PrintAdd_Value);
	lastcell = FunctionExternal_Recursive_Liposome(&precell, NULL, (struct Liposome *(*)())precell.v_function);
	lastcell = FunctionExternal_Recursive_Liposome(&precell, (struct Liposome *(*)())precell.t_function, (struct Liposome *(*)())precell.v_function);
	lastcell = Function_Recursive_Liposome(&precell);
	Function_PrintAdd_Value(lastcell);
	return(0);
}
