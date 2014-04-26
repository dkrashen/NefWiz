%{ // -*-c-*-
#undef yywrap
#define yywrap() 1
int count = 0;
%}

%s LEAVE

%%
([0-9]+)|("-"[0-9]+) {
    count++;
}
(" "|"\t")+ ;
\n {
    BEGIN LEAVE;
};
<LEAVE>.* ;
%%

main(int argc, char *argv[])
{
    yylex();
    printf("%d\n",count);
}
