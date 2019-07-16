#include <stdio.h>

int print_head();
int print_tail();
int print_table_from_stdin();

int main(int argc, char **argv) {
	int x_pics;
	int y_pics;
	if(argc == 3){
		sscanf(argv[1],"%d",&x_pics);
		sscanf(argv[2],"%d",&y_pics);
		print_table_from_stdin(x_pics,y_pics,5,5);
	}
	return(0);
}

int print_head(){
	printf("<head><title>sequence view</title></head>\n");
	printf("<body>\n");
	return(0);
}

int print_tail(){
	printf("</body>\n");
	return(0);
}

int print_table_from_stdin(int td_num, int tr_num, int wid_col, int hei_row){
	char c;
	int i;
	int j;
	printf("<table dorder=0 cellspacing=0 cellpadding=0>\n");
	i = 0;
	j = 0;
	while(scanf("%c",&c) != EOF){
		if((c != '\n')&&(c != ' ')){
			if(i == 0){
				printf("\t<tr>");
			}
			printf("<td ");
			if(c == 'A'||c == 'a'){
				printf("bgcolor=");
				printf("#0000FF ");
			}
			else if(c == 'T'||c == 't'){
				printf("bgcolor=");
				printf("#00FF00 ");
			}
			else if(c == 'G'||c == 'g'){
				printf("bgcolor=");
				printf("#FF0000 ");
			}
			else if(c == 'C'||c == 'c'){
				printf("bgcolor=");
				printf("#00FFFF ");
			}
			else if(c == 'N'||c == 'n'){
				printf("bgcolor=");
				printf("#FFFFFF ");
			}
			printf("width=%d ",wid_col);
			printf("height=%d",hei_row);
			printf(">");
			printf("%c",c);
			printf("</td>");
			i++;
			if(i == td_num){
				printf("</tr>\n");
				i = 0;
			}
			j++;
		}
	}
	if((j < td_num*tr_num)&&(j%td_num != 0)){
		printf("</tr>\n");
	}
	printf("</table>\n");
	printf("%d ",td_num*tr_num);
	printf("%d ",j);
	printf("%d\n",j%td_num);
	return(0);
}
