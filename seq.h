#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF_LEN
#define BUFF_LEN 1024
#endif

struct Seq {		//<conj><open><Head><close>
	int LVself;
	int ACself;
	int conj;	//is conjugate (,) => Next
	int open;	//open list => Next
	char *Head;
	int close;	//close list => current
	struct Seq *Next;
	struct Seq *Parent;
};

struct Seq Function_Create_Seq(void){
	struct Seq *seq;
	if((seq = malloc(sizeof(struct Seq) * 1)) == NULL){
		fprintf(stderr,"[Fail] malloc.\n");
		exit(1);
	}
	(*seq).LVself = 0;
	(*seq).ACself = 0;
	(*seq).open = 0;
	if(((*seq).Head = malloc(sizeof(char) * BUFF_LEN)) == NULL){
		fprintf(stderr,"[Fail] malloc.\n");
		exit(1);
	}
	(*seq).close = 0;
	(*seq).Next = NULL;
	(*seq).Parent = NULL;
}
