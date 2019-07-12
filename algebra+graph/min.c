#include <stdio.h>
#include <math.h>
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif

int main(int argc, char **argv){
	int i;
	int tmp;
	int minimum;
	int flag = 0;
	if(argc == 1){
		while(scanf("%d",&tmp) != EOF){
			if(flag == 1){
				minimum = min(minimum,tmp);
			}else if(flag == 0){
				minimum = tmp;
				flag = 1;
			}
		}
	}
	printf("%d\n",minimum);
	return(0);
}
