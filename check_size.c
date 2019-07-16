#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <complex.h>

int main(){
	printf("char                        \t:%ld:\tbyte\n",sizeof(char));
	printf("_Bool                       \t:%ld:\tbyte\n",sizeof(_Bool));
	printf("mode_t                      \t:%ld:\tbyte\n",sizeof(mode_t));
	printf("short int                   \t:%ld:\tbyte\n",sizeof(short int));
	printf("int                         \t:%ld:\tbyte\n",sizeof(int));
	  int a[2][2];
	printf("int 2D:2x2                  \t:%ld:\tbyte\n",sizeof(a));
	printf("long int                    \t:%ld:\tbyte\n",sizeof(long int));
	printf("long long int               \t:%ld:\tbyte\n",sizeof(long long int));
	printf("float                       \t:%ld:\tbyte\n",sizeof(float));
	  float b[2][2];
	printf("float 2D:2x2                \t:%ld:\tbyte\n",sizeof(b));
	printf("double                      \t:%ld:\tbyte\n",sizeof(double));
	printf("long double                 \t:%ld:\tbyte\n",sizeof(long double));
	printf("_Complex                    \t:%ld:\tbyte\n",sizeof(_Complex));
	printf("complex                     \t:%ld:\tbyte\n",sizeof(complex));
	  complex c;
	printf("complex __real__            \t:%ld:\tbyte\n",sizeof(__real__ c));
	printf("complex __imag__            \t:%ld:\tbyte\n",sizeof(__imag__ c));
	printf("double _Complex             \t:%ld:\tbyte\n",sizeof(double _Complex));
	  double _Complex d;
	printf("double _Comples __real__    \t:%ld:\tbyte\n",sizeof(__real__ d));
	printf("double _Comples __imag__    \t:%ld:\tbyte\n",sizeof(__imag__ d));
	printf("size_t                      \t:%ld:\tbyte\n",sizeof(size_t));
	printf("time_t                      \t:%ld:\tbyte\n",sizeof(time_t));
	printf("void                        \t:%ld:\tbyte\n",sizeof(void));
	printf("pointer char*               \t:%ld:\tbyte\n",sizeof(char*));
	printf("pointer int*                \t:%ld:\tbyte\n",sizeof(int*));
	printf("pointer double*             \t:%ld:\tbyte\n",sizeof(double*));
	printf("pointer void*               \t:%ld:\tbyte\n",sizeof(void*));
	return(0);
}
