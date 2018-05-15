#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
	int b;
	int p;
	int out;
	sscanf(argv[1],"%d",&b);
	sscanf(argv[2],"%d",&p);
	out = (int)pow(b,p);
	printf("%d\n",out);
}
