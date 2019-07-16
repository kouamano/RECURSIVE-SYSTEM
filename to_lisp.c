#include <stdio.h>

int main(int argc, char **argv){
	char c;
	while(scanf("%c",&c) != EOF){
		if(c == '('){
			printf("(list ");
		}else if(c == ','){
			printf(" ");
		}else if(c == ':'){
			printf(" ");
		}else{
			printf("%c",c);
		}
	}
	return(0);
}
