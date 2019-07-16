/* ck-bracket.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_FILE_NAME 2048
#define BRK_S '{'
#define BRK_E '}'

struct option {
	int help;
	char brks;
	char brke;
	char *file;
};

void init_option(struct option *opt) {
	opt->help = 0;
	opt->brks = BRK_S;
	opt->brke = BRK_E;
	opt->file = malloc(sizeof(char) * LEN_FILE_NAME);
	if(opt->file == NULL){
		fprintf(stderr,"[ERR] malloc: failed.\n");
		exit(0);
	}
}

void get_option(int optc, char ** optv){
}

void help(void){
	printf("USAGE:\n");
	printf("  ck-bracket if=<file> [bs=<bracket start>] [be=<bracket end>] [-h]\n");
}

int main(int argc, char **argv){
	return(0);
}
