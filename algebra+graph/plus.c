#include <stdio.h>
#include <math.h>

main(int argc, char **argv){
	int i;
	float tmp=0;
	float var=0;
	if(argc == 1){
		while(scanf("%f",&tmp) != EOF){
			var = var+tmp;
		}
	printf("%f\n",var);
	}else{
		for(i=1;i<argc;i++){
			sscanf(argv[i],"%f",&tmp);
			var = var+tmp;
		}
	printf("%f\n",var);
	}
}
