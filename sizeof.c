#include <stdio.h>
#include <stdlib.h>

int *vec;

int main(void){
	vec = malloc(sizeof(int)*4);
	printf("Type      :size in bytes:\n");
	printf("char            :%d:\n",(int)sizeof(char));
	printf("int             :%d:\n",(int)sizeof(int));
	printf("float           :%d:\n",(int)sizeof(float));
	printf("double          :%d:\n",(int)sizeof(double));
	printf("long int        :%d:\n",(int)sizeof(long int));
	printf("long double     :%d:\n",(int)sizeof(long double));
	printf("long long int   :%d:\n",(int)sizeof(long long int));
	printf("char *          :%d:\n",(int)sizeof(char *));
	printf("int *           :%d:\n",(int)sizeof(int *));
	printf("float *         :%d:\n",(int)sizeof(float *));
	printf("double *        :%d:\n",(int)sizeof(double *));
	return(0);
}
