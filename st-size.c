#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C-structure.h"
//#include "G-structure.h"
//#include "List-structure.h"
#include "T-structure.h"
//#include "T-convStructure.h"

void main(void){
	printf("struct LinkTable ");
	printf(":%d:\n",sizeof(struct LinkTable));
	printf("  menbers ");
	printf("  parent_SN:%d:\n",sizeof(int));
	printf("  Lv:%d:\n",sizeof(int));
	printf("  Head:%d:\n",sizeof(char *));
	printf("  Conj:%d:\n",sizeof(int));
	printf("  LinkVC:%d:\n",sizeof(int));
	printf("  LinkV:%d:\n",sizeof(int *));
	printf("struct Tree ");
	printf(":%d:\n",sizeof(struct Tree));
}
