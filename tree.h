#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF_LEN
#define BUFF_LEN 1024
#endif

struct Tree {
	char *Head;
	int LVself;
	int NCself;
	int ACself;
	int open;
	int close;
	int NextCount;
	int ArgCount;
	struct Tree **Next;
};
