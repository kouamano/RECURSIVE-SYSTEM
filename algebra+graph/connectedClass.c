/*connectedClass                      */
/* input : dfile -> adjacency matrix  */
/* connected : >= 1                   */
/* not-connected : 0                  */
/* diagonal : class                   */
/* output : Node Id list with class   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/alloc.c"
#include "../../include/data_read.c"
#define FILE_NAME_LEN 1024
#define SEPS "\t "

struct options {
	int help;
	int stat;
	int check;
	int create;
	int print;
	char *dfile;
	int msize;
};

void help(void){
	printf("DESCRIPTION:\n");
	printf(" connectedClass prints node IDs with its connected-class from adjacency matrix.\n");
	printf("USAGE:\n");
	printf(" connectedClass [-h] [-s] [-c] [-A|-a] [-m] df=<file of distance matrix> size=<matrix size> .\n");
	printf("  -h : help.\n");
	printf("  -s : status.\n");
	printf("  -c : check args.\n");
	printf("  -A|-a : create/not create the symmetric adjacency matrix from input.\n");
	printf("  -m : print matrix.\n");
	printf("  file of distance matrix : with no header.\n");
	printf("  matrix size (size=0 :: auto) : size of square matrix.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Testing.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).dfile = malloc(sizeof(char) * FILE_NAME_LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).create = 1;
	(*opt).print = 0;
	(*opt).dfile[0] = '\0';
	(*opt).msize = 0;
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
		}else if(strcmp(optv[i],"-a") == 0){
			(*opt).create = 0;
		}else if(strcmp(optv[i],"-A") == 0){
			(*opt).create = 1;
		}else if(strcmp(optv[i],"-m") == 0){
			(*opt).print = 1;
		}else if(strncmp(optv[i],"df=",3) == 0){
			sscanf(optv[i],"df=%s",(*opt).dfile);
		}else if(strncmp(optv[i],"size=",5) == 0){
			sscanf(optv[i],"size=%d",&(*opt).msize);
		}else{
			printf("%s : undefined.",optv[i]);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.dfile:%s:\n",(*opt).dfile);
	printf(" opt.msize:%d:\n",(*opt).msize);
	printf(" opt.create:%d:\n",(*opt).create);
	printf(" opt.print:%d:\n",(*opt).print);
}

int main(int argc, char **argv){
	FILE *fp;
	int c;
	int i,j,i2,j2,z;
	int ng = 0;
	int ie = 0;
	struct options *opt;
	float **dmat;
	//float *class;
	int *class;
	int lineClass = -1;
	int colClass = -1;
	int currentClass = -1;

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
	/* get size */
        if((*opt).msize == 0){
                int col = 0;
                if((fp = fopen((*opt).dfile,"r")) == NULL){
			perror((*opt).dfile);
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
                ((*opt).msize) = (col+1);
        }
	/* allocation */
	dmat = f_alloc_mat((*opt).msize,(*opt).msize);
	//class = f_alloc_vec((*opt).msize);
	class = i_alloc_vec((*opt).msize);
	/* read */
	if((fp = fopen((*opt).dfile,"r")) == NULL){
		perror((*opt).dfile);
		exit(1);
	}
	read_ftable_from_stream((*opt).msize, (*opt).msize,fp,dmat);
	fclose(fp);

	/* algorithm */
	/** class initialize */
	for(i=0;i<(*opt).msize;i++){
		class[i]=i;
	}
	/** create symmetric */
	if((*opt).create == 1){
		for(i=0;i<(*opt).msize;i++){
			for(j=0;j<(*opt).msize;j++){
				if(dmat[i][j] > 0 && dmat[j][i] == 0){
					dmat[j][i] = 1;
				}
			}
		}
	}
	/** create diagonal */
	for(i=0;i<(*opt).msize;i++){
		dmat[i][i]=1;
	}
	/** rewrite class */
	lineClass = -1;
	for(i=0;i<(*opt).msize;i++){
		lineClass = i;
		for(j=0;j<(*opt).msize;j++){
			colClass = j;
			if(dmat[i][j] > 0){
				//printf("colClass %d\n",colClass);
				break;
			}
		}
		//printf("break\n");
		//if(lineClass >= 0 && colClass >= 0){
			if(lineClass > colClass){
				currentClass = colClass;
			}else{
				currentClass = lineClass;
			}
			if(currentClass != -1 && currentClass > class[j]){
				currentClass = class[j];
			}
			for(j2=0;j2<(*opt).msize;j2++){
				if(dmat[i][j2] > 0){
					class[j2] = currentClass;
				}
			}
		//}
		currentClass = -1;
	}

	/* print class */
	for(j2=0;j2<(*opt).msize;j2++){
		printf("%d ",class[j2]);
	}
	printf("\n");

	/* print dmat */
	if((*opt).print == 1){
		for(i=0;i<(*opt).msize;i++){
			for(j=0;j<(*opt).msize;j++){
				printf("%f ",dmat[i][j]);
			}
			printf("\n");
		}
	}
 
	return(0);
}
