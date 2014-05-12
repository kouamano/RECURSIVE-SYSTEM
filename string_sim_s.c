/* string_sim_s */
/* gives a similarity between two short ascii sequence using 1-gram. */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_LEN_STR 300

struct option {
	char *firstseq;
	char *secondseq;
};

int init_options (struct option *opt) {
	opt->firstseq[0] = '\0';
	opt->secondseq[0] = '\0';
	return(0);
}

int get_options (int optc, char **optv, struct option *opt) {
	sscanf(optv[0],"%s",opt->firstseq);
	sscanf(optv[1],"%s",opt->secondseq);
	return(0);
}

void help (void) {
	printf("USAGE:\n");
	printf("  sims seq1 seq2\n");
}

double simshort (char *firstseq, int firstlen, char *secondseq, int secondlen) {
	int i1 = 0;
	int i2 = 0;
	int j1 = 0;
	int j2 = 0;
	int first_selfmatch = 0;
	int second_selfmatch = 0;
	int first_secondmatch = 0;
	/* (* firstseq self match */
	for(i1=0;i1<firstlen;i1++){
		for(i2=0;i2<firstlen;i2++){
			fprintf(stderr,"%c-%c ",firstseq[i1],firstseq[i2]);
			if(firstseq[i1] == firstseq[i2]){
				first_selfmatch++;
			}
		}
	}
	fprintf(stderr,"%d\n",first_selfmatch);
	/* *) */
	/* (* secondseq self match */
	for(j1=0;j1<secondlen;j1++){
		for(j2=0;j2<secondlen;j2++){
			fprintf(stderr,"%c-%c ",secondseq[j1],secondseq[j2]);
			if(secondseq[j1] == secondseq[j2]){
				second_selfmatch++;
			}
		}
	}
	fprintf(stderr,"%d\n",second_selfmatch);
	/* *) */
	/* (* firstseq secondseq match */
	for(j1=0;j1<secondlen;j1++){
		for(i1=0;i1<firstlen;i1++){
			fprintf(stderr,"%c-%c ",secondseq[j1],firstseq[i1]);
			if(secondseq[j1] == firstseq[i1]){
				first_secondmatch++;
			}
		}
	}
	fprintf(stderr,"%d\n",first_secondmatch);
	/* *) */
	return( pow((double)first_secondmatch,2) / (first_selfmatch * second_selfmatch) );
}

int main (int argc, char **argv) {
	/* (* vars */
	struct option opt;
	int firstlen = 0;
	int secondlen = 0;
	double match = 0;
	/* )* */

	/* (* arg check */
	if(argc == 1){
		help();
		exit(0);
	}
	/* *) */

	/* (* options */
	if( (opt.firstseq = malloc(sizeof(char) * 100)) == NULL){printf("ERROR : faild: malloc().\n");}
	if( (opt.secondseq = malloc(sizeof(char) * 100)) == NULL){printf("ERROR : faild: malloc().\n");}
	init_options(&opt);
	get_options(argc-1,argv+1,&opt);
	/* *) */

	firstlen = strlen(opt.firstseq);
	fprintf(stderr,"firstlen:%d\n",firstlen);
	secondlen = strlen(opt.secondseq);
	fprintf(stderr,"secondlen:%d\n",secondlen);
	match = simshort(opt.firstseq, firstlen, opt.secondseq, secondlen);
	printf("%f\n",match);
	return(0);
}
