#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#define WL 1

int main(void){
	int i;
	struct List *cell;
	float v[6] = {0,1,2,3,4,5};

	printf("===== ex.0-01 =\n");
	cell = malloc(sizeof(struct List) * 3);
	for(i=0;i<3;i++){
		init_List_zero(&cell[i]);
	}
	//Function_Add_Next(&cell[0],&cell[1]);
	Function_Add_NextRtd(NULL,&cell[0],&cell[1]);
	//Function_Add_Arg(&cell[1],&cell[2]);
	Function_Add_ArgRtd(&cell[0],&cell[1],&cell[2]);
	printf("#T "); ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	printf("=====\n");

	printf("===== ex.0-02 =\n");
	cell = malloc(sizeof(struct List) * 3);
	for(i=0;i<3;i++){
		init_List_zero(&cell[i]);
	}
	//Function_Add_Next(&cell[0],&cell[1]);
	Function_Add_NextRtd(NULL,&cell[0],&cell[1]);
	//Function_Add_Arg(&cell[0],&cell[2]);
	Function_Add_ArgRtd(NULL,&cell[0],&cell[2]);
	printf("#T "); ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	printf("=====\n");

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
		Function_Add_NextRtd(NULL,&cell[0],&cell[i]);
	}
	printf("#T "); ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	printf("#S "); ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n     -----     -----     ");
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
	Function_Add_NextRtd(NULL,&cell[0],&cell[1]);
	for(i=2;i<5;i++){
		Function_Add_NextRtd(&cell[i-2],&cell[i-1],&cell[i]);
	}
	Function_Add_NextRtd(&cell[3],&cell[4],&cell[5]);
	printf("#T "); ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	printf("#S "); ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n     -----     -----     ");
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
	Function_Add_NextRtd(NULL,&cell[0],&cell[1]);
	for(i=2;i<6;i++){
		Function_Add_ArgRtd(&cell[0],&cell[1],&cell[i]);
	}
	printf("#T "); ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	printf("#S "); ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n     -----     -----     ");
	ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n");
	printf("=====\n");

	printf("===== ex.05-01 =\n");
	struct List *Branch1 = Function_Create_Next(&cell[1]);
	Function_Create_Arg(&cell[1],Branch1);
	Function_Create_Arg(&cell[1],Branch1);
	//Function_Create_Next(Branch1);
	printf("#T "); ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	printf("#S "); ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n     -----     -----     ");
	ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n");
	printf("=====\n");

	printf("===== ex.05-02 =\n");
	Function_Create_Next(&cell[1]);
	printf("#T "); ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	printf("#S "); ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n     -----     -----     ");
	ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n");
	printf("=====\n");

	printf("===== ex.05-03 =\n");
	Function_Create_Next(Branch1);
	printf("#T "); ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	printf("#S "); ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,0,NULL); printf("\n");
	ExFunction_Recursive_Tree_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n     -----     -----     ");
	ExFunction_Recursive_S_Print(&cell[0], (struct List *(*)())Function_Print_Status,WL,NULL);
	printf("\n");
	printf("=====\n");

	return(0);
}
