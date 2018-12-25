#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#ifndef BUFF_LEN
#define BUFF_LEN 1024
#endif

void main(void){
	//succseed
	int i;
	struct Tree *top;
	for(i=0;i<1000000;i++){
		top = Create_Node(BUFF_LEN);
		Function_RecursiveFreeForce(top);
		//Function_RecursiveFree(top);
		free(top);
		printf("%d\n",i);
	}
}
