#include <stdio.h>
#include <math.h>

int main(int argc, char **argv){
	int i;
	float tmp=1;
	float var=1;
	if(argc == 1){
		while(scanf("%f",&tmp) != EOF){
			var = var*tmp;
		}
		printf("%f\n",var);
	}else{
		for(i=1;i<argc;i++){
			sscanf(argv[i],"%f",&tmp);
			var = var*tmp;
		}
		printf("%f\n",var);
	}
	return(0);
}
			
