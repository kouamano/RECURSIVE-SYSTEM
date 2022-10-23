#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024
#define BUFF_LEN 1024
//  UNDER CONSTRUCTION
// TODO: print simple ARG

// protopype

struct options {
	int help;
	int stat;
	int check;
	int buff;
	int war;
	char *in;
};

void help(void){
	printf("USAGE:\n");
	printf(" s2t [-h] [-s] [-c] buff=<size(int)> in=<input file> w=<print warnning>.\n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  buff : set integer.\n");
	printf("  in : set *chars (len < 1024).\n");
	printf("  war : set integer.\n");
}

void status(void){
	printf("DESCRIPTION:\n");
	printf(" converts S form to T form, NOT applicable to purefunction.\n");
	printf("STATUS:\n");
	printf(" Testing.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).in = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).buff = BUFF_LEN;
	(*opt).in[0] = '\0';
	(*opt).war = 0;
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
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff);
		}else if(strncmp(optv[i],"w=",2) == 0){
			sscanf(optv[i],"w=%d",&(*opt).war);
		}else if(strncmp(optv[i],"in=",3) == 0){
			sscanf(optv[i],"in=%s",(*opt).in);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.buff:%d:\n",(*opt).buff);
	printf(" opt.in:%s:\n",(*opt).in);
	printf(" opt.war:%d:\n",(*opt).war);
}

// function definition
int search_pos_BRK_S_LAST(char *_BUF, int WAR){
        int pos = -1;
        int len_BUF = 0;
        int i;
        len_BUF = strlen(_BUF);
        if(WAR > 2){ fprintf(stderr,"    ::len_BUF:%d:::\n",len_BUF); }
        for(i=0;i<len_BUF;i++){
                if(_BUF[i] == '('){
                        pos = i;
                }
        }
        return(pos);
}


int print_BUF_HEAD(char _TRIG_CHAR, char _PREV_T_CHAR, char _PREV_CHAR, int _TRIG, int _BRK_E_COUNT, char *_BUF_HEAD, int *_SHLINK_POS, char *_BUF_TMP, int *_BRK_REMAIN, int _LIST_LV, int WAR){
	int RETURN_LEN = 0;
	int BUF_LEN = 0;
	int COPY_S_PTR = 0;
	int BRK_S_LAST = 0;
	int i;
	_BUF_TMP[0] = '\0';
	strcpy(_BUF_TMP,_BUF_HEAD);
	BUF_LEN = strlen(_BUF_TMP);
	BRK_S_LAST =  search_pos_BRK_S_LAST(_BUF_HEAD,WAR);
	if(WAR > 0){ fprintf(stderr," - TRIG:%d:C:%c - \n",_TRIG,_TRIG_CHAR); }
	if(_BUF_HEAD[BUF_LEN-1] == ',' && _BUF_HEAD[0] == '('){
		if(WAR > 0){ fprintf(stderr," -- CASE:1 -- \n"); }
		if(WAR > 0){ fprintf(stderr,"::LIST_LV:%d:::\n",_LIST_LV); }
		if(WAR > 0){ fprintf(stderr,"::BRK_R:%d:::\n",*_BRK_REMAIN); }
		if(WAR > 0){ fprintf(stderr,"::B_LEN:%d:::\n",BUF_LEN); }
		if(WAR > 0){ fprintf(stderr,"::P_T_CHAR:%c:::\n",_PREV_T_CHAR); }
		if(WAR > 0){ fprintf(stderr,"::P_CHAR:%c:::\n",_PREV_CHAR); }
		if(WAR > 0){ fprintf(stderr,"::REMAIN:%s:::\n",_BUF_TMP); }
		_BUF_TMP[BUF_LEN-1] = '(';	//Be carefull !!
		//(*_BRK_REMAIN)--;
		_BUF_TMP[BUF_LEN] = '\0';	//Be carefull !!
		//printf(";;;%s;;;",_BUF_TMP+1);
		/*
		if(*_BRK_REMAIN < 2){
			//printf("%s",_BUF_TMP+(*_BRK_REMAIN));
			printf("%s",_BUF_TMP+1);
			(*_BRK_REMAIN)--;
			_BUF_HEAD[0] = '\0';
			_BUF_TMP[0] = '\0';
			RETURN_LEN = 0;
		}else{
		*/
			//printf("%s",_BUF_TMP+BRK_S_LAST);
			//if(_PREV_CHAR == ')'){
			//if(_BRK_E_COUNT > 0 && _PREV_T_CHAR != ',' && _PREV_CHAR != ')'){
				//printf("%s",",");
				//printf("%s",",");
			//}
			printf("%s",_BUF_TMP+(*_BRK_REMAIN));
			(*_BRK_REMAIN)--;
			if(WAR > 0){ fprintf(stderr,"  ::POUT:%s:::\n",_BUF_TMP+(*_BRK_REMAIN)); }
			_BUF_HEAD[0] = '\0';
			_BUF_TMP[0] = '\0';
			RETURN_LEN = 0;
		/*
		}
		*/
	}else if(_BUF_HEAD[BUF_LEN-1] == ',' && _BUF_HEAD[0] != '('){
		if(BUF_LEN > 1){		// IF LEN > 1
			if(WAR > 0){ fprintf(stderr," -- CASE:2 -- \n"); }
			if(WAR > 0){ fprintf(stderr,"::LIST_LV:%d:::\n",_LIST_LV); }
			if(WAR > 0){ fprintf(stderr,"::BRK_R:%d:::\n",*_BRK_REMAIN); }
			if(WAR > 0){ fprintf(stderr,"::B_LEN:%d:::\n",BUF_LEN); }
			if(WAR > 0){ fprintf(stderr,"::P_T_CHAR:%c:::\n",_PREV_T_CHAR); }
			if(WAR > 0){ fprintf(stderr,"::P_CHAR:%c:::\n",_PREV_CHAR); }
			if(WAR > 0){ fprintf(stderr,"::REMAIN:%s:::\n",_BUF_TMP); }
			if(WAR > 0){ fprintf(stderr,"::POUT:%s:::\n",_BUF_TMP); }
			printf("%s",_BUF_TMP);
			//printf("%s","");
			_BUF_HEAD[0] = '\0';
			_BUF_TMP[0] = '\0';
			RETURN_LEN = 0;
		}else{
			if(WAR > 0){ fprintf(stderr," -- CASE:3 -- \n"); }
			if(WAR > 0){ fprintf(stderr,"::LIST_LV:%d:::\n",_LIST_LV); }
			if(WAR > 0){ fprintf(stderr,"::BRK_R:%d:::\n",*_BRK_REMAIN); }
			if(WAR > 0){ fprintf(stderr,"::B_LEN:%d:::\n",BUF_LEN); }
			if(WAR > 0){ fprintf(stderr,"::P_CHAR:%c:::\n",_PREV_CHAR); }
			if(WAR > 0){ fprintf(stderr,"::REMAIN:%s:::\n",_BUF_TMP); }
			if(WAR > 0){ fprintf(stderr,"::POUT:%s:::\n",_BUF_TMP); }
			if(_LIST_LV > 1){
				//printf("%s",_BUF_TMP);
			}else{
				printf("%s",_BUF_TMP);
			}
			//printf("%s",_BUF_TMP);
			//printf("%s","");
			_BUF_HEAD[0] = '\0';
			_BUF_TMP[0] = '\0';
			RETURN_LEN = 0;
		}
	}else if(_BUF_HEAD[BUF_LEN-1] == ')'){
		if(WAR > 0){ fprintf(stderr," -- CASE:4 -- \n"); }
		if(WAR > 0){ fprintf(stderr,"::LIST_LV:%d:::\n",_LIST_LV); }
		if(WAR > 0){ fprintf(stderr,"::BRK_R:%d:::\n",*_BRK_REMAIN); }
		if(WAR > 0){ fprintf(stderr,"::B_LEN:%d:::\n",BUF_LEN); }
		if(WAR > 0){ fprintf(stderr,"::P_CHAR:%c:::\n",_PREV_CHAR); }
		if(WAR > 0){ fprintf(stderr,"::REMAIN:%s:::\n",_BUF_TMP); }
		// search COPY_S_PTR
		for(i=BUF_LEN-1;i>=0;i--){
			if(WAR > 1){ fprintf(stderr,"  ::i:%d:::",i); }
			if(WAR > 1){ fprintf(stderr,"  ::c:%c:::\n",_BUF_TMP[i]); }
			if(_BUF_TMP[i] == '('){
				COPY_S_PTR = i;
				break;
			}else{
				COPY_S_PTR = -1;
			}
		}
		if(WAR > 1){ fprintf(stderr,"::C:%d:::\n",COPY_S_PTR); }
		if(COPY_S_PTR != -1){
			_BUF_TMP[BUF_LEN-1] = '(';
			_BUF_TMP[BUF_LEN] = ')';
			_BUF_TMP[BUF_LEN+1] = '\0';
			//printf(";;;%s;;;",_BUF_TMP+COPY_S_PTR+1);
			printf("%s",_BUF_TMP+COPY_S_PTR+1);
			if(WAR > 0){ fprintf(stderr,"  ::POUT:%s:::\n",_BUF_TMP+COPY_S_PTR+1); }
			(*_BRK_REMAIN)--;
			_BUF_HEAD[COPY_S_PTR] = '\0';
			RETURN_LEN = COPY_S_PTR;
		}else{
			//printf(";;;%s;;;",_BUF_TMP);
			printf("%s",_BUF_TMP);
			if(*_BRK_REMAIN > 0){
				printf("%s","(");
				if(WAR > 0){ fprintf(stderr,"  ::POUT:%s:::\n","("); }
				(*_BRK_REMAIN)--;
			}
			_BUF_TMP[0] = '\0';
			_BUF_HEAD[0] = '\0';
			RETURN_LEN = 0;
		}
	}
	return(RETURN_LEN);
}

int shlink_BUF_HEAD(char *_BUF_HEAD, int *_SHLINK_POS, char *_BUF_TMP){
	// not used
	return(0);
}

int main(int argc, char **argv){
	struct options *opt;
	int ie = 0;
	FILE *IN;
	int is_open = 0;
	int c;
	int COUNT = 0;
	char PREV_CHAR = '\0';
	char PREV_T_CHAR = '\0';
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

	// open file
	if((IN = fopen((*opt).in,"r")) == NULL){
		perror((*opt).in);
		exit(1);
	}
	is_open = 1;

	// main function
	int PRINT_TRIG_ACC = 1;
	int PRINT_TRIG = 0;
	char *BUF_HEAD;
	int BUF_PTR = 0;
	int *SHLINK_POS;
	int PTR_BACK = 0;
	char *BUF_TMP;
	int BRK_REMAIN = 0;
	int LIST_LV = 0;
	int BRK_E_COUNT = 0;
	char TRIG_CHAR = '\0';
	//int P_COUNT = 0;
	if((BUF_HEAD = malloc((size_t)sizeof(char)*(*opt).buff)) == NULL){
		fprintf(stderr,"[FAILED] malloc() @ BUF_HEAD @ main .\n");
		exit(1);
	}
	BUF_HEAD[0] = '\0';
	if((SHLINK_POS = malloc((size_t)sizeof(char)*(*opt).buff)) == NULL){
		fprintf(stderr,"[FAILED] malloc() @ SHLINK_POS @ main .\n");
		exit(1);
	}
	SHLINK_POS[0] = '\0';
	if((BUF_TMP = malloc((size_t)sizeof(char)*(*opt).buff)) == NULL){
		fprintf(stderr,"[FAILED] malloc() @ BUF_TMP @ main .\n");
		exit(1);
	}
	BUF_TMP[0] = '\0';

	PRINT_TRIG_ACC = 1;
	while((c = fgetc(IN)) != EOF){
		COUNT++;
		PRINT_TRIG = 0;
		if((*opt).war > 0){ fprintf(stderr,"::COUNTER:%d:CHAR:%c:::\n",COUNT,c); }
		if(c == '('){
			LIST_LV++;
			BRK_REMAIN++;
		}
		if(c == ')'){
			LIST_LV--;
			BRK_E_COUNT++;
		}
		if(c == '['){
			PRINT_TRIG_ACC--;
		}
		if(c == ']'){
			PRINT_TRIG_ACC++;
		}
		if(PRINT_TRIG_ACC > 0 && c == ','){
			PRINT_TRIG = 1;
			TRIG_CHAR = c;
		}
		if(PRINT_TRIG_ACC > 0 && c == ')'){
			PRINT_TRIG = 2;
			TRIG_CHAR = c;
		}
		BUF_HEAD[BUF_PTR] = c;
		BUF_PTR++;
		BUF_HEAD[BUF_PTR] = '\0';
		if(PRINT_TRIG > 0){
			BUF_PTR = print_BUF_HEAD(TRIG_CHAR,PREV_T_CHAR,PREV_CHAR,PRINT_TRIG,BRK_E_COUNT,BUF_HEAD,SHLINK_POS,BUF_TMP,&BRK_REMAIN,LIST_LV,(*opt).war);
			//BUF_HEAD[BUF_PTR+1] = '\0';
			BUF_HEAD[BUF_PTR] = '\0';
			PREV_T_CHAR = c;
		}
		if(c == '\n'){
			TRIG_CHAR = c;
			LIST_LV = 0;
			printf("%s",BUF_HEAD);
			PRINT_TRIG_ACC = 1;
			PRINT_TRIG = 0;
			BUF_HEAD[0] = '\0';
			BUF_PTR = 0;
			(*SHLINK_POS) = 0;
			PTR_BACK = 0;
			BUF_TMP[0] = '\0';
			BRK_REMAIN = 0;
			BRK_E_COUNT = 0;
			if((*opt).war > 0){ fprintf(stderr,"\n"); }
		}
		PREV_CHAR = c;	
	}

	// close file
	if(is_open > 0){
		fclose(IN);
	}

	/* test */
	//printf("%s",BUF_HEAD);
	//printf("%s\n",BUF_HEAD+1);
	/* test */


	// finish
	return(0);
}
