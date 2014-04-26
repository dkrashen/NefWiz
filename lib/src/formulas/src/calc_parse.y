%{
#include "basic_types.h"
#include "stdio.h"
#include "string.h"
#include "stringy.c"
#define YYSTYPE char *

int quit = 0;

FILE *outfile;
static bool fileout;
%}

%token NUMBER
%token PLUS MINUS TIMES
%token LEFT_PARENS RIGHT_PARENS
%token END
%token EQUALS

%left PLUS MINUS
%left TIMES


%start Input

%%

Input:
 Line
| Line Input
;


Line:
 END { printf("\n"); exit(1); }
| Exp END { 
     printf("\n\n |> "); 
}
;

Exp:
NUMBER EQUALS Num_Exp {
     printf("\n\t");
     printf("%s = %s;\n\n", $1, $3);
     if (fileout)
	 fprintf(outfile, "%s = %s;\n\n\n", $1, $3);
}
| Num_Exp {
    printf("\n\t"); 
    printf("%s;", $1);
    if (fileout)
	fprintf(outfile, "%s;\n\n\n", $1);
}
;

Num_Exp: 
 NUMBER              { $$ = $1; }
| Num_Exp PLUS Num_Exp { 
    $$ =
	str_concat(
	    str_concat(
		str_concat(
		    str_concat("sbplus(", $1), ", "), $3), ")");
}

| Num_Exp TIMES Num_Exp { 
    $$ = 
	str_concat(
	    str_concat(
		str_concat(
		    str_concat("sbtimes(", $1), ", "), $3), ")");
}

| Num_Exp MINUS Num_Exp {
    $$ = 
	str_concat(
	    str_concat(
		str_concat(
		    str_concat("sbminus(", $1), ", "), $3), ")");
}

| LEFT_PARENS Num_Exp RIGHT_PARENS   { 
    $$ = $2; }
;

%%

#include<stdio.h>
#include<stdlib.h>




////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////// MAIN ROUTINE ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


main(int argc, char *argv[])
{
    if (argc > 1)
    {
	fileout = TRUE;
	outfile = fopen(argv[1], "a");
    }
    else
	fileout = FALSE;

	printf(" |> ");
	yyparse();

    if (fileout)
	fclose(outfile);
}

#include "calc_parse_lexer.c"


yyerror(s)
{
    printf("ouch!\n");

}
