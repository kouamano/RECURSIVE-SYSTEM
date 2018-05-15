#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
	double n;
	if(argc == 1){
		scanf("%lf",&n);
		printf("%lf\n",sqrt(n));
	}else if(argc == 2){
		sscanf(argv[1],"%lf",&n);
		printf("%lf\n",sqrt(n));
	}else{
		printf("argument must be int or float.\n");
		return(1);
	}
	return(0);
}
