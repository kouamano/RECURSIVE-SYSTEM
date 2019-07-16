#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int *string_match(char *str1, char *str2){
	int *arr;
	int len1,len2;
	int i,j;
	int k=0;
	len1 = strlen(str1);
	len2 = strlen(str2);
	arr = malloc(sizeof(int)*len1*len2);
	for(i=0;i<len1;i++){
		for(j=0;j<len2;j++){
			if(str1[i] == str2[j]){
				arr[k] = 1;
				k++;
			}else{
				arr[k] = 0;
				k++;
			}
		}
	}
	return(arr);
}

int string_match_print(char *str1, char *str2){
	int len1,len2;
	int i,j;
	len1 = strlen(str1);
	len2 = strlen(str2);
	for(i=0;i<len1;i++){
		for(j=0;j<len2;j++){
			if(str1[i] == str2[j]){
				printf("%s","1 ");
			}else{
				printf("%s","0 ");
			}
		}
		printf("%c",'\n');
	}
	return(0);
}

int main(int argc, char **argv){
	char string1[4096];
	char string2[4096];
	int str_len1,str_len2;	//#
	int *a;
	int i,j;
	if(argc == 3){
		sscanf(argv[1],"%s",string1);
		sscanf(argv[2],"%s",string2);
		str_len1 = strlen(string1);	//#
		str_len2 = strlen(string2);	//#
		string_match_print(string1,string2);
		printf("%s\n","next");
		a = string_match(string1,string2);
		for(i=0;i<str_len1;i++){
			for(j=0;j<str_len2;j++){
				printf("%d ",a[i*str_len2+j]);
			}
			printf("%c",'\n');
		}
		printf("%s\n","next");
		for(i=0;i<str_len1*str_len2;i++){
			printf("%d",a[i]);
		}
		printf("%c",'\n');
	}
	return(0);
}


