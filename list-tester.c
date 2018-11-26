#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define WL 1

int main(void){
	int i;
	struct List *cell;
	float v[6] = {0,1,2,3,4,5};

	printf("===== ex.01 =\n");
	cell = malloc(sizeof(struct List) * 6);
	if(cell == NULL){printf("[Err] malloc() @ main .\n");exit(1);}
	for(i=0;i<6;i++){
		init_List_zero(&cell[i]);
		cell[i].Head = malloc(sizeof(char)*256);
		sprintf(cell[i].Head,"%s","FLOAT");
		cell[i].Val = v[i];
		cell[i].function = &Function_Print_Head;
	}
	for(i=1;i<6;i++){
		Function_Add_NextRtd(&cell[0],&cell[i]);
	}
	ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,0); printf("\n");
	ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n");
	printf("=====\n");

	printf("===== ex.03 =\n");
	cell = malloc(sizeof(struct List) * 6);
	if(cell == NULL){printf("[Err] malloc() @ main .\n");exit(1);}
	for(i=0;i<6;i++){
		init_List_zero(&cell[i]);
		sprintf(cell[i].Head,"%s","FLOAT");
		cell[i].Val = v[i];
		cell[i].function = &Function_Print_Head;
	}
	for(i=1;i<5;i++){
		Function_Add_NextRtd(&cell[i-1],&cell[i]);
	}
	Function_Add_NextRtd(&cell[4],&cell[5]);
	ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,0); printf("\n");
	ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n");
	printf("=====\n");

	printf("===== ex.05 =\n");
	cell = malloc(sizeof(struct List) * 6);
	if(cell == NULL){printf("[Err] malloc() @ main .\n");exit(1);}
	for(i=0;i<6;i++){
		init_List_zero(&cell[i]);
		cell[i].Head = malloc(sizeof(char)*256);
		sprintf(cell[i].Head,"%s","FLOAT");
		cell[i].Val = v[i];
		cell[i].function = &Function_Print_Head;
	}
	Function_Add_NextRtd(&cell[0],&cell[1]);
	for(i=2;i<6;i++){
		Function_Add_ArgRtd(&cell[1],&cell[i],&cell[0]);
	}
	ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,0); printf("\n");
	ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n");
	printf("=====\n");

	return(0);
}
