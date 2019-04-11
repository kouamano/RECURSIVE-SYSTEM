%{
#include <stdio.h>
#include "y.tab.h"
int  yywrap(void) { return 1; }
%}
%%
\$[\$#0-9a-zA-Z]*	return ARGEX;
[a-zA-Z]*		return ALPH;
[0-9]*			return NUM;
\[[0-9,]*\]		return DIM;
,			return LIST;
\(			return FUNC_S;
\)			return FUNC_E;
->			return RULE;
\;			return REF;
\[			return REF_S;
\]			return REF_E;
:			return SET;
#			return LABEL;
['\t' ]			return SP;
\n			return END;
.			return ERR;
%%
/*
#include "yybase.c"
void main() { yylex(); }
*/
