#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/strop.c"
#define MAX_LEN_STR 1000
#define MAX_LEN_LIST 200
#define MAX_LINE_TABLE 10000
#define MAX_COLUMN_TABLE 64

struct Table {
	int head;
	int tail;
	char *body;
};

struct Cell {
	int head;
	int tail;
	char *body;
	//struct Cell *prev;
	int prev;
	int leaf_node;
};

struct Table *AllocTable(int size, int body_size){
	int i;
	struct Table *out;
	if((out = calloc(size,sizeof(struct Table))) == NULL){
		printf("failed: malloc();\n");
		exit(1);
	}
	for(i=0;i<size;i++){
		out[i].body = calloc(body_size,sizeof(char));
	}
	return(out);
};

struct Cell *AllocCell(int size, int body_size){
	int i;
	struct Cell *out;
	if((out = calloc(size,sizeof(struct Cell))) == NULL){
		printf("failed: malloc().\n");
		exit(1);
	}
	for(i=0;i<size;i++){
		out[i].body = calloc(body_size,sizeof(char));
	}
	return(out);
}

int read_table_from_stream(FILE *IN, struct Table *table){
	char c;
	char tmp[MAX_LEN_STR];
	int p_tmp = 0;
	int p_cell = 0;
	while((c = fgetc(IN)) != EOF){
		if(c == '\n'){
			tmp[p_tmp] = 0;
			sscanf(tmp,"%d,%d,%s",&table[p_cell].head,&table[p_cell].tail,table[p_cell].body);
			p_tmp = 0;
			p_cell++;
		}else{
			tmp[p_tmp] = c;
			p_tmp++;
		}
	}
	return(p_cell);
}
/*
int search_from_table(int current_point, struct Cell cell, int table_size, struct Table *table, struct Table *out){
	int i = 0;
	int p_out = 0;
	int size_out = 0;
	for(i=0;i<table_size;i++){
		if(cell.tail == table[i].head){
			out[p_out].head = table[i].head
			size_out++;
		}
	}
	return(0);
}
*/

int print_recursive(struct Cell cell, struct Cell *list, char *separator){
	printf("%s%s",cell.body,separator);
	if(cell.prev >= 0){
		print_recursive(list[cell.prev],list,separator);
	}else{
		return(0);
	}
	return(0);
};


int main(int argc, char **argv){
	int i;
	FILE *IN;
	struct Table *table;
	table = AllocTable(MAX_LEN_LIST,100);
	struct Table *ref_table;
	ref_table = AllocTable(MAX_LEN_LIST,100);
	int len_table;
	struct Cell *list;
	char tmp_str[MAX_LEN_STR];
	char *tmp_str2;
	list = AllocCell(MAX_LEN_LIST,100);
	IN = fopen(argv[1],"r");
	len_table = read_table_from_stream(IN,table);
	fclose(IN);
	for(i=0;i<len_table;i++){
		//printf("%d %d %s\n",table[i].head,table[i].tail,table[i].body);
	}
	list[0].head = table[0].head;
	list[0].tail = table[0].tail;
	strcpy(list[0].body,table[0].body);
	list[0].prev = -1;
	list[0].leaf_node = 0;
	int list_pointer = 0;
	int add_pointer = 0;
	int last_pointer = 0;
	int k = 0;
	while(list[list_pointer].body[0] != 0){
		for(i=0;i<len_table;i++){
			if(list[list_pointer].tail == table[i].head){
				last_pointer++;
				add_pointer++;
				list[list_pointer].leaf_node = 0;
				list[last_pointer].head = table[i].head;
				list[last_pointer].tail = table[i].tail;
				strcpy(list[last_pointer].body,table[i].body);
				list[last_pointer].prev = list_pointer;
			}
		}
		if(add_pointer == 0){
			list[list_pointer].leaf_node = 1;
		}
		list_pointer++;
		k++;
		add_pointer = 0;
	}
	for(i=0;i<list_pointer;i++){
		//printf("%s ",list[i].body);
		//printf("%d\n",list[i].leaf_node);
	}
	printf("----- ----- ---- \n");
	for(i=0;i<list_pointer;i++){
		strrev(list[i].body);
	}
	for(i=0;i<list_pointer;i++){
		if(list[i].leaf_node == 1){
			print_recursive(list[i],list,"-");
			printf("\n");
		}
	}
	printf("----- ----- ---- \n");
	strcpy(tmp_str,"1234");
	printf(":%s:\n",tmp_str);
	tmp_str2 = strrev(tmp_str);
	printf(":%s:\n",tmp_str2);
	printf(":%s:\n",tmp_str);
	return(0);
}
