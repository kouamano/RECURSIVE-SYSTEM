#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BASE_SEQ_LEN 400000000
#define FILTER_SEQ_LEN 4096
#define FILE_NAME_SIZE 2048
#define TMP_SEQ_SIZE 1024
#define IGCHAR_SIZE 128
#define IGCHAR_NUM 64
#define DROP_SPACE

struct argop {
	char *basefilename;
	char *base;
	char *filterfilename;
	char *filter;
	char *out_sep;
	char **ignore;
	int match_type;	/* compare:0, score:1 */
	int gap;
	int w_message_level;
	int check_level;
};

void print_argop(struct argop opt){
	printf("basefilename:%s:\n",opt.basefilename);
	printf("base sequence:%s:\n",opt.base);
	printf("filterfilename:%s:\n",opt.filterfilename);
	printf("filter:%s:\n",opt.filter);
	printf("matching type:%d:\n",opt.match_type);
	printf("gap size:%d:\n",opt.gap);
}

void print_help(void){
	printf("USAGE:\n");
	printf("\tseqfilter");
	printf(" [bif=\"base sequence file\"]");
	printf(" [base=\"base sequence\"]");
	printf(" {fif=\"filter sequence file\" | filter=\"filter sequence\"}");
	printf(" [match=Compare | match=Score]");
	printf(" [gap=\"gap size\"]");
	printf(" [--check]");
	printf("\n");
}

int get_options(int arg_start, int arg_end, char **arg_s, struct argop *opt){
	int i = 0;
	int r = 0;
	int s = 0;
	int filter_len = 0;
	int tmp_seq_len = 0;
	r = arg_end - arg_start;
	while(r > 0){
		for(i=arg_start;i<arg_end;i++){
			if(strcmp(arg_s[i],"--help") == 0){
				print_help();
				exit(0);
			}else if(strcmp(arg_s[i],"--check") == 0){
				if((s&1) == 0){
					s = s + 1;
				}
				r--;
			}else if(strncmp(arg_s[i],"bif=",4) == 0){
				sscanf(arg_s[i],"bif=%s",opt->basefilename);
				if((s&2) == 0){
					s = s + 2;
				}
				r--;
			}else if(strncmp(arg_s[i],"fif=",4) == 0){
				sscanf(arg_s[i],"fif=%s",opt->filterfilename);
				if((s&4) == 0){
					s = s + 4;
				}
				r--;
			}else if(strcmp(arg_s[i],"match=Compare") == 0){
				opt->match_type = 1;
				if((s&8) == 0){
					s = s + 8;
				}
				r--;
			}else if(strcmp(arg_s[i],"match=Score") == 0){
				opt->match_type = 2;
				if((s&8) == 0){
					s = s + 8;
				}
			}else if(strncmp(arg_s[i],"gap=",4) == 0){	
				sscanf(arg_s[i],"gap=%d",&opt->gap);
				if((s&16) == 0){
					s = s + 16;
				}
				r--;
			}else if(strncmp(arg_s[i],"ignore=",7) == 0){
				if((s&32) == 0){
					s = s + 32;
				}
				r--;
			}else if(strncmp(arg_s[i],"sep=",4) == 0){
				sscanf(arg_s[i],"sep=%s",opt->out_sep);
				if((s&64) == 0){
					s = s + 64;
				}
			}else if(strncmp(arg_s[i],"base=",5) == 0){
				tmp_seq_len = strlen(arg_s[i]) - 3;
				if(tmp_seq_len > TMP_SEQ_SIZE){
					printf("tmp_seq_len exceeded TMP_SEQ_SIZE.\n if you want to use longer size, please redefine TMP_SEQ_SIZE or use 'bif=' option.\n");
					exit(1);
				}
				if((opt->base = malloc(sizeof(char) * tmp_seq_len)) == NULL){
					printf("failed : malloc(char).\n");
					exit(1);
				}
				sscanf(arg_s[i],"base=%s",opt->base);
				if((s&128) == 0){
					s = s + 128;
				}
				r--;
			}else if(strncmp(arg_s[i],"filter=",7) == 0){
				filter_len = strlen(arg_s[i]) - 6;
				if(filter_len > TMP_SEQ_SIZE){
					printf("filter_len exceeded TMP_SEQ_SIZE.\n if you want to use longer size, please redefine TMP_SEQ_SIZE or use 'fif=' option.\n");
				}
				sscanf(arg_s[i],"filter=%s",opt->filter);
				if((s&256) == 0){
					s = s + 256;
				}
				r--;
			}else if(strncmp(arg_s[i],"-w",2) == 0){
				sscanf(arg_s[i],"-w%d",&opt->w_message_level);
				if((s&512) == 0){
					s = s + 512;
				}
				r--;
			}else{
				printf("unknown option : %s.\n",arg_s[i]);
				exit(1);
			}
		}
	}
	return(s);
}

int is_match(const char *base, const char *filter, int len){
	int r = -1;
	r = strncmp(base,filter,len);
	if(r == 0){
		return(1);
	}else{
		return(0);
	}
}

int match_score(const char *base, const char *filter, int len){
	int i = 0;
	int r = 0;
	for(i=0;i<len;i++){
		if(base[i] == filter[i]){
			r++;
		}
	}
	return(r);
}

int numelize(const char *base, int base_len, const char *filter, int filter_len, int (*score)(), int *out_vec){
	int i = 0;
	int r = 0;
	r = base_len - filter_len + 1;
	for(i=0;i<r;i++){
		out_vec[i] = score(base+i,filter,filter_len);
	}
	return(0);
}

int main(int argc, char **argv){
	struct argop options;
	int opt_status = 0;
	char *base_sequence = NULL;
	int base_seq_len = 0;
	char *filter_sequence = NULL;
	int filter_seq_len = 0;
	FILE *input_file = NULL;
	int i = 0;
	int j = 0;
	char c = '\0';
	int opt_seq_len = 0;
	int *vec = NULL;
	int a = 0;
	/* (* initializing options */
	if((options.basefilename = malloc(sizeof(char) * FILE_NAME_SIZE)) == NULL){
		printf("failed : malloc(char).\n");
		exit(1);
	}
	options.basefilename[0] = '\0';
	if((options.filterfilename = malloc(sizeof(char) * FILE_NAME_SIZE)) == NULL){
		printf("failed : malloc(char).\n");
		exit(1);
	}
	options.filterfilename[0] = '\0';
	if((options.base = malloc(sizeof(char) * TMP_SEQ_SIZE)) == NULL){
		printf("failed : malloc(char).\n");
		exit(1);
	}
	options.base[0] = '\0';
	if((options.filter = malloc(sizeof(char) * TMP_SEQ_SIZE)) == NULL){
		printf("failed : malloc(char).\n");
		exit(1);
	}
	options.filter[0] = '\0';
	if((options.out_sep = malloc(sizeof(char) * TMP_SEQ_SIZE)) == NULL){
		printf("failed : malloc(char).\n");
		exit(1);
	}
	strcpy(options.out_sep," ");
	if((options.ignore = malloc(sizeof(char*) * IGCHAR_NUM)) == NULL){
		printf("failed : malloc(char*).\n");
		exit(1);
	}
	for(i=0;i<IGCHAR_NUM;i++){
		if((options.ignore[i] = malloc(sizeof(char) * IGCHAR_SIZE)) == NULL){
			printf("failed : malloc(char).\n");
			exit(1);
		}
	}
	options.match_type = 1;
	options.gap = 1;
	options.w_message_level = 1;
	options.check_level = 1;
	/* *) */
	/* (* getting options */
	opt_status = get_options(1,argc,argv,&options);
	if((opt_status&1) == 1){
		printf("status:%d:\n",opt_status);
		print_argop(options);
		exit(0);
	}
	/* *) */
	/* (* getting base sequenc */
	if((opt_status&130) == 0){		/* base from stdin */
		if((base_sequence = malloc(sizeof(char) * BASE_SEQ_LEN)) == NULL){
			printf("failed : malloc(char).\n");
			exit(1);
		}
		#ifdef DROP_SPACE
		i = 0;
		while(scanf("%c",&c) != EOF){
			if((c != ' ')&&(c != '\t')&&(c != '\n')){
				base_sequence[i] = c;
				i++;
			}
		}
		base_sequence[i] = '\0';
		#else
		i = 0;
		while(scanf("%c",&c) != EOF){
			base_sequence[i] = c;
			i++;
		}
		#endif
	}else if((opt_status&2) == 2){		/* base from file */
		if((base_sequence = malloc(sizeof(char) * BASE_SEQ_LEN)) == NULL){
			printf("failed : malloc(char).\n");
			exit(1);
		}
		#ifdef DROP_SPACE
		input_file = fopen(options.basefilename,"r");
		i = 0;
		while((c = fgetc(input_file)) != EOF){
			if((c != ' ')&&(c != '\t')&&(c != '\n')){
				base_sequence[i] = c;
				i++;
			}
		}
		base_sequence[i] = '\0';
		fclose(input_file);
		#else
		i = 0;
		while((c = fgetc(input_file)) != EOF){
			base_sequence[i] = c;
			i++;
		}
		#endif
	}else if((opt_status&128) == 128){	/* base from 'base=' option */
		if((base_sequence = malloc(sizeof(char) * BASE_SEQ_LEN)) == NULL){
			printf("failed : malloc(char).\n");
			exit(1);
		}
		#ifdef DROP_SPACE
		i = 0;
		j = 0;
		opt_seq_len = strlen(options.base);
		for(i=0;i<opt_seq_len;i++){
			if((options.base[i] != ' ')&&(options.base[i] != '\t')&&(options.base[i] != '\n')){
				base_sequence[j] = options.base[i];
				j++;
			}
		}
		free(options.base);
		#else
		strcpy(base_sequence,options.base);
		free(options.base);
		#endif
	}
	/* *) */
	/* (* getting filter sequenc */
	if((opt_status&4) == 4){		/* filter from file */
		if((filter_sequence = malloc(sizeof(char) * FILTER_SEQ_LEN)) == NULL){
			printf("failed : malloc(char).\n");
			exit(1);
		}
		#ifdef DROP_SPACE
		input_file = fopen(options.filterfilename,"r");
		i = 0;
		while((c = fgetc(input_file)) != EOF){
			if((c != ' ')&&(c != '\t')&&(c != '\n')){
				filter_sequence[i] = c;
				i++;
			}
		}
		filter_sequence[i] = '\0';
		fclose(input_file);
		#else
		i = 0;
		while((c = fgetc(input_file)) != EOF){
			filter_sequence[i] = c;
			i++;
		}
		#endif
	}else if((opt_status&256) == 256){	/* filter from 'filter=' option */
		if((filter_sequence = malloc(sizeof(char) * FILTER_SEQ_LEN)) == NULL){
			printf("failed : malloc(char).\n");
			exit(1);
		}
		#ifdef DROP_SPACE
		i = 0;
		j = 0;
		opt_seq_len = strlen(options.filter);
		for(i=0;i<opt_seq_len;i++){
			if((options.filter[i] != ' ')&&(options.filter[i] != '\t')&&(options.filter[i] != '\n')){
				filter_sequence[j] = options.filter[i];
				j++;
			}
		}
		free(options.filter);
		#else
		strcpy(filter_sequence,options.filter);
		free(options.filter);
		#endif
	}
	/* *) */
	/* (* caluculating score */
	base_seq_len = strlen(base_sequence);
	filter_seq_len = strlen(filter_sequence);
	a = base_seq_len - filter_seq_len + 1;
	if((vec = calloc(sizeof(int),(a+1))) == NULL){
		printf("failed : malloc(int).\n");
		exit(1);
	}
	/* printf("filter_sequence:%s:\n",filter_sequence); */
	/* printf("base_sequence:%s:\n",base_sequence); */
	if(options.match_type == 1){
		numelize(base_sequence, base_seq_len, filter_sequence, filter_seq_len, &is_match, vec);
	}else if(options.match_type == 2){
		numelize(base_sequence, base_seq_len, filter_sequence, filter_seq_len, &match_score, vec);
	}
	printf("%d",vec[0]);
	for(i=1;i<a;i++){
		printf("%s%d",options.out_sep,vec[i]);
	}
	printf("\n");
	/* *) */
	return(0);
}
