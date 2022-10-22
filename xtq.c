#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* definition and structure */
#include "./xtq_defstrc.h"

/* help */
void help(void){
	printf("USAGE:\n");
	printf(" xtq [-h] [-s] [-c] [-pt] [-pn] [-pB] [-pBS] [-pT] in=<input file> buff=<buffer size> blocks=<blocks> pf=<print format> BH=<block header> BF=<block footer> SH=<status header> SF=<status footer>.\n");
	printf("  -h : help.\n");
	printf("  -s : status.\n");
	printf("  -c : check args.\n");
	printf("  -pt : print terminal chars.\n");
	printf("  -pn : print LF after block.\n");
	printf("  -pB : print blocks.\n");
	printf("  -pBS : print blocks with status.\n");
	printf("  -pT : print blocks with T-form.\n");
	printf("  input file : input file.\n");
	printf("  buffer size : buffer size.\n");
	printf("  blocks : number of blocks.\n");
	printf("  print format : format for block (default:\"%%s\").\n");
	printf("  block header : header for B option.\n");
	printf("  block footer : footer for B option.\n");
	printf("  status header : header for S option.\n");
	printf("  status footer : footer for S option.\n");
}
void status(void){
	printf("STATUS:\n");
	printf("  complete primal function.\n");
}

/* option */
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
	if(((*p).pf = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).BH = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).BF = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).SH = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).SF = malloc(sizeof(char) * LEN)) == NULL){
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
	(*opt).pt = 0;
	(*opt).pn = 0;
	(*opt).pb = 0;
	(*opt).pbs = 0;
	(*opt).ptf = 0;
	strcpy((*opt).pf,"%s");
	strcpy((*opt).SH,"[[[");
	strcpy((*opt).SF,"]]]");
	(*opt).BH[0] = '\0';
	(*opt).BF[0] = '\0';
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
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).file);
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff);
		}else if(strncmp(optv[i],"blocks=",7) == 0){
			sscanf(optv[i],"blocks=%d",&(*opt).blocks);
		}else if(strncmp(optv[i],"-pt",3) == 0){
			(*opt).pt = 1;
		}else if(strncmp(optv[i],"-pn",3) == 0){
			(*opt).pn = 1;
		}else if(strncmp(optv[i],"-pBS",4) == 0){
			(*opt).pbs = 1;
		}else if(strncmp(optv[i],"-pB",3) == 0){
			(*opt).pb = 1;
		}else if(strncmp(optv[i],"-pT",3) == 0){
			(*opt).ptf = 1;
		}else if(strncmp(optv[i],"pf=",3) == 0){
			sscanf(optv[i],"pf=%s",(*opt).pf);

		}else if(strncmp(optv[i],"BH=",3) == 0){
			sscanf(optv[i],"BH=%s",(*opt).BH);

		}else if(strncmp(optv[i],"BF=",3) == 0){
			sscanf(optv[i],"BF=%s",(*opt).BF);

		}else if(strncmp(optv[i],"SH=",3) == 0){
			sscanf(optv[i],"SH=%s",(*opt).SH);

		}else if(strncmp(optv[i],"SF=",3) == 0){
			sscanf(optv[i],"SF=%s",(*opt).SF);
		}
	}
}
void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.file:%s:\n",(*opt).file);
	printf(" opt.buff:%d:\n",(*opt).buff);
	printf(" opt.blocks:%d:\n",(*opt).blocks);
	printf(" opt.pt:%d:\n",(*opt).pt);
	printf(" opt.pn:%d:\n",(*opt).pn);
	printf(" opt.pb:%d:\n",(*opt).pb);
	printf(" opt.pbs:%d:\n",(*opt).pbs);
	printf(" opt.ptf:%d:\n",(*opt).ptf);
	printf(" opt.pf:%s:\n",(*opt).pf);
	printf(" opt.SH:%s:\n",(*opt).SH);
	printf(" opt.SF:%s:\n",(*opt).SF);
}

/* block operation */
#include "./xtq_block.h"
#include "./xtq_block_T.h"

/* read operation */
#include "./xtq_read.h"

/* executer */
#include "./xtq_executer.h"

/* main */
int main(int argc, char **argv){
	/** vals **/
	struct options *opt;
	int ie = 0;
	int if_open = 0;
	FILE *IN = NULL;
	struct Block *Bl = NULL;
	/** initialize **/
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	/** arg processing **/
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
	/** create block **/
	Bl = alloc_Bl_arr((*opt).blocks);
	/*** create top node ***/
	struct Bl_create_opt create_opt;
	create_opt.str_size = 1;
	create_Nd(Bl,0,create_opt);
	/** input **/
	if((IN = fopen((*opt).file,"r")) == NULL){
		perror((*opt).file);
		exit(1);
	}
	if_open = 1;
	struct Bl_tree_report *report;
	report = alloc_Bl_tree_report();
	read_x(opt, IN, Bl, 0, 0, 1, 0, report);
	if(if_open == 1){
		fclose(IN);
	}
	/** operation **/
	//print_tree_report(report);
	Executer(Bl,0,*opt,*report);
	/** finalize **/
	return(0);
}
