%{ // -*-c-*-
#undef yywrap
#define yywrap() 1

int divisor[100];
int genus;
int i;

extern void display_converted(int *div);
%}

%%
(" "*[0-9]+) { 
    if (i >= 0)
	sscanf(yytext, "%d", &(divisor[i]));
    i++;
    if (i > (genus / 2))
    {
	display_converted(divisor);
	printf("\n");
	i = -1;
    }
}
\n|" " ;
%%

main(int argc, char *argv[])
{
    i = -1;
    genus = atoi(argv[1]);
    yylex();
}


void display_converted(int *div)
{
    int i;
    for (i = 2 ; i <= (genus / 2) ; i++)
    {
	fflush(stdout);
	printf("%d   ", i * (genus - i) * div[1] - (genus - 1) * div[i]);
    }
}
