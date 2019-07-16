#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	int n;
	char c;
	int i = 0;
	int j = 0;
	if(argc == 2){
		sscanf(argv[1],"%d",&n);
		printf(">%08d\n",j);
		j++;
		while(scanf("%c",&c) != EOF){
			if(i == n){
				printf("\n>%08d\n",j);
				j++;
				i = 0;
			}
			printf("%c",c);
			i++;
		}
	}else if(argc == 3){
		char filename[512];
		FILE *fp;
		if(strncmp(argv[1],"f=",2) == 0){
			sscanf(argv[1],"f=%s",filename);
			sscanf(argv[2],"%d",&n);
			if((fp = fopen(filename,"r")) == NULL){
				perror(filename);
				exit(1);
			}else{
				printf(">%08d\n",j);
				j++;
				while((c = fgetc(fp)) != EOF){
					if(i == n){
						printf("\n>%08d\n",j);
						j++;
						i = 0;
					}
					printf("%c",c);
					i++;
				}
			}
			fclose(fp);
		}
	}
	return(0);
}
