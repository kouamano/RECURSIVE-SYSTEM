#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/pub/include/dim_alloc.c"
#define MAX_LEN 100000000

struct f_freqs {
	float v;
	int f;
};

struct f_freqs *f_frequencies(const int length, const float *data, int *freq_length){
	int i;
	int j;
	int size;
	int hit;
	struct f_freqs *frq;
	if((frq = calloc(sizeof(struct f_freqs),length)) == NULL){
		fprintf(stderr,"[E]failed : malloc(), exit.\n");
		exit(1);
	}
	frq[0].v = data[0];
	frq[0].f = 1;
	size = 1;
	hit = 0;
	for(i=1;i<length;i++){
		hit = 0;
		for(j=0;j<size;j++){
			if(data[i] == frq[j].v){
				frq[j].f++;
				hit = 1;
				break;
			}
		}
		if(hit == 0){
			frq[size].v = data[i];
			frq[size].f++;
			size++;
		}
	}
	if((frq = realloc(frq,sizeof(struct f_freqs)*size)) == NULL){
		fprintf(stderr,"[E]failed : malloc(), exit.\n");
		exit(1);
	}
	*freq_length = size;
	return(frq);
}

int main(int argc, char **argv){
	int i;
	int j;
	int l_len;
	int freq_len;
	char tmp[128];
	char c;
	float *ff;
	struct f_freqs *out;
	FILE *fp;
	ff = f_alloc_list(MAX_LEN);
	i = 0;
	j = 0;
	l_len = 0;
	if(argc == 1){
		while(scanf("%c",&c) != EOF){
			if((c != ' ')&&(c != '\n')&&(c != '\t')&&(c != '\0')){
				tmp[i] = c;
				i++;
			}else{
				tmp[i] = '\0';
				sscanf(tmp,"%f",&ff[j]);
				j++;
				i = 0;
			}
		}
		l_len = j;
	}else if(argc == 2){
		i = 0;
		j = 0;
		l_len = 0;
		if((fp = fopen(argv[1],"r")) == NULL){
			perror(argv[1]);
			exit(1);
		}
		while((c = fgetc(fp)) != EOF){
			if((c != ' ')&&(c != '\n')&&(c != '\t')&&(c != '\0')){
				tmp[i] = c;
				i++;
			}else{
				tmp[i] = '\0';
				sscanf(tmp,"%f",&ff[j]);
				j++;
				i = 0;
			}
		}
		fclose(fp);
		l_len = j;
	}
	
	out = f_frequencies(l_len, ff, &freq_len);
	for(i=0;i<freq_len;i++){
		printf("%f %d\n",out[i].v,out[i].f);
	}

	return(0);
}
