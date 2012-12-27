/* term_score.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "/home/pub/include/alloc.c"
#define IDSIZE 256

struct argop {
	int withID;
	char filename[1024];
	int dimANDnum[2];
	int TFtype;
	int DFtype;
	float DFrt;
	int verbose;
};

int read_ftable_from_stream(int num, int dim, FILE *stream, float **table){
	int i;
	int j;
	float ftmp;
	for(i=0;i<num;i++){
		for(j=0;j<dim;j++){
			fscanf(stream,"%f",&ftmp);
			table[i][j] = ftmp;
		}
	}
	return(0);
}

int read_ID_ftable_from_stream(int num, int dim, FILE *stream, float **table, char **IDs){
	int i;
	int j;
	float ftmp;
	char ctmp[IDSIZE];
	for(i=0;i<num;i++){
		fscanf(stream,"%s",ctmp);
		strcpy(IDs[i],ctmp);
		for(j=1;j<dim+1;j++){
			fscanf(stream,"%f",&ftmp);
			table[i][j-1] = ftmp;
		}
	}
	return(0);
}

int read_ftable_from_stdin(int num, int dim, float **table){
	int i;
	int j;
	float ftmp;
	for(i=0;i<num;i++){
		for(j=0;j<dim;j++){
			scanf("%f",&ftmp);
			table[i][j] = ftmp;
		}
	}
	return(0);
}

int read_ID_ftable_from_stdin(int num, int dim, float **table, char **IDs){
	int i;
	int j;
	float ftmp;
	char ctmp[IDSIZE];
	for(i=0;i<num;i++){
		scanf("%s",ctmp);
		strcpy(IDs[i],ctmp);
		for(j=1;j<dim+1;j++){
			scanf("%f",&ftmp);
			table[i][j-1] = ftmp;
		}
	}
	return(0);
}

int read_ilist_from_stream(int num, FILE *stream, int *list){
	int i;
	int itmp;
	for(i=0;i<num;i++){
		fscanf(stream,"%d",&itmp);
		list[i] = itmp;
	}
	return(0);
}

int read_ilist_from_stdin(int num, int *list){
	int i;
	int itmp;
	for(i=0;i<num;i++){
		scanf("%d",&itmp);
		list[i] = itmp;
	}
	return(0);
}

void print_help(void){
	printf("Usage :\n");
	printf("\ttf_idf [-II|-Ii|-iI|-ii] [if=\"input file\"] [dm=\"col\",\"row\"] [DF=\"type\",\"root\"] [-v\"n\"]\n");
	printf("DF options :\n");
	printf("\t0:plane IDF, 1:log (ln) IDF, 2:root IDF, 4:unique DF, 8:total DF\n");
}

int get_options(int arg_start, int arg_end, char **arg_s, struct argop *opt){
	int i = 0;
	int r = 0;
	int s = 0;
	r = arg_end - arg_start;
	while(r > 0){
		for(i=arg_start;i<arg_end;i++){
			if(strcmp(arg_s[i],"-II") == 0){
				opt->withID = 3;
				r--;
			}else if(strcmp(arg_s[i],"-Ii") == 0){
				opt->withID = 2;
				r--;
			}else if(strcmp(arg_s[i],"-ii") == 0){
				opt->withID = 0;
				r--;
			}else if(strncmp(arg_s[i],"if=",3) == 0){
				sscanf(arg_s[i],"if=%s",opt->filename);
				if((s&2) == 0){
					s = s + 2;
				}
				r--;
			}else if(strncmp(arg_s[i],"dm=",3) == 0){
				sscanf(arg_s[i],"dm=%d,%d",&opt->dimANDnum[0],&opt->dimANDnum[1]);
				if((s&4) == 0){
					s = s + 4;
				}
				r--;
			}else if(strncmp(arg_s[i],"TF=",3) == 0){
				sscanf(arg_s[i],"TF=%d",&opt->TFtype);
				r--;
			}else if(strncmp(arg_s[i],"DF=",3) == 0){
				sscanf(arg_s[i],"DF=%d,%f",&opt->DFtype,&opt->DFrt);
				r--;
			}else if(strncmp(arg_s[i],"-v",2) == 0){
				sscanf(arg_s[i],"-v%d",&opt->verbose);
				r--;
			}else if(strcmp(arg_s[i],"-h") == 0){
				print_help();
				exit(0);
			}else{
				printf("unknown option : %s\n",arg_s[i]);
				exit(0);
			}
		}
	}
	return(s);
}

int main(int argc, char **argv){
	FILE *ifp;
	int i;
	int j;
	struct argop options;
	int status = 0;
	float **ftable;
	char **IDlist;
	int N;	/* number of samples */
	float *IDF_list;
	options.withID = 0;
	options.filename[0] = '\0';
	options.TFtype = 0;
	options.DFtype = 5;	/* 0:plane, 1:log, 2:root[n], 4:uniq, 8:total */
	options.verbose = 3;
	status = get_options(1,argc,argv,&options);
	/* (*get matrix */
	if((status == 0)&&((options.withID&2) == 0)){		/* from stdin, without "dm=", without ID */
		read_ilist_from_stdin(2,options.dimANDnum);
		ftable = f_alloc_mat(options.dimANDnum[1],options.dimANDnum[0]);
		read_ftable_from_stdin(options.dimANDnum[1],options.dimANDnum[0],ftable);
	}else if((status == 0)&&((options.withID&2) == 2)){	/* from stdin, without "dm=", with ID */
		read_ilist_from_stdin(2,options.dimANDnum);
		ftable = f_alloc_mat(options.dimANDnum[1],options.dimANDnum[0]);
		IDlist = c_alloc_mat(options.dimANDnum[0],IDSIZE);
		read_ID_ftable_from_stdin(options.dimANDnum[1],options.dimANDnum[0],ftable,IDlist);
	}else if((status == 2)&&((options.withID&2) == 0)){	/* from file, without "dm=", without ID */
		ifp = fopen(options.filename,"r");
		read_ilist_from_stream(2,ifp,options.dimANDnum);
		ftable = f_alloc_mat(options.dimANDnum[1],options.dimANDnum[0]);
		read_ftable_from_stream(options.dimANDnum[1],options.dimANDnum[0],ifp,ftable);
		fclose(ifp);
	}else if((status == 2)&&((options.withID&2) == 2)){	/* from file, without "dm=", with ID */
		ifp = fopen(options.filename,"r");
		read_ilist_from_stream(2,ifp,options.dimANDnum);
		ftable = f_alloc_mat(options.dimANDnum[1],options.dimANDnum[0]);
		IDlist = c_alloc_mat(options.dimANDnum[0],IDSIZE);
		read_ID_ftable_from_stream(options.dimANDnum[1],options.dimANDnum[0],ifp,ftable,IDlist);
		fclose(ifp);
	}else if((status == 4)&&((options.withID&2) == 0)){	/* from stdin, with "dm=", without ID */
		ftable = f_alloc_mat(options.dimANDnum[1],options.dimANDnum[0]);
		read_ftable_from_stdin(options.dimANDnum[1],options.dimANDnum[0],ftable);
	}else if((status == 4)&&((options.withID&2) == 2)){	/* from stdin, with "dm=", with ID */
		ftable = f_alloc_mat(options.dimANDnum[1],options.dimANDnum[0]);
		IDlist = c_alloc_mat(options.dimANDnum[0],IDSIZE);
		read_ID_ftable_from_stdin(options.dimANDnum[1],options.dimANDnum[0],ftable,IDlist);
	}else if((status == 6)&&((options.withID&2) == 0)){	/* from file, with "dm=", without ID */
		ifp = fopen(options.filename,"r");
		ftable = f_alloc_mat(options.dimANDnum[1],options.dimANDnum[0]);
		read_ftable_from_stream(options.dimANDnum[1],options.dimANDnum[0],ifp,ftable);
		fclose(ifp);
	}else if((status == 6)&&((options.withID&2) == 2)){	/* from file, with "dm=", without ID */
		ifp = fopen(options.filename,"r");
		ftable = f_alloc_mat(options.dimANDnum[1],options.dimANDnum[0]);
		IDlist = c_alloc_mat(options.dimANDnum[0],IDSIZE);
		read_ID_ftable_from_stream(options.dimANDnum[1],options.dimANDnum[0],ifp,ftable,IDlist);
		fclose(ifp);
	}else{
	}
	/* *) */
	/*  (*print options etc. */
	if(options.verbose > 1){
		printf("status :%d:\n",status);
		printf("verbose :%d:\n",options.verbose);
		printf("filename :%s:\n",options.filename);
		printf("TFtype :%d:\n",options.TFtype);
		printf("DFtype :%d:\n",options.DFtype);
		printf("DFrt :%f:\n",options.DFrt);
	}
	/* *) */
	/* (*calculate TF/IDF */
	N = options.dimANDnum[1];
	IDF_list = f_calloc_vec(options.dimANDnum[0]);
	if(options.DFtype == 4){			/* plane, uniq */
		for(i=0;i<options.dimANDnum[1];i++){
			for(j=0;j<options.dimANDnum[0];j++){
				if(ftable[i][j] > 0){
					IDF_list[j]+=1;
				}
			}
		}
		for(j=0;j<options.dimANDnum[0];j++){
			 IDF_list[j] = N/IDF_list[j];
		}
	}else if(options.DFtype == 5){ 			/* log, uniq */
		for(i=0;i<options.dimANDnum[1];i++){
			for(j=0;j<options.dimANDnum[0];j++){
				if(ftable[i][j] > 0){
					IDF_list[j]+=1;
				}
			}
		}
		for(j=0;j<options.dimANDnum[0];j++){
			 IDF_list[j] = log(N/IDF_list[j]);
		}
	}else if(options.DFtype == 6){			/* root[n], uniq */
		for(i=0;i<options.dimANDnum[1];i++){
			for(j=0;j<options.dimANDnum[0];j++){
				if(ftable[i][j] > 0){
					IDF_list[j]+=1;
				}
			}
		}
		for(j=0;j<options.dimANDnum[0];j++){
			 IDF_list[j] = pow(N/IDF_list[j],options.DFrt);
		}
	}else if(options.DFtype == 8){			/* plane, total */
		for(i=0;i<options.dimANDnum[1];i++){
			for(j=0;j<options.dimANDnum[0];j++){
				IDF_list[j]+=ftable[i][j];
			}
		}
		for(j=0;j<options.dimANDnum[0];j++){
			 IDF_list[j] = N/IDF_list[j];
		}
	}else if(options.DFtype == 9){			/* log, total */
		for(i=0;i<options.dimANDnum[1];i++){
			for(j=0;j<options.dimANDnum[0];j++){
				IDF_list[j]+=ftable[i][j];
			}
		}
		for(j=0;j<options.dimANDnum[0];j++){
			 IDF_list[j] = log(N/IDF_list[j]);
		}
	}else if(options.DFtype == 10){			/* root[n], total */
		for(i=0;i<options.dimANDnum[1];i++){
			for(j=0;j<options.dimANDnum[0];j++){
				IDF_list[j]+=ftable[i][j];
			}
		}
		for(j=0;j<options.dimANDnum[0];j++){
			 IDF_list[j] = pow(N/IDF_list[j],options.DFrt);
		}
	}else{
		printf("DFtype :%d: -- not available.\n",options.DFtype);
		exit(0);
	}
	/* *) */
	/* (*print weight */
	if(options.verbose > 1){
		printf("weight :");
		printf("%f",IDF_list[0]);
		for(j=1;j<options.dimANDnum[0];j++){
			printf(",%f",IDF_list[j]);
		}
		printf(":\n");
	}
	/* *) */
	/* (*print table */
	if((options.verbose&1)==1){
		printf("%d %d\n",options.dimANDnum[0],options.dimANDnum[1]);
	}
	if((options.withID&1) == 0){
		for(i=0;i<options.dimANDnum[1];i++){
			printf("%f",ftable[i][0]*IDF_list[0]);
			for(j=1;j<options.dimANDnum[0];j++){
				printf(" %f",ftable[i][j]*IDF_list[j]);
			}
			printf("\n");
		}
	}else if((options.withID&1) == 1){
		for(i=0;i<options.dimANDnum[1];i++){
			printf("%s ",IDlist[i]);
			printf("%f",ftable[i][0]*IDF_list[0]);
			for(j=1;j<options.dimANDnum[0];j++){
				printf(" %f",ftable[i][j]*IDF_list[j]);
			}
			printf("\n");
		}
	}
	/* *) */
	return(0);
}
