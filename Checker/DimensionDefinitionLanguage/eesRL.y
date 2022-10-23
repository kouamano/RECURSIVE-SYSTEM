%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
int yylex(void);
extern char *yytext;
// lexfile: llf.l
%}

%token DIM ARGEX ALPH NUM FUNC_S FUNC_E RULE LIST REF REF_S REF_E SET LABEL SP END ERR
%right FUNC_S
%right FUNC_E
%left LIST

%%
line_list
	: line
	| line_list line

line
	: dimension_expression END 	{printf(":END:\n");}
	| dimension_expression_ref END 	{printf(":END:\n");}

dimension_expression_ref
	: dimension_expression REF refs	{printf(":Ref:");}

refs
	: ref
	| refs LIST ref

ref
	: arg SET REF_S ALPH SET numalph REF_E
	| arg SET REF_S arg SET numalph REF_E
	| arg SET REF_S ALPH SET arg REF_E
	| arg SET REF_S arg SET arg REF_E
	| arg SET REF_S LABEL SET NUM REF_E	{printf(":RefL:");}

dimension_expression
	: arg				{printf(":Dataset:");}
	| list				{printf(":Dataset:");}
	| arg RULE arg			{printf(":In->Out:");}
	| arg RULE list			{printf(":In->Out:");}
	| list RULE arg			{printf(":In->Out:");}
	| list RULE list		{printf(":In->Out:");}
	| label arg			{printf(":Dataset:");}
	| label list			{printf(":Dataset:");}
	| label arg RULE arg		{printf(":In->Out:");}
	| label arg RULE list		{printf(":In->Out:");}
	| label list RULE arg		{printf(":In->Out:");}
	| label list RULE list		{printf(":In->Out:");}

label
	: LABEL NUM sps			{printf(":#:");}

sps
	: SP
	| sps SP

list
	: FUNC_S func FUNC_E
	| list list

func
	: arg
	| FUNC_S func FUNC_E
	| func LIST func
	| func func

arg
	: ARGEX
	| ARGEX DIM

numalph
	: NUM
	| ALPH
	| numalph numalph

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
