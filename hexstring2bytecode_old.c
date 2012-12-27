#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME_LEN 256
#define BYTE_LEN 2

struct options {
	int help;
	char file_name[FILE_NAME_LEN];
};

void help(){
	printf("USAGE:\n");
	printf("  hexstring2bytecode [if=<file>] [-h]\n");
}

void init_options(struct options *opt){
	opt->help = 0;
	opt->file_name[0] = '\0';
}

void get_options(int optc, char **optv, struct options *opt){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			opt->help = 1;
		}else if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",opt->file_name);
		}
	}
}

void check_options(struct options opt){
	printf("OPTIONS:\n");
	printf("  help:%d:\n",opt.help);
	printf("  file_name:%s:\n",opt.file_name);
}

int atoi16( const char *NumberString )
{
	char *stopString;
	int result = strtol( NumberString, &stopString, 16 );
	return result;
}

int main(int argc, char **argv){
	FILE *IN;
	int is_open = 0;
	int ie = 0;
	struct options opt;
	signed int c;
	char N_byte[BYTE_LEN + 1];
	int N_byte_len = BYTE_LEN;
	int counter = 0;
	int i = 0;
	int byte_code = 0;
	init_options(&opt);
	get_options(argc-1, argv+1, &opt);
	if(opt.help == 1){
		help();
		ie++;
	}
	if(ie > 0){
		exit(0);
	}
	if(strlen(opt.file_name) > 0){
		if((IN = fopen(opt.file_name,"r")) == NULL){
			perror(opt.file_name);
			exit(1);
		}
		is_open++;
	}else{
		IN = stdin;
	}


	/* (* core code */
	while((c = fgetc(IN)) != EOF){
		i = counter%N_byte_len;
		N_byte[i] = c;
		if(i == N_byte_len-1){
			N_byte[N_byte_len] = '\0';
			//sscanf(N_byte,"%d",&byte_code);
			byte_code = atoi16(N_byte);
			fprintf(stdout,"%c",byte_code);
		}
		counter++;
	}
	if(i != N_byte_len-1){	// -1 でなく -2 ?
		N_byte[i+1] = '\0';
                byte_code = atoi16(N_byte);
                fprintf(stdout,"%c",byte_code);
	}
	/* *) */
	

	if(is_open > 0){
		fclose(IN);
	}
	return(0);
}
