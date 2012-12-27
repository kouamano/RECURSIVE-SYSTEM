#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MASK0 255
#define MASK1 65280
#define MASK2 16711680
#define MASK3 4278190080
#define MASK4 1095216660480
#define MASK5 280375465082880
#define MASK6 71776119061217280
#define MASK7 18374686479671623680u


typedef union{
        unsigned int IN;
        char CH[5];
}Fgram;

typedef union{
	long long unsigned int IN;
	char CH[9];
}Egram;

Fgram fgram;
Egram egram;
Egram query;
Egram query2;
Egram query3;

int main(){
	int i;
	for(i=0;i<9;i++){
		egram.CH[i] = 0;
	}
	for(i=0;i<9;i++){
		query.CH[i] = 0;
		query2.CH[i] = 0;
		query3.CH[i] = 0;
	}
	for(i=0;i<4;i++){
		fgram.CH[i] = 0;
	}
	fgram.CH[4] = 'X';
	fgram.CH[5] = 'X';
	printf("size of Fgram:%d:\n",sizeof(Fgram));

	query.CH[0] = 'c';
	query.CH[1] = 'd';

	query2.CH[0] = 'a';
	query2.CH[1] = 'b';
	query2.CH[2] = 'c';
	query2.CH[3] = 'd';

	query3.CH[0] = 'O';
	query3.CH[1] = 'N';

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
	printf("len(f):%d:\n",strlen(fgram.CH));
	printf("e:%llX:\n",egram.IN);
	printf("q:%llX:\n",query.IN);
	printf("q2:%llX:\n",query2.IN);
	query2.IN = query2.IN >> 8;
	printf("q2 shift1:%llX:\n",query2.IN);
	query2.IN = query2.IN >> 8;
	printf("q2 shift2:%llX:\n",query2.IN);
	printf("q3:%llX:\n",query3.IN);
	printf("e [mask0]:%llx:\n",egram.IN&MASK0);
	printf("e [mask1]:%llx:\n",egram.IN&MASK1);
	printf("e [mask2]:%llx:\n",egram.IN&MASK2);
	printf("e [mask3]:%llx:\n",egram.IN&MASK3);
	printf("e [mask4]:%llx:\n",egram.IN&MASK4);
	printf("e [mask5]:%llx:\n",egram.IN&MASK5);
	printf("e [mask6]:%llx:\n",egram.IN&MASK6);
	printf("e [mask7]:%llx:\n",egram.IN&MASK7);
	//egram.IN&MASK7;
	printf("e [mask0-1]:%llx:\n",egram.IN&(MASK1+MASK0));
	printf("e [mask0-3]:%llx:\n",egram.IN&(MASK3+MASK2+MASK1+MASK0));
	return(0);
}
