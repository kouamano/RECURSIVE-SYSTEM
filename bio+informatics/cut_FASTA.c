#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME_LEN 1024
#define STRING_SHORT_LEN 1024
#define IGNORE_CHAR " \t\n"

struct option {
	int help;
	int check;
	char *input_file_name;
	int start;
	int size;
	int input_with_head;
	int output_with_head;
	int output_with_original_head;
	char *output_head;
	int alph_only;
	//int ACGT_only;
	int ALL_char;
	int exact_ALL_char;
	int status;
};

void print_help(void){
	printf("DESCRIPTION:\n");
	printf("\tcut_FASTA create plural fasta sequences from one fasta sequence.\n");
	printf("\twith no overlap and no interval.\n");
	printf("USEAGE:\n");
	printf("\tcut_FASTA if=<file name> [start=<start position>] [size=<frame size (bp)>] [-I|-i] [-o|-O<head>|-H<head>] [-a|-N|-A|-X] [-h] [-c]\n");
	printf("OPTIONS:\n");
	printf("\t-h|--help:the program prints this message and exits.\n");
	printf("\t-c|--check:the program prints its arguments and exits.\n");
	printf("\tif=<>:specify a input file.\n");
	printf("\tstart=<>:specify start position. default value is 0.\n");
	printf("\tsize=<>:specify size of frame sequence. default value is 1000.\n");
	printf("\t-i:without input head (annotation).\n");
	printf("\t-I:with input head (annotation).\n");
	printf("\t-o:output without head (annotation).\n");
	printf("\t-O:output with head (annotation) specified by the user.\n");
	printf("\t-H:output with original head (annotation).\n");
	printf("\t-a:data is expected to consist of alphabet text.\n");
	printf("\t-N:data is expected to consist of nucleotide text.\n");
	printf("\t-A:data is expected to consist of ASCII text.\n");
	printf("\t-X:data is expected to consist of ASCII text containing blank.\n");
	printf("EXAMPLE:\n");
	printf("\tcut_FASTA if=test.fasta -I start=4 size=20 -OSeq_%%03d\n");
}

int init_option(struct option *opt){
	opt->help = 0;
	opt->check = 0;
	if((opt->input_file_name = calloc(FILE_NAME_LEN,sizeof(char))) == NULL){
		fprintf(stderr,"[E]failed: calloc() in init_option(). ");
		fprintf(stderr," -- exit.\n");
		exit(1);
	}
	opt->start = 0;
	opt->size = 1000;
	opt->input_with_head = 1;
	opt->output_with_head = 1;
	opt->output_with_original_head = 0;
	if((opt->output_head = calloc(STRING_SHORT_LEN,sizeof(char))) == NULL){
		fprintf(stderr,"[E]failed: calloc() in init_option() ");
		fprintf(stderr," -- exit.\n");
		exit(1);
	}
	opt->alph_only = 1;
	//opt->ACGT_only = 0;
	opt->ALL_char = 0;
	opt->exact_ALL_char = 0;
	opt->status = 0;
	return(0);
}

int get_option(int optc, char **optv, struct option *opt){
	int err_status = 0;
	int i;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"--help") == 0){
			opt->help = 1;
		}else if(strcmp(optv[i],"-h") == 0){
			opt->help = 1;
		}else if(strcmp(optv[i],"--check") == 0){
			opt->check = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			opt->check = 1;
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",opt->input_file_name);
		}else if(strncmp(optv[i],"start=",5) == 0){
			sscanf(optv[i],"start=%d",&opt->start);
		}else if(strncmp(optv[i],"size=",5) == 0){
			sscanf(optv[i],"size=%d",&opt->size);
		}else if(strcmp(optv[i],"-i") == 0){
			opt->input_with_head = 0;
		}else if(strcmp(optv[i],"-I") == 0){
			opt->input_with_head = 1;
		}else if(strcmp(optv[i],"-o") == 0){
			opt->output_with_head = 0;
		}else if(strncmp(optv[i],"-O",2) == 0){
			opt->output_with_head = 1; sscanf(optv[i],"-O%s",opt->output_head); }else if(strncmp(optv[i],"-H",2) == 0){
			opt->output_with_head = 1;
			opt->output_with_original_head = 1;
			sscanf(optv[i],"-H%s",opt->output_head);
		}else if(strcmp(optv[i],"-a") == 0){
			opt->alph_only = 1;
			//opt->ACGT_only = 0;
			opt->ALL_char = 0;
			opt->exact_ALL_char = 0;
		}else if(strcmp(optv[i],"-N") == 0){
			opt->alph_only = 0;
			//opt->ACGT_only = 1;
			opt->ALL_char = 0;
			opt->exact_ALL_char = 0;
		}else if(strcmp(optv[i],"-A") == 0){
			opt->alph_only = 0;
			//opt->ACGT_only = 0;
			opt->ALL_char = 1;
			opt->exact_ALL_char = 0;
		}else if(strcmp(optv[i],"-X") == 0){
			opt->alph_only = 0;
			//opt->ACGT_only = 0;
			opt->ALL_char = 0;
			opt->exact_ALL_char = 1;
		}else{
			fprintf(stderr,"[W]Unknown option\t:%s:\n",optv[i]);
		}
	}
	return(err_status);
}

void print_option(struct option opt){
	printf("ARGUMENTS:\n");
	printf("help                      :%d:\n",opt.help);
	printf("check                     :%d:\n",opt.check);
	printf("file                      :%s:\n",opt.input_file_name);
	printf("start                     :%d:\n",opt.start);
	printf("size                      :%d:\n",opt.size);
	printf("input with head           :%d:\n",opt.input_with_head);
	printf("output with head          :%d:\n",opt.output_with_head);
	printf("output with original head :%d:\n",opt.output_with_original_head);
	printf("additional head           :%s:\n",opt.output_head);
	printf("print alphabet only?      :%d:\n",opt.alph_only);
	//printf("print ACGT only?          :%d:\n",opt.ACGT_only);
	printf("print all char?           :%d:\n",opt.ALL_char);
	printf("print exact all char?     :%d:\n",opt.exact_ALL_char);
}

int main(int argc, char **argv){
	/* (* declaration */
	FILE *IN;
	struct option opt;
	int file_open = 0;
	char c;
	int count_position = 0;
	int count_char = 0;
	int count_word = 0;
	//int i = 0;
	/* *) */
	/* (* option operations */
	init_option(&opt);
	get_option(argc-1,argv+1,&opt);
	if(opt.help == 1){
		print_help();
	}
	if(opt.check == 1){
		print_option(opt);
	}
	if((opt.help == 1)||(opt.check == 1)){
		exit(0);
	}
	/* *) */
	/* (* test */
	/* *) */
	/* (* file open */
	if(strlen(opt.input_file_name) > 0){
		if((IN = fopen(opt.input_file_name,"r")) == NULL){
			perror(opt.input_file_name);
			exit(1);
		}else{
			file_open = 1;
		}
	}else{
		IN = stdin;
	}
	/* *) */
	/* (* read file */
	if(opt.input_with_head == 0){
		if((c = getc(IN)) == '>'){
			fprintf(stderr,"[W]annotation line found.\n");
			count_position++;
			if((opt.ALL_char == 1)||(opt.exact_ALL_char == 1)){
				printf("%c",c);
			}
		}
	}else{
		while((c = getc(IN)) != '>');
		while((c = getc(IN)) != '\n');
	}
	if(opt.alph_only == 1){
		if(opt.start > 0){
			if(opt.output_with_head == 1){
				printf(">");
				printf(opt.output_head,count_word);
				printf("\n");
			}
			while(opt.start > count_position){
				c = getc(IN);
				if(((65<=(int)c)&&((int)c<=90))||((97<=(int)c)&&((int)c<=122))){
					count_position++;
					printf("%c",c);
				}
			}
			printf("\n");
			count_word++;
		}
		if(opt.output_with_head == 1){
			printf(">");
			printf(opt.output_head,count_word);
			printf("\n");
		}
		while((c = getc(IN)) != EOF){
			if(((65<=(int)c)&&((int)c<=90))||((97<=(int)c)&&((int)c<=122))){
				if(count_char == opt.size){
					count_word++;
					printf("\n");
					if(opt.output_with_head == 1){
						printf(">");
						printf(opt.output_head,count_word);
						printf("\n");
					}
					count_char = 0;
				}
				printf("%c",c);
				count_char++;
			}
		}
		printf("\n");
	}else if(opt.ALL_char == 1){
		if(opt.start > 0){
			if(opt.output_with_head == 1){
				printf(">");
				printf(opt.output_head,count_word);
				printf("\n");
			}
			while(opt.start > count_position){
				c = getc(IN);
				if((c==IGNORE_CHAR[1])&&(c==IGNORE_CHAR[2])&&(IGNORE_CHAR[3])){
					count_position++;
					printf("%c",c);
				}
			}
			printf("\n");
			count_word++;
		}
		if(opt.output_with_head == 1){
			printf(">");
			printf(opt.output_head,count_word);
			printf("\n");
		}
		while((c = getc(IN)) != EOF){
			if((c==IGNORE_CHAR[1])&&(c==IGNORE_CHAR[2])&&(IGNORE_CHAR[3])){
				if(count_char == opt.size){
					count_word++;
					printf("\n");
					if(opt.output_with_head == 1){
						printf(">");
						printf(opt.output_head,count_word);
						printf("\n");
					}
					count_char = 0;
				}
				printf("%c",c);
				count_char++;
			}
		}
		printf("\n");
	}else if(opt.exact_ALL_char == 1){
		if(opt.start > 0){
			if(opt.output_with_head == 1){
				printf(">");
				printf(opt.output_head,count_word);
				printf("\n");
			}
			while(opt.start > count_position){
				c = getc(IN);
				//if((c==IGNORE_CHAR[1])&&(c==IGNORE_CHAR[2])&&(IGNORE_CHAR[3])){
					count_position++;
					printf("%c",c);
				//}
			}
			printf("\n");
			count_word++;
		}
		if(opt.output_with_head == 1){
			printf(">");
			printf(opt.output_head,count_word);
			printf("\n");
		}
		while((c = getc(IN)) != EOF){
			//if((c==IGNORE_CHAR[1])&&(c==IGNORE_CHAR[2])&&(IGNORE_CHAR[3])){
				if(count_char == opt.size){
					count_word++;
					printf("\n");
					if(opt.output_with_head == 1){
						printf(">");
						printf(opt.output_head,count_word);
						printf("\n");
					}
					count_char = 0;
				}
				printf("%c",c);
				count_char++;
			//}
		}
		printf("\n");
	}
	/* *) */
	/* (* file close */
	if(file_open == 1){
		fclose(IN);
	}
	/* *) */
	return(0);
}
