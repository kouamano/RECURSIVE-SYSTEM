%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
int yylex(void);
extern char *yytext;
%}

%token LETTER NUM EMP END ERR

%%
s_expression
	: atom_sym
	| "(" s_expression s_expression ")"
	| "(" s_expression s_expression_L ")"

s_expression_L
	: s_expression
	| s_expression_L EMP s_expression

atom_sym
	: LETTER atom_part

atom_part
	: EMP
	| LETTER atom_part
	| NUM atom_part

%%
int yyerror(char const *str)
{
    extern char *yytext;
    fprintf(stderr, "ERR:%s:\n", yytext);
    return 0;
}

int main(void)
{
    extern int yyparse(void);
    extern FILE *yyin;

    yyin = stdin;
    if (yyparse()) {
        exit(1);
    }
    printf(":::CLEAR:::\n");
}
