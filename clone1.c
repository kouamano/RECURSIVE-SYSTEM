#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>

int pf(float *f){
	int i = 0;
	printf("pf:%f\n",*f);
	return(i);
}

int pi(int *f){
	int i = 1;
	printf("pi:%d\n",*f);
	return(i);
}

float func(float i){
	return(i);
}

int main(int argc, char** argv){
	int c_stack = 100000;
	int j = 10;
	int va = 9;
	int vb = 2;
	int *alloc_a;
	alloc_a = malloc(sizeof(int)*10);
	alloc_a[0] = 12;
	int (*a)(int *f);
	int (*b)(void *f);
	float (*c)(float i) = &func;
	a = &pi;
	b = (int (*)(void *))(&pi);
	pi(&vb);
	a(&va);
	//clone((int (*)(void *))&a,&c_stack,0,&j);
	//clone((int (*)(void *))&b,&c_stack,0,&j);
	clone((int (*)(void *))&pi,&c_stack,0,&alloc_a[0]);
	//clone((int (*)(void *))&a,&c_stack,0,&alloc_a[12]);
	return(0);
}
