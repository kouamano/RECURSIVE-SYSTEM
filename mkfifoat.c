#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#define LEN 1024

struct options {
	int help;
	int stat;
	int check;
	int argint;
	char *argpath;
};

void help(void){
	printf("USAGE:\n");
	printf(" mkfifoat [-h] [-s] [-c] int=<mode> path=<path>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  int : set mode.\n");
	printf("  path : target (len < 1024).\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Under construction.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).argpath = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).argint = 0;
	(*opt).argpath[0] = '\0';
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
		}else if(strncmp(optv[i],"int=",4) == 0){
			sscanf(optv[i],"int=%d",&(*opt).argint);
		}else if(strncmp(optv[i],"path=",5) == 0){
			sscanf(optv[i],"path=%s",(*opt).argpath);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.argint:%d:\n",(*opt).argint);
	printf(" opt.argpath:%s:\n",(*opt).argpath);
}

int checkCreateDir(const char *tstr, char *dstr, int mode){
	//fprintf(stderr,"IN:checkCraeteDir()\n");
	struct stat _statBuf;
	int _ret = -1;
	int _mkstat = -1;
	char *sdstr;
	if( (sdstr = malloc(sizeof(char) * LEN)) == NULL){
		printf("malloc error.\n");
		exit(-1);
	}
	sdstr[0] = '\0';
	_ret = stat(tstr,&_statBuf);
	if(_ret == 0){// if exist tstr
		;
	}else{
		// create
		_mkstat = mkdir(dstr, S_IRWXU);
		// if failed
		if(_mkstat == 0){
			;
		}else{
			dstr = dirname(dstr);
			checkCreateDir(tstr,dstr,S_IRWXU);
		}
		strcpy(sdstr,tstr);
		checkCreateDir(tstr,sdstr,S_IRWXU);
	}
	//fprintf(stderr,"OUT:checkCraeteDir()\n");
	return(_ret);
}

int main(int argc, char **argv){
	int fifostat = 0;
	char *dir;
	if( (dir = malloc(sizeof(char) * LEN)) == NULL){
		printf("malloc error.\n");
		exit(-1);
	}
	char *vdir;
	if( (vdir = malloc(sizeof(char) * LEN)) == NULL){
		printf("malloc error.\n");
		exit(-1);
	}
	char *vpath;
	if( (vpath = malloc(sizeof(char) * LEN)) == NULL){
		printf("malloc error.\n");
		exit(-1);
	}
	struct stat statBuf;
	int ret = -1;
	int fst = -1;
	struct options *opt;
	int ie = 0;
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
	
	/*check dir*/
	strcpy(vpath, (*opt).argpath);
	strcpy(vdir, dirname(vpath));
	strcpy(dir, vdir);
	fst = stat((*opt).argpath,&statBuf);
	fprintf(stderr,"target:exist:%d:\n",fst);
	if(fst == 0){
		fprintf(stderr,"targetfile:already exists.\n");
		exit(0);
	}
	ret = checkCreateDir(dir, vdir, (*opt).argint);
	fprintf(stderr,"dir:exist:%d:\n",ret);
	fifostat = mkfifo((*opt).argpath, (*opt).argint);
	fprintf(stderr,"fifo:create:%d:\n",ret);

	return(0);
}
