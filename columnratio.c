/* columnratio.c */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "../include/data_read.c"
#include "../include/alloc.c"

#define LEN_FILE_NAME 2048
#define LEN_SHORT_TERM 48
#define LF '\n'
#define FS ' '

struct option {
	char *input_file_name;
	int line_length;
	int term_length;
	int cskip;
	int rskip;
	float sum;
	int column_size;
	int row_size;
	int check_opt;
	int print_help;
};

int init_option(struct option *opt){
	if((opt->input_file_name = calloc(LEN_FILE_NAME,sizeof(char))) == NULL){
		fprintf(stderr,"[ERROR] failed : calloc() in init_option().\n");
		exit(1);
	}
	opt->line_length = 10000000;
	opt->term_length = 2048;
	opt->cskip = 0;
	opt->rskip = 0;
	opt->sum = 1000;
	opt->column_size = 10000;
	opt->row_size = 1000;
	opt->check_opt = 0;
	return(0);
}

int get_option(int optc, char **optv, struct option *opt){
	int i;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			opt->print_help = 1;
		}
		else if(strcmp(optv[i],"-c") == 0){
			opt->check_opt = 1;
		}
		else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",opt->input_file_name);
		}
		else if(strncmp(optv[i],"cskip=",6) == 0){
			sscanf(optv[i],"cskip=%d",&opt->cskip);
		}
		else if(strncmp(optv[i],"rskip=",6) == 0){
			sscanf(optv[i],"rskip=%d",&opt->rskip);
		}
		else if(strncmp(optv[i],"sum=",4) == 0){
			sscanf(optv[i],"sum=%f",&opt->sum);
		}
		else if(strncmp(optv[i],"ll=%d",3) == 0){
			sscanf(optv[i],"ll=%d",&opt->line_length);
		}
		else if(strncmp(optv[i],"tl=%d",3) == 0){
			sscanf(optv[i],"tl=%d",&opt->term_length);
		}
		else if(strncmp(optv[i],"c=%d",2) == 0){
			sscanf(optv[i],"c=%d",&opt->column_size);
		}
		else if(strncmp(optv[i],"r=%d",2) == 0){
			sscanf(optv[i],"r=%d",&opt->row_size);
		}
		else {
			printf("[WARN] unknown option:%s:.\n",optv[i]);
		}
	}
	return(0);
}

void print_option(struct option opt){
	printf("PARAMETERS:\n");
	printf("  file :%s:\n",opt.input_file_name);
	printf("  line buffer :%d:\n",opt.line_length);
	printf("  term buffer :%d:\n",opt.term_length);
	printf("  column skip :%d:\n",opt.cskip);
	printf("  row skip :%d:\n",opt.rskip);
	printf("  sum :%f:\n",opt.sum);
	printf("  column size :%d:\n",opt.column_size);
	printf("  row size :%d:\n",opt.row_size);
	printf("\n");
}

void print_help(){
	printf("USAGE:\n");
	printf("  columnratio if=<input file> [rskip=<skip size>] [cskip=<skip size>] [c=<column size>] [r=<row size>] [ll=<line buf length>] [tl=<term buf length>] [sum=<sum>] [-c] [-h]\n");
	printf("\n");
}

int main(int argc, char **argv){

	/* (* vars */
	struct option opt;
	FILE *IFP = NULL;
	int ie = 0;
	int c = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int y = 0;
	int line_start = -1;
	int num_lines = 0;
	int num_columns = 0;
	char *line = NULL;
	int line_ptr = 0;
	char *term = NULL;
	double *vec = NULL;
	float **mat = NULL;
	int IN_FS = 0;
	float ftmp = 0;
	/* *) */

	/* (* option analysis */
	init_option(&opt);
	get_option(argc-1,argv+1,&opt);
	if(argc < 2){
		opt.print_help = 1;
		ie++;
	}
	if(opt.print_help == 1){
		print_help();
		ie++;
	}
	if(opt.check_opt == 1){
		print_option(opt);
		ie++;
	}
	if(ie > 0){
		exit(0);
	}
	/* *) */

	/* (* allocation */
	vec = calloc(opt.column_size,sizeof(double));
	if(vec == NULL){
		fprintf(stderr,"[ERROR] failed : calloc for vec.\n");
		exit(1);
	}
	line = calloc(opt.line_length,sizeof(char));
	if(line == NULL){
		fprintf(stderr,"[ERROR] failed : calloc for line.\n");
		exit(1);
	}
	term = calloc(opt.term_length,sizeof(char));
	if(term == NULL){
		fprintf(stderr,"[ERROR] failed : calloc for term.\n");
		exit(1);
	}
	mat = f_calloc_mat(opt.column_size,opt.row_size);
	/* *) */

	/* (* read file */
	/* open */
	if((IFP = fopen(opt.input_file_name,"r")) == NULL){
		perror(opt.input_file_name);
		exit(1);
	}

	/* skip lines */
	while(num_lines < opt.rskip){
		while((c = fgetc(IFP)) != LF){
		}
		num_lines++;
	}

	/* read lines */
	while((c = fgetc(IFP)) != EOF){
		if(c == LF){
			num_columns = 0;
			line_start = 0;
			line[line_ptr] = '\0';

			/* Del last space */
			while(line[line_ptr-1] == FS){
				line[line_ptr-1] = '\0';
				line_ptr--;
			}

			/* Del multi space */
			x = 0;
			IN_FS = 0;
			for(i=0;i<line_ptr;i++){
				if((line[i] == FS)&&(IN_FS > 0)){
					IN_FS++;
				}else if((line[i] == FS)&&(IN_FS == 0)){
					IN_FS++;
					line[x] = line[i];
					x++;
				}else if((line[i] != FS)&&(IN_FS > 0)){
					IN_FS = 0;
					line[x] = line[i];
					x++;
				}else if((line[i] != FS)&&(IN_FS == 0)){
					line[x] = line[i];
					x++;
				}
			}
			line[x] = '\0';
			line_ptr = x;

			/* skip columns */
			while(num_columns < opt.cskip){
				if(line[line_start] == FS){
					num_columns++;
				}
				line_start++;
			}

			j = 0;
			k = 0;
			for(i=line_start;i<line_ptr;i++){
				if(line[i] == FS){
					term[j] = '\0';
					sscanf(term,"%f",&ftmp);
					vec[k] = vec[k] + ftmp;
					mat[num_lines][k] = ftmp;
					k++;
					j = 0;
					ftmp = 0;
				}else{
					term[j] = line[i];
					j++;
				}
			}
			term[j] = '\0';
			sscanf(term,"%f",&ftmp);
			vec[k] = vec[k] + ftmp;
			mat[num_lines][k] = ftmp;
			k++;
			j = 0;

			line_ptr = 0;
			num_lines++;
		}
		else {
			line[line_ptr] = c;
			line_ptr++;
		}
	}

	/* close */
	fclose(IFP);
	/* *) */

	/* (* print result */
	for(y=0;y<num_lines;y++){
		for(x=0;x<k;x++){
			printf("%10.16f ",mat[y][x]/vec[x]*opt.sum);
		}
		printf("\n");
	}
	/* *) */

	/* (* exit main */
	return(0);
	/* *) */

}
