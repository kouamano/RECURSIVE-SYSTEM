#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define LEN 1024
#define INTR 60

int main(int argc, char **argv){
	if(argc == 3){
		int i;
		char proc[128];
		char file[256];
		FILE *ifp;
		FILE *ofp;
		char of[128];
		char c;
		char line[LEN];
		sscanf(argv[1],"%s",&proc);
		sprintf(file,"/proc/%s/status",proc);
		sscanf(argv[2],"%s",&of);
		printf("%s\n",file);
		for(;;){
			sleep(INTR);
			if((ifp = fopen(file,"r")) == NULL){
				perror(file);
				exit(1);
			}
			if((ofp = fopen(of,"a")) == NULL){
				perror(of);
				exit(1);
			}
			while((fgets(line,LEN,ifp)) != NULL){
				if(strncmp(line,"VmRSS",5) == 0){
					printf("%s",line);
					fputs(line,ofp);
				}
			}
			fclose(ofp);
			fclose(ifp);
		}
		exit(0);
	}
}
