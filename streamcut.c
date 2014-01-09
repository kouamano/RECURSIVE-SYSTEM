/* streamcut.c */
/* (* declare */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARG_LEN 512
#define FILE_NAME_SIZE 1024
/* *) */
/* (* arg operation */
struct options {
	int help;
	int stat;
	int check;
	char *spanstr;
	char *filename;
};

void help(void){
	printf("USAGE:\n");
	printf(" streamcut [-h] [-s] [-c] span=<span> if=<file>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  span : string span: ex. 10-20,25-30.\n");
	printf("  file : input file.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Under construction.\n");
	printf("TODO:\n");
	printf(" create function <-spanstr2spanint(spanstr).\n");
	printf(" create function seekWhilePut(*FILE,p1,p2).\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).spanstr = malloc(sizeof(char) * ARG_LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).filename = malloc(sizeof(char) * FILE_NAME_SIZE)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).spanstr[0] = '\0';
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
		}else if(strncmp(optv[i],"span=",4) == 0){
			sscanf(optv[i],"span=%s",(*opt).spanstr);
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",(*opt).filename);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.help:%d:\n",(*opt).help);
	printf(" opt.stat:%d:\n",(*opt).stat);
	printf(" opt.check:%d:\n",(*opt).check);
	printf(" opt.spanstr:%s:\n",(*opt).spanstr);
	printf(" opt.filename:%s:\n",(*opt).filename);
}
/* *) */
/* (* functions */
int *spanstr2spanint(char *str){
	int len = 0;
	int frag = 0;
	int i = 0;
	len = strlen(str);
	//printf("len:%d:\n",len);
	for(i=0;i<len;i++){
		//printf(":%d:\n",i);
		if(str[i] == ','){
			frag++;
		}
	}
	frag++;
	//printf("frag:%d:\n",frag);
}

void seekWhilePut(FILE *fp, int p1, int p2){
}
/* *) */
/* (* main */
int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;

	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
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

	/* (* argolithm */
	spanstr2spanint((*opt).spanstr);
	/* *) */

	return(0);
}
/* *) */
