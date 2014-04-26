%{ // -*-c-*-
#undef yywrap
#define yywrap() 1

int beta[100];
int genus;
int i, j;

extern void display_converted(int *div);
%}

%%
(" "*[0-9]+) { 
    sscanf(yytext, "%d", &(beta[i]));
    i++;
    if (i > (genus / 2))
    {
	display_converted(beta);
	printf("\n");
	i = 2;
    }
}
\n|" " ;
%%

main(int argc, char *argv[])
{
    i = 2;
    beta[1] = 0;
    genus = atoi(argv[1]);
    yylex();
}

int reduce(int i)
{
  int dummy;

  if (i > (genus / 2))
    dummy = genus - i;
      else dummy = i;

  return dummy;
}


void display_converted(int *e)
{
    int i, j;
    int b[1000];
    int a; // lambda coeff

    // b1[0] is the numerator of the current b1 and b1[1]is the
    // denominator. testb1 is the possible b1 to replace with if
    // it is a larger b1tion.
    int b1[2], testb1[2];

    // sets b1 to the max of b1 and testb1.
    void domax()
	{
	    if (b1[0] * testb1[1] < b1[1] * testb1[0])
	    {
		b1[0] = testb1[0];
		b1[1] = testb1[1];
	    }
	}

    b1[0] = 0;
    b1[1] = 1;

    for (i = 2 ; i<= (genus / 2) ; i++)
    {
	testb1[0] = (genus - 1) * e[i];
	testb1[1] = i * (genus - i);

	domax();
    }
    for (i = 1 ; i <= (genus - 1) ; i++)
	for (j = 1 ; (i + j) <= (genus - 1) ; j++)
	{
	    testb1[0] = (e[reduce(i)] + e[reduce(j)] - 
			 e[reduce(i + j)]) * (genus - 1);
	    testb1[1] = 2 * i * j;
	
	    domax();
	}
    
    for (i = 1 ; i <= (genus / 2) ; i++)
	b[i] = 2 * (i * (genus - i) * b1[0] - b1[1] * (genus - 1) * e[i]);
    
    b[0] = b[1] / 2;

    for (i = 2 ; i <= (genus / 2) ; i++)
	if (b[0] < b[i] / 2)
	    b[0] = b[i] / 2;

    a = 12 * b[0] - b[1];
    
    printf("%d    ", a);
    for (i = 0 ; i <= (genus / 2) ; i++)
    {
	printf("%d   ", b[i]);
    }
}
