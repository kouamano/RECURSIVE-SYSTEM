/* escape_char.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/alloc.c"
#define LEN 1024
#define CH_LEN 2

struct options {
	int help;
	int stat;
	int check;
	//int argint;
	//char *argstr;
	char *esc;
	char *sf; //source file
	char *lf; //target list file
};

void help(void){
	printf("USAGE:\n");
	printf(" escape_char [-h] [-s] [-c] esc=<escape char> sf=<source file> lf=<target list file> \n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  escape char : default :\\: .\n");
	printf("  source file : source text.\n");
	printf("  target list file : list of target char.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" test.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).esc = malloc(sizeof(char) * CH_LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).sf = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).lf = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	//(*opt).argint = 0;
	//(*opt).argstr[0] = '\0';
	(*opt).esc[0] = '\\';
	(*opt).esc[1] = '\0';
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
		}else if(strncmp(optv[i],"esc=",4) == 0){
			sscanf(optv[i],"esc=%s",(*opt).esc);
		}else if(strncmp(optv[i],"sf=",3) == 0){
			sscanf(optv[i],"sf=%s",(*opt).sf);
		}else if(strncmp(optv[i],"lf=",3) == 0){
			sscanf(optv[i],"lf=%s",(*opt).lf);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.esc:%s:\n",(*opt).esc);
	printf(" opt.sf:%s:\n",(*opt).sf);
	printf(" opt.lf:%s:\n",(*opt).lf);
}

int check_esc(int ch, char *target){
	int i;
	int l;
	l = strlen(target);
	for(i=0;i<l;i++){
		if(ch == (int)target[i]){
			return(1);
		}
	}
	return(0);
}


int main(int argc, char **argv){
	FILE *IN;
	int c;
	int i;
	int lf_size;
	char *target_chars;
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

	/* get list of target chars */
	if((IN = fopen((*opt).lf,"r")) == NULL){
		perror((*opt).lf);
		exit(1);
	}
	lf_size = 0;
	while((c = fgetc(IN)) != EOF){
		lf_size++;
	}
	target_chars = c_alloc_vec(lf_size + 1);
	fseek(IN,0U,SEEK_SET);
	i = 0;
	while((c = fgetc(IN)) != EOF){
		if(c != '\n'){
			target_chars[i] = c;
			i++;
		}
	}
	i++;
	target_chars[i] = '\0';
	//printf("%s",target_chars);
	fclose(IN);

	/* read source and escape */
	if((IN = fopen((*opt).sf,"r")) == NULL){
		perror((*opt).sf);
		exit(1);
	}
	while((c = fgetc(IN)) != EOF){
		if(check_esc(c,target_chars)){
			putchar((*opt).esc[0]);
			putchar(c);
		}else{
			putchar(c);
		}
	}
	fclose(IN);

	return(0);
}
