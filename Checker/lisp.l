%{
#include <stdio.h>
#include "y.tab.h"
int  yywrap(void) { return 1; }
%}
%%
[a-z]+				return LETTER;
[0-9]+				return NUM;
[ ]				return EMP;
\n				return END;
.				return ERR;
%%
/*
#include "yybase.c"
void main() { yylex(); }
*/
