#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME_LEN 1024
#define STRING_SHORT_LEN 1024
#define SEP "\n"

struct option {
	int help;
	int check;
	char *input_file_name;
	int size;
	int gap;
	char *output_head;
	int user_head;
	int output_char_type;	/* 0:alp(no space); 5:atgcnATGCN */
	char *serial_NO_type;
};

void init_option(struct option *opt){
	opt->help = 0;
	opt->check = 0;
	if((opt->input_file_name = calloc(sizeof(char) , FILE_NAME_LEN)) == NULL){printf("failed: malloc().\n"); exit(0);}
	opt->input_file_name[0] = '\0';
	opt->size = 1000;
	opt->gap = 0;
	if((opt->output_head = calloc(sizeof(char) , FILE_NAME_LEN)) == NULL){printf("failed: malloc().\n"); exit(0);}
	opt->user_head = 0;
	opt->output_char_type = 0;
	if((opt->serial_NO_type = calloc(sizeof(char) , FILE_NAME_LEN)) == NULL){printf("failed: malloc().\n"); exit(0);}
	sscanf("%012d","%s",opt->serial_NO_type);
}

get_option(struct option *opt, int optc, char **optv){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			opt->help = 1;
		}else if(strcmp(optv[i],"--help") == 0){
			opt->help = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			opt->check = 1;
		}else if(strcmp(optv[i],"--check") == 0){
			opt->check = 1;
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",opt->input_file_name);
		}else if(strncmp(optv[i],"size=",5) == 0){
			sscanf(optv[i],"size=%d",&opt->size);
		}else if(strncmp(optv[i],"gap=",4) == 0){
			sscanf(optv[i],"gap=%d",&opt->gap);
		}else if(strncmp(optv[i],"type=",5) == 0){
			sscanf(optv[i],"type=%d",&opt->output_char_type);
		}else if(strncmp(optv[i],"SN=",3) == 0){
			sscanf(optv[i],"SN=%s",opt->serial_NO_type);
		}else if(strncmp(optv[i],"head=",5) == 0){
			sscanf(optv[i],"head=%s",opt->output_head);
			opt->user_head = 1;
		}else{
			fprintf(stderr,"Unknown option:%s\n.",optv[i]);
		}
	}
}

void print_option(struct option opt){
	printf("\nARGUMENTS:\n");
	printf("\thelp			:%d:\n",opt.help);
	printf("\tcheck			:%d:\n",opt.check);
	printf("\tfile			:%s:\n",opt.input_file_name);
	printf("\tsize			:%d:\n",opt.size);
	printf("\tgap			:%d:\n",opt.gap);
	printf("\toutput head		:%s:\n","<not asigned>");
	printf("\toutput char type	:%s:\n","<not available>");
	printf("\tuser header		:%s:\n",opt.user_head);
	printf("\tserial No. type	:%s:\n",opt.serial_NO_type);
	printf("\n");
}


void help(void){
	printf("\nUSEAGE:\n");
	printf("\twindow_FASTA if=<input file> size=<size> [gap=<gap>] [type=<output char type>] [head=<user defined header>] [SN=<serial No. type>] [-h] [-c]\n");
	printf("\nDESCRIPTION:\n");
	printf("\twindow_FASTA create plural fasta sequences from one fasta sequence.\n");
	printf("\twith overlap or interval.\n");
	printf("\n");
	printf("\tsize: window size.\n");
	printf("\tgap: gap size (between the end of frame and the start of the next frame); if the size is initiated as negative, then makes overlap.\n");
	printf("\toutput head: set to be FASTA head.\n");
	printf("\tuser defined head: instead of FASTA head.\n");
	printf("\toutput char type: allow character type.\n");
	printf("\tserial No. type: serial No. sequence format in C.\n");
	printf("\n");
	printf("EXAMPLE(S):\n");
	printf("\n");
}

int main(int argc, char **argv){
	struct option opt;
	int ie = 0;
	int is_open = 0;
	int c = 0;
	int i = 0;
	int ptr = 0;
	//int bfskip = 0;
	//char *bf;
	FILE *IN;

	/* (* options */
	init_option(&opt);
	get_option(&opt,argc-1,argv+1);
	if( (opt.help == 1) || (opt.check == 1) ){ie = 1;}
	if( opt.help == 1 ){help();}
	if( opt.check == 1 ){print_option(opt);}
	if(ie == 1){exit(0);}
	/* *) */

	/* (* file open */
	if(strlen(opt.input_file_name) == 0){
		IN = stdin;
	}else{
		if((IN = fopen(opt.input_file_name,"r")) == NULL){
			perror(opt.input_file_name);
			exit(0);
		}
		is_open++;
	}
	/* *) */

	/* (* pre read */
	while((c = getc(IN)) != '>');
	if(opt.user_head < 1){
		opt.output_head[i] = c;
	}
	while((c = getc(IN)) != '\n'){
		i++;
		if(opt.user_head < 1){
			opt.output_head[i] = c;
		}
	}
	i++;
	opt.output_head[i] = '\0';
	/* *) */

	/* (* while 1 */
	if(opt.gap == 0){
		int SN = 0;
		printf("%s_",opt.output_head);
		printf(opt.serial_NO_type,0);
		printf(SEP);
		while((c = getc(IN)) != EOF){
			if(c>=0x40 && c<=0x7e){
				ptr++;
				printf("%c",c);
				if(ptr%opt.size == 0){
					SN++;
					printf("\n%s_",opt.output_head);
					printf(opt.serial_NO_type,SN);
					printf(SEP);
				}
			}
		}
		printf("\n");
	}

	else if(opt.gap > 0){
		int SN = 0;
		int a = 0;
		printf("%s_",opt.output_head);
		printf(opt.serial_NO_type,0);
		printf(SEP);
		while((c = getc(IN)) != EOF){
			if(c>=0x40 && c<=0x7e){
				a = ((ptr)%(opt.gap + opt.size));
				if(a < opt.size){
					printf("%c",c);
				}
				if(a == opt.size){
					SN++;
					printf("\n%s_",opt.output_head);
					printf(opt.serial_NO_type,SN);
					printf(SEP);
				}
				ptr++;
			}
		}
		printf("\n");
	}

	else if(opt.gap < 0){
		if((opt.gap * 2) + opt.size < 0){
			printf("gap size must be over half of frame size.\n");
			exit(0);
		}
		int SN = 0;
		int ptr = 0;
		int block_ptr = 0;
		char *block;
		char *tail;
		block = calloc(sizeof(char) , opt.size + 1);
		tail = calloc(sizeof(char) , -opt.gap + 1);
		if(opt.size + opt.gap < 0){
			fprintf(stderr,"ERROR too big gap (set gap <= size).\n");
		}
		while(ptr < opt.size){
			c = fgetc(IN);
			if(c>=0x40 && c<=0x7e){
				block[ptr] = c;
				ptr++;
			}
		}
		printf("%s_",opt.output_head);
		printf(opt.serial_NO_type,SN);
		printf("\n");
		printf("%s",block);
		strncpy(tail,block+opt.size+opt.gap,-opt.gap);
		for(i=0;i<opt.size + 1;i++){
			block[i] = 0;
		}
		ptr = 0;
		//printf("hoge\n");
		//printf("--%s--\n",tail);
		while((c = getc(IN)) != EOF){
			if(c>=0x40 && c<=0x7e){
				if(ptr%(opt.size+opt.gap) == 0){
					SN++;
					if(ptr != 0){
						printf("%s",tail);
					}
					printf("%s\n",block);
					//printf("[%d]",opt.size+opt.gap);
					//strncpy(tail,block+opt.size+opt.gap+opt.gap,-opt.gap);
					printf("%s_",opt.output_head);
					printf(opt.serial_NO_type,SN);
					printf("\n");
					if(ptr == 0){
						printf("%s",tail);
					}
					strncpy(tail,block+opt.size+opt.gap+opt.gap,-opt.gap);
					//printf("=%s=",tail);
					block_ptr = 0;
					for(i=0;i<opt.gap;i++){
						block[i] = 0;
					}
				}
				block[block_ptr] = c;
				block_ptr++;
				ptr++;
			}
		}
		block[block_ptr] = 0;
		printf("%s",tail);
		printf("%s",block);
		printf("\n");
	}
	/* *) */

	/* (* while 2
		int SN = 0;
		printf("%s_",opt.output_head);
		printf(opt.serial_NO_type,0);
		printf(SEP);
		while((c = getc(IN)) != EOF){
			if(c>=0x40 && c<=0x7e){
				printf("%c",c);
				if(ptr%opt.size == (opt.size - 1)){
					SN++;
					printf("\n%s_",opt.output_head);
					printf(opt.serial_NO_type,SN);
					printf(SEP);
					fseek(IN,opt.gap,SEEK_CUR);
				}
				ptr++;
			}
		}
		printf("\n");
	 *) */

	/* (* file close*/
	if(is_open > 0){
		fclose(IN);
	}
	/* *) */

	return(0);
}
