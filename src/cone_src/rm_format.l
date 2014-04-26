%{ // -*-c-*-
#undef yywrap
#define yywrap() 1
%}

%s GENUS

%%
^g\n {
    BEGIN GENUS;
}
<GENUS>^[0-9]+\n {
    BEGIN 0;
}
<GENUS>\n ;
^((" "|\t)*)([0-9]+)((" "|\t)*)([0-9]+)((" "|\t)*)rational((" "|\t)*)\n ;
^((" "|\t)*)(([a-z]|[A-Z]|\*|"/"|-)+).*\n ;
^(" "|\t)*\n ;
%%

main(int argc, char *argv[])
{
    yylex();
}
