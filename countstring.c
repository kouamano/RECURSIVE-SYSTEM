#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 4000000
#define MAX_IDS 1000000
#define FRG_LEN 20

struct counter {
	char s[FRG_LEN+1];
	int n;
};

struct counter string_counter[MAX_LEN];
char string[MAX_LEN];
int s_len = 0;

int main(int argc, char **argv){
	int i;
	int j;
	char c;
	int c_len = 0;
	int hit = 0;
	int seg_size = 0;
	int gap_size = 0;
	char file_name[512];
	FILE *IN;
	int loop = 0;
	char fragment[FRG_LEN+1];
	string[0] = '\0';
	for(i=0;i<MAX_LEN;i++){
		string_counter[i].s[0] = '\0';
		string_counter[i].n = 0;
	}
	if(argc == 3){
		sscanf(argv[1],"%d",&seg_size);
		sscanf(argv[2],"%d",&gap_size);
		while(scanf("%c",&c) != EOF){
			string[s_len] = c;
			s_len++;
		}
		string[s_len] = '\0';
	}else if(argc == 4){
		sscanf(argv[1],"%d",&seg_size);
		sscanf(argv[2],"%d",&gap_size);
		sscanf(argv[3],"%s",file_name);
		if((IN = fopen(file_name,"r")) == NULL){
			perror(file_name);
			exit(1);
		}else{
			while((c = fgetc(IN)) != EOF){
				string[s_len] = c;
				s_len++;
			}
			fclose(IN);
			string[s_len] = '\0';
		}
	}
	loop = ((s_len-seg_size-1)/gap_size);
	strncpy(fragment,string+(0*gap_size),seg_size);
	fragment[seg_size] = '\0';
	strcpy(string_counter[0].s,fragment);
	string_counter[0].n++;
	c_len = 1;
	for(i=1;i<=loop;i++){
		strncpy(fragment,string+(i*gap_size),seg_size);
		fragment[seg_size] = '\0';
		for(j=0;j<=c_len;j++){
			if(strcmp(fragment,string_counter[j].s) != 0){
				if(string_counter[j].s[0] == '\0'){
					strcpy(string_counter[j].s,fragment);
					string_counter[j].n++;
					hit = 0;
					break;
				}
				hit = 0;
			}else if(strcmp(fragment,string_counter[j].s) == 0){
				string_counter[j].n++;
				hit = 1;
				break;
			}
		}
		if(hit == 0){
			c_len++;
		}
	}
	for(i=0;i<c_len;i++){
		printf("%s ",string_counter[i].s);
		printf("%d\n",string_counter[i].n);
	}
	return(1);
}
