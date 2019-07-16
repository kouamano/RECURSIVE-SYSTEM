/* complex_list_wt.c               */
/* main program of complex_list_wt */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#define FILE_NAME_SIZE 260
#define SHORT_STRING_SIZE 1024
#define LONG_STRING_SIZE 20000
#define SHORT_BUFF_SIZE 512
#define LONG_BUFF_SIZE 10000
#define BRK_S "{"
#define BRK_E "}"
#include "../include/alloc.c"
#include "../include/complexop.h"
#include "../include/complexop.c"
#include "../include/complex-data_read.c"

struct option {
	int print_help;
	int check_option;
	int check_size;
	char base_file[FILE_NAME_SIZE];
	char kernel_file[FILE_NAME_SIZE];
	int base_format;
	int kernel_format;
	long int base_size;
	unsigned int kernel_size;
	char base_separator;
	char kernel_separator;
	int buff_size;
	int slide_step;
	int overhang;	/* 0 : none, 1 : self, 2 : set value */
	float oh_fill_value;
	int oh_conj_direction;
	int oh_fill_direction;
	char convolve_method[SHORT_STRING_SIZE];
};

void init_options(struct option *opt){
	(*opt).print_help = 0;
	(*opt).check_option = 0;
	(*opt).check_size = 0;
	(*opt).base_file[0] = '\0';
	(*opt).kernel_file[0] = '\0';
	(*opt).base_format = 1;
	(*opt).kernel_format = 1;
	(*opt).base_separator = ',';
	(*opt).kernel_separator = ',';
	(*opt).base_size = 10000000;
	(*opt).kernel_size = 10000;
	(*opt).buff_size = 30;
	(*opt).slide_step = 1;
	(*opt).overhang = 1;	/* 1:base, 2:user value */
	(*opt).oh_fill_value = 0;
	(*opt).oh_conj_direction = 1;
	(*opt).oh_fill_direction = 1;
	sscanf("Product","%s",(*opt).convolve_method);
}

void get_options(int optc, char** optv, struct option *opt){
	int i;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			(*opt).print_help = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check_option = 1;
		}else if(strcmp(optv[i],"-s") == 0){
			(*opt).check_size = 1;
		}else if(strncmp(optv[i],"bf=",3) == 0){
			sscanf(optv[i],"bf=%s",(*opt).base_file);
		}else if(strncmp(optv[i],"kf=",3) == 0){
			sscanf(optv[i],"kf=%s",(*opt).kernel_file);
		}else if(strncmp(optv[i],"bfm=",4) == 0){
			sscanf(optv[i],"bfm=%d",&(*opt).base_format);
		}else if(strncmp(optv[i],"kfm=",4) == 0){
			sscanf(optv[i],"kfm=%d",&(*opt).kernel_format);
		}else if(strncmp(optv[i],"bfs=",4) == 0){
			sscanf(optv[i],"bfs=%c",&(*opt).base_separator);
		}else if(strncmp(optv[i],"kfs=",4) == 0){
			sscanf(optv[i],"kfs=%c",&(*opt).kernel_separator);
		}else if(strncmp(optv[i],"bs=",3) == 0){
			sscanf(optv[i],"bs=%ld",&(*opt).base_size);
		}else if(strncmp(optv[i],"ws=",3) == 0){
			sscanf(optv[i],"ks=%d",&(*opt).kernel_size);
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff_size);
		}else if(strncmp(optv[i],"slide=",6) == 0){
			sscanf(optv[i],"slide=%d",&(*opt).slide_step);
		}else if(strncmp(optv[i],"overhang=",9) == 0){
			sscanf(optv[i],"overhang=%d",&(*opt).overhang);
		}else if(strncmp(optv[i],"fill=",5) == 0){
			sscanf(optv[i],"fill=%f",&(*opt).oh_fill_value);
		}else if(strncmp(optv[i],"conj_direction=",15) == 0){
			sscanf(optv[i],"conj_direction=%d",&(*opt).oh_conj_direction);
		}else if(strncmp(optv[i],"fill_direction=",15) == 0){
			sscanf(optv[i],"fill_direction=%d",&(*opt).oh_fill_direction);
		}else if(strncmp(optv[i],"conv=",5) == 0){
			sscanf(optv[i],"conv=%s",(*opt).convolve_method);
		}else{
			fprintf(stderr,"unknown option \"%s\".\n",optv[i]);
		}
	}
}

void print_options(struct option opt){
	printf("OPTION SETTING:\n");
	printf("  help:%d:\n",opt.print_help);
	printf("  base file:%s:\n",opt.base_file);
	printf("  kernel file:%s:\n",opt.kernel_file);
	printf("  base format:%d:\n",opt.base_format);
	printf("  kernel format:%d:\n",opt.kernel_format);
	printf("  base separator:%c:\n",opt.base_separator);
	printf("  kernel separator:%c:\n",opt.kernel_separator);
	printf("  base size:%ld:\n",opt.base_size);
	printf("  kernel size:%d:\n",opt.kernel_size);
	printf("  buffer size:%d:\n",opt.buff_size);
	printf("  slide step:%d:\n",opt.slide_step);
	printf("  overhang:%d:\n",opt.overhang);
	printf("  overhang fill value:%f:\n",opt.oh_fill_value);
	printf("  overhang conjugate direction:%d:\n",opt.oh_conj_direction);
	printf("  overhang fill direction:%d:\n",opt.oh_fill_direction);
	printf("  convolve method:%s:\n",opt.convolve_method);
	printf("\n");
}

void help(void){
	printf("complex_list_wt\n");
	printf("\nUSAGE:\n");
	printf("  complex_list_convolve bf=<base file> kf=<kernel file> [bfm=<base format>] [kfm=<kernel format>] [bfs=<base field separetor>] [kfs=<kernel field separator>] [bs=<base size>] [ks=<kernel size>] [buff=<buffer size>] [slide=<slide step>] overhang=<overhang option> [fill=<overhang filling value>] [conj_direction=<direction>] [fill_direction=<direction>] [conv=<convolve method>] [-h] [-c] [-s]\n");
	printf("\nFILE FORMAT:\n");
	printf("example:\n");
	printf("  1+3i,1,i,1i,...\n");
	printf("\nOPTION REMARK:\n");
	printf("  overhang : 1:use the base, 2:use the value specified by fill option.\n");
	printf("\n");
}

void print_size(void){
	printf("SIZE:\n");
	printf("  char            \t:%ld:\tbyte\n",sizeof(char));
	printf("  _Bool           \t:%ld:\tbyte\n",sizeof(_Bool));
	printf("  short int       \t:%ld:\tbyte\n",sizeof(short int));
	printf("  int             \t:%ld:\tbyte\n",sizeof(int));
	printf("  long int        \t:%ld:\tbyte\n",sizeof(long int));
	printf("  long long int   \t:%ld:\tbyte\n",sizeof(long long int));
	printf("  float           \t:%ld:\tbyte\n",sizeof(float));
	printf("  double          \t:%ld:\tbyte\n",sizeof(double));
	printf("  long double     \t:%ld:\tbyte\n",sizeof(long double));
	printf("  size_t          \t:%ld:\tbyte\n",sizeof(size_t));
	printf("  pointer char*   \t:%ld:\tbyte\n",sizeof(char*));
	printf("  pointer int*    \t:%ld:\tbyte\n",sizeof(int*));
	printf("  pointer double* \t:%ld:\tbyte\n",sizeof(double*));
	printf("\n");
}

int main(int argc, char** argv){
	struct option opt;
	struct cmplx *KNL = NULL;
	int length_KNL = 0;
	struct cmplx *BASE = NULL;
	long int length_BASE = 0;
	struct cmplx *EXBASE = NULL;
	long int length_EXBASE = 0;
	struct cmplx *ADDITION = NULL;
	long int length_ADDITION = 0;
	FILE *IN;
	int exit_im = 0;
	int i = 0;
	int j = 0;

	/* (*  set option */
	init_options(&opt);
	get_options(argc-1,argv+1,&opt);
	if(opt.print_help == 1){
		help();
		exit_im = 1;
	}
	if(opt.check_option == 1){
		print_options(opt);
		exit_im = 1;
	}
	if(opt.check_size == 1){
		print_size();
		exit_im = 1;
	}
	if(exit_im >= 1){
		exit(0);
	}
	if((opt.base_file[0] == '\0') || (opt.kernel_file[0] == '\0')){
		help();
		exit(0);
	}
	/* *) */

	/* (* read KNL */
	KNL = alloc_cmplx_vec(KNL,(size_t)opt.kernel_size);
	if((IN = fopen(opt.kernel_file,"r")) == NULL){
		perror(opt.kernel_file);
		exit(1);
	}
	length_KNL = read_cmplx_vec_from_fp(KNL,opt.kernel_format,opt.kernel_separator,IN);
	fclose(IN);
	/* *) */

	/* (* read base */
	BASE = alloc_cmplx_vec(BASE,(size_t)opt.base_size);
	if((IN = fopen(opt.base_file,"r")) == NULL){
		perror(opt.base_file);
		exit(1);
	}
	length_BASE = read_cmplx_vec_from_fp(BASE,opt.base_format,opt.base_separator,IN);
	fclose(IN);
	/* *) */

	/* (* create overhang and convolve */
	if(opt.overhang >= 1){
		printf(BRK_S);
		length_ADDITION = length_KNL - 1;
		length_EXBASE = length_BASE + length_ADDITION;
		ADDITION = alloc_cmplx_vec(ADDITION,length_ADDITION);
		if(opt.overhang == 1){
			for(i=0;i<length_ADDITION;i++){
				ADDITION[i] = BASE[i%length_BASE];
			}
		}
		EXBASE = conjugate_new_complex_vec(BASE,length_BASE,opt.oh_conj_direction,ADDITION,length_ADDITION,opt.oh_fill_direction);
		convolve_complex_vec(EXBASE,(long int)length_EXBASE,KNL,(long int)length_KNL,opt.convolve_method,opt.slide_step,1);
		free(ADDITION);
		free(EXBASE);
		printf(BRK_E);
		printf("\n");
	}else{
		convolve_complex_vec(BASE,(long int)length_BASE,KNL,(long int)length_KNL,opt.convolve_method,opt.slide_step,1);
	}
	/* *) */
	return(0);
}
