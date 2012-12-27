/* complex_list_wt.c               */
/* main program of complex_list_wt */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define FILE_NAME_SIZE 260
#define SHORT_STRING_SIZE 1024
#define LONG_STRING_SIZE 20000
#define SHORT_BUFF_SIZE 512
#define LONG_BUFF_SIZE 10000
#define BRK_S "{"
#define BRK_E "}"
#include "/home/pub/include/alloc.c"
#include "complexop.h"
#include "complexop.c"

struct option {
	int print_help;
	int check_option;
	int check_size;
	char base_file[FILE_NAME_SIZE];
	char wavelet_file[FILE_NAME_SIZE];
	int base_format;
	int wavelet_format;
	long int base_size;
	unsigned int wavelet_size;
	char base_separator;
	char wavelet_separator;
	int buff_size;
	int scale_start;
	int scale_end;
	int scale_step;
	int slide_step;
	char scale_step_func[SHORT_STRING_SIZE];
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
	(*opt).wavelet_file[0] = '\0';
	(*opt).base_format = 1;
	(*opt).wavelet_format = 1;
	(*opt).base_separator = ',';
	(*opt).wavelet_separator = ',';
	(*opt).base_size = 10000000;
	(*opt).wavelet_size = 10000;
	(*opt).buff_size = 30;
	(*opt).scale_start = 1;
	(*opt).scale_end = 64;
	(*opt).scale_step = 1;
	(*opt).slide_step = 1;
	sscanf("linier","%s",(*opt).scale_step_func);
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
		}else if(strncmp(optv[i],"wf=",3) == 0){
			sscanf(optv[i],"wf=%s",(*opt).wavelet_file);
		}else if(strncmp(optv[i],"bfm=",4) == 0){
			sscanf(optv[i],"bfm=%d",&(*opt).base_format);
		}else if(strncmp(optv[i],"wfm=",4) == 0){
			sscanf(optv[i],"wfm=%d",&(*opt).wavelet_format);
		}else if(strncmp(optv[i],"bfs=",4) == 0){
			sscanf(optv[i],"bfs=%c",&(*opt).base_separator);
		}else if(strncmp(optv[i],"wfs=",4) == 0){
			sscanf(optv[i],"wfs=%c",&(*opt).wavelet_separator);
		}else if(strncmp(optv[i],"bs=",3) == 0){
			sscanf(optv[i],"bs=%ld",&(*opt).base_size);
		}else if(strncmp(optv[i],"ws=",3) == 0){
			sscanf(optv[i],"ws=%d",&(*opt).wavelet_size);
		}else if(strncmp(optv[i],"buff=",5) == 0){
			sscanf(optv[i],"buff=%d",&(*opt).buff_size);
		}else if(strncmp(optv[i],"scale=",6) == 0){
			sscanf(optv[i],"scale=%d,%d",&(*opt).scale_start,&(*opt).scale_end);
		}else if(strncmp(optv[i],"scale_step=",11) == 0){
			sscanf(optv[i],"scale_step=%d",&(*opt).scale_step);
		}else if(strncmp(optv[i],"slide=",6) == 0){
			sscanf(optv[i],"slide=%d",&(*opt).slide_step);
		}else if(strncmp(optv[i],"scale_func=",11) == 0){
			sscanf(optv[i],"scale_func=%s",(*opt).scale_step_func);
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
	printf("  wavelet file:%s:\n",opt.wavelet_file);
	printf("  base format:%d:\n",opt.base_format);
	printf("  wavelet format:%d:\n",opt.wavelet_format);
	printf("  base separator:%c:\n",opt.base_separator);
	printf("  wavelet separator:%c:\n",opt.wavelet_separator);
	printf("  base size:%ld:\n",opt.base_size);
	printf("  wavelet size:%d:\n",opt.wavelet_size);
	printf("  buffer size:%d:\n",opt.buff_size);
	printf("  scale start:%d:\n",opt.scale_start);
	printf("  scale end:%d:\n",opt.scale_end);
	printf("  scale step:%d:\n",opt.scale_step);
	printf("  scale step function:%s:\n",opt.scale_step_func);
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
	printf("  complex_list_wt bf=<base file> wf=<mother wavelet file> [bfm=<base format>] [wfm=<wavelet format>] [bfs=<base field separetor>] [wfs=<wavelet field separator>] [bs=<base size>] [ws=<mother wavelet size>] [buff=<buffer size>] scale=<from (integer)>,<to (integer)> [scale_step=<step>] [slide=<slide step>] [scale_func=<scale step function>] overhang=<overhang option> [fill=<overhang filling value>] [conj_direction=<direction>] [fill_direction=<direction>] [conv=<convolve method>] [-h] [-c] [-s]\n");
	printf("\nFILE FORMAT:\n");
	printf("example:\n");
	printf("  1+3i,1,i,1i,...\n");
	printf("\nOPTION REMARK:\n");
	printf("  scale func     : currently only \"linier\" option is available.\n");
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
	struct cmplx *MW = NULL;
	int length_MW = 0;
	struct cmplx **scaled_MW_list = NULL;
	int *scale_scaled_MW_list = 0;
	struct cmplx *BASE = NULL;
	long int length_BASE = 0;
	struct cmplx *EXBASE = NULL;
	long int length_EXBASE = 0;
	struct cmplx *ADDITION = NULL;
	int length_ADDITION = 0;
	FILE *IN;
	int exit_im = 0;
	int scale_width = 0;
	/*int scale_position = 0;*/
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
	if((opt.base_file[0] == '\0') || (opt.wavelet_file[0] == '\0')){
		help();
		exit(0);
	}
	/* *) */

	/* (* read MW */
	MW = alloc_cmplx_vec(MW,(size_t)opt.wavelet_size);
	if((IN = fopen(opt.wavelet_file,"r")) == NULL){
		perror(opt.wavelet_file);
		exit(1);
	}
	length_MW = read_cmplx_vec_from_fp(MW,opt.wavelet_format,opt.wavelet_separator,IN);
	fclose(IN);
	//printf("length_MW:%d:\n",length_MW);
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

	/* (* create scaled_MW_list */
	scale_width = (int)((opt.scale_end - opt.scale_start)/opt.scale_step) + 1;
	scale_scaled_MW_list = i_alloc_vec(scale_width);
	scaled_MW_list = calloc_cmplx_vec_ptr(scaled_MW_list,scale_width);
	j = 0;
	for(i=opt.scale_start;i<=opt.scale_end;i+=opt.scale_step){
		scale_scaled_MW_list[j] = i;
		scaled_MW_list[j] = scaled_cmplx_vec(MW,length_MW,scale_scaled_MW_list[j],scaled_MW_list[j]);
		//printf("%d\n",scale_scaled_MW_list[j]);
		j++;
	}
	/* *) */

	/* (* test 
	printf("----test start-----\n");
	printf("j:%d:\n",j);
	printf("scale_width:%d:\n",scale_width);
	for(i=0;i<scale_width;i++){
		printf("%d:",scale_scaled_MW_list[i]);
		printf("%d\n",length_MW);
		print_cmplx_vec(scaled_MW_list[i],scale_scaled_MW_list[i]*length_MW,"");
		printf("\n\n");
	}
	printf("----test end-----\n");
	 *) */


	/* UNDER CONSTRUCTION,  next : for scaled_MW array -- 2 */
	/* (* create overhang and convolve */
	if(opt.overhang >= 1){
		printf(BRK_S);
		length_ADDITION = length_MW * scale_scaled_MW_list[0] - 1;
		length_EXBASE = length_BASE + length_ADDITION;
		ADDITION = alloc_cmplx_vec(ADDITION,length_ADDITION);
		if(opt.overhang == 1){
			for(i=0;i<length_ADDITION;i++){
				ADDITION[i] = BASE[i%length_BASE];
			}
		}
		EXBASE = conjugate_new_complex_vec(BASE,length_BASE,opt.oh_conj_direction,ADDITION,length_ADDITION,opt.oh_fill_direction);
		convolve_complex_vec(EXBASE,(long int)length_EXBASE,scaled_MW_list[0],(long int)length_MW*scale_scaled_MW_list[0],opt.convolve_method,opt.slide_step,1);
		free(ADDITION);
		free(EXBASE);
		for(j=1;j<scale_width;j++){
			printf(",");
			length_ADDITION = length_MW * scale_scaled_MW_list[j] - 1;
			length_EXBASE = length_BASE + length_ADDITION;
			ADDITION = alloc_cmplx_vec(ADDITION,length_ADDITION);
			if(opt.overhang == 1){
				for(i=0;i<length_ADDITION;i++){
					ADDITION[i] = BASE[i];
				}
			}
			EXBASE = conjugate_new_complex_vec(BASE,length_BASE,opt.oh_conj_direction,ADDITION,length_ADDITION,opt.oh_fill_direction);
			convolve_complex_vec(EXBASE,(long int)length_EXBASE,scaled_MW_list[j],(long int)length_MW*scale_scaled_MW_list[j],opt.convolve_method,opt.slide_step,1);
			free(ADDITION);
			free(EXBASE);
		}
		printf(BRK_E);
		printf("\n");
	}else{
		convolve_complex_vec(BASE,(long int)length_BASE,scaled_MW_list[0],(long int)length_MW*scale_scaled_MW_list[0],opt.convolve_method,opt.slide_step,1);
	}
	/* *) */


	return(0);
}
