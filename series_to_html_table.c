#include <stdio.h>

int read_from_stdin();
int print_table_start();
int print_table_end();
int print_astatable();

int main(int argc, char **argv){
	int count;
	if(argc == 1){
		printf("<table>\n");
		print_table_start();
		count = read_from_stdin();
		print_table_end();
		printf("</table>\n");
		printf("<br>\n");
		printf("%dunits tested\n",count);
	}
	return(0);
}

int read_from_stdin(){
	int count = 0;
	int n = 0;
	int flag = 1;
	char c;
	char str[10];
	int i = 0;
	int j = 0;
	while(scanf("%c",&c) != EOF){
		if((c != '\n')&&(c != ' ')){
			*(str+i) = c;
			i++;
			flag = 0;
			count = count + 1;
		}else{
			if(flag == 0){
				*(str+i) = '\0';
				sscanf(str,"%d",&n);
				print_astatable(n,count);
				j++;
				i = 0;
				n = 0;
				*str = '\0';
				flag = flag + 1;
			}else{
				flag = flag + 1;
			}
		}
	}
	return(count);
}

int print_table_start(){
	printf("<td valign=top>\n");
	printf("\t<table>\n");
	printf("\t<tr>\n");
	printf("\t\t<td>+</td>\n");
	printf("\t</tr>\n");
	printf("\t</table>\n");
	printf("</td>\n");
	return(0);
}

int print_table_end(){
	printf("<td valign=top>\n");
	printf("\t<table>\n");
	printf("\t<tr>\n");
	printf("\t\t<td>-</td>\n");
	printf("\t</tr>\n");
	printf("\t</table>\n");
	printf("</td>\n");
	return(0);
}

int print_astatable(int n, int p){
	int i;
	printf("<td valign=top>\n");
	printf("\t<table>\n");
	printf("\t<tr>\n");
	printf("\t\t<td>%d</td>\n",p);
	printf("\t</tr>\n");
	printf("\t<tr>\n");
	printf("\t\t<td>_</td>\n");
	printf("\t</tr>\n");
	for(i = 0;i < n;i++){
		printf("\t<tr>\n");
		printf("\t\t<td>*</td>\n");
		printf("\t</tr>\n");
	}
	printf("\t</table>\n");
	printf("</td>\n");
	return(0);
}
