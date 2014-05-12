/* match_table_great.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
#define ARR_SIZ 20000
#define STR_SIZ 1024

float score();
float **score_table();

int main(int argc, char **argv){
	char arg[1024];
	long int h,i,j;
	FILE *in;
	char line[1024];
	char string_tmp[argc][1024];
	char *string_f;

	if(argc == 1){				//assign to string_f
		string_f = malloc(sizeof(char)*ARR_SIZ*STR_SIZ);
		h = 0;
		while(scanf("%s",line) != EOF){
			sprintf(string_f+h*STR_SIZ,line);
			h++;
		}
		for(i=0;i<h;i++){
			for(j=0;j<=i;j++){
				printf("%f ",score(string_f+i*STR_SIZ,string_f+j*STR_SIZ));
			}
			printf("\n");
		}
		free(string_f);
	}else{
		sscanf(argv[1],"%s",arg);
		if(strcmp(arg,"-f") == 0){	//assign to string_f
			if((in = fopen(argv[2],"r")) == NULL){
				perror(argv[2]);
				exit(1);
			}else{
				string_f = malloc(sizeof(char)*ARR_SIZ*STR_SIZ);
				h = 0;
				while(fgets(line,sizeof(line),in) != NULL){
					strncpy(string_f+h*STR_SIZ,line,strlen(line)-1);
					h++;
				}
			}
			fclose(in);
			for(i=0;i<h;i++){
				for(j=0;j<=i;j++){
					printf("%f ",score(string_f+i*STR_SIZ,string_f+j*STR_SIZ));
				}
				printf("\n");
			}
			free(string_f);
		}else{				//assign to string_tmp
			for(i=1;i<argc;i++){
				sscanf(argv[i],"%s",string_tmp[i]);
			}
			i = 0;
			for(i=1;i<argc;i++){
				j = 0;
				for(j=1;j<=i;j++){
					printf("%f ",score(string_tmp[i],string_tmp[j]));
				}
				printf("\n");
			}
		}
	}
	return(0);
}	//END main

float score(char *st1, char *st2){
	unsigned int i;
	int len1 = strlen(st1);
	int len2 = strlen(st2);
	int m = 0;
	int maxlen;
	int minlen;
	float p;
	maxlen = max(len1,len2);
	minlen = min(len1,len2);
	for(i=0;i<minlen;i++){
		if(st1[i] == st2[i]){
			m++;
		}
	}
	p = (float)m/(float)maxlen;
	return(p);
}	//END score

/*
max_len(char *st1, char *st2){
	int len1 = strlen(st1);
	int len2 = strlen(st2);
	int len;
	len = max(len1,len2);
	return(len);
}	//END max_len
*/
