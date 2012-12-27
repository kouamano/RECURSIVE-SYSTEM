/* FILE_NAME */
/* bracket_fill.c */
/* END */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* CODE */
int main(int argc, char **argv){
	int c = 0;
	int tr1 = 0;
	int tr2 = 0;
	int tr3 = 0;
	FILE *IN;
	IN = stdin;
	while((c = fgetc(IN)) != EOF){
		if(c == '['){
			tr1++;
		}
		if(c == ']'){
			tr1--;
		}
		if(c == '('){
			tr2++;
		}
		if(c == ')'){
			tr2--;
		}
		if(c == '{'){
			tr3++;
		}
		if(c == '}'){
			tr3--;
		}
		if((tr1 > 0)||(tr2 > 0)||(tr3 > 0)){
			if(c == ' '){
				printf("_");
			}else{
				printf("%c",c);
			}
		}else{
				printf("%c",c);
		}
	}
	return(0);
}
/* END */
