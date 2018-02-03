/* Floyd-Warshall method                 */
/*  needs : dmat (input)                 */
/*   inf : -1                            */
/*  needs : pmat (for route reconstruct) */
/*   no link : -1                        */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024
#define SEPS "\t "
#include "../include/alloc.c"
#include "../include/data_read.c"
#include "../include/math_base.c"

struct options {
	int help;
	int stat;
	int check;
	int size;
	char *dmat;
	char *pmat;
};

void help(void){
	printf("USAGE:\n");
	printf(" Fl-Wrs [-h] [-s] [-c] dmat=<distance matrix file> pmat=<routematrix> size=<no. of nodes> \n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  size : no. of nodes [integer].\n");
	printf("  dmat : distance matrix file [string].\n");
	printf("  pmat : route information matrix (output file) [string].\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Under construction: just copied from code of MST.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).dmat = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).pmat = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).size= 0;
	(*opt).dmat[0] = '\0';
	(*opt).pmat[0] = '\0';
}

void get_options(int optc, char **optv, struct options *opt){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-s") == 0){
			(*opt).stat = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check = 1;
		}else if(strncmp(optv[i],"size=",5) == 0){
			sscanf(optv[i],"size=%d",&(*opt).size);
		}else if(strncmp(optv[i],"dmat=",5) == 0){
			sscanf(optv[i],"dmat=%s",(*opt).dmat);
		}else if(strncmp(optv[i],"pmat=",5) == 0){
			sscanf(optv[i],"pmat=%s",(*opt).pmat);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.size:%d:\n",(*opt).size);
	printf(" opt.dmat:%s:\n",(*opt).dmat);
	printf(" opt.pmat:%s:\n",(*opt).pmat);
}




int main(int argc, char **argv){
	float **dmat;
	FILE *fp;
	int c;
	int i,j;

	struct options *opt;
	int ie=0;
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	if(argc == 1){
		(*opt).help = 1;
	}
	if((*opt).help == 1){
		help();
		ie = 1;
	}
	if((*opt).stat == 1){
		status();
		ie = 1;
	}
	if((*opt).check == 1){
		check_options(opt);
		ie = 1;
	}
	if(ie == 1){
		exit(0);
	}
	//if opt.size == 0; automatic
	if((*opt).size == 0){	//auto-get of size
		int col = 0;
		if((fp = fopen((*opt).dmat,"r")) == NULL){
		perror((*opt).dmat);
		exit(1);
		}
		while((c=fgetc(fp)) != EOF){
			if(c == SEPS[0]||c == SEPS[1]){
				col++;
			} else if(c == '\n'){
				break;
			}else{
				;
			}
		}
		fclose(fp);
		((*opt).size)=col + 1;
	}
	//printf(";;;%d;;;\n",(*opt).size);

	dmat = f_alloc_mat((*opt).size,(*opt).size);
	if((fp = fopen((*opt).dmat,"r")) == NULL){
		perror((*opt).dmat);
		exit(1);
	}
	read_ftable_from_stream((*opt).size, (*opt).size,fp,dmat);
	fclose(fp);
	/*
        for(i=0;i<(*opt).size;i++){
                for(j=0;j<(*opt).size;j++){
                        printf("%f ",dmat[i][j]);
                }
                printf("\n");
        }
	*/



	return(0);
}
