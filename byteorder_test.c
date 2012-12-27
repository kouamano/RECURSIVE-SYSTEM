#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef union{
        unsigned int IN;
        char CH[4];
}Fgram;

typedef union{
	unsigned long long int IN;
	char CH[8];
}Egram;

Fgram fgram;
Egram egram;

int main(){
	fgram.CH[0] = 'a';
	fgram.CH[1] = 'b';
	fgram.CH[2] = 'c';
	fgram.CH[3] = 'd';
	egram.CH[0] = 'a';
	egram.CH[1] = 'b';
	egram.CH[2] = 'c';
	egram.CH[3] = 'd';
	egram.CH[4] = 'e';
	egram.CH[5] = 'f';
	egram.CH[6] = 'g';
	egram.CH[7] = 'h';
	printf("f:%x:\n",fgram.IN);
	printf("e:%lx:\n",egram.IN);
	return(0);
}
