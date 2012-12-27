#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	char c;
	char cc;
	int i = 0;
	if(argc == 1){
		printf("countchar <character (1 byte)> <file>\n");
		exit(0);
	}
	if(argc == 2){
		sscanf(argv[1],"%c",&c);
		while((scanf("%c",&cc)) != EOF){
			if(cc == c){
				i++;
			}
		}
	}
	if(argc == 3){
		FILE *in;
		if((in = fopen(argv[2],"r")) == NULL){
			perror(argv[2]);
			exit(1);
		}else{
			sscanf(argv[1],"%c",&c);
			while((cc = fgetc(in)) != EOF){
				if(cc == c){
					i++;
				}
			}
		}
		fclose(in);
	}
	printf("%c:%d\n",c,i);
	return(0);
}
