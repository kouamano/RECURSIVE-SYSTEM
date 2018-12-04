#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF_LEN
#define BUFF_LEN 1024
#endif

struct Seq {
	int LVself;
	int ACself;
	int conj;
	int open;
	char *Head;
	int close;
	struct Seq *Next;
	struct Seq *Parent;
};
