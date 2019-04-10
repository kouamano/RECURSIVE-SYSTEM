%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
int yylex(void);
extern char *yytext;
%}

%token ARGEX ALPH NUM DIM LIST FUNC_S FUNC_E RULE REW REF REF_S REF_E LABEL END ERR
%left ARGEX
%right FUNC_S
%left FUNC_E
%right LIST

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
	| arg RULE arg REW arg			{printf(":In->Out=>REW:");}
	| arg RULE arg REW list			{printf(":In->Out=>REW:");}
	| arg RULE list REW arg			{printf(":In->Out=>REW:");}
	| arg RULE list REW list		{printf(":In->Out=>REW:");}
	| list RULE arg REW arg			{printf(":In->Out=>REW:");}
	| list RULE arg REW list		{printf(":In->Out=>REW:");}
	| list RULE list REW arg		{printf(":In->Out=>REW:");}
	| list RULE list REW list		{printf(":In->Out=>REW:");}

list
	: FUNC_S func FUNC_E

func
	: arg
	| FUNC_S func FUNC_E
	| func LIST func

arg
	: ARGEX
	| ARGEX DIM
	| LABEL ARGEX
	| LABEL ARGEX DIM
	| '$' LABEL ARGEX
	| '$' LABEL ARGEX DIM

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
    printf("::S:CLEAR::\n");
}
