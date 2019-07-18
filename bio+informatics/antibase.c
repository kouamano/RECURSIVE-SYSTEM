#include <stdio.h>
#include <stdlib.h>

void print_anti_char_from_stdin();
void print_anti_char_from_file();

int main(int argc, char **argv){
	FILE *fp;
	if(argc == 1){
		print_anti_char_from_stdin();
		printf("\n");
	}else if(argc == 2){
		if((fp = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
		print_anti_char_from_file(fp);
		printf("\n");
		fclose(fp);
	}
	return(0);
}

void print_anti_char_from_stdin(){
	char c;
	while(scanf("%c",&c) != EOF){
		if((c != '\n')&&(c != ' ')){
			if(c == 'A'||c == 'a'){
				printf("T");
			}else if(c == 'T'||c == 't'){
				printf("A");
			}else if(c == 'G'||c == 'g'){
				printf("C");
			}else if(c == 'C'||c == 'c'){
				printf("G");
			}else if(c == 'N'||c == 'n'){
				printf("X");
			}
		}
	}
}

void print_anti_char_from_file(FILE *fp){
	char c;
	while((c = fgetc(fp)) != EOF){
		if((c != '\n')&&(c != ' ')){
			if(c == 'A'||c == 'a'){
				printf("T");
			}else if(c == 'T'||c == 't'){
				printf("A");
			}else if(c == 'G'||c == 'g'){
				printf("C");
			}else if(c == 'C'||c == 'c'){
				printf("G");
			}else if(c == 'N'||c == 'n'){
				printf("X");
			}
		}
	}
}
