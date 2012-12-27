#include <stdio.h>

int fib(int n){
	int out;
	if(n == 0){
		out = 1;
	}else if(n == 1){
		out = 1;
	}else{
		out = fib(n-1) + fib(n-2);
	}
	return(out);
}

int main(int argc, char **argv){
	int m;
	sscanf(argv[1],"%d",&m);
	printf("%d\n",fib(m));
}
