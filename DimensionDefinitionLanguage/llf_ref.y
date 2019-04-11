%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
int yylex(void);
extern char *yytext;
%}

%token DIM ARG FUNC_S FUNC_E RULE LIST REF ALPH NUM REF_S REF_E SET END ERR

%%
line_list
	: line
	| line_list line

line
	: dimension_expression_ref END 	{printf("END:\n");}
	| dimension_expression END 	{printf("END:\n");}

dimension_expression_ref
	: dimension_expression REF refs	{printf(":Ref:");}

refs
	: ref
	| refs LIST ref

ref
	: arg SET REF_S ALPH SET REF_E
	| arg SET REF_S ALPH SET NUM REF_E
	| arg SET REF_S ALPH SET arg REF_E

dimension_expression
	: arg				{printf(":Dataset:");}
	| list				{printf(":Dataset:");}
	| arg RULE arg			{printf(":In->Out:");}
	| arg RULE list			{printf(":In->Out:");}
	| list RULE arg			{printf(":In->Out:");}
	| list RULE list		{printf(":In->Out:");}

list
	: FUNC_S argfunc FUNC_E


argfunc
	: arg
	| argfunc LIST arg
	| argfunc LIST FUNC_S argfunc FUNC_E


arg
	: ARG
	| ARG DIM

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
