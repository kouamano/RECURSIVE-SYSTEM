#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN_FILE_NAME 1024 

struct option {
	int count;
	int ratio;
	int dom;
	char *file;
};

void init_option(struct option *options){
	options->count = 0;
	options->ratio = 0;
	options->dom = 1;
	if((options->file = calloc(LEN_FILE_NAME,sizeof(char))) == NULL){
		fprintf(stderr,"failed: malloc() -- exit.\n");
		exit(1);
	}
}

int get_options(struct option *options, int opt_start, int opt_end, char **optv){
	int i;
	int r = 0;
	for(i=opt_start;i<opt_end;i++){
		if(strcmp(optv[i],"-c") == 0){
			options->count = 1;
			options->dom = 1;
		}else
		if(strcmp(optv[i],"-r") == 0){
			options->ratio = 1;
			options->dom = 1;
		}else
		if(strncmp(optv[i],"-r",2) == 0){
			options->ratio = 1;
			sscanf(optv[i],"-r%d",&options->dom);
		}else
		if(strncmp(optv[i],"if=",3) == 0){
			sscanf(optv[i],"if=%s",options->file);
		}else
		{
			r++;
		}
	}
	return(r);
}

int countAT(char c){
	if((c == 'a')||(c == 'A')||(c == 't')||(c == 'T')){
		return(1);
	}else{
		return(0);
	}
	return(0);
}

int counter(FILE *IN, int *_counter){
	char c;
	int ig = 0;
	int len = 0;
	while((c = fgetc(IN)) != EOF){
		if((c == '>')&&(ig == 0)){
			ig = 1;
		}else if((c == '>')&&(ig == 1)){
			if(c == '\n'){
				ig = 0;
			}
		}else if((c != '>')&&(ig == 1)){
			if(c == '\n'){
				ig = 0;
			}
		}else if((c != '>')&&(ig != 1)){
			if((c != '\n')&&(c != ' ')&&(c != '\t')){
				len++;
			}
			*_counter=*_counter + countAT(c);
		}
	}
	return(len);
}

int main(int argc, char **argv){
	int _counter = 0;
	int len = 0;
	FILE *IN;
	int is_open = 0;
	struct option options;
	init_option(&options);
	get_options(&options,1,argc,argv);
	if((options.count == 0)&&(options.ratio == 0)){
		options.ratio = 1;
	}
	if(strlen(options.file) > 0){
		if((IN = fopen(options.file,"r")) == NULL){
			perror(options.file);
			exit(1);
		}
		is_open = 1;
	}else{
		IN = stdin;
	}
	len = counter(IN,&_counter);
	if(options.count == 1){printf("%d/%d\n",_counter,len);}
	if(options.ratio == 1){printf("%f\n",(float)_counter * options.dom / len);}
	if(is_open == 1){
		fclose(IN);
	}
	/*
	printf("count:%d:\n",options.count);
	printf("ratio:%d:\n",options.ratio);
	printf("dom:%d:\n",options.dom);
	printf("file:%s:\n",options.file);
	*/
	return(0);
}
