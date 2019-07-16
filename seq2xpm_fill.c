#include <stdio.h>
#include <string.h>

int main(int argc, char **argv){
	static unsigned int i=0;
	static unsigned int count=0;
	unsigned int j;
	unsigned int k;
	char cc;
	unsigned int wid;
	unsigned int hig;
	unsigned int app;
	unsigned int res;
	sscanf(argv[1],"%d",&wid);
	sscanf(argv[2],"%d",&hig);

	printf("%s","/* XPM */\n");
	printf("%s","static char * test_xpm[] = {\n");
	printf("%c",'\"');
	printf("%d %d %d %d",wid,hig,4,1);
	printf("%s","\"\n");
	printf("\"A c #fff000\"\n");
	printf("\"C c #f0f0f0\"\n");
	printf("\"G c #000fff\"\n");
	printf("\"T c #0f0f0f\"\n");
	printf("\"X c white\"\n");

	while(scanf("%c",&cc) != EOF){
		if(cc != '\n'){
			if(i == 0){
				printf("%c",'\"');
			}
			printf("%c",cc);
			i++;
			if(i == wid){
				printf("%c",'\"');
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
		printf("%c",'\n');
		count = count+1;
	}
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
	printf("};");
	return(0);
}
