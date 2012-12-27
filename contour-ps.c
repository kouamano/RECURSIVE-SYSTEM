#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int wid;
static int hei;
static int init_x_scale = 10;
static int init_y_scale = 10;
static float ratio = 10;

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
	return(0);
}

int main(int argc, char **argv){
	if(argc == 2){	//for test
		print_def();
		exit(0);
	}
	if(argc == 3){
		sscanf(argv[1],"%d",&wid);
		sscanf(argv[2],"%d",&hei);
		print_head(wid*init_x_scale, hei*init_y_scale);
		print_def();
		print_offset(init_x_scale,init_y_scale,-1,0);
		print_next_from_stdin();
		print_tail();
		exit(0);
	}
	return(0);
}


