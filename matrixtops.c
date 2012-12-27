/* matrixop.c */

/*************************************************/
/* Copyright (c) 2003-2005 AMANO Kou             */
/* University of Tsukuba                         */
/* University of Library And Information Science */
/* National Institute of Agrobilogical Sciences  */
/* kamano@affrc.go.jp                            */
/*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/pub/include/dim_alloc.c"
#define RSIZ 5

int print_head();
int print_def();
int print_offset();
int print_tail();
int print_next_from_stdin();
int print_table_from_file();
int print_matrix_from_file();
static int wid;
static int hei;
static int init_x_scale = RSIZ;
static int init_y_scale = RSIZ;

int main(int argc, char **argv){
	if(argc == 2){
		print_table_from_file(argv[1],&wid,&hei);
		exit(0);
	}else if(argc == 4){
		sscanf(argv[1],"%d",&wid);
		sscanf(argv[2],"%d",&hei);
		print_matrix_from_file(argv[3],&wid,&hei);
	}
	return(0);
}

int print_head(int w, int h){
	printf("%c",'%');
	printf("!PS-Adobe-2.0\n");
	printf("%c%c",'%','%');
	printf("BoundingBox: 0 0 %d %d\n",w,h);
	printf("%c%c\n",'%','!');
	printf("\n");
	return(0);
}

int print_def(){
	printf("/box{newpath\n");
	printf("\t0 0 moveto\n");
	printf("\t0 1 lineto\n");
	printf("\t1 1 lineto\n");
	printf("\t1 0 lineto\n");
	printf("\tclosepath\n");
	printf("}def gsave\n");
	printf("\n");
	return(0);
}

int print_offset(int x_scale, int y_scale, int x_offset, int y_offset){
	printf("%d %d scale\n",x_scale,y_scale);
	printf("%d %d translate\n",x_offset,y_offset);
	printf("\n");
	return(0);
}

int print_tail(){
	printf("\n");
	printf("grestore\n");
	printf("showpage\n");
	return(0);
}

int print_table_from_file(char *file_name, int *dim, int *num){
	FILE *in;
	int c;
	float f;
	char tmp_str[30];
	int i;
	int j;
	int k;
	int prev_sep;
	int y_count = 0;
	int x_count = 0;
	in = fopen(file_name,"r");
	if(in == NULL){
		perror(file_name);
		exit(1);
	}
	i = 0;
	while((c = getc(in)) != ' '){
		tmp_str[i] = c;
		i++;
	}
	tmp_str[i] = '\0';
	sscanf(tmp_str,"%d",dim);
	i = 0;
	while((c = getc(in)) != '\n'){
		tmp_str[i] = c;
		i++;
	}
	tmp_str[i] = '\0';
	sscanf(tmp_str,"%d",num);
	print_head(wid*init_x_scale, hei*init_y_scale);
	print_def();
	print_offset(init_x_scale,init_y_scale,-1,hei-1);
	i = 0;
	j = 0;
	k = 0;
	prev_sep = 0;
	while((c = fgetc(in)) != EOF){


		if((c != '[') && (c != ']')){
			if((c != ' ') && (c != ',') && (c != '\t') && (c != '\n')){
				tmp_str[i] = c;
				i++;
				prev_sep = 0;
			}else if(c == '/'){
				break;
			}else{

		if(y_count < hei){
			if(x_count == wid){
				printf("\n%d %d translate\n",-wid,-1);
				x_count = 0;
				y_count = y_count+1;
			}
		}

				if(j < *dim-1){
					if(prev_sep == 0){
						tmp_str[i] = '\0';
						sscanf(tmp_str,"%f",&f);
						printf("%s %s %s setrgbcolor\n",tmp_str,tmp_str,tmp_str);
						printf("1 0 translate box fill\n");
						x_count = x_count + 1;
						i = 0;
						j++;
					}
					prev_sep = 1;
				}else if(j == *dim-1){
					if(prev_sep == 0){
						tmp_str[i] = '\0';
						sscanf(tmp_str,"%f",&f);
						printf("%s %s %s setrgbcolor\n",tmp_str,tmp_str,tmp_str);
						printf("1 0 translate box fill\n");
						x_count = x_count + 1;
						i = 0;
						j = 0;
						k++;
					}
					prev_sep = 1;
				}
			}
		}


	}
	tmp_str[i] = '\0';
	sscanf(tmp_str,"%f",&f);
	fclose(in);
	print_tail();
	return(0);
}

int print_matrix_from_file(char *file_name, int *dim, int *num){
	FILE *in;
	int c;
	float f;
	char tmp_str[30];
	int i;
	int j;
	int k;
	int wid;
	int hei;
	int prev_sep;
	int y_count = 0;
	int x_count = 0;
	in = fopen(file_name,"r");
	wid = *dim;
	hei = *num;
	print_head(wid*init_x_scale, hei*init_y_scale);
	print_def();
	print_offset(init_x_scale,init_y_scale,-1,hei-1);
	i = 0;
	j = 0;
	k = 0;
	prev_sep = 0;
	while((c = fgetc(in)) != EOF){


		if((c != '[') && (c != ']')){
			if((c != ' ') && (c != ',') && (c != '\t') && (c != '\n')){
				tmp_str[i] = c;
				i++;
				prev_sep = 0;
			}else if(c == '/'){
				break;
			}else{

		if(y_count < hei){
			if(x_count == wid){
				printf("\n%d %d translate\n",-wid,-1);
				x_count = 0;
				y_count = y_count+1;
			}
		}

				if(j < *dim-1){
					if(prev_sep == 0){
						tmp_str[i] = '\0';
						sscanf(tmp_str,"%f",&f);
						printf("%s %s %s setrgbcolor\n",tmp_str,tmp_str,tmp_str);
						printf("1 0 translate box fill\n");
						x_count = x_count + 1;
						i = 0;
						j++;
					}
					prev_sep = 1;
				}else if(j == *dim-1){
					if(prev_sep == 0){
						tmp_str[i] = '\0';
						sscanf(tmp_str,"%f",&f);
						printf("%s %s %s setrgbcolor\n",tmp_str,tmp_str,tmp_str);
						printf("1 0 translate box fill\n");
						x_count = x_count + 1;
						i = 0;
						j = 0;
						k++;
					}
					prev_sep = 1;
				}
			}
		}


	}
	tmp_str[i] = '\0';
	sscanf(tmp_str,"%f",&f);
	fclose(in);
	print_tail();
	return(0);
}

