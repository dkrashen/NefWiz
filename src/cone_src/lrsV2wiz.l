%{ // -*-c-*-
#undef yywrap
int num_div = 0;
int printing;
int genus; 
%}

%s LAMBDA
%s DELTA

%%
V-.*\n                     ;
begin.*\n                  ;
end.*\n                    ;
^\*.*\n                    ;
" "+\n                     ;
^" "+1.*\n                 ;
\n                         ;
^" "+[0-9]+                { BEGIN LAMBDA; }
<LAMBDA>[0-9]+             { BEGIN DELTA ; 
                             if (printing == 1) 
                               printf("\n%s ", yytext) ; 
                             num_div++ ; }
<DELTA>(" "*[0-9]+" "*)+   { BEGIN 0 ; 
                             if (printing == 1) 
                               printf("%s ", yytext) ; }

%%

yywrap()
{
    return 1;
}


main(int argc, char *argv[])
{
    FILE *file;
    if (argc < 2)
    {
	printing = 1;
	yylex();
	printf("\ng\n%d\nn\n%d\n\ns", genus, num_div);
    }
    else
    {
	file = fopen(argv[1], "r");
	printing = 0;
	yyin = file;
	yylex();
	printf("\ng\n%d\n\n", genus);
	printf("/");
	printf("*\n");
	printf("extremal rays : %d\n", num_div);
	printf("*");
	printf("/\n");
	printf("\ns");
	fclose(file);
	file = fopen(argv[1], "r");
	printing = 1;
	yylex();
	printf("\ne");
	fclose(file);
	printf("\n");
    }
    printf("\n");
}
