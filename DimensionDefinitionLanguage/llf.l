%{
#include <stdio.h>
#include "y.tab.h"
int  yywrap(void) { return 1; }
%}
%%
\$[0-9]+		return ARG;
\[[0-9,]*\]		return DIM;
,			return LIST;
\(			return FUNC_S;
\)			return FUNC_E;
->			return RULE;
\n			return END;
.			return ERR;
%%
/*
#include "yybase.c"
void main() { yylex(); }
*/
