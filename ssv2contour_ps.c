#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif
#define X_SCALE 10
#define Y_SCALE 10
#define X 300
#define Y 120000
void print_head();
void print_def();
void print_offset();
void print_tail();
void read_to_array_from_stdin();
void print_next_from_stdin();
static int wid;
static int hei;
static int init_x_scale = X_SCALE;
static int init_y_scale = Y_SCALE;
static float ratio = 10;
static float *array;

static int len_X[Y];
static int len_Y;
static float v_max = 0;
static float v_min = 0;
static int len_X_max = 0;
static int len_Y_max = 0;

int main(int argc, char **argv){
	if(argc == 1){
		//int i;
		int x;
		int y;
		array = malloc(sizeof(float)*X*Y);
		if(array == NULL){
			printf("failed : malloc() -- exit.\n");
			exit(0);
		}
		read_to_array_from_stdin();
		/*
		for(y=0;y<=len_Y;y++){
			for(x=0;x<=len_X[y];x++){
				printf("%d ",array[y*X+x]);
			}
			printf("\n");
		}
		*/
		wid = len_X_max+1;
		hei = len_Y_max+1;
		print_head(wid*init_x_scale, hei*init_y_scale);
		print_def();
		print_offset(init_x_scale,init_y_scale,-1,0);
		for(y=0;y<=len_Y;y++){
			for(x=0;x<=len_X[y];x++){
				//printf("%d ",array[y*X+x]);
				printf("%f %f %f setrgbcolor\n",(float)array[y*X+x]/v_max,(float)array[y*X+x]/v_max,(float)array[y*X+x]/v_max);
				printf("1 0 translate ");
				printf("box fill\n");
			}
			printf("\n%d %d translate\n",-len_X[y]-1,1);
			printf("\n");
		}
		print_tail();
		exit(0);
	}else if(argc == 2){
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
	return(1);
}

void print_head(int w, int h){
	printf("%c",'%');
	printf("!PS-Adobe-2.0\n");
	printf("%c%c",'%','%');
	printf("BoundingBox: 0 0 %d %d\n",w,h);
	printf("%c%c\n",'%','!');
	printf("\n");
}

void print_def(){
	printf("/box{newpath\n");
	printf("\t0 0 moveto\n");
	printf("\t0 1 lineto\n");
	printf("\t1 1 lineto\n");
	printf("\t1 0 lineto\n");
	printf("\tclosepath\n");
	printf("}def gsave\n");
	printf("\n");
}

void print_offset(int x_scale, int y_scale, int x_offset, int y_offset){
	printf("%d %d scale\n",x_scale,y_scale);
	printf("%d %d translate\n",x_offset,y_offset);
	printf("\n");
}

void print_tail(){
	printf("\n");
	printf("grestore\n");
	printf("showpage\n");
}

void read_to_array_from_stdin(){
	char c;
	int i = 0;
	int j = 0;
	int k = 0;
	char str[128];
	int prev_space = 0;
	while((scanf("%c",&c)) != EOF){
		if((c != ' ')&&(c != '\n')){
			str[i] = c;
			i++;
			prev_space = 0;
		}else if(c == ' '){
			str[i] = '\0';
			sscanf(str,"%f",&array[j*X+k]);
			//printf("%d,%d,%d ",j,k,array[j*X+k]);
			v_max = max(v_max,array[j*X+k]);
			v_min = min(v_min,array[j*X+k]);
			i = 0;
			if(prev_space == 0){
				k++;
			}
			prev_space = 1;
		}else if(c == '\n'){
			str[i] = '\0';
			sscanf(str,"%f",&array[j*X+k]);
			//printf("%d,%d,%d\n",j,k,array[j*X+k]);
			v_max = max(v_max,array[j*X+k]);
			v_min = min(v_min,array[j*X+k]);
			len_X[j] = k;
			len_X_max = max(len_X_max,k);
			len_Y = j;
			len_Y_max = j;
			i = 0;
			k = 0;
			j++;
			prev_space = 0;
		}
	}
}

void print_next_from_stdin(){
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
