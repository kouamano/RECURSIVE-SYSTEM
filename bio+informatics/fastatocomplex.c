#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define FILE_NAME_LEN 1024
#define BS "{"
#define BE "}"

struct opt {
	int status;
	char file[FILE_NAME_LEN];
	int fasta_sequence_length;
	int fasta_annotation_length;
	int with_bracket;
	int to_upper;
	int insert_LF;
};

int initialize_options(struct opt *options){
	options->status = 0;
	options->file[0] = 0; options->fasta_sequence_length = 100000000;
	options->fasta_annotation_length = 128;
	options->with_bracket = 1;
	options->to_upper = 1;
	options->insert_LF = 0;
	return options->status;
}

int get_options(int optc, char **optv, struct opt *options){
	int i;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			if((options->status&1) != 1){
				options->status = options->status + 1;
			}
		}else if(strcmp(optv[i],"-c") == 0){
			if((options->status&2) != 2){
				options->status = options->status + 2;
			}
		}else if(strncmp(optv[i],"f=",2) == 0){
			sscanf(optv[i],"f=%s",options->file);
		}else if(strncmp(optv[i],"-l",2) == 0){
			sscanf(optv[i],"-l%d",&options->fasta_sequence_length);
		}else if(strncmp(optv[i],"-H",2) == 0){
			sscanf(optv[i],"-H%d",&options->fasta_annotation_length);
		}else if(strcmp(optv[i],"-b") == 0){
			options->with_bracket = 1;
		}else if(strcmp(optv[i],"+b") == 0){
			options->with_bracket = 0;
		}else if(strcmp(optv[i],"-U") == 0){
			options->to_upper = 1;
		}else if(strcmp(optv[i],"+U") == 0){
			options->to_upper = 0;
		}else if(strncmp(optv[i],"-L",2) == 0){
			sscanf(optv[i],"-L%d",&options->insert_LF);
		}else if(strncmp(optv[i],"+L",2) == 0){
			options->insert_LF = 0;
		}else{
			printf("[W]unknown option:%s:\n",optv[i]);
		}
	}
	return options->status;
}

void print_options(struct opt options){
	printf("OPTION SET:\n");
	printf("  status:%d:\n",options.status);
	printf("  file:%s:\n",options.file);
	printf("  sequence length:%d:\n",options.fasta_sequence_length);
	printf("  annotation length:%d:\n",options.fasta_annotation_length);
	printf("  print bracket:%d:\n",options.with_bracket);
	printf("  to_upper:%d:\n",options.to_upper);
	printf("  insert_LF:%d:\n",options.insert_LF);
}

void help(void){
	printf("USAGE:\n");
	printf("  fastatocomplex f=<file> -l<length> -H<length of FASTA annotation> [-b|+b] [-U|+U] [-L<line count>|+L] -h -c\n");
	printf("OPTIONS:\n");
	printf("  -b: print with bracket.\n");
	printf("  -h: print help.\n");
	printf("  -c: print options.\n");
	printf("  -L: print linefeed.\n");
	printf("OUTPUT:\n");
	printf("  A -> 1\n");
	printf("  T -> -1\n");
	printf("  G -> I\n");
	printf("  C -> -I\n");
}

main(int argc, char **argv){
	signed char c;
	struct opt option;
	FILE *fp;
	int in_head = 0;
	int in_seq = 0;
	int count = 0;
	initialize_options(&option);
	get_options(argc-1,argv+1,&option);
	if(strlen(option.file) == 0){
		help();
		exit(1);
	}
	if((option.status&1) == 1){
		help();
	}
	if((option.status&2) == 2){
		print_options(option);
	}
	if(((option.status&2) == 2)||((option.status&1) == 1)){
		exit(0);
	}
	fp = fopen(option.file,"r");
	if(option.with_bracket == 1){
		printf(BS);
	}
	if(option.to_upper == 1){
		while((c = fgetc(fp)) != EOF){
	                if((in_head == 0)&&(in_seq == 0)){
	                        if(c == '>'){
	                                in_head = 1;
	                        }else{
	                                in_head = 0;
	                                in_seq = 1;
	                        }
	                }else if((in_head == 1)&&(in_seq == 0)){
	                        if(c == '\n'){
	                                in_head = 0;
	                                in_seq = 1;
	                        }
	                }else if((in_head == 0)&&(in_seq == 1)){
	                        if(c == '>'){
	                                fprintf(stderr,"warning: multiple fasta sequence found.\n");
	                                in_head = 1;
	                                in_seq = 0;
	                        }else if(toupper(c) == 'A'){
					printf("1,");
					count++;
	                        }else if(toupper(c) == 'T'){
					printf("-1,");
					count++;
				}else if(toupper(c) == 'G'){
					printf("I,");
					count++;
				}else if(toupper(c) == 'C'){
					printf("-I,");
					count++;
				}else if(c == '\n'){
					;
				}else if(c == '\t'){
					;
				}else if(c == ' '){
					;
				}else{
					printf("0,");
					count++;
				}
	                }else{
	                        fprintf(stderr,"system confusing: check file format.\n");
	                        exit(1);
	                }
			if(option.insert_LF > 0){
				if(count == option.insert_LF){
					printf("\n");
					count = 0;
				}
			}
		}
	}else if(option.to_upper == 0){
                while((c = fgetc(fp)) != EOF){
                        if((in_head == 0)&&(in_seq == 0)){
                                if(c == '>'){
                                        in_head = 1;
                                }else{
                                        in_head = 0;
                                        in_seq = 1;
                                }
                        }else if((in_head == 1)&&(in_seq == 0)){
                                if(c == '\n'){
                                        in_head = 0;
                                        in_seq = 1;
                                }
                        }else if((in_head == 0)&&(in_seq == 1)){
                                if(c == '>'){
                                        fprintf(stderr,"warning: multiple fasta sequence found.\n");
                                        in_head = 1;
                                        in_seq = 0;
                                }else if(c == 'A'){
                                        printf("1,");
					count++;
                                }else if(c == 'T'){
                                        printf("-1,");
					count++;
                                }else if(c == 'G'){
                                        printf("I,");
					count++;
                                }else if(c == 'C'){
                                        printf("-I,");
					count++;
                                }else if(c == '\n'){
                                        ;
                                }else if(c == '\t'){
                                        ;
                                }else if(c == ' '){
                                        ;
                                }else{
                                        printf("0,");
					count++;
                                }
                        }else{
                                fprintf(stderr,"system confusing: check file format.\n");
                                exit(1);
                        }
			if(option.insert_LF > 0){
				if(count == option.insert_LF){
					printf("\n");
					count = 0;
				}
			}
                }
	}
	if(option.with_bracket == 1){
		printf(BE);
	}
	printf("\n");
	fclose(fp);
}







