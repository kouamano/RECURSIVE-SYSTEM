#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void nb(char *str){
	int i;
	int n;
	char cc[2];
	char str2[256];
	int l = 0;
	//printf(":::%s:::",str);
	l = strlen(str);
	if((strcmp(str,"0") == 0)||(strcmp(str,"3") == 0)||(strcmp(str,"6") == 0)||(strcmp(str,"9") == 0)){
		printf("3!\n");
	}else if(l > 1){
		n = 0;
		for(i=0;i<=l;i++){
			cc[0] = str[i];
			cc[1] = '\0';
			n = n + atoi(cc);
			//printf("--%d--",n);
		}
		sprintf(str2,"%d",n);
		nb(str2);
	}else{
		printf("%s\n",str);
	}
}

int main(int argc, char **argv){
	if(argc > 1){
		nb(argv[1]);
	}
	return(0);
}
