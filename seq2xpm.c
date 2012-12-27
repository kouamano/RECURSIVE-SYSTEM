#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	static unsigned int i=0;
	static unsigned int count=0;
	unsigned int j;
	char cc;
	unsigned int wid;
	unsigned int hig;
	unsigned int res;
	sscanf(argv[1],"%d",&wid);
	sscanf(argv[2],"%d",&hig);

	printf("%s","/* XPM */\n");
	printf("%s","static char * sequence_xpm[] = {\n");
	printf("%c",'\"');
	printf("%d %d %d %d",wid,hig,11,1);
	printf("%s","\",\n");
	printf("\"A c #ff0000\",\n");
	printf("\"a c #ff0000\",\n");
	printf("\"C c #000000\",\n");
	printf("\"c c #000000\",\n");
	printf("\"G c #ffffff\",\n");
	printf("\"g c #ffffff\",\n");
	printf("\"T c #00ffff\",\n");
	printf("\"t c #00ffff\",\n");
	printf("\"N c #808080\",\n");
	printf("\"n c #808080\",\n");
	printf("\"X c white\",\n");

	while(scanf("%c",&cc) != EOF){
		if(cc != '\n'){
			if(i == 0){
				printf("%c",'\"');
			}
			printf("%c",cc);
			i++;
			if(i == wid){
				printf("%c",'\"');
				printf("%c",',');
				printf("%c",'\n');
				count++;
				i=0;
			}
		}
	}
	if(i != 0){
		res = wid - i;
		for(j=0; j<res; j++){
			printf("%c",'X');
		}
		printf("%c",'\"');
		printf("%c",',');
		printf("%c",'\n');
		count = count+1;
	}
/*
	if(count < hig){
		app = hig-count;
		for(j=0; j<app; j++){
			printf("\"");
			for(k=0; k<wid; k++){
				printf("X");
			}
			printf("\"\n");
		}
	}
*/
	printf("};");
	return(0);
}
