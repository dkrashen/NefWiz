%{ // -*-c-*-
#undef yywrap
#define yywrap() 1
%}

%%
([0-9]+)|("-"[0-9]+) {
    printf("%6d ", atoi(yytext));
}
" " ;
%%

main(int argc, char *argv[])
{
    yylex();
}
