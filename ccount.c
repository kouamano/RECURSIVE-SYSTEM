#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 4000000

struct counter {
	char c;
	int n;
};
static char string[MAX_LEN+1];
static struct counter count[MAX_LEN];

int main(int argc, char **argv){
	int i;
	int j;
	signed char c;
	int s_len = 0;
	int c_len = 0;
	int hit = 0;
	FILE *IN;
	for(i=0;i<MAX_LEN;i++){
		count[i].c = '\0';
		count[i].n = 0;
	}
	if(argc == 1){
		while(scanf("%c",&c) != EOF){
			string[s_len] = c;
			s_len++;
		}
		string[s_len] = '\0';
	}else if(argc == 2){
		if((IN = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
		while((c = fgetc(IN)) != EOF){
			string[s_len] = c;
			s_len++;
		}
		fclose(IN);
		string[s_len] = '\0';
	}
	count[0].c = string[0];
	count[0].n++;
	c_len = 1;
	for(i=1;i<=s_len;i++){
		for(j=0;j<=c_len;j++){
			if(string[i] != count[j].c){
				if(count[j].c == '\0'){
					count[j].c = string[i];
					count[j].n++;
					hit = 0;
					break;
				}
				hit = 0;
			}else if(string[i] == count[j].c){
				count[j].n++;
				hit = 1;
				break;
			}
		}
		if(hit == 0){
			c_len++;
		}
	}
	/*printf("c_len:%d\n",c_len);*/
	for(i=0;i<c_len;i++){
		if(count[i].c == '\n'){
			printf("%s\t%d\n","\\n",count[i].n);
		}else if(count[i].c == '\r'){
			printf("%s\t%d\n","\\r",count[i].n);
		}else if(count[i].c == '\t'){
			printf("%s\t%d\n","\\t",count[i].n);
		}else if(count[i].c == ' '){
			printf("%s\t%d\n","\\s",count[i].n);
		}else{
			printf("%c\t%d\n",count[i].c,count[i].n);
		}
	}
	return(0);
}
