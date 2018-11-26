#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define WL 1

int main(void){
	int i;
	struct List precell;
	struct List *cell;
	float v[5] = {1,2,3,7,5};

	printf("===== ex.01 =\n");
	init_List_zero(&precell);
	cell = malloc(sizeof(struct List) * 5);
	if(cell == NULL){printf("[Err] malloc() @ main .\n");exit(1);}
	for(i=0;i<5;i++){
		init_List_zero(&cell[i]);
		cell[i].Head = malloc(sizeof(char)*256);
		sprintf(cell[i].Head,"%s","FLOAT");
		cell[i].function = NULL;
		cell[i].Val = v[i];
		cell[i].function = &Function_Print_Head;
		Function_Add_NextRtd(&precell,&cell[i]);
	}
	ExFunction_Recursive_Tree_Print(&precell, (struct List *(*)())Function_Print_Status,0); printf("\n");
	ExFunction_Recursive_S_Print(&precell, (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_S_Print(&precell, (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n");
	printf("=====\n");

	printf("===== ex.02 =\n");
	init_List_zero(&precell);
	cell = malloc(sizeof(struct List) * 5);
	if(cell == NULL){printf("[Err] malloc() @ main .\n");exit(1);}
	for(i=0;i<5;i++){
		init_List_zero(&cell[i]);
		cell[i].Head = malloc(sizeof(char)*256);
		sprintf(cell[i].Head,"%s","FLOAT");
		cell[i].function = NULL;
		cell[i].Val = v[i];
		cell[i].function = &Function_Print_Head;
	}
	Function_Add_NextRtd(&precell,&cell[0]);
	for(i=1;i<5;i++){
		Function_Add_NextRtd(&cell[i-1],&cell[i]);
	}
	ExFunction_Recursive_Tree_Print(&precell, (struct List *(*)())Function_Print_Status,0); printf("\n");
	ExFunction_Recursive_S_Print(&precell, (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_S_Print(&precell, (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n");
	printf("=====\n");

	printf("===== ex.03 =\n");
	init_List_zero(&precell);
	cell = malloc(sizeof(struct List) * 5);
	if(cell == NULL){printf("[Err] malloc() @ main .\n");exit(1);}
	for(i=0;i<5;i++){
		init_List_zero(&cell[i]);
		sprintf(cell[i].Head,"%s","FLOAT");
		cell[i].function = NULL;
		cell[i].Val = v[i];
		cell[i].function = &Function_Print_Head;
		Function_Add_ArgRtd(&precell,&cell[i]);
	}
	ExFunction_Recursive_Tree_Print(&precell, (struct List *(*)())Function_Print_Status,0); printf("\n");
	ExFunction_Recursive_S_Print(&precell, (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_S_Print(&precell, (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n");
	printf("=====\n");

	printf("===== ex.04 =\n");
	init_List_zero(&precell);
	cell = malloc(sizeof(struct List) * 5);
	if(cell == NULL){printf("[Err] malloc() @ main .\n");exit(1);}
	for(i=0;i<5;i++){
		init_List_zero(&cell[i]);
		sprintf(cell[i].Head,"%s","FLOAT");
		cell[i].function = NULL;
		cell[i].Val = v[i];
		cell[i].function = &Function_Print_Head;
	}
	for(i=0;i<3;i++){
		Function_Add_NextRtd(&precell,&cell[i]);
	}
	Function_Add_NextRtd(&cell[2],&cell[3]);
	Function_Add_ArgRtd(&cell[3],&cell[4]);
	ExFunction_Recursive_Tree_Print(&precell, (struct List *(*)())Function_Print_Status,0); printf("\n");
	ExFunction_Recursive_S_Print(&precell, (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_S_Print(&precell, (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n");
	printf("===== =====\n");
	ExFunction_Recursive_List(&precell,Function_Print_Index);
	printf("===== =====\n");
	printf("=====\n");


	//lastcell = FunctionExternal_Recursive_Liposome(&precell, NULL, (struct Liposome *(*)())precell.v_function);
	return(0);
}
