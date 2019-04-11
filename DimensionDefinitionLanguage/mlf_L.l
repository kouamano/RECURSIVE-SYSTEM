%{
#include <stdio.h>
#include "y.tab.h"
int  yywrap(void) { return 1; }
%}
%%
(\$[a-zA-Z]*)*(\$[0-9]+)	return ARGEX;
[a-zA-Z]+			return ALPH;
[0-9]+				return NUM;
\[[0-9,]*\]			return DIM;
,				return LIST;
\(				return FUNC_S;
\)				return FUNC_E;
->				return RULE;
;				return REF;
\[				return REF_S;
\]				return REF_E;
:				return SET;
['\t' ]				return SP;
#				return LABEL;
\n				return END;
.				return ERR;
%%
/*
#include "yybase.c"
void main() { yylex(); }
*/
