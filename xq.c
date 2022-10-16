#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024

/* help */
void help(void){
	printf("USAGE:\n");
	printf(" xq [-h] [-s] [-c] [-pT] if=<input file> buff=<buffer size> blocks=<blocks>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  -pT : print terminal chars.\n");
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
	//printt option
	int pt;
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
	(*opt).pt = 0;
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
		}else if(strncmp(optv[i],"-pT",3) == 0){
			(*opt).pt = 1;
		}
	}
}
void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.file:%s:\n",(*opt).file);
	printf(" opt.buff:%d:\n",(*opt).buff);
	printf(" opt.blocks:%d:\n",(*opt).blocks);
	printf(" opt.pt:%d:\n",(*opt).pt);
}
/* block operation */
#include "./xq_block.h"
/* read operation */
#include "./xq_read.h"
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
	Bl = alloc_Block_arr((*opt).blocks);
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
	printf("\n===== ===== ===== =====\n");
	print_tree_report(report);

	/** finalize **/
	return(0);
}
