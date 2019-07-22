%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
int yylex(void);
extern char *yytext;
%}

%token FUNC_S FUNC_E DIV HEAD NULLCHAR
%right FUNC_S
%left FUNC_E

%%
list
	: head
	| body
	| head body

body
	: FUNC_S FUNC_E
	| FUNC_S arg FUNC_E
	| FUNC_S body FUNC_E
	| FUNC_S body DIV body FUNC_E
	| body body

arg
	: head
	| arg DIV head

head
	: HEAD
	| NULLCHAR

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
    printf("::GT:CLEAR::\n");
}
