#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/pub/include/alloc.c"
#define MAX_LEN 100000000

struct f_rfreqs {
	int r;
	int f;
};

struct f_rfreqs *f_frequencies(const float range, const int length, const float *data, int *freq_length){
	int i;
	int j;
	int size;
	float q;
	int hit;
	struct f_rfreqs *frq;
	if((frq = calloc(length,sizeof(struct f_rfreqs))) == NULL){
		fprintf(stderr,"[E]failed : malloc(), exit.\n");
		exit(1);
	}
	if(data[0] >= 0){
		q = data[0]/range;
	}else{
		q = data[0]/range;
		if((data[0] - q*range) == 0){
			q = data[0]/range;
		}else{
			q = data[0]/range - 1;
		}
	}
	frq[0].r = (int)q;
	frq[0].f = 1;
	size = 1;
	hit = 0;
	for(i=1;i<length;i++){
		hit = 0;
		for(j=0;j<size;j++){
			if(data[i] >= 0){
				q = data[i]/range;
			}else{
				q = data[i]/range;
				if((data[i] - q*range) == 0){
					q = data[i]/range;
				}else{
					q = data[i]/range - 1;
				}
			}
			if((int)q == frq[j].r){
				frq[j].f++;
				hit = 1;
				break;
			}
		}
		if(hit == 0){
			frq[size].r = q;
			frq[size].f++;
			size++;
		}
	}
	if((frq = realloc(frq,sizeof(struct f_rfreqs)*size)) == NULL){
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
	float seg;
	char tmp[128];
	char c;
	float *ff = NULL;
	struct f_rfreqs *out;
	FILE *fp;
	ff = f_alloc_vec(MAX_LEN);
	i = 0;
	j = 0;
	l_len = 0;
	if(argc == 2){
		sscanf(argv[1],"%f",&seg);
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
	}else if(argc == 3){
		i = 0;
		j = 0;
		l_len = 0;
		sscanf(argv[1],"%f",&seg);
		if((fp = fopen(argv[2],"r")) == NULL){
			perror(argv[2]);
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
	
	out = f_frequencies(seg, l_len, ff, &freq_len);
	for(i=0;i<freq_len;i++){
		printf("%d<=,<%d %d\n",out[i].r*(int)seg,(out[i].r+1)*(int)seg,out[i].f);
	}

	return(0);
}
