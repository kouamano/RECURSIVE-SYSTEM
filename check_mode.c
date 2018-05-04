#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	printf("S_IRWXU         \t:%ld:\t00700\n",S_IRWXU);
	printf("S_IRUSR         \t:%ld:\t00400\n",S_IRUSR);
	printf("S_IWUSR         \t:%ld:\t00200\n",S_IWUSR);
	return(0);
}
