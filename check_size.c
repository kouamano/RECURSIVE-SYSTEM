#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("char            \t:%ld:\tbyte\n",sizeof(char));
	printf("_Bool           \t:%ld:\tbyte\n",sizeof(_Bool));
	printf("short int       \t:%ld:\tbyte\n",sizeof(short int));
	printf("int             \t:%ld:\tbyte\n",sizeof(int));
	  int a[2][2];
	printf("int 2D:2x2      \t:%ld:\tbyte\n",sizeof(a));
	printf("long int        \t:%ld:\tbyte\n",sizeof(long int));
	printf("long long int   \t:%ld:\tbyte\n",sizeof(long long int));
	printf("float           \t:%ld:\tbyte\n",sizeof(float));
	  int b[2][2];
	printf("float 2D:2x2    \t:%ld:\tbyte\n",sizeof(b));
	printf("double          \t:%ld:\tbyte\n",sizeof(double));
	printf("long double     \t:%ld:\tbyte\n",sizeof(long double));
	printf("size_t          \t:%ld:\tbyte\n",sizeof(size_t));
	printf("time_t          \t:%ld:\tbyte\n",sizeof(time_t));
	printf("void            \t:%ld:\tbyte\n",sizeof(void));
	printf("pointer char*   \t:%ld:\tbyte\n",sizeof(char*));
	printf("pointer int*    \t:%ld:\tbyte\n",sizeof(int*));
	printf("pointer double* \t:%ld:\tbyte\n",sizeof(double*));
	printf("pointer void*   \t:%ld:\tbyte\n",sizeof(void*));
	return(0);
}
