#include <stdio.h>

int main(int argc, char **argv){
	int i;
	int start;
	int stop;
	sscanf(argv[1],"%d",&start);
	sscanf(argv[2],"%d",&stop);
	for(i = start;i <= stop;i++){
		printf("%d\n",i);
	}
}
