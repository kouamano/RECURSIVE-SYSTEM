/* SIMilarity between two Strings using N-gram */
/* gives a similarity between two short ascii sequence using n-gram. */

/* CODENAME :*/
/* string_sim_n.c */
/* :END */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define MAX_LEN_STR 300

struct option {
	char *firstseq;
	char *secondseq;
	int n;
};

int init_options (struct option *opt) {
	opt->firstseq[0] = '\0';
	opt->secondseq[0] = '\0';
	opt->n = 0;
	return(0);
}

int get_options (int optc, char **optv, struct option *opt) {
	//sscanf(optv[0],"%s",opt->firstseq);
	strcpy(opt->firstseq,optv[0]);
	//sscanf(optv[1],"%s",opt->secondseq);
	strcpy(opt->secondseq,optv[1]);
	sscanf(optv[2],"%d",&(opt->n));
	return(0);
}

void help (void) {
	printf("USAGE:\n");
	printf("  string_sim_n seq1 seq2 n(>=2)\n");
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
			//fprintf(stderr,"%c-%c ",firstseq[i1],firstseq[i2]);
			if(firstseq[i1] == firstseq[i2]){
				first_selfmatch++;
			}
		}
	}
	//fprintf(stderr,"%d\n",first_selfmatch);
	/* *) */
	/* (* secondseq self match */
	for(j1=0;j1<secondlen;j1++){
		for(j2=0;j2<secondlen;j2++){
			//fprintf(stderr,"%c-%c ",secondseq[j1],secondseq[j2]);
			if(secondseq[j1] == secondseq[j2]){
				second_selfmatch++;
			}
		}
	}
	//fprintf(stderr,"%d\n",second_selfmatch);
	/* *) */
	/* (* firstseq second match */
	for(j1=0;j1<secondlen;j1++){
		for(i1=0;i1<firstlen;i1++){
			//fprintf(stderr,"%c-%c ",secondseq[j1],firstseq[i1]);
			if(secondseq[j1] == firstseq[i1]){
				first_secondmatch++;
			}
		}
	}
	//fprintf(stderr,"%d\n",first_secondmatch);
	/* *) */
	return( pow((double)first_secondmatch,2) / (first_selfmatch * second_selfmatch) );
}

double simshortn (char *firstseq, int firstlen, char *secondseq, int secondlen, int n) {
	int i1 = 0;
	int i2 = 0;
	int j1 = 0;
	int j2 = 0;
	int r = 0;
	int nmatch = 0;
	int first_selfmatch = 0;
	int second_selfmatch = 0;
	int first_secondmatch = 0;
	/* (* firstseq self match */
	for(i1=0;i1<firstlen-n+1;i1++){
		for(i2=0;i2<firstlen-n+1;i2++){
			nmatch = 0;
			for(r=0;r<n;r++){
				//fprintf(stderr,"%c-%c ",firstseq[i1+r],firstseq[i2+r]);
				if(firstseq[i1+r] == firstseq[i2+r]){
					nmatch++;
				}
			}
			//fprintf(stderr,"n=%d",nmatch);
			//fprintf(stderr,":");
			if(nmatch == n){
				first_selfmatch++;
			}
		}
	}
	//fprintf(stderr,"cmatch=%d\n",first_selfmatch);
	/* *) */
	/* (* secondseq self match */
	nmatch = 0;
	for(j1=0;j1<secondlen-n+1;j1++){
		for(j2=0;j2<secondlen-n+1;j2++){
			nmatch = 0;
			for(r=0;r<n;r++){
				//fprintf(stderr,"%c-%c ",secondseq[j1+r],secondseq[j2+r]);
				if(secondseq[j1+r] == secondseq[j2+r]){
					nmatch++;
				}
			}
			//fprintf(stderr,"n=%d",nmatch);
			//fprintf(stderr,":");
			if(nmatch == n){
				second_selfmatch++;
			}
		}
	}
	//fprintf(stderr,"cmatch=%d\n",second_selfmatch);
	/* *) */
	/* (* firstseq second match */
	nmatch = 0;
	for(j1=0;j1<secondlen-n+1;j1++){
		for(i1=0;i1<firstlen-n+1;i1++){
			nmatch = 0;
			for(r=0;r<n;r++){
				//fprintf(stderr,"%c-%c ",secondseq[j1+r],firstseq[i1+r]);
				if(secondseq[j1+r] == firstseq[i1+r]){
					nmatch++;
				}
			}
			//fprintf(stderr,"n=%d",nmatch);
			//fprintf(stderr,":");
			if(nmatch == n){
				first_secondmatch++;
			}
		}
	}
	//fprintf(stderr,"cmatch=%d\n",first_secondmatch);
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
	if(argc != 4){
		help();
		exit(0);
	}
	/* *) */

	/* (* options */
	if( (opt.firstseq = malloc(sizeof(char) * 100)) == NULL){printf("ERROR : faild: malloc().\n");}
	if( (opt.secondseq = malloc(sizeof(char) * 100)) == NULL){printf("ERROR : faild: malloc().\n");}
	init_options(&opt);
	get_options(argc-1,argv+1,&opt);
	if(opt.n < 2){
		fprintf(stderr,"WARN: please set n >= 2.\n");
	}
	/* *) */

	firstlen = strlen(opt.firstseq);
	//fprintf(stderr,"firstlen:%d\n",firstlen);
	secondlen = strlen(opt.secondseq);
	//fprintf(stderr,"secondlen:%d\n",secondlen);
	//match = simshort(opt.firstseq, firstlen, opt.secondseq, secondlen);
	match = simshortn(opt.firstseq, firstlen, opt.secondseq, secondlen, opt.n);
	printf("%f\n",match);
	return(0);
}
