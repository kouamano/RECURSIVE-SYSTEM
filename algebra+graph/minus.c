#include <stdio.h>
#include <math.h>

main(int argc, char **argv){
	int i;
	float start=0;
	float tmp=0;
	float var=0;
	if(argc == 1){
		scanf("%f",&start);
		var = start;
		while(scanf("%f",&tmp) != EOF){
			var = var-tmp;
		}
		printf("%f",var);
	}else{
		sscanf(argv[1],"%f",&start);
		var = start;
		for(i=2;i<argc;i++){
			sscanf(argv[i],"%f",&tmp);
			var = var-tmp;
		}
		printf("%f\n",var);
	}
}
