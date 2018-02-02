#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1024
#include "../include/alloc.c"
#include "../include/data_read.c"
#include "../include/math_base.c"

struct options {
	int help;
	int stat;
	int check;
	int n;
	int size;
	char *dlist;
};

void help(void){
	printf("USAGE:\n");
	printf(" mstL [-h] [-s] [-c] n=<nodes (start with 1)> dlist=<\"sorted\" distance list of all node-pairs> size=<no. of entry> \n");
	printf("  -h : help.\n");
	printf("  -s : stat.\n");
	printf("  -c : check args.\n");
	printf("  n : no. of nodes [integer].\n");
	printf("  dlsit : \"<node1> <node2> <dist>\" (space-separated).\n");
	printf("  size : no. of lines [integer].\n");
}

void status(void){
	printf("STATUS:\n");
	printf(" Under construction.\n");
}

struct options *alloc_options(void){
	struct options *p;
	if((p = malloc(sizeof(struct options) * 1)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	if(((*p).dlist = malloc(sizeof(char) * LEN)) == NULL){
		printf("failed : malloc() in alloc_options().\n");
		exit(1);
	}
	return(p);
}

void init_options(struct options *opt){
	(*opt).help = 0;
	(*opt).stat = 0;
	(*opt).check = 0;
	(*opt).size= 0;
	(*opt).dlist[0] = '\0';
}

void get_options(int optc, char **optv, struct options *opt){
	int i = 0;
	for(i=0;i<optc;i++){
		if(strcmp(optv[i],"-h") == 0){
			(*opt).help = 1;
		}else if(strcmp(optv[i],"-s") == 0){
			(*opt).stat = 1;
		}else if(strcmp(optv[i],"-c") == 0){
			(*opt).check = 1;
		}else if(strncmp(optv[i],"n=",2) == 0){
			sscanf(optv[i],"n=%d",&(*opt).n);
		}else if(strncmp(optv[i],"size=",5) == 0){
			sscanf(optv[i],"size=%d",&(*opt).size);
		}else if(strncmp(optv[i],"dlist=",6) == 0){
			sscanf(optv[i],"dlist=%s",(*opt).dlist);
		}
	}
}

void check_options(struct options *opt){
	printf("OPTIONS:\n");
	printf(" opt.n:%d:\n",(*opt).n);
	printf(" opt.size:%d:\n",(*opt).size);
	printf(" opt.dlist:%s:\n",(*opt).dlist);
}

int main(int argc, char **argv){
	float **dlist;
	FILE *fp;
	int c;
	struct options *opt;
	int ie=0;
	int c1;
	int n1;
	int *n1_list;
	int c2;
	int n2;
	int *n2_list;
	int targetClass;
	int joinClass;
	float dst;
	float *dst_list;
	int count = 0;
	int i,j;
	int *classes;
	int classOneCount = 0;

	/*argument operation*/
	opt = alloc_options();
	init_options(opt);
	get_options(argc-1, argv+1, opt);
	if(argc == 1){
		(*opt).help = 1;
	}
	if((*opt).help == 1){
		help();
		ie = 1;
	}
	if((*opt).stat == 1){
		status();
		ie = 1;
	}
	if((*opt).check == 1){
		check_options(opt);
		ie = 1;
	}
	if(ie == 1){
		exit(0);
	}

	/*get size of list*/
	if((*opt).size == 0){
		if((fp=fopen((*opt).dlist,"r")) == NULL){
			perror((*opt).dlist);
			exit(1);
		}
		count = 0;
		while( (c=fgetc(fp)) != EOF ){
			if(c == '\n'){
				count++;
			}
		}
		fclose(fp);
		(*opt).size = count;
		fprintf(stderr,"Line count:%d\n",count);
	}

	/*memory allocation*/
	n1_list = i_alloc_vec((*opt).size);
	n2_list = i_alloc_vec((*opt).size);
	dst_list = f_alloc_vec((*opt).size);
	classes = i_alloc_vec((*opt).n);

	/*class initialization*/
	for(i=0;i<(*opt).n;i++){
		classes[i] = i;
		//printf("%d\n",classes[i]);
	}

	/*datastream*/
	i = 0;
	if((fp=fopen((*opt).dlist,"r")) == NULL){
		perror((*opt).dlist);
		exit(1);
	}
	while(i < (*opt).size){
		fscanf(fp,"%d",&n1);
		n1_list[i] = n1;
		//printf("%d\n",n1_list[i]);

		fscanf(fp,"%d",&n2);
		n2_list[i] = n2;
		//printf("%d\n",n2_list[i]);

		fscanf(fp,"%f",&dst);
		dst_list[i] = dst;
		//printf("%f\n",dst_list[i]);

		i++;
	}
	fclose(fp);

	/*print initial classes*/
	printf("\t{");
	for(i=0;i<(*opt).n;i++){
		printf("%d ",classes[i]);
	}
	printf("}\n");
	/*create MST*/
	for(i=0;i<(*opt).size;i++){
		//printf("i:%d\n",i);
		c1 = classes[n1_list[i]];
		printf("id:%d;c1:%d ",n1_list[i],c1);
		c2 = classes[n2_list[i]];
		printf("id:%d;c2:%d ",n2_list[i],c2);
		printf("dst:%f\t",dst_list[i]);
		if(c1 != c2){
			targetClass = max(c1,c2);
			joinClass = min(c1,c2);
			/*rewrite class of mate of max(c1,c2)*/
			for(j=0;j<(*opt).n;j++){
				if(classes[j] == targetClass){
					classes[j] = joinClass;
					//printf("%d ",classes[j]);
				}
			}
			/*print classes*/
			printf("{");
			for(j=0;j<(*opt).n;j++){
				printf("%d ",classes[j]);
			}
			printf("}\n");
		}else{
			printf("\n");
		}
		/*check break loop*/
		classOneCount = 0;
		for(j=0;j<(*opt).n;j++){
			if(classes[j] == 1){
				classOneCount++;
			}
		}
		if(classOneCount == (*opt).n){
			break;
		}
	}
	return(0);
}


