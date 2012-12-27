#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *read_from_stdin();
char *str_shift();
//char *test();
static int s_size, g_size, offset;

int main(int argc, char **argv){
	char *str;
	if(argc == 4){
		sscanf(argv[1],"%d",&s_size);
		sscanf(argv[2],"%d",&g_size);
		sscanf(argv[3],"%d",&offset);
	}
	str = malloc(s_size*sizeof(char));
	read_from_stdin();
	return(0);
}

char *read_from_stdin(){
	char c;
	char *cc;
	//char first_str[s_size+1];
	char *str;
	int j;
	str = malloc((s_size+1)*sizeof(char));
	j = 0;
	while(scanf("%c",&c)){
		if((c != '\n')&&(c != ' ')){
			if(j == s_size){
				*(str+j) = '\0';
				break;
			}else{
				*(str+j) = c;
				j++;
			}
		}
	}
	printf("%s",str);
	while(scanf("%c",&c) != EOF){
		if((c != '\n')&&(c != ' ')){
			cc[0] = c;
			cc[1] = '\0';
			str = str_shift(cc,str,s_size,g_size);
		}
	}
	return(str);
}

char *str_shift(char *str, char *c, int len, int gap){
	char *str2;
	int i;
	str2 = malloc((len+1)*sizeof(char));
	for(i=0;i<len;i++){
		*(str2+i) = *(str+i+gap);
	}
	*(str2+i) = '\0';
	strcat(str2,c);
	return(str2);
}

int test(char c, char *str){
	printf("%c",c);
	return(0);
}
