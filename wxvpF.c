#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZ 1000

void help(void){
	printf("USAGE:\n");
	printf("  wxvpF <file>\n");
}

char **c_alloc_mat(int num, int dim){
        char **c;
        int i;
        if((c = malloc((size_t)sizeof(char *)*num)) == NULL){
                fprintf(stderr,"[E]failed : malloc() at %ld byte.\n",(long int)sizeof(char *)*num);
                exit(1);
        }
        if((c[0] = malloc((size_t)sizeof(char)*num*dim)) == NULL){
                fprintf(stderr,"[E]failed : malloc() at %ld byte.\n",(long int)sizeof(char)*num*dim);
                exit(1);
        }
        for(i=1;i<num;i++){
                c[i] = c[i-1]+dim;
        }
        return(c);
}


int main(int argc, char **argv){
	char **commlist = NULL;
	int C;
	int LFcount = 0;
	int i;
	int j;
	FILE *IN;

	IN = fopen(argv[1],"r");
	while((C = fgetc(IN)) != EOF){
                if(C == '\n'){
                        LFcount++;
                }
        }
        LFcount++;
	fclose(IN);
	commlist = c_alloc_mat(LFcount,MSG_SIZ);
	//exit(0);
        IN = fopen(argv[1],"r");
        i = 0;
        j = 0;
        while(C = fgetc(IN)){
                if(C == '\n'){
                        j++;
                        commlist[i][j] = '\0';
                        j = 0;
                        i++;
                }else if(C == EOF){
                        j++;
                        commlist[i][j] = '\0';
                        break;
                }else{
                        commlist[i][j] = C;
                        j++;
                }
        }
	fclose(IN);

	/*
	printf("prog:%s:\n",argv[1]);
	if(argv[1] != NULL){
		execvp(argv[1],argv+1);
	}else{
		help();
	}
	*/
	return(0);
}
