%{
#include <stdio.h>
#include "y.tab.h"
int  yywrap(void) { return 1; }
%}
%%
\(				return FUNC_S;
\)				return FUNC_E;
,				return DIV;
[.]*				return HEAD;
''				return NULLCHAR;
%%
/*
#include "yybase.c"
void main() { yylex(); }
*/
