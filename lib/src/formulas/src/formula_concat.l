%{ // -*-c-*-
#undef yywrap
%}

%s VAR_TYPE
%s COMMENT

%%

[ \t]+ ;
\n ;
" " ;

([a-z]|[A-Z]|[0-9]|("_"))+"."c  printf("%s ", yytext);

%%

yywrap()
{
    return 1;
}

main()
{
    yylex();
}
