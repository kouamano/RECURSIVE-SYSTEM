/*** palind.c ***/
/*** DNA (RNA) palindrome search program ***/

/* (*INCLUDE FILES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../../include/alloc.c"
/* INCLUDE FILES*) */

/* (*GLOBAL VARS --including prototypes-- */
struct parindlome_p {
	char *str_p;
	int l_end;
	int l_int;
};
int min_l_end;
int max_l_end;
int min_l_int;
int max_l_int;
int L;
char input_file[128];
char *seq;
int get_args();
struct parindlome_p *test_pari();
/* GLOBAL VARS*) */

/* (*MAIN ROUTINE */
int main(int argc, char **argv){
	get_args(1,argc,argv);
	printf("end:%d,%d\n",min_l_end,max_l_end);
	printf("int:%d,%d\n",min_l_int,max_l_int);
	printf("input:%s\n",input_file);
	exit(0);
}
/* MAIN ROUTINE*) */

/* (*SUB ROUTINES */
int get_args(int start, int stop, char **argstr){
	int i = 0;
	int r = 0;
	int s = 0;
	r = stop-start;
	while(r > 0){
		for(i=start;i<stop;i++){
			if(strncmp(argstr[i],"end=",4) == 0){
				sscanf(argstr[i],"end=%d,%d",&min_l_end,&max_l_end);
				//printf("end:%d,%d\n",min_l_end,max_l_end);
				if((s&1) == 0){
					s = s + 1;
				}
				r--;
			}else if(strncmp(argstr[i],"int=",4) == 0){
				sscanf(argstr[i],"int=%d,%d",&min_l_int,&max_l_int);
				//printf("int:%d,%d\n",min_l_int,max_l_int);
				if((s&2) == 0){
					s = s + 2;
				}
				r--;
			}else if(strncmp(argstr[i],"if=",3) == 0){
				sscanf(argstr[i],"if=%s",input_file);
				//printf("input:%s\n",input_file);
				if((s&4) == 0){
					s = s + 4;
				}
				r--;
			}else{
				printf("unknown option: %s.\n",argstr[i]);
				exit(1);
			}
		}
	}
	return(s);
}
/* SUB ROUTINES*) */

/*** pari.c ***/
