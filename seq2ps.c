#include <stdio.h>
#include <stdlib.h>

int print_head();
int print_def();
int print_offset();
int print_tail();
int print_next_from_stdin();
static int wid;
static int hei;
static int init_x_scale = 10;
static int init_y_scale = 10;

int main(int argc, char **argv){
	if(argc == 3){
		sscanf(argv[1],"%d",&wid);
		sscanf(argv[2],"%d",&hei);
		print_head(wid*init_x_scale, hei*init_y_scale);
		print_def();
		print_offset(init_x_scale,init_y_scale,-1,hei-1);
		print_next_from_stdin();
		print_tail();
		exit(0);
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

int print_next_from_stdin(){
	char c;
	int x_count = 0;
	int y_count = 0;
	while(scanf("%c",&c) != EOF){
		if((c != '\n')&&(c != ' ')){
			if(y_count < hei){
				if(x_count == wid){
					printf("\n%d %d translate\n",-wid,-1);
					x_count = 0;
					y_count = y_count+1;
				}
			}
			if(c == 'A'||c == 'a'){
				printf("0 0 1 setrgbcolor\n");
				//printf("1 1 scale\n");
				printf("1 0 translate ");
				printf("box fill\n");
				//printf("count : %d\n",count);
			}else if(c == 'G'||c == 'g'){
				printf("0 1 0 setrgbcolor\n");
				//printf("1 1 scale\n");
				printf("1 0 translate ");
				printf("box fill\n");
				//printf("count : %d\n",count);
			}else if(c == 'T'||c == 't'){
				printf("1 0 0 setrgbcolor\n");
				//printf("1 1 scale\n");
				printf("1 0 translate ");
				printf("box fill\n");
				//printf("count : %d\n",count);
			}else if(c == 'C'||c == 'c'){
				printf("0 1 1 setrgbcolor\n");
				//printf("1 1 scale\n");
				printf("1 0 translate ");
				printf("box fill\n");
				//printf("count : %d\n",count);
			}
			x_count = x_count + 1;
		}
	}
	return(0);
}
