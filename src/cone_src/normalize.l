%{ // -*-c-*-
#undef yywrap
extern void normalize();
int genus; 
int d[1000];
int current = 0; 
int lambda;
int i;
%}
%s LAMBDA
%s DELTA
%s GENUS
%s NUM_DIV
%%

^"genus = "                BEGIN GENUS;
<GENUS>[0-9]+              { genus = atoi(yytext) ; BEGIN NUM_DIV ; }
<NUM_DIV>^num.*\n          BEGIN 0 ;
^" "+1" "+(" "*0" "*)*\n   { BEGIN LAMBDA ; }
<LAMBDA>[0-9]+             { BEGIN DELTA ; current = 0 ; 
                             lambda = atoi(yytext) ; }
<DELTA>" "+                ;
<DELTA>[0-9]+              { d[current] = atoi(yytext); current++ ; }
<DELTA>\n                  { BEGIN LAMBDA ; normalize() ; current = 0 ; }
%%

yywrap()
{
    return 1;
}

void normalize()
{
    int count, count2;
    float av;
    int half;

    if (i == -2)
    {    
	av = 0.0;
	for (count2 = 0 ; count2 <= (genus / 2) ; count2++)
	    av += d[count2];
	av += lambda;
	printf("%9.6f ", ((float) lambda) / (av));
    }

    else if (i == -1)
	printf("%9.6f ", ((float) lambda) / (lambda));

    else 
	printf("%9.6f ", ((float) lambda) / (d[i]));

    for (count = 0 ; count <= (genus / 2) ; count++)
    {
	if (i == -2)
	    printf("%9.6f ", ((float) d[count]) / (av));
	else if (i == -1)
	    printf("%9.6f ", ((float) d[count]) / (lambda));
	else
	    printf("%9.6f ", ((float) d[count]) / ((float) d[i]));
    }
    printf("\n\n");
}

main(int argc, char *argv[])
{
    if (argc > 1)
	i = atoi(argv[1]);
    else
	i = -2;
	    
    yylex();
}
