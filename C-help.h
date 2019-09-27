/* help */
void status(void){
	printf("\n");
	printf("STATUS\n");
	printf("======\n");
	printf(" - Under construction\n");
	printf("\n");
	printf("  * Inner product.\n");
	printf("\n");
	printf(" - COMPILED@\n");
	printf("   %s\n",ctime);
	printf("   %s\n",cdate);
}
void help(void){
	printf("\n");
	printf("USAGE\n");
	printf("=====\n");
	printf("\n");
	printf(" tq.o [-h|-hF|-hC|-hS|-hD|-hE] [-s] [-c] [-test] buff=<(int)size> in=<file name of input form> out=<file name of outout form> data=<data file> data_buff=<(int)size> w=<warnning level> -F<x> -C<x> -P<x>.\n");
	printf("\n");
	printf(" - Full information\n");
	printf("\n");
	printf("   tq.o -h -hF -hC -hS -hD -hE -s -c -CL\n");
	printf("\n");
	printf(" - Main options\n");
	printf("\n");
	printf("  * -h : help.\n");
	printf("  * -hF : function help.\n");
	printf("  * -hC : compile help.\n");
	printf("  * -hS : search help.\n");
	printf("  * -hD : data help.\n");
	printf("  * -hE : print examples.\n");
	printf("  * -s : prints status.\n");
	printf("  * -c : check args.\n");
	printf("  * -test : execute test code.\n");
	printf("  * -Pin : print input form.\n");
	printf("  * -Pout : print output form.\n");
	printf("  * -Pprod : print inner production of binded data.\n");
	printf("  * buff : set integer for buffer size to read heads.\n");
	printf("  * in : set input-form file name (length < 1024).\n");
	printf("  * out : set output-form file name (length < 1024).\n");
	printf("  * data : CSV data file name.\n");
	printf("  * data_buff : set integer for buffer size to read data.\n");
	printf("  * war : set integer for warnnig level.\n");
}
void function_help(void){
	printf("\n");
	printf(" - Format options\n");
	printf("\n");
	printf("  * -FT : prints T-form.\n");
	printf("  * -FS : prints S-form.\n");
	printf("  * -FJ : prints JSON form.\n");
	printf("  * -FW : prints Wolfram language form.\n");
	printf("  * -FX : prints XML form.\n");
	printf("  * -FC : prints shell script form.\n");
	printf("  * -FN : prints seq node-no.\n");
	printf("  * -FMa : prints Adjacency matrix form.\n");
	printf("  * -Fh : prints hierarchical-form.\n");
	printf("  * -Fst : prints import status.\n");
	printf("  * -Fhst : prints import status with hierarchical-form.\n");
	printf("  * -Ftest : prints from test function.\n");
}
void compile_help(void){
	printf("\n");
	printf(" - Compile options\n");
	printf("\n");
	printf("  * -C : print compiled form.\n");
	printf("  * -CL : list buitin operators.\n");
	printf("  * -Cr : prints the \"print-restrict\" char at the end of line.\n");
	printf("  * -Cc : clear head.\n");
	printf("  * -Cd : rewite head to dot.\n");
}
void search_help(void){
	printf("\n");
	printf(" - Search options\n");
	printf("\n");
	printf("  * Sh=<head> (Under construction).\n");
	printf("  * Sp=<position>.\n");
}
void data_help(void){
	printf("\n");
	printf(" - Data option\n");
	printf("\n");
	printf("  * DD=<delimiter> currently unused, definded by definition file.\n");
}
void language_help(void){
	printf("\n");
	printf("LANGUAGE\n");
	printf("========\n");
	printf("\n");
	printf("  | LANGUAGE :: <head>|<tree>\n");
	printf("  | <head> ::= <label><reference><operator><name><bind>\n");
	printf("  | <tree> ::= <head>('('(<head>|<tree>)(','(<head>|<tree>)*')')+\n");
}
void option_header(void){
	printf("\n");
	printf("OPTIONS\n");
	printf("=======\n");
}
void list_builtins(void){
	printf("\n");
	printf(" - Builtin operators\n");
	printf("\n");
	printf("  * #<n> : <label>: head.\n");
	printf("  * ##<n> : <label>: tree.\n");
	printf("  * $#<n> : <reference>: head.\n");
	printf("  * $##<n> : <reference>: tree.\n");
	printf("  * $`$ : <operator>: quating head.\n");
	printf("  * $``$ : <operator>: quating tree.\n");
	printf("  * $~$ : <operator>: riteral head.\n");
	printf("  * $~~$ : <operator>: riteral tree.\n");
	printf("  * $U$ : <operator>: unpack single level.\n");
	printf("  * $UU$ : <operator>: unpack tree (test ver.).\n");
	printf("  * $PI$ : <operator>: inner production for binded data.\n");
	printf("  * $$ : <name> prefix: dictionary reference (term ID).\n");
	printf("  * $X$ : <name> prefix: dictionary reference (term string).\n");
	printf("  * $$$ : <name> prefix: dictionary reference (class ID).\n");
	printf("  * $$X$ : <name> prefix: dictionary reference (class string).\n");
	printf("  * $NULL$ : <name>: null object.\n");
	printf("  * @(<string>) : <name>: binded data.\n");
	printf("  * [<n>] : <bind>: data bind.\n");
	printf("  * @(<tree>*) : <bind>: pseudo-bind.\n");
}
void put_examples(void){
	printf("\n");
	printf("EXAMPLES\n");
	printf("========\n");
	printf("\n");
	printf("ex.1::\n");
	printf("\n");
	printf(" test.csv::\n");
	printf("\n");
	printf("  Length,Weight\n");
	printf("\n");
	printf(" $ echo '#1$Op$Name($#1[1])' | tq.o in=/dev/stdin -FT -Pin data=test.csv\n");
	printf("  => #1$Op$Name($#1[1]@@#1$Op$Name(Length))\n");
	printf("\n");
	printf(" - #1 : <label>\n");
	printf(" - $#1 : <reference>\n");
	printf(" - $Op$ : <operator>\n");
	printf(" - Name : <name>\n");
	printf(" - [1] : <bind>\n");
	printf(" - @ : <name>: binded mark\n");
	printf("\n");
	printf("ex.2 (referencing tree)::\n");
	printf("\n");
	printf(" $ echo 'A(B(#1C),$#1(D))'\n");
	printf("  => A(B(#1C),$#1@#1C(D))\n");
	printf("                  ^^^^^^^\n");
	printf("                  Binding referenced tree.\n");
	printf("\n");
	printf("ex.3 (creating graph)::\n");
	printf("\n");
	printf(" $ echo '$G$($V$(#0,#1,#2),$E$($#0($#1,$#2),$#1($#0,$#2), $#2($#0,$#1)))' | tq.o in=/dev/stdin -FMa -Pin\n");
	printf("  =>\n");
	printf(" ====multiline====>\n");
	printf(" [:$G$:0],1,,,,5,,,,,,,,,,\n");
	printf(" ,[:$V$:1],2,3,4,,,,,,,,,,,\n");
	printf(" ,,[:#0:2],,,,,,,,,,,,,\n");
	printf(" ,,,[:#1:3],,,,,,,,,,,,\n");
	printf(" ,,,,[:#2:4],,,,,,,,,,,\n");
	printf(" ,,2,3,,[:$E$:5],6,,,9,,,12,,,\n");
	printf(" ,,,3,4,,[:$#0:6->2],7,8,,,,,,,\n");
	printf(" ,,,,,,,[:$#1:7->3],,,,,,,,\n");
	printf(" ,,,,,,,,[:$#2:8->4],,,,,,,\n");
	printf(" ,,2,,4,,,,,[:$#1:9->3],10,11,,,,\n");
	printf(" ,,,,,,,,,,[:$#0:10->2],,,,,\n");
	printf(" ,,,,,,,,,,,[:$#2:11->4],,,,\n");
	printf(" ,,2,3,,,,,,,,,[: $#2:12],13,14,\n");
	printf(" ,,,,,,,,,,,,,[:$#0:13->2],,\n");
	printf(" ,,,,,,,,,,,,,,[:$#1:14->3],\n");
	printf(" <====multiline====\n");
	printf("\n");
	printf("ex.4 (binding and reforming CSV)::\n");
	printf("\n");
	printf(" [bind]\n");
	printf("\n");
	printf(" test.csv::\n");
	printf("\n");
	printf("  Length,Weight\n");
	printf("  mm,kg\n");
	printf("  1,2\n");
	printf("  322,4\n");
	printf("  5,68\n");
	printf("\n");
	printf(" in.ddf::\n");
	printf("\n");
	printf("  (#1[2],#2[2],[3](#4[2]))\n");
	printf("\n");
	printf(" out.ddl::\n");
	printf("\n");
	printf("  $PI$($#1,Quantity($#4,$#2))\n");
	printf("\n");
	printf(" $ tq.o in=in.ddf out=out.ddl data=test.csv -FT -Pprod -C\n");
	printf("  => (((Length,Quantity(1,mm)),(Weight,Quantity(2,kg))),((Length,Quantity(322,mm)),(Weight,Quantity(4,kg))),((Length,Quantity(5,mm)),(Weight,Quantity(68,kg))))\n");
	//printf("ex.4 (binding and reforming CSV)::\n");
	printf("\n");
	printf(" [over write]\n");
	printf("\n");
	printf(" test.csv::\n");
	printf("\n");
	printf("  Length,Weight\n");
	printf("  mm,kg\n");
	printf("  1,2\n");
	printf("  322,4\n");
	printf("  5,68\n");
	printf("\n");
	printf(" in.ddf::\n");
	printf("\n");
	printf("  (#1[2],#2[2],[3](#4[2]))\n");
	printf("\n");
	printf(" out2.ddl::\n");
	printf("\n");
	printf("  $PI$(@(L,W),Quantity($#4,$#2))\n");
	printf("\n");
	printf(" $ tq.o in=in.ddf out=out2.ddl data=test.csv -FT -Pprod -C\n");
	printf("  => (((L,Quantity(1,mm)),(W,Quantity(2,kg))),((L,Quantity(322,mm)),(W,Quantity(4,kg))),((L,Quantity(5,mm)),(W,Quantity(68,kg))))\n");

}

/* checking */
void check_options(struct options *opt){
	printf("\n");
	printf("OPTION SETTING\n");
	printf("==============\n\n");
	printf(" * opt.help:%d:\n",(*opt).help);
	printf(" * opt.stat:%d:\n",(*opt).stat);
	printf(" * opt.check:%d:\n",(*opt).check);
	printf(" * opt.war:%d:\n",(*opt).war);
	printf(" * opt.test:%d:\n",(*opt).test);
	printf(" * opt.buff:%d:\n",(*opt).buff);
	printf(" * opt.data_buff:%d:\n",(*opt).data_buff);
	printf(" * opt.in:\"%s\":\n",(*opt).in);
	printf(" * opt.out:\"%s\":\n",(*opt).out);
	printf(" * opt.data:\"%s\":\n",(*opt).data);
	printf(" * opt.Pin:%d:\n",(*opt).Pin);
	printf(" * opt.Pout:%d:\n",(*opt).Pout);
	printf(" * opt.Pprod:%d:\n",(*opt).Pprod);
	printf(" * opt.hF:%d:\n",(*opt).hF);
	printf(" * opt.hC:%d:\n",(*opt).hC);
	printf(" * opt.hS:%d:\n",(*opt).hS);
	printf(" * opt.hD:%d:\n",(*opt).hD);
	printf(" * opt.hE:%d:\n",(*opt).hE);
}
void check_function_options(struct function_options *fopt){
	printf("\n|\n\n");
	printf(" * converters:\n\n");
	printf("  * opt.fcount:%d:\n",(*fopt).f_counter);
	printf("  * opt.FT:%d:\n",(*fopt).f_print_T);
	printf("  * opt.FS:%d:\n",(*fopt).f_print_S);
	printf("  * opt.FJ:%d:\n",(*fopt).f_print_J);
	printf("  * opt.FW:%d:\n",(*fopt).f_print_W);
	printf("  * opt.FX:%d:\n",(*fopt).f_print_X);
	printf("  * opt.FC:%d:\n",(*fopt).f_print_C);
	printf("  * opt.FN:%d:\n",(*fopt).f_print_N);
	printf("  * opt.FMa:%d:\n",(*fopt).f_print_Ma);
	printf("  * opt.Fst:%d:\n",(*fopt).f_print_status);
	printf("  * opt.Fh:%d:\n",(*fopt).f_print_hierarchy);
	printf("  * opt.Fhst:%d:\n",(*fopt).f_print_hierarchy_status);
	printf("  * opt.Ftest:%d:\n",(*fopt).f_print_test);
}
void check_compile_options(struct compile_options *copt){
	printf("\n|\n\n");
	printf(" * compilers:\n\n");
	printf("  * opt.ccount:%d:\n",(*copt).c_counter);
	printf("  * opt.c_list:%d:\n",(*copt).c_list);
	printf("  * opt.c_restrict:%d:\n",(*copt).c_restrict);
	printf("  * opt.c_clear:%d:\n",(*copt).c_clear);
	printf("  * opt.c_dot:%d:\n",(*copt).c_dot);
}
void check_search_options(struct search_options *sopt){
	printf("\n|\n\n");
	printf(" * search:\n\n");
	printf("  * opt.scount:%d:\n",(*sopt).s_counter);
	printf("  * opt.pos:%s:\n",(*sopt).pos);
	printf("  * opt.head:%s:\n",(*sopt).head);
}
void check_data_options(struct data_options *dopt){
	printf("\n|\n\n");
	printf(" * data:\n\n");
	printf("  * opt.DD:%c:\n",(*dopt).dd);
}
