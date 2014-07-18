#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/alloc.c"
#define LEN 1024

struct options {
	int help;
	int stat;
	int check;
	int n;
	//int argint;
	//char *argstr;
	char *od;
	char *df;
	char *sf;
};

void help(void){
	printf("USAGE:\n");
	printf(" template [-h] [-s] [-c] [-n|+n] [od=<output delimter>] df=<delimiter> sf=<source>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  -n|+n : add(-n)/remove(+n) delimiters to LF.\n");
	printf("  delimiter : delimiter file - 1 delimiter / 1 line.\n");
	printf("  output delimiter : delimiter for output file.\n");
	printf("  source : source file.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" this program is template.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).od = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).df = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).sf = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).n = 1;
	//(*opt).argstr[0] = '\0';
	(*opt).od[0] = '\n';
	(*opt).od[1] = '\0';
	(*opt).df[0] = '\0';
	(*opt).sf[0] = '\0';
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
		}else if(strcmp(optv[i],"-n") == 0){
			(*opt).n = 1;
		}else if(strcmp(optv[i],"+n") == 0){
			(*opt).n = 0;
		//}else if(strncmp(optv[i],"int=",4) == 0){
		//	sscanf(optv[i],"int=%d",&(*opt).argint);
		//}else if(strncmp(optv[i],"str=",4) == 0){
		//	sscanf(optv[i],"str=%s",(*opt).argstr);
		}else if(strncmp(optv[i],"od=",3) == 0){
			sscanf(optv[i],"od=%s",(*opt).od);
		}else if(strncmp(optv[i],"df=",3) == 0){
			sscanf(optv[i],"df=%s",(*opt).df);
		}else if(strncmp(optv[i],"sf=",3) == 0){
			sscanf(optv[i],"sf=%s",(*opt).sf);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	//printf(" opt.argint:%d:\n",(*opt).argint);
	printf(" opt.n:%d:\n",(*opt).n);
	printf(" opt.od:%s:\n",(*opt).od);
	printf(" opt.df:%s:\n",(*opt).df);
	printf(" opt.sf:%s:\n",(*opt).sf);
}

int main(int argc, char **argv){
	int i;
	struct options *opt;
	int ie = 0;
	int c = 0;
	int tmpptr = 0;
	int tmpptr2 = 0;
	FILE *IN;
	char *delims_list;
	int len_delims_list = 0;
	int num_delims = 0;
	int *ptr_delims;
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

	/* (* read df */
	if((IN = fopen((*opt).df,"r")) == NULL){
		perror((*opt).df);
		exit(1);
	}
	len_delims_list = 0;
	num_delims = 0;
	while((c = fgetc(IN)) != EOF){
		len_delims_list++;
		if(c == '\n'){
			num_delims++;
		}
	}
	fseek(IN,0U,SEEK_SET);
	/* option brunch */
	if((*opt).n == 0){
		delims_list = c_alloc_vec(len_delims_list + 1);
		ptr_delims = i_alloc_vec(num_delims);
	}else{
		delims_list = c_alloc_vec(len_delims_list + 1 + 2);
		ptr_delims = i_alloc_vec(num_delims + 1);
	}
	tmpptr = 0;
	tmpptr2 = 0;
	ptr_delims[0] = tmpptr;
	tmpptr2++;
	while((c = fgetc(IN)) != EOF){
		if(c == '\n'){
			delims_list[tmpptr] = '\0';
			ptr_delims[tmpptr2] = tmpptr+1;
			tmpptr2++;
		}else{
			delims_list[tmpptr] = c;
		}
		tmpptr++;
	}
	fclose(IN);
	/* option brunch */
	if((*opt).n != 0){
		delims_list[tmpptr] = '\n';
		tmpptr++;
		delims_list[tmpptr] = '\0';
		tmpptr++;
		ptr_delims[tmpptr2] = tmpptr;
		num_delims++;
	}
	/* *) */

	/*UNDER CONSTRUCTION*/
	
	printf("len:%d:\n",len_delims_list);
	printf("num:%d:\n",num_delims);
	for(i=0;i<num_delims;i++){
		printf("%d\n",ptr_delims[i]);
	}
	printf("-------\n");
	for(i=0;i<num_delims;i++){
		printf(":%s:\n",delims_list+ptr_delims[i]);
	}
	printf("-------\n");
	
	return(0);
}
