#include <stdio.h>

int main(int argc, char *argv[]){
	long base;
	long op;
	long mod;
	if(argc == 1){
		exit(0);
	}else if(argc == 2){
		sscanf(argv[1],"%d",&base);
		scanf("%d",&op);
	}else if(argc == 3){
		sscanf(argv[1],"%d",&op);
		sscanf(argv[2],"%d",&base);
	}
	mod = op%base;
	printf("%d\n",mod);
	return(1);
}
