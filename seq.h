#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef BUFF_LEN
#define BUFF_LEN 1024
#endif

//structure
struct Seq {		//<conj><open><Head><close>
	int LVself;
	int ACself;
	int conj;	//is conjugate (,) => Next
	int open;	//open list => Next
	char *Head;
	int close;	//close list => current
	struct Seq *Prev;
	struct Seq *Next;
	struct Seq *Parent;
};

//functions
////restructure function
struct Seq *Function_Create_Seq(void){
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
	(*seq).Prev = NULL;
	(*seq).Next = NULL;
	(*seq).Parent = NULL;
	return(seq);
}
struct Seq *Function_Search_Parent(struct Seq *seq){
	int current_lv;
	int parent_lv;
	struct Seq *parent;
	current_lv = (*seq).LVself;
	parent_lv = current_lv - 1;
	parent = seq;
	if(parent_lv < 1){
		return(parent);
	}
	while((*(*parent).Prev).LVself != parent_lv){
		parent = (*parent).Prev;
	}
	return(parent);
}
struct Seq *Function_Add_Next(struct Seq *_current, struct Seq *_next){
	(*_current).Next = _next;
	(*_next).Prev = _current;
	(*_next).Parent = Function_Search_Parent(_next);
	return(_next);
}
////Print function
void Function_Print_Node(struct Seq *seq){
	printf("$$%ld: :",(*seq).Parent);
	printf("$%ld:",seq);
	printf(":Prev=%ld:",(*seq).Prev);
	printf(":Next=%ld:",(*seq).Next);
	printf(":LVs=%d:",(*seq).LVself);
}

////Apply function
int ExFunction_Recursive_Seq(struct Seq *seq, struct Seq *(*e_function)(struct Seq *)){
	if(e_function != NULL){
		(*e_function)(seq);
	}
	if((*seq).Next != NULL){
		ExFunction_Recursive_Seq((*seq).Next,e_function);
	}
	return(0);
}



