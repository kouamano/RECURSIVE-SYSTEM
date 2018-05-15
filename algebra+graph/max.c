#include <stdio.h>
#include <math.h>
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif

main(int argc, char **argv){
	int i;
	int tmp;
	int maximum;
	int flag = 0;
	if(argc == 1){
		while(scanf("%d",&tmp) != EOF){
			if(flag == 1){
				maximum = max(maximum,tmp);
			}else if(flag == 0){
				maximum = tmp;
				flag = 1;
			}
		}
	}
	printf("%d\n",maximum);
}
