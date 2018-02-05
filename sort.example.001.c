#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/alloc.c"

int mat[10][5];
typedef int bigint[10];
//int **mat;
int *vec;

int cmp(int *x, int *y){
	if(*x < *y){
		return(-1);
	}else if(*x > *y){
		return(1);
	}else{
		return(0);
	}
}

int cmp_v(int *x, int *y){
	if(*(x+1) < *(y+1)){
		return(-1);
	}else if(*(x+1) > *(y+1)){
		return(1);
	}else{
		return(0);
	}
}

int main(){
	int i,j;
	/*
	mat = malloc(sizeof(int *)*10);
	for(i=0;i<10;i++){
		mat[i] = malloc(sizeof(int)*5);
	}
	*/
	vec = i_calloc_vec(10);
	vec[0] = 5;
	vec[1] = 0;
	vec[2] = 7;
	vec[3] = 9;
	vec[4] = 15;
	vec[5] = 12;
	vec[8] = 10;
	mat[0][0] = 2;
	mat[0][1] = 7;
	mat[0][2] = 6;
	mat[0][3] = 8;
	mat[0][4] = 7;
	mat[1][1] = 7;
	mat[2][1] = 9;
	mat[3][1] = 10;
	mat[4][1] = 2;
	mat[5][1] = 7;
	mat[6][1] = 8;
	mat[7][1] = 6;
	mat[8][1] = 20;
	mat[9][1] = 1;
	for(i=0;i<10;i++){
		printf("%d\n",vec[i]);
	}
	qsort(vec,10,sizeof(int),(int(*)(const void*, const void*))&cmp);
	printf("-----\n");
	for(i=0;i<10;i++){
		printf("%d\n",vec[i]);
	}
	printf("-----\n");
	for(i=0;i<10;i++){
		for(j=0;j<5;j++){
			printf(" %d",mat[i][j]);
		}
		printf("\n");
	}
	qsort(mat,10,sizeof(int)*5,(int(*)(const void*, const void*))cmp_v);
	printf("-----\n");
	for(i=0;i<10;i++){
		for(j=0;j<5;j++){
			printf(" %d",mat[i][j]);
		}
		printf("\n");
	}
	return(0);
}
