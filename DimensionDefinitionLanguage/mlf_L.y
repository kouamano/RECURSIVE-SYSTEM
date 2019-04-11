%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
int yylex(void);
extern char *yytext;
%}

%token DIM ARGEX FUNC_S FUNC_E RULE LIST REF ALPH NUM REF_S REF_E SET SP LABEL END ERR

%%
line_list
	: line
	| line_list line

line
	: dimension_expression_ref END 	{printf(":END:\n");}
	| dimension_expression END 	{printf(":END:\n");}

dimension_expression_ref
	: dimension_expression REF refs	{printf(":Ref:");}

refs
	: ref
	| refs LIST ref

ref
	: arg SET REF_S ALPH SET NUM REF_E
	| arg SET REF_S ALPH SET arg REF_E

dimension_expression
	: arg					{printf(":Dataset:");}
	| list					{printf(":Dataset:");}
	| arg RULE arg				{printf(":In->Out:");}
	| arg RULE list				{printf(":In->Out:");}
	| list RULE arg				{printf(":In->Out:");}
	| list RULE list			{printf(":In->Out:");}
	| label arg				{printf("L:Dataset:");}
	| label list				{printf("L:Dataset:");}
	| label arg RULE arg			{printf("L:In->Out:");}
	| label arg RULE list			{printf("L:In->Out:");}
	| label list RULE arg			{printf("L:In->Out:");}
	| label list RULE list			{printf("L:In->Out:");}


label
	: LABEL NUM sps

sps
	: SP
	| sps SP

list
	: arg func_seq

func_seq
	: func_b
	| func_seq func_b

func_b
	: FUNC_S argm FUNC_E

argm
	: args
	| args FUNC_S argm FUNC_E
	| args FUNC_S argm FUNC_E LIST argm

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
    printf(":::CLEAR:::\n");
}
