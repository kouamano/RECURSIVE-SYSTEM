#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <curses.h>
#define DEFAULT 0
#define PREC 1
// HELP
#define ARGERR "USAGE:\n\
equ op n1 [n2 ... nX]\n\
n1: First parameter\n\
n2: Second parameter\n\
nX: Xth parameter\n\
op:\n"
#define ALLOPTS "OPTIONS:\n\
	linear: f(x)= ax+b\n\
	power: f(x)= a(b)^x\n\
	exponent: quadratic+, highest degree a, first coefficient b\n"
#define LINUS "f(x)= ax+b\n\
USAGE:\n\
equ linear a b\n"
#define POWUS "f(x)= a(b)^x\n\
USAGE:\n\
equ power a b\n"
#define EXPUS "Quadratic and up; highest degree a, first coefficient b\n\
USAGE:\n\
equ exponent a b [c ... ]\n"

enum opType {
	linear,
	power,
	exponent
};
enum set {
	yes,
	no
};
struct ops {
	enum opType type;
	unsigned short int highDeg;
	double * op;
};

char * linearf(double x, double a, double b);
char * powerf(double x, double a, double b);
char * exponentf(double x, unsigned short int highDeg, double * vars);
char * autoRound(double number);
unsigned short int decimal(double number);

int main(int argc, char * argv[]) {
	struct ops vars;
	enum set funct;
	double base = DEFAULT, xv;
	short int count;
	int ch;
	char * ras;

	if(argc < 3) {
		fprintf(stderr, ARGERR);
		fprintf(stderr, ALLOPTS);
	}
	else {
		if(!strcmp("exponent", argv[1])) {
			vars.highDeg = atof(argv[2]);
			if(argc < (int) vars.highDeg + 4) {
				fprintf(stderr, EXPUS);
			}
			else {
				vars.type = exponent;
				vars.op = (double *) malloc(sizeof(double) * ((int) vars.highDeg + 1));
				for(count = 3; count <= argc - 1; count++) {
					printf("%d..", (int) count);
					vars.op[(int) count - 2] = atof(argv[(int) count]);
					printf("OK\n");
				}
				printf("111\n");
				funct = yes;
			}
		}
		else {
			fprintf(stderr, ALLOPTS);
			funct = no;
		}
		if(funct == yes) {
			printf("222\n");
			xv = 0;
			printf("333\n");
			for(count = 0; count <= 5; count++) {
				printf("444\n");
				ras = exponentf(xv, vars.highDeg, vars.op);
				printf("%s\n", ras);
				printf("555\n");
				free(ras);
				printf("666\n");
				xv += 1;
			}
			free(vars.op);
		}
	}
	return 0;
}
char * exponentf(double x, unsigned short int highDeg, double * vars) {
	printf("1\n");
	char print[64], * ret, *xc, *y;
	printf("2\n");
	double b = 0;
	printf("3\n");
	short int count;
	printf("4\n");
	xc = autoRound(x);
	printf("5\n");
	for(count = (short int) highDeg; count >= 0; count--) {
		printf("	%d\n", (int) highDeg - (int) count);
		b += vars[(int) highDeg - (int) count] * pow(x, (int) count);
	}
	printf("6\n");
	y = autoRound(b);
	printf("7\n");
	sprintf(print, "f(%s)=  %s", xc, y);
	printf("8\n");
	ret = (char *) malloc(strlen(print) + 1);
	printf("9\n");
	strcpy(ret, print);
	printf("10\n");
	free(xc);
	printf("11\n");
	free(y);
	printf("12\n");
	return ret;
}
char * autoRound(double number) {
	char * ret, print[32];
	unsigned short int count, loc = decimal(number);
	enum set found = false;
	sprintf(print, "%lf", number);
	for(count = loc + 6; count >= loc; count--) {
		if(print[(int) count] != '0') {
			if(print[(int) count] == '.') {
				count -= 1;
			}
			ret = (char *) malloc((int) count + 2);
			strncpy(ret, print, (int) count + 1);
			ret[(int) count + 1] = '\0';
			found = true;
			break;
		}
	}
	if(found == false) {
		ret = (char *) malloc(strlen(print) + 1);
		strcpy(ret, print);
	}
	return ret;
}
unsigned short int decimal(double number) {
	char string[32];
	unsigned short int count;
	sprintf(string, "%lf", number);
	for(count = 0; count <= strlen(string) - 1; count++) {
		if(string[(int) count] == '.') {
			break;
		}
	}
	return count;
}
