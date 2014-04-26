%{ // -*-c-*-
#undef yywrap

extern FILE *outfile;
extern bool fileout;
%}

%s VAR_TYPE
%s COMMENT

%%

[ \t]+ ;


^1 {
    if (fileout) fprintf(outfile, "\n// %s", yytext);
    yylval = str_copy("one");
    return NUMBER;
}

^2 {
    if (fileout) fprintf(outfile, "\n// %s", yytext);
    yylval = str_copy("two");
    return NUMBER;
}

^3 {
    if (fileout) fprintf(outfile, "\n// %s", yytext);
    yylval = str_copy("three");
    return NUMBER;
}

^4 {
    if (fileout) fprintf(outfile, "\n// %s", yytext);
    yylval = str_copy("four");
    return NUMBER;
}

^([a-z]|[A-Z]|[0-9]|"_")+ {
    if (fileout) fprintf(outfile, "\n// %s", yytext);
    yylval = str_copy(yytext);
    return NUMBER;
}




1 {
    if (fileout) fprintf(outfile, "%s", yytext);
    yylval = str_copy("one");
    return NUMBER;
}

2 {
    if (fileout) fprintf(outfile, "%s", yytext);
    yylval = str_copy("two");
    return NUMBER;
}

3 {
    if (fileout) fprintf(outfile, "%s", yytext);
    yylval = str_copy("three");
    return NUMBER;
}

4 {
    if (fileout) fprintf(outfile, "%s", yytext);
    yylval = str_copy("four");
    return NUMBER;
}

([a-z]|[A-Z]|[0-9]|"_")+ {
    if (fileout) fprintf(outfile, "%s", yytext);
    yylval = str_copy(yytext);
    return NUMBER;
}

"+" {
    if (fileout) fprintf(outfile, " + ");
    return PLUS;
}


"*" {
    if (fileout) fprintf(outfile, " * ");
    return TIMES;
}


"-" {
    if (fileout) fprintf(outfile, " - ");
    return MINUS;
}


^"(" {
    if (fileout) fprintf(outfile, "\n// (");
    return LEFT_PARENS;
}

"(" {
    if (fileout) fprintf(outfile, "(");
    return LEFT_PARENS;
}

")" {
    if (fileout) fprintf(outfile, ")");
    return RIGHT_PARENS;
}

"\n" {
    if (fileout) fprintf(outfile, "\n\n");
    return END;
}

"=" {
    if (fileout) fprintf(outfile, " = ");
    return EQUALS;
}

%%

yywrap()
{
    return 1;
}


