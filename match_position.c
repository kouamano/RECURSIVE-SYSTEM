#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "../include/alloc.c"
#define F_NAME_LEN 1024

struct options {
	int help;
	int stat;
	int check;
	int qsize;
	int ign;
	int ex;
	char *sfile;
	char *qfile;
};

void help(void){
	printf("USAGE:\n");
	printf(" match_potistion [-h] [-s] [-c] [-i] qf=<query file> sf=<source file> [qb=<query buf>] [ex=<bytes for extra print>]\n");
	printf("  -h : print help and exit.\n");
	printf("  -s : print status and exit.\n");
	printf("  -c : print option values and exit.\n");
	printf("  -i : ignore case.\n");
	printf("  <query file> : query file, 1 term / 1 line.\n");
	printf("  <source file> : source file, as single string.\n");
	printf("  <query buf> : query buffer size,\n");
	printf("              | qb=0 : auto.\n");
	printf("  <bytes for extra print> : print extra byte at both ends (int).\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" available.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).sfile = malloc(sizeof(char) * F_NAME_LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).qfile = malloc(sizeof(char) * F_NAME_LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).ign = 0;
	(*opt).ex = 0;
	(*opt).qsize = 0;
	(*opt).sfile[0] = '\0';
	(*opt).qfile[0] = '\0';
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
		}else if(strcmp(optv[i],"-i") == 0){
			(*opt).ign = 1;
		}else if(strncmp(optv[i],"qf=",3) == 0){
			sscanf(optv[i],"qf=%s",(*opt).qfile);
		}else if(strncmp(optv[i],"sf=",3) == 0){
			sscanf(optv[i],"sf=%s",(*opt).sfile);
		}else if(strncmp(optv[i],"ex=",3) == 0){
			sscanf(optv[i],"ex=%d",&(*opt).ex);
		}else{
			fprintf(stderr,"%s : undefined.\n",optv[i]);
		}
	}
}

void check_options(struct options *opt){
	printf("opt.help:%d:\n",(*opt).help);
	printf("opt.stat:%d:\n",(*opt).stat);
	printf("opt.check:%d:\n",(*opt).check);
	printf("opt.ign:%d:\n",(*opt).ign);
	printf("opt.ex:%d:\n",(*opt).ex);
	printf("opt.qsize:%d:\n",(*opt).qsize);
	printf("opt.qfile:%s:\n",(*opt).qfile);
	printf("opt.sfile:%s:\n",(*opt).sfile);
}

#include "strncmpi.c"

int main(int argc, char **argv){
	//vars
	struct options *opt;
	FILE *IN;
	char *qbuf;
	char c;
	int ie = 0;
	int i, j, k;
	int num_qptrs;
	int *qptrs;
	int curr_pos_qptr;
	size_t source_size;
	char *source;
	int b_head, b_tail;
	char *ex_head, *ex_tail;
	int LFcount = 0;

	//option analysis
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);

	//exit condition
	if(strlen((*opt).qfile) == 0){
		(*opt).help = 1;
	}
	if(strlen((*opt).sfile) == 0){
		(*opt).help = 1;
	}
	//put help
	if((*opt).help ==1){
		help();
		ie = 1;
	}
	//put status
	if((*opt).stat ==1){
		status();
		ie = 1;
	}
	//put opt
	if((*opt).check == 1){
		check_options(opt);
		ie = 1;
	}
	//exit
	if(ie > 0){
		exit(0);
	}

	//get qfile size
	if((IN = fopen((*opt).qfile,"r")) == NULL){
		perror((*opt).qfile);
		exit(1);
	}
	i = 0;
	while(((c = fgetc(IN)) != EOF)){
		i++;
	}
	(*opt).qsize = i;
	fclose(IN);

	//alloc qbuf
	if((qbuf = malloc(sizeof(char) * (((*opt).qsize) + 1))) == NULL){
		printf("failed : malloc() for qbuf.\n");
		exit(1);
	}
	qbuf[(*opt).qsize] = '\0';

	//open qfile
	if((IN = fopen((*opt).qfile,"r")) == NULL){
		perror((*opt).qfile);
		exit(1);
	}
	//read qfile
	i = 0;
	num_qptrs = 0;
	while(((c = fgetc(IN)) != EOF)){
		if(c == '\n'){
			num_qptrs++;
			c = '\0';
		}
		qbuf[i] = c;
		i++;
	}
	qbuf[i] = '\0';
	//close qfile
	fclose(IN);

	//alloc qptrs
	if((qptrs = malloc(sizeof(int) * (num_qptrs + 1))) == NULL){
		printf("failed : malloc() for qptrs.\n");
		exit(1);
	}
	//record qptr
	i = 0;
	curr_pos_qptr = 0;
	qptrs[curr_pos_qptr] = i;
	for(i=0;i<(*opt).qsize;i++){
		if(qbuf[i] == '\0'){
			curr_pos_qptr++;
			qptrs[curr_pos_qptr] = (i+1);
		}
	}

	//get sfile size
	if((IN = fopen((*opt).sfile,"r")) == NULL){
		perror((*opt).sfile);
		exit(1);
	}
	i = 0;
	while((c = getc(IN)) != EOF){
		i++;
	}
	source_size = i;
	fclose(IN);

	//alloc source
	if((source = malloc(sizeof(char)*(source_size + 1))) == NULL){
		printf("failed : malloc() for source.\n");
		exit(1);
	}

	//open sfile
	if((IN = fopen((*opt).sfile,"r")) == NULL){
		perror((*opt).sfile);
		exit(1);
	}
	//read sfile
	i = 0;
	while(((c = fgetc(IN)) != EOF)){
		source[i] = c;
		i++;
	}
	source[i] = '\0';
	//close sfile
	fclose(IN);

	//scan
	if((*opt).ign == 0 && (*opt).ex == 0){
		for(i=0;i<num_qptrs;i++){  //query
			LFcount = 0;
			for(j=0;j<source_size;j++){ //source
				if(strncmp(source+j,"\n",1) == 0){LFcount++;}
				if(strncmp(qbuf+(qptrs[i]),source+j,strlen(qbuf+(qptrs[i]))) == 0){
					printf("%s",qbuf+(qptrs[i]));
					printf("	%d	%d	L:%d\n",j,j-1+(int)strlen(qbuf+(qptrs[i])),LFcount);
				}
			}
		}
	}else if((*opt).ign != 0 && (*opt).ex == 0){
		for(i=0;i<num_qptrs;i++){  //query
			LFcount = 0;
			for(j=0;j<source_size;j++){ //source
				if(strncmp(source+j,"\n",1) == 0){LFcount++;}
				if(strncmpi(qbuf+(qptrs[i]),source+j,strlen(qbuf+(qptrs[i]))) == 0){
					printf("%s",qbuf+(qptrs[i]));
					printf("	%d	%d	L:%d\n",j,j-1+(int)strlen(qbuf+(qptrs[i])),LFcount);
				}
			}
		}
	}else if((*opt).ign == 0 && (*opt).ex > 0){
		ex_head = c_alloc_vec((*opt).ex + 1);
		ex_tail = c_alloc_vec((*opt).ex + 1);
		for(i=0;i<num_qptrs;i++){  //query
			LFcount = 0;
			for(j=0;j<source_size;j++){ //source
				if(strncmp(source+j,"\n",1) == 0){LFcount++;}
				if(strncmp(qbuf+(qptrs[i]),source+j,strlen(qbuf+(qptrs[i]))) == 0){
					// print extra byte
					//putchar('[');
					b_head = 0;
					for(k=0;k<(*opt).ex;k++){
						if(j-(*opt).ex+k >= 0){
							//putchar(*(source+j-(*opt).ex+k));
							ex_head[k] = *(source+j-(*opt).ex+k);
							b_head++;
						}
					}
					ex_head[k] = '\0';
					printf("%s",qbuf+(qptrs[i]));
					// print extra byte
					b_tail = 0;
					for(k=0;k<(*opt).ex;k++){
						if(j+strlen(qbuf+qptrs[i])+k < source_size){
							//putchar(*(source+j+strlen(qbuf+qptrs[i])+k));
							ex_tail[k] = *(source+j+strlen(qbuf+qptrs[i])+k);
							b_tail++;
						}
					}
					ex_tail[k] = '\0';
					// print pointers
					printf("	%d	%d	%d	%d	%s%s	L:%d",j,j-1+(int)strlen(qbuf+(qptrs[i])),b_head,b_tail,ex_head,ex_tail,LFcount);
					//putchar(']');
					putchar(4);
					putchar('\n');
				}
			}
		}
	}else if((*opt).ign != 0 && (*opt).ex > 0){
		ex_head = c_alloc_vec((*opt).ex + 1);
		ex_tail = c_alloc_vec((*opt).ex + 1);
		for(i=0;i<num_qptrs;i++){  //query
			LFcount = 0;
			for(j=0;j<source_size;j++){ //source
				if(strncmp(source+j,"\n",1) == 0){LFcount++;}
				if(strncmpi(qbuf+(qptrs[i]),source+j,strlen(qbuf+(qptrs[i]))) == 0){
					// print extra byte
					//putchar('[');
					b_head = 0;
					for(k=0;k<(*opt).ex;k++){
						if(j-(*opt).ex+k >= 0){
							//putchar(*(source+j-(*opt).ex+k));
							ex_head[k] = *(source+j-(*opt).ex+k);
							b_head++;
						}
					}
					ex_head[k] = '\0';
					printf("%s",qbuf+(qptrs[i]));
					// print extra byte
					b_tail = 0;
					for(k=0;k<(*opt).ex;k++){
						if(j+strlen(qbuf+qptrs[i])+k < source_size){
							//putchar(*(source+j+strlen(qbuf+qptrs[i])+k));
							ex_tail[k] = *(source+j+strlen(qbuf+qptrs[i])+k);
							b_tail++;
						}
					}
					ex_tail[k] = '\0';
					// print pointers
					printf("	%d	%d	%d	%d	%s%s	L:%d",j,j-1+(int)strlen(qbuf+(qptrs[i])),b_head,b_tail,ex_head,ex_tail,LFcount);
					//putchar(']');
					putchar(4);
					putchar('\n');
				}
			}
		}
	}
	return(0);
}
