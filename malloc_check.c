#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LEN 1024

struct options {
	int help;
	int stat;
	int check;
	int size;
	int itv;
};

void help(void){
	printf("USAGE:\n");
	printf(" malloc-check [-h] [-s] [-c] size=<size> itv=<interval>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  size : malloc size.\n");
	printf("  itv : interval of asignment.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Under construction.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	/*
	if(((*p).argstr = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	*/
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).size = 0;
	(*opt).itv = 0;
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
		}else if(strncmp(optv[i],"itv=",4) == 0){
			sscanf(optv[i],"itv=%d",&(*opt).itv);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	//printf(" opt.argint:%d:\n",(*opt).argint);
	//printf(" opt.argstr:%s:\n",(*opt).argstr);
	printf(" opt.size:%d:\n",(*opt).size);
	printf(" opt.itv:%d:\n",(*opt).itv);
}

int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	int i;
	int *ptr;
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	printf("args\n");
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

	/* test */
	printf("alloc\n");
	if( (ptr = malloc((size_t)sizeof(int)*(*opt).size)) == NULL ){
		fprintf(stderr,"failed.\n");
		exit(1);
	}
	if((*opt).itv == 0){
		printf("no agign\n");
	}else{
		printf("agign: itv:%d\n",(*opt).itv);
		for(i=0;i<(*opt).size;i+=(*opt).itv){
			printf("%d\n",i);
			ptr[i] = i;
		}
	}
	printf("sleep:1000\n");
	sleep(1000);
	
	return(0);
}
