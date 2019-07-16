#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 4000000
#define MAX_LINES 20000
#define MAX_LENGTH 256
#define SEPA '\n'

struct counter {
	char c[MAX_LENGTH];
	int n;
};

char whole_string[MAX_SIZE];
int whole_string_length = 0;
int string_pointer = 0;
struct counter count[MAX_LINES];

int main(int argc, char **argv){
	int i = 0;
	int j = 0;
	int p = 0;
	char c;
	FILE *IN;
	char fragment[MAX_LENGTH];
	int fragment_length = 0;
	int fragment_pointer = 0;
	struct counter count[MAX_LINES];
	int hit = 0;
	for(i=0;i<MAX_LINES;i++){
		count[i].c[0] = '\0';
		count[i].n = 0;
	}
	if(argc == 1){
		while(scanf("%c",&c) != EOF){
			whole_string[whole_string_length] = c;
			whole_string_length++;
		}
		whole_string[whole_string_length] = '\0';
	}else if(argc == 2){
		if((IN = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
		while((c = fgetc(IN)) != EOF){
			whole_string[whole_string_length] = c;
			whole_string_length++;
		}
		fclose(IN);
		whole_string[whole_string_length] = '\0';
	}
	//printf("%s",whole_string);
	while(whole_string[p] != SEPA){
		fragment[p] = whole_string[p];
		p++;
	}
	if((fragment_length = p-string_pointer) > MAX_LENGTH){
		fprintf(stderr,"warning : fragmnet length was too long.\n");
	}
	strncpy(fragment,whole_string+string_pointer,fragment_length);
	fragment[fragment_length] = '\0';
	//printf("%s = %d\n",fragment,fragment_length);
	strcpy(count[0].c,fragment);
	count[0].n++;
	fragment_pointer++;
	string_pointer = p;

	for(i=p+1;i<whole_string_length;i++){
		if(whole_string[i] == SEPA){
			if((fragment_length = i-string_pointer-1) > MAX_LENGTH){
				fprintf(stderr,"warning : fragmnet length was too long.\n");
			}
			strncpy(fragment,whole_string+string_pointer+1,fragment_length);
			fragment[fragment_length] = '\0';
			for(j=0;j<=fragment_pointer;j++){
				if(strcmp(fragment,count[j].c) != 0){
					if(count[j].c[0] == '\0'){
						strcpy(count[j].c,fragment);
						count[j].n++;
						hit = 0;
						break;
					}
					hit = 0;
				}else if(strcmp(fragment,count[j].c) == 0){
					count[j].n++;
					hit = 1;
					break;
				}
			}
			if(hit == 0){
				fragment_pointer++;
			}
			string_pointer = i;
		}
	}
	for(i=0;i<fragment_pointer;i++){
		printf("%s %d\n",count[i].c,count[i].n);
	}
	return(0);
}
