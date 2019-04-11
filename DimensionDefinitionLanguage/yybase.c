int yyerror(char const *str)
{
    extern char *yytext;
    fprintf(stderr, "parser error near %s\n", yytext);
    return 0;
}
