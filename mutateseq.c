#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BASE_LENGTH 300000000
#define NAME_LEN 125
#define COMM_LEN 256

static unsigned long seed;
static char *base;
static int len_m_pstn;

void usage(void){
	printf("usage : \n");
	printf("cat \"file\" | mutateseq n=\"munber_of_points\"\n");
	printf("mutateseq f=\"file\" n=\"munber_of_points\"\n");
	printf("mutateseq f=\"file\" n=\"munber_of_points\"\n");
	printf("mutateseq f=\"file\" n=\"munber_of_points\" seed=\"random_seed\"\n");
}

int point_mutation_rand(char *str, int *pstn, int len_pstn, time_t m_seed){
	int i;
	srand(m_seed);
	for(i=0;i<len_pstn;i++){
		switch(random()%(4)){
			case 0 : *(str+pstn[i]) = 'A';break;
			case 1 : *(str+pstn[i]) = 'G';break;
			case 2 : *(str+pstn[i]) = 'T';break;
			case 3 : *(str+pstn[i]) = 'C';break;
		}
	}
	return(0);
}

int *make_mutation_pstn_rand(int n, int range, unsigned long u_seed){
	int i;
	int *arr;
	arr = malloc((n+16)*sizeof(int));
	if(arr == NULL){
		printf("failed : malloc() -- exit.\n");
		exit(0);
	}
	seed = time(NULL)+u_seed;
	for(i=0;i<n;i++){
		srand(seed);
		arr[i] = rand()%(range);
		seed = seed+arr[i]+i;
	}
	return(arr);
}

int main(int argc, char *argv[]){
	unsigned long u_seed;
	int i;
	char c;
	int *m_pstn;
	int mutate_times;
	int baselen;
	base = malloc(BASE_LENGTH*sizeof(char));
	if(base == NULL){
		printf("failed : malloc(base) -- exit.\n");
		exit(0);
	}
	if(argc == 1){
		usage();
	}else if(argc == 2){
		sscanf(argv[1],"n=%d",&mutate_times);
		u_seed = 0;
		len_m_pstn = mutate_times;
		i = 0;
		while(scanf("%c",&c) != EOF){
			if((c != '\n')&&(c != ' ')){
				base[i] = c;
				i++;
			}
		}
		base[i] = '\0';
		baselen = i;
		m_pstn = make_mutation_pstn_rand(mutate_times,baselen,u_seed);
		point_mutation_rand(base,m_pstn,len_m_pstn,u_seed);
		printf("%s\n",base);
	}else if(argc == 3){
		char filename[NAME_LEN];
		char comment[COMM_LEN];
		FILE *fp;
		int flag = 0;
		if(strncmp(argv[1],"f=",2) == 0){
			int j = 0;
			sscanf(argv[1],"f=%s",filename);
			sscanf(argv[2],"n=%d",&mutate_times);
			len_m_pstn = mutate_times;
			u_seed = 0;
			i = 0;
			if((fp = fopen(filename,"r")) == NULL){
				perror(filename);
				exit(1);
			}else{
				while((c = fgetc(fp)) != EOF){
					if(c == '>'){
						flag = 1;
					}
					if(flag == 1){
						if(c != '\n'){
							comment[j] = c;
							j++;
						}else{
							flag = 0;
							comment[j] = '\n';
							j++;
							comment[j] = '\0';
						}
					}else if(flag == 0){
						if((c != '\n')&&(c != ' ')){
							base[i] = c;
							i++;
						}
					}
				}
				base[i] = '\0';
			}
			fclose(fp);
			printf("%s",comment);
		}else{
			sscanf(argv[1],"n=%d",&mutate_times);
			sscanf(argv[2],"seed=%ld",&u_seed);
			len_m_pstn = mutate_times;
			i = 0;
			while(scanf("%c",&c) != EOF){
				if((c != '\n')&&(c != ' ')){
					base[i] = c;
					i++;
				}
			}
			base[i] = '\0';
		}
		baselen = i;
		m_pstn = make_mutation_pstn_rand(mutate_times,baselen,u_seed);
		point_mutation_rand(base,m_pstn,len_m_pstn,u_seed);
		printf("%s\n",base);
	}else if(argc == 4){
		char filename[NAME_LEN];
		char comment[COMM_LEN];
		FILE *fp;
		int flag = 0;
		if(strncmp(argv[1],"f=",2) == 0){
			int j = 1;
			sscanf(argv[1],"f=%s",filename);
			sscanf(argv[2],"n=%d",&mutate_times);
			sscanf(argv[3],"seed=%ld",&u_seed);
			len_m_pstn = mutate_times;
			i = 0;
			if((fp = fopen(filename,"r")) == NULL){
				perror(filename);
				exit(1);
			}else{
				while((c = fgetc(fp)) != EOF){
					if(c == '>'){
						flag = 1;
						comment[0] = 1;
					}
					if(flag == 1){
						if(c != '\n'){
							comment[j] = c;
							j++;
						}else{
							flag = 0;
							comment[j] = '\n';
							j++;
							comment[j] = '\0';
						}
					}else if(flag == 0){
						if((c != '\n')&&(c != ' ')){
							base[i] = c;
							i++;
						}
					}
				}
				base[i] = '\0';
			}
			fclose(fp);
			printf("%s",comment);
			baselen = i;
			m_pstn = make_mutation_pstn_rand(mutate_times,baselen,u_seed);
			point_mutation_rand(base,m_pstn,len_m_pstn,u_seed);
			printf("%s\n",base);
		}else{
			usage();
		}
	}
	return(0);
}
