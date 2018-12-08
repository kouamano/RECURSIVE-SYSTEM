#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF
#define BUFF 1024
#endif

struct SList {
	char *Head;
	int LV;
	int ACself;
	int ArgCount;
	struct SList **Arg;
};
