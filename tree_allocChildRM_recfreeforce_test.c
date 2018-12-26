#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tree.h"
#ifndef BUFF_LEN
#define BUFF_LEN 1024
#endif

void main(void){
	//success
	int i;
	struct Tree *top;
	struct Tree *child;
	for(i=0;i<2000000;i++){
		top = Create_Node(BUFF_LEN);
		child = Create_Node(BUFF_LEN);
		Add_Next(top,child);
		child = Create_Node(BUFF_LEN);
		Add_Next(top,child);
		child = Create_Node(BUFF_LEN);
		Add_Next((*top).Next[0],child);
		Function_RecursiveFreeForce(top);
		free(top);
		printf("%d\n",i);
	}
}
