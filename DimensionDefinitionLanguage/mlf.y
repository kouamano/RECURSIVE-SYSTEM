%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
int yylex(void);
extern char *yytext;
%}

%token DIM ARGEX FUNC_S FUNC_E RULE LIST REF ALPH NUM REF_S REF_E SET SP LABEL END ERR
%left ARGEX
%left LIST
%right FUNC_S
%left FUNC_E

%%
line_list
	: line
	| line_list line

line
	: dimension_expression END 	{printf(":END:\n");}

dimension_expression
	: arg					{printf(":Dataset:");}
	| list					{printf(":Dataset:");}
	| arg RULE arg				{printf(":In->Out:");}
	| arg RULE list				{printf(":In->Out:");}
	| list RULE arg				{printf(":In->Out:");}
	| list RULE list			{printf(":In->Out:");}

list
	: arg func_b

func_b
	: FUNC_S argm FUNC_E

argm
	: args
	| arg func_b
	| argm argm
	| argm LIST argm

args
	: arg
	| args LIST arg
arg
	: ARGEX
	| ARGEX DIM

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
    printf("::CLEAR::\n");
}
