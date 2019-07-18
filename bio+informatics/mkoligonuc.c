#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../../include/sprint_bin.c"
#define DIGIT 2

int main(int argc, char **argv){
	int num;
	char str[33];
	int i;
	int j;
	int times;
	int let;
	sscanf(argv[1],"%d",&let);
	num = pow(4,let);
	times = DIGIT*let;
	for(i=0;i<num;i++){
		sprint_bin(i,str,times);
		for(j=0;j<let;j++){
			if(strncmp(str+(DIGIT*j),"00",2) == 0){
				printf("A");
			}else if(strncmp(str+(DIGIT*j),"01",2) == 0){
				printf("C");
			}else if(strncmp(str+(DIGIT*j),"10",2) == 0){
				printf("G");
			}else if(strncmp(str+(DIGIT*j),"11",2) == 0){
				printf("T");
			}else{
				printf("STR:%s\n",str);
			}
		}
		printf("\n");
	}
	return(0);
}
