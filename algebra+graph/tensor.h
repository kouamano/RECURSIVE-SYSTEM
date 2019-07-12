/* tensor.c */
#include <stdio.h>
#include <stdlib.h>
#define DEPTH 4
int main(void){
	struct intTensor IT;
	int point[DEPTH] = {2,1,3,4};
	int v_read;
	IT.depth = DEPTH;
	IT.size = malloc(sizeof(int) * DEPTH);
	IT.size[0] = 3;
	IT.size[1] = 2;
	IT.size[2] = 4;
	IT.size[3] = 5;
	IT.value = malloc(sizeof(int) * intProduct(IT.depth,IT.size));
	IT.value[23] = 23;
	IT.value[119] = 11900;
	v_read = readPointIntTensor(point,&IT);
	printf("%d\n",v_read);
	return(0);
}
