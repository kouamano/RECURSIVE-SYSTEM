#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./jtq_def.h"
#include "./jtq_struct.h"

void help(void){
	printf("USAGE:\n");
	printf(" jtq [-h] [-s] [-c] in=<input file> buff=<buff size> nodes=<number of nodes> sh=<status header> sf=<status footer>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  input file : input file.\n");
	printf("  buff size : buffer size.\n");
	printf("  number of nodes : number of allocated nodes.\n");
	printf("  status header : print status with this header (1023 chars).\n");
	printf("  status footer : print status with this footer (1023 chars).\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Under construction.\n");
}

struct options {
	int help;
	int stat;
	int check;
	int buff;
	int nodes;
	char *infile;

	char *status_header;
	char *status_footer;
};

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).infile = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).status_header = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).status_footer = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).buff = LEN;
	(*opt).nodes = LEN;
	(*opt).infile[0] = '\0';
	strcpy((*opt).status_header,"<<<");
	strcpy((*opt).status_footer,">>>");
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
			sscanf(optv[i],"in=%s",(*opt).infile);
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff);
		}else if(strncmp(optv[i],"nodes=",5) == 0){
			sscanf(optv[i],"nodes=%d",&(*opt).nodes);
		}else if(strncmp(optv[i],"sh=",3) == 0){
			sscanf(optv[i],"sh=%s",(*opt).status_header);
		}else if(strncmp(optv[i],"sf=",3) == 0){
			sscanf(optv[i],"sf=%s",(*opt).status_header);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.help:%d:\n",(*opt).help);
	printf(" opt.stat:%d:\n",(*opt).stat);
	printf(" opt.check:%d:\n",(*opt).check);
	printf(" opt.buff:%d:\n",(*opt).buff);
	printf(" opt.nodes:%d:\n",(*opt).nodes);
	printf(" opt.infile:%s:\n",(*opt).infile);
	printf(" opt.sh:%s:\n",(*opt).status_header);
	printf(" opt.sf:%s:\n",(*opt).status_footer);
}

#include "./jtq_buff.h"
#include "./jtq_Nd.h"
#include "./jtq_read.h"
#include "./jtq_executer.h"

int main(int argc, char **argv){
	struct NdReport *report;
	struct options *opt = NULL;
	struct Nd *NdArr = NULL;
	FILE *IN;
	int ie = 0;

	/* init */
	opt = alloc_options();
	init_options(opt);
	NdArr = alloc_Nd_arr((*opt).nodes);

	/* option operation */
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

	/* alloc nodes */
	struct Nd *top_node;
	top_node = alloc_Nd_arr((*opt).nodes);

	/* read json */
	if((IN = fopen((*opt).infile,"r")) == NULL){
		perror("(*opt).infile");
		exit(1);
	}
	report = read_json(opt,IN,NdArr,0);
	fclose(IN);

	/* print nodes */
	print_report(report);
	print_json(opt,NdArr,0,0);
	executer();

	/* finish */
	return(0);
}
