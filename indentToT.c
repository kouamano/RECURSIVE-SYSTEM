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
	int i = 0;
	int lineLV = 0;
	int plineLV = 0;
	int currentLV = 0;
	int diffLV = 0;
	int cdiffLV = 0;
	int LF = 0;
	//int EBP = 0;

	
	putc('(',stdout);
	while((C = fgetc(IN)) != EOF){
		if(C == (*opt).idt){
			currentLV++;
		}else if(C == '\n'){
			plineLV = currentLV;
			currentLV = 0;
		}else{
			lineLV = currentLV;
		}
		diffLV = lineLV - plineLV;
		cdiffLV = lineLV - currentLV;
		//EBP = 0;


		if(C == '\n'){
			;
		}else if(C != (*opt).idt){
			if(PC == ' '){
				if(diffLV > 0){
					for(i=0;i<diffLV;i++){
						putc('(',stdout);
					}
				}else if(diffLV == 0){
						//putc(',',stdout);
				}else{
					for(i=0;i<-diffLV;i++){
						putc(')',stdout);
						putc(',',stdout);
					}
				}
			}else if(PC == '\n'){
				if(diffLV < 0){
					for(i=0;i<-diffLV;i++){
						putc(')',stdout);
						//EBP++;
					}
					putc(',',stdout);
				}
			}
		}


		if(PC == '\n' && diffLV >= 0){
			putc(';',stdout);
		}
		printf("p:%d,c:%d,l:%d:",plineLV,currentLV,lineLV);
		printf("'%c'",C);
		if(C != ' ' && C != '\n'){
			//putc(C,stdout);
		}
		printf("\n");


		if(C == '\n'){
			;
		}else if(C != (*opt).idt){
			if(PC == ' '){
				if(diffLV > 0){
					for(i=0;i<diffLV;i++){
						//putc('(',stdout);
					}
				}else if(diffLV == 0){
						//putc(',',stdout);
				}else{
					for(i=0;i<-diffLV;i++){
						//putc('}',stdout);
					}
				}
			}
		}

		PC = C;
	}
	if(cdiffLV > 0){
		for(i=0;i<cdiffLV;i++){
			putc(')',stdout);
		}
	}
	putc(')',stdout);

	if(is_open > 0){
		fclose(IN);
	}

	putc('\n',stdout);
	return(0);
}
