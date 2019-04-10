%{
#include <stdio.h>
#include "y.tab.h"
int  yywrap(void) { return 1; }
%}
%%
$[$@~#&0-9a-zA-Z`._\-;/ ]*	return ARGEX;
[a-zA-Z]*			return ALPH;
[0-9]*				return NUM;
\[[0-9,]*\]			return DIM;
,				return LIST;
\(				return FUNC_S;
\)				return FUNC_E;
\t->\t				return RULE;
\t=>\t				return REW;
\#[#0-9]+			return LABEL;
\n				return END;
.				return ERR;
%%
/*
#include "yybase.c"
void main() { yylex(); }
*/
