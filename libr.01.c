#include <stdio.h>
#include <stdlib.h>

int main(){
	printf("int             \t:%ld:\tbyte\n",sizeof(int));
	  int a[2][2];
	printf("int 2D:2x2      \t:%ld:\tbyte\n",sizeof(a));
	printf("pointer int*    \t:%ld:\tbyte\n",sizeof(int*));
	return(0);
}
