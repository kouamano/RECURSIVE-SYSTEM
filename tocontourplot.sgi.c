#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int print_head();
int print_def();
int print_offset();
int print_tail();
int read_to_array_from_stdin();
int print_array_from_stdin(int **);
int print_next_from_stdin();
static int wid;
static int hei;
static int init_x_scale = 10;
static int init_y_scale = 10;
static float ratio = 10;
static double **array;
static int v_max;
static int v_min;
#define X 100
#define Y 50

int main(int argc, char **argv){
	if(argc == 1){
		int i;
		array = malloc(sizeof(double)*X*Y);
		if(array == NULL){
			printf("failed : malloc() -- exit.\n");
			exit(0);
		}
		*array = malloc(sizeof(double *)*Y);
		if(*array == NULL){
			printf("failed : malloc() -- exit.\n");
			exit(0);
		}
		for(i=0;i<Y;i++){
			array[i] = *array+i*X;
		}
		array[3][9] = 9;
		//printf("%d\n",array[3][9]);
		read_to_array_from_stdin();
	}else if(argc == 2){	//for test
		print_def();
		exit(0);
	}else if(argc == 3){
		sscanf(argv[1],"%d",&wid);
		sscanf(argv[2],"%d",&hei);
		print_head(wid*init_x_scale, hei*init_y_scale);
		print_def();
		print_offset(init_x_scale,init_y_scale,-1,0);
		print_next_from_stdin();
		print_tail();
		exit(0);
	}
}

int print_head(int w, int h){
	printf("%c",'%');
	printf("!PS-Adobe-2.0\n");
	printf("%c%c",'%','%');
	printf("BoundingBox: 0 0 %d %d\n",w,h);
	printf("%c%c\n",'%','!');
	printf("\n");
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
}

int print_offset(int x_scale, int y_scale, int x_offset, int y_offset){
	printf("%d %d scale\n",x_scale,y_scale);
	printf("%d %d translate\n",x_offset,y_offset);
	printf("\n");
}

int print_tail(){
	printf("\n");
	printf("grestore\n");
	printf("showpage\n");
}

int read_to_array_from_stdin(){
	char c;
	int i = 0;
	int j = 0;
	int k = 0;
	char str[1280];
	//int prev_space = 0;
	while((scanf("%c",&c)) != EOF){
		//printf("%c",c);
		if((c != ' ')&&(c != '\n')){
			str[i] = c;
			i++;
		}else if(c == ' '){
			str[i] = '\0';
			sscanf(str,"%d",&array[j][k]);
			printf("%d,%d,%d ",j,k,array[j][k]);
			i = 0;
			k++;
			//prev_space = 1;
		}else if(c == '\n'){
			str[i] = '\0';
			sscanf(str,"%d",&array[j][k]);
			printf("%d,%d,%d\n",j,k,array[j][k]);
			i = 0;
			k = 0;
			j++;
		}
	}
}

int print_array_from_stdin(int **a){
}

int print_next_from_stdin(){
	char c;
	char str[256];
	int str_count = 0;
	float f;
	int wd_count = 0;
	int line_count = 0;
	while(scanf("%c",&c) != EOF){
		if((c != '\n')&&(c != ' ')){
			str[str_count] = c;
			str_count++;
		}else if(c == ' '){
			wd_count++;
			str[str_count] = '\0';
			sscanf(str,"%f",&f);
			str_count = 0;
			printf("%f %f %f setrgbcolor\n",f/ratio,f/ratio,f/ratio);
			printf("1 0 translate ");
			printf("box fill\n");
		}else if(c == '\n'){
			line_count++;
			wd_count++;
			str[str_count] = '\0';
			sscanf(str,"%f",&f);
			str_count = 0;
			printf("%f %f %f setrgbcolor\n",f/ratio,f/ratio,f/ratio);
			printf("1 0 translate ");
			printf("box fill\n");
			printf("\n%d %d translate\n",-wd_count,1);
			str_count = 0;
			wd_count = 0;
		}
	}
}
