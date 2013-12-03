#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Liposome {
	char Head[256];
	int TimeArraySize;
	float *Time;
	struct Liposome *(*t_function)();
	int ValueArraySize;
	float *Value;
	struct Liposome *(*v_function)();
	struct Liposome *Next;
};

struct Liposome *Function_PrintAdd_Value(struct Liposome *liposome){
	int i;
	for(i=0;i<liposome->ValueArraySize;i++){
		printf("%f ",liposome->Value[i]);
	}
	liposome->Value[2]++;
	printf("\n");
	return(liposome);
}

struct Liposome *Function_Recursive_Liposome(struct Liposome *liposome){
	struct Liposome *out = liposome;
	if(liposome == NULL){
		printf("NULL\n");
		return(NULL);
	}
	if((*liposome).t_function != NULL){
		(*liposome).t_function(liposome);
	}
	if((*liposome).v_function != NULL){
		(*liposome).v_function(liposome);
	}
	if(strcmp(liposome->Head,"NEST") == 0){
		Function_Recursive_Liposome(liposome);
	}
	if(liposome->Next != NULL){
		Function_Recursive_Liposome(liposome->Next);
	}
	return(out);
}
/*
struct Liposome *Function_Recursive_Liposome(struct Liposome *liposome, struct Liposome *(*t_function)(), struct Liposome *(*v_function)()){
	struct Liposome *out = liposome;
	if(liposome == NULL){
		printf("NULL\n");
		return(NULL);
	}
	if(t_function != NULL){
		t_function(liposome);
	}
	if(v_function != NULL){
		v_function(liposome);
	}
	if(strcmp(liposome->Head,"NEST") == 0){
		Function_Recursive_Liposome(liposome,t_function,v_function);
	}
	if(liposome->Next != NULL){
		Function_Recursive_Liposome(liposome->Next,t_function,v_function);
	}
	return(out);
}
*/
int main(void){
	int i;
	float v[5] = {1,2,3,7,5};
	struct Liposome cell[5];
	struct Liposome precell;
	struct Liposome *lastcell;
	for(i=0;i<5;i++){
		sprintf(cell[i].Head,"%s","FLOAT");
		cell[i].TimeArraySize = 0;
		cell[i].Time = NULL;
		cell[i].t_function = NULL;
		cell[i].ValueArraySize = 5;
		cell[i].Value = v;
		cell[i].v_function = &Function_PrintAdd_Value;
		//cell[i].v_function = NULL;
		cell[i].Next = NULL;
	}
	//sprintf(precell.Head,"%s","NEST");
	sprintf(precell.Head,"%s","FLOAT");
	precell.TimeArraySize = 0;
	precell.Time = NULL;
	//precell.t_function = NULL;
	precell.t_function = &Function_PrintAdd_Value;
	precell.ValueArraySize = 5;
	precell.Value = v;
	precell.v_function = &Function_PrintAdd_Value;
	//precell.Next = NULL;
	precell.Next = &cell[4];
	cell[4].Next = &cell[1];
	cell[1].Next = &cell[3];
	cell[3].Next = &cell[2];
	//printf("%s\n",precell.Head);
	//lastcell = Function_Recursive_Liposome(&precell, NULL, (struct Liposome *(*)())precell.v_function);
	//lastcell = Function_Recursive_Liposome(&precell, (struct Liposome *(*)())&Function_PrintAdd_Value, (struct Liposome *(*)())&Function_PrintAdd_Value);
	//lastcell = Function_Recursive_Liposome(&precell, NULL, (struct Liposome *(*)())precell.v_function);
	//lastcell = Function_Recursive_Liposome(&precell, (struct Liposome *(*)())precell.t_function, (struct Liposome *(*)())precell.v_function);
	lastcell = Function_Recursive_Liposome(&precell);
	Function_PrintAdd_Value(lastcell);
	return(0);
}
