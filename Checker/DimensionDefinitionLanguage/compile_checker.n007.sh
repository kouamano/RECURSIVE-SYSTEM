#!/bin/bash
# checker
##gt
echo gt
lex gt.l
yacc -dv gt.y
gcc44 y.tab.c lex.yy.c -lfl -ll
mv a.out gt
mv y.output gt.output

##t
echo t
lex t.l
yacc -dv t.y
gcc44 y.tab.c lex.yy.c -lfl -ll
mv a.out t
mv y.output t.output
##et
echo et
lex t.l
yacc -dv et.y
gcc44 y.tab.c lex.yy.c -lfl -ll
mv a.out et
mv y.output et.output
##eet
echo eet
lex t.l
yacc -dv eet.y
gcc44 y.tab.c lex.yy.c -lfl -ll
mv a.out eet
mv y.output eet.output


##s
echo s
lex s.l
yacc -dv s.y
gcc44 y.tab.c lex.yy.c -lfl -ll
mv a.out s
mv y.output s.output
##es
echo es
lex s.l
yacc -dv es.y
gcc44 y.tab.c lex.yy.c -lfl -ll
mv a.out es
mv y.output es.output
##ees
echo ees
lex s.l
yacc -dv ees.y
gcc44 y.tab.c lex.yy.c -lfl -ll
mv a.out ees
mv y.output ees.output



##c
echo c
lex c.l
yacc -dv c.y
gcc44 y.tab.c lex.yy.c -lfl -ll
mv a.out c
mv y.output c.output


##g
echo g
lex g.l
yacc -dv g.y
gcc44 y.tab.c lex.yy.c -lfl -ll
mv a.out g
mv y.output g.output



