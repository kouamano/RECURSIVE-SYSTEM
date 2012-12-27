#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR "00004f00"

char *str;

int main(){
	unsigned long long int ulli = 0;
	unsigned long long int ullj = 0;
	str = calloc(100,sizeof(char));
	sprintf(str,"%s",STR);
	printf(":%s:@str\n",str);

	printf("--- using strtoull() ---\n");
	ulli = strtoull(str,NULL,16);
	printf(":%llX:@16\n",ulli);
	printf(":%lld:@10\n",ulli);

	printf("--- using sscanf() ---\n");
	sscanf(str,"%llX",&ullj);
	printf(":%llX:@16\n",ullj);
	return(0);
}
