#include <stdio.h>
int read_from_stdin(char *);

int flag = 0;

int main(int argc, char **argv){
	if(argc == 1){
		char arr[1024];
		read_from_stdin(arr);
		printf("%s",arr);
		printf("%d",flag);
		read_from_stdin(arr);
		printf("%s",arr);
		printf("%d",flag);
		//read_from_stdin(arr);
		//printf("%s",arr);
		//printf("%d",flag);
	}
	return(0);
}

int read_from_stdin(char *arr){
	char c;
	int i = 0;
	int n = 0;
	flag = 0;
	while(n == 0){
		scanf("%c",&c);
		if(c == '*'){
			//*(arr+i) = '\0';
			break;
		}else if(c != EOF){
			*(arr+i) = c;
			i++;
		}
	}
	*(arr+i) = '\0';
	return(0);
}
