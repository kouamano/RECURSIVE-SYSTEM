#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024

struct options {
	int help;
	int stat;
	int check;
	//int argint;
	char *file;
	char idt;
	int buff;
};

void help(void){
	printf("DESCRIPTION:\n");
	printf(" indentToT prints T-form from indent format.\n");
	printf("USAGE:\n");
	printf(" indentToT [-h] [-s] [-c] in=<file> idt=<char> buff=<size>\n");
	printf("  -h : help.\n");
	printf("  -s : status.\n");
	printf("  -c : check args.\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Under const.\n");
}

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
	(*opt).idt = ' ';
	(*opt).buff = 1024 * 1024;
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
		}else if(strncmp(optv[i],"idt=",4) == 0){
			sscanf(optv[i],"idt=%c",&(*opt).idt);
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).file);
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.help:%d:\n",(*opt).help);
	printf(" opt.stat:%d:\n",(*opt).stat);
	printf(" opt.file:%s:\n",(*opt).file);
	printf(" opt.idt:%c:\n",(*opt).idt);
	printf(" opt.buff:%d:\n",(*opt).buff);
}

int get_LV(char *line, char idt){
	int i = 0;
	int len = 0;
	len = strlen(line);
	for(i=0;i<len;i++){
		if(line[i] != ' '){
			break;
		}
	}
	return(i);
}

int cp_BUFF(char *src, char *dst){
	int i;
	int len;
	len = strlen(src);
	for(i=0;i<len;i++){
		dst[i] = src[i];
	}
	dst[len] = '\0';
	return(len);
}

int drip_Pos(char *line){
	int i = 0;
	while(line[i] == ' '){
		i++;
	}
	return(i);
}

int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	int is_open = 0;
	int C = 0;
	int PC = 0;
	FILE *IN;
	char *BUFF;
	char *pBUFF;
	if((BUFF = malloc(sizeof(char) * (*opt).buff)) == NULL){
		perror("Fail: malloc()\n");
		exit(0);
	}
	if((pBUFF = malloc(sizeof(char) * (*opt).buff)) == NULL){
		perror("Fail: malloc()\n");
		exit(0);
	}
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
	if((IN = fopen((*opt).file,"r")) == NULL){
		perror((*opt).file);
		exit(1);
	}
	is_open = 1;
	int Ccount = 0;
	int Lcount = 0;
	int i = 0;
	int j = 0;

	BUFF[0] = '\0';
	int BUFF_ptr = 0;
	int LV = 0;
	pBUFF[0] = '\0';
	int pBUFF_ptr = 0;
	int pLV = 0;
	int diffLV = 0;
	putc('(',stdout);
	while((C = fgetc(IN)) != EOF){
		if(C == '\n'){
			BUFF[BUFF_ptr] = '\0';
			LV = get_LV(BUFF,(*opt).idt);	
			pLV = get_LV(pBUFF,(*opt).idt);	
			diffLV = LV - pLV;
			if(diffLV > 0){
				putc(',',stdout);
				for(j=0;j<diffLV;j++){
					putc('(',stdout);
				}
			}else if(diffLV == 0 && Lcount > 0){
				putc(',',stdout);
			}else{
				for(j=0;j<-diffLV;j++){
					putc(')',stdout);
				}
				if(Lcount > 0){
					putc(',',stdout);
				}
			}
			printf("%s",BUFF);
			cp_BUFF(BUFF,pBUFF);
			pBUFF_ptr = BUFF_ptr;
			BUFF[0] = '\0';
			BUFF_ptr = 0;
			putc('\n',stdout);
			Lcount++;
		}else{
			BUFF[BUFF_ptr] = C;
			BUFF_ptr++;
		}
		Ccount++;
	}
	putc(')',stdout);
	if(is_open > 0){
		fclose(IN);
	}
	putc('\n',stdout);


	return(0);
}
