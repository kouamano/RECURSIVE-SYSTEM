#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024

/* help */
void help(void){
	printf("USAGE:\n");
	printf(" xq [-h] [-s] [-c] if=<input file> buff=<buffer size> blocks=<blocks>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  inputfile : input file.\n");
	printf("  buff : buffer size.\n");
	printf("  blocks : number of blocks.\n");
}
void status(void){
	printf("STATUS:\n");
	printf("  under construction.\n");
}
/* option */
struct options {
	int help;
	int stat;
	int check;
	char *file;
	int buff;
	int blocks;
};
struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).file = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}
void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).file[0] = '\0';
	(*opt).buff = LEN;
	(*opt).blocks = LEN;
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
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",(*opt).file);
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff);
		}else if(strncmp(optv[i],"blocks=",7) == 0){
			sscanf(optv[i],"blocks=%d",&(*opt).blocks);
		}
	}
}
void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.file:%s:\n",(*opt).file);
	printf(" opt.buff:%d:\n",(*opt).buff);
	printf(" opt.blocks:%d:\n",(*opt).blocks);
}
/* main */
int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
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
	return(0);
}
