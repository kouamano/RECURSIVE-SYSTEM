/* streamcut.c */
/* (* include, declare */
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
	char *conj;
};

void help(void){
	printf("USAGE:\n");
	printf(" streamcut [-h] [-s] [-c] span=<span> if=<file> con=<conjugater>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  span : string span: start at 1, ex: 1-1,2-3.\n");
	printf("  file : input file.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" test usage.\n");
	printf("TODO:\n");
	//printf(" create function <-spanstr2spanint(spanstr).\n");
	//printf(" create function seekWhilePut(*FILE,p1,p2).\n");
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
	if(((*p).conj = malloc(sizeof(char) * ARG_LEN)) == NULL){
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
	(*opt).filename[0] = '\0';
	(*opt).conj[0] = '\0';
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
		}else if(strncmp(optv[i],"con=",4) == 0){
			sscanf(optv[i],"con=%s",(*opt).conj);
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
	printf(" opt.conj:%s:\n",(*opt).conj);
}
/* *) */
/* (* functions */
int **spanstr2spanint(char *str, int *fragment){
	int len = 0;
	int frag = 0;
	int i = 0;
	int *start;
	int *end;
	char *strBUF;
	int ptr = 0;
	int **retptr;
	len = strlen(str);
	if((strBUF = malloc(sizeof(char) * len)) == NULL){
		printf("failed : malloc() in spanstr2spanint().\n");
		exit(1);
	}
	if((retptr = malloc(sizeof(int *) * 2)) == NULL){
		printf("failed : malloc() in spanstr2spanint().\n");
		exit(1);
	}
	for(i=0;i<len;i++){
		if(str[i] == ','){
			frag++;
		}
	}
	frag++;
	if((start = malloc(sizeof(int) * frag)) == NULL){
		printf("failed : malloc() in spanstr2spanint().\n");
		exit(1);
	}
	if((end = malloc(sizeof(int) * frag)) == NULL){
		printf("failed : malloc() in spanstr2spanint().\n");
		exit(1);
	}
	//printf("frag:%d:\n",frag);
	for(i=0;i<frag;i++){
		sscanf(str+ptr,"%[^,],",strBUF);
		ptr = ptr+strlen(strBUF)+1;
		//printf("ret:%d:\n",ret);
		//printf("BUF:%s:\n",strBUF);
		sscanf(strBUF,"%d-%d",&start[i],&end[i]);
		//printf("start:%d: - end:%d:\n",start[i],end[i]);
	}
	*fragment = frag;
	retptr[0] = start;
	retptr[1] = end;
	return(retptr);
}

void seekWhilePut(FILE *fp, int p1, int p2){
	int i;
	int c;
	fseek(fp,p1,SEEK_SET);
	for(i=0;i<(p2-p1)+1;i++){
		c = fgetc(fp);
		putc(c,stdout);
	}
}
/* *) */
/* (* main */
int main(int argc, char **argv){
	struct options *opt;
	int **pos;
	int fragment;
	int ie = 0;
	FILE *IN;
	int is_open = 0;
	int c;
	int i;

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
	pos = spanstr2spanint((*opt).spanstr,&fragment);
	//printf("fragment:%d:\n",fragment);
	//printf("pos[0][0]:%d:\n",pos[0][0]);
	//printf("pos[1][0]:%d:\n",pos[1][0]);
	//printf("pos[0][1]:%d:\n",pos[0][1]);
	//printf("pos[1][1]:%d:\n",pos[1][1]);
	if((IN = fopen((*opt).filename,"r")) == NULL){
		perror((*opt).filename);
		exit(1);
	}else{
		for(i=0;i<fragment;i++){
			seekWhilePut(IN,pos[0][i],pos[1][i]);
			printf("%s",(*opt).conj);
		}
		fclose(IN);
	}
	/*
	while((c = fgetc(IN)) != EOF){
		putc(c,stdout);
	}
	*/
	
	/* *) */

	return(0);
}
/* *) */
