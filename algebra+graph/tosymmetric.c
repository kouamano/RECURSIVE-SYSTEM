/* tosymmetric.c */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "../../include/data_read.c"
#include "../../include/alloc.c"

#define LEN_FILE_NAME 2048
#define LEN_SAMPLE_NAME 256
#define LEN_TMP_STR 128

struct option {
	char *input_file_name;
	int FLS;		/* first input line as size (col row) */
	int OFLS;		/* first output line as size (col row) */
	int FCN;		/* first input column as name */
	int OFCN;		/* first output column as name */
	int column_size;
	int row_size;
	int check_opt;
	int print_help;
	char ONF[LEN_TMP_STR];
};

int init_option(struct option *opt){
	if((opt->input_file_name = calloc(LEN_FILE_NAME,sizeof(char))) == NULL){
		fprintf(stderr,"[ERROR] failed : calloc() in init_option().\n");
		exit(1);
	}
	opt->FLS = 0;
	opt->OFLS = 0;
	opt->FCN = 0;
	opt->OFCN = 0;
	opt->column_size = -1;
	opt->row_size = -1;
	opt->check_opt = 0;
	sprintf(opt->ONF,"%s","%.12lf ");
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
		else if(strncmp(optv[i],"FLS=",4) == 0){
			sscanf(optv[i],"FLS=%d",&opt->FLS);
		}
		else if(strncmp(optv[i],"OFLS=",5) == 0){
			sscanf(optv[i],"OFLS=%d",&opt->OFLS);
		}
		else if(strncmp(optv[i],"FCN=",4) == 0){
			sscanf(optv[i],"FCN=%d",&opt->FCN);
		}
		else if(strncmp(optv[i],"OFCN=",5) == 0){
			sscanf(optv[i],"OFCN=%d",&opt->OFCN);
		}
		else if(strncmp(optv[i],"c=%d",2) == 0){
			sscanf(optv[i],"c=%d",&opt->column_size);
		}
		else if(strncmp(optv[i],"r=%d",2) == 0){
			sscanf(optv[i],"r=%d",&opt->row_size);
		}
		else if(strncmp(optv[i],"ONF=%s",4) == 0){
			sscanf(optv[i],"ONF=%s",opt->ONF);
			if((int)strlen(strcat(opt->ONF," ")) < 1){
				fprintf(stderr,"[WARN] failed: strcat().\n");
			}
		}
		else {
			fprintf(stderr,"[WARN] unknown option:%s:.\n",optv[i]);
		}
	}
	return(0);
}

void print_option(struct option opt){
	printf("PARAMETERS:\n");
	printf("  file :%s:\n",opt.input_file_name);
	printf("  FLS :%d:\n",opt.FLS);
	printf("  OFLS :%d:\n",opt.OFLS);
	printf("  FCN :%d:\n",opt.FCN);
	printf("  OFCN :%d:\n",opt.OFCN);
	printf("  ONF :%s:\n",opt.ONF);
	printf("  column size :%d:\n",opt.column_size);
	printf("  row size :%d:\n",opt.row_size);
	printf("\n");
}

void print_help(){
	printf("USAGE:\n");
	printf("  tosymmetric if=<input file> [FLS={0|1}] [OFLS={0|1}] [FCN={0|1}] [OFCN={0|1}] [ONF=<format>] [c=<column size>] [r=<row size>] [-c] [-h]\n");
	printf("\n");
	printf("OPTIONS:\n");
	printf("  if= : input file.\n");
	printf("  FLS= : first input line as size.\n");
	printf("  OFLS= : first output line as size.\n");
	printf("  FCN= : first input column as name.\n");
	printf("  OFCN= : first output column as name.\n");
	printf("  ONF= : output numeric format in C.\n");
	printf("  c= : column size.\n");
	printf("  r= : row size.\n");
	printf("  -c : print options.\n");
	printf("  -h : print help.\n");
	printf("\n");
}

int main(int argc, char **argv){

	/* (* vars */
	struct option opt;
	FILE *IFP = NULL;
	int ie = 0;
	int c = 0;
	int dim_smpl = 0;
	int num_smpl = 0;
	float **src_mat = NULL;
	char **src_name = NULL;
	int i;
	int j;
	int k;
	double v;
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

	/* (* read file */
	if((IFP = fopen(opt.input_file_name,"r")) == NULL){
		perror(opt.input_file_name);
		exit(1);
	}
	if(opt.FLS == 1){
		read_ilist_from_stream(1,IFP,&dim_smpl);
		fprintf(stderr,"sample dimensions:%d:\n",dim_smpl);
		read_ilist_from_stream(1,IFP,&num_smpl);
		fprintf(stderr,"number of samples:%d:\n",num_smpl);
		src_mat = f_alloc_mat(num_smpl,dim_smpl);
		src_name = c_alloc_mat(num_smpl,LEN_SAMPLE_NAME);
		if(opt.FCN == 1){
			read_ID_ftable_from_stream(num_smpl,dim_smpl,IFP,src_mat,src_name);
		} else if(opt.FCN == 0){
			read_ftable_from_stream(num_smpl,dim_smpl,IFP,src_mat);
		}
	} else if(opt.FLS == 0){
		dim_smpl = opt.column_size;
		fprintf(stderr,"sample dimensions:%d:\n",dim_smpl);
		num_smpl = opt.row_size;
		fprintf(stderr,"number of samples:%d:\n",num_smpl);
		if(num_smpl < 1){ fprintf(stderr,"[ERROR] number of samples : not defined.\n"); }
		if(dim_smpl < 1){ fprintf(stderr,"[ERROR] number of dimensions : not defined.\n"); }
		src_mat = f_alloc_mat(num_smpl,dim_smpl);
		src_name = c_alloc_mat(num_smpl,LEN_SAMPLE_NAME);
		if(opt.FCN == 1){
			read_ID_ftable_from_stream(num_smpl,dim_smpl,IFP,src_mat,src_name);
		} else if(opt.FCN == 0){
			read_ftable_from_stream(num_smpl,dim_smpl,IFP,src_mat);
		}

	}
	fclose(IFP);
	/* *) */

	/* (* print symmetric matrix */
	if(opt.OFLS == 1){
		printf("%d %d\n",dim_smpl,num_smpl);
	}
	if(opt.OFCN == 1){
		for(i=0;i<num_smpl;i++){
			printf("%s ",src_name[i]);
			for(j=0;j<num_smpl;j++){
				v = 0;
				for(k=0;k<dim_smpl;k++){
					v += src_mat[i][k] * src_mat[j][k];
				}
				printf(opt.ONF,v);
			}
			printf("\n");
		}
	} else if(opt.OFCN == 0){
		for(i=0;i<num_smpl;i++){
			//printf("%s ",src_name[i]);
			for(j=0;j<num_smpl;j++){
				v = 0;
				for(k=0;k<dim_smpl;k++){
					v += src_mat[i][k] * src_mat[j][k];
				}
				printf(opt.ONF,v);
			}
			printf("\n");
		}
	}
	/* *) */

	/* (* exit main */
	return(0);
	/* *) */

}
