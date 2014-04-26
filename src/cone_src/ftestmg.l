%{ // -*-c-*-
#undef yywrap
#define yywrap() 1

int a;
int divisor[100];
int genus;
int i = -1;

extern void display_is_f(int a, int *div);
%}

%%

(" "*[0-9]+) {
    if (i == -1)
	sscanf(yytext, "%d", &a);
    else
	sscanf(yytext, "%d", &(divisor[i]));
    i++;
    if (i > (genus / 2))
    {
	i = -1;
	display_is_f(a, divisor);
	printf("\n");
    }
}
\n|" " ;
%%

main(int argc, char *argv[])
{
    if (argc < 2)
    {
	printf("usage : %s <genus>\n", argv[0]);
	exit(1);
    }
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

char type_1_true(int a, int b[])
{
    char answer;

    if (a - 12*b[0] + b[1] >= 0)
	answer = 1;
    else
    {
	printf("type 1 failed\n");
    }

    return answer;
}

char type_2_true(int a, int b[])
{
    int i;
    char answer = 1;

    for (i = 0 ; i <= (genus / 2) ; i++)
    {
	if (b[i] < 0)
	{
	    printf("type 2 failed for i = %d\n", i);
	    answer = 0;
	}
    }

    return answer;
}

char type_3_true(int a, int b[])
{
    int i;
    char answer = 1;

    for (i = 1 ; i <= (genus / 2) ; i++)
    {
	if (2 * b[0] - b[i] < 0)
	{
	    printf("type 3 failed for i = %d\n", i);
	    answer = 0;
	}
    }

    return answer;
}



char type_4_true(int a, int b[])
{
    int i, j;
    char answer = 1;

    for (i = 1 ; i <= (genus - 1) ; i++)
	for (j = 1 ; (i + j) <= (genus - 1) ; j++)
	{
	    if ((b[reduce(i)] + b[reduce(j)] - b[reduce(i + j)]) < 0)
	    {
		printf("type 4 failed for i = %d, j = %d\n", i, j);
		answer = 0;
	    }
	}

    return answer;
}


char type_5_true(int a, int b[])
{
    int i, j, k;
    char answer = 1;

    for (i = 1 ; i <= (genus - 1) ; i++)
	for (j = 1 ; j <= (genus - 1) ; j++)
	    for (k = 1 ; (i + j + k) <= (genus - 1) ; j++)
	{
	    if ((b[reduce(i)] + b[reduce(j)] +b[reduce(k)] +
		 b[reduce(i + j + k)] - b[reduce(i + j)] - 
		 b[reduce(i + k)] - b[reduce(j + k)]) < 0)
	    {
		printf("type 5 failed for i = %d, j = %d, k = %d\n", i, j, k);
		answer = 0;
	    }
	}
    
    return answer;
}



void display_is_f(int a, int b[])
{
    int i;
    if (type_1_true(a, b) &&
	type_2_true(a, b) &&
	type_3_true(a, b) &&
	type_4_true(a, b) &&
	type_5_true(a, b))
    {
	printf("F : ");
	printf("%6d ", a);
	for (i = 0 ; i <= (genus / 2) ; i++)
	{
	    printf("%6d ", b[i]);
	    fflush(stdout);
	}
    }
    else
    {
	printf("**NOT F : ");
	printf("%6d ", a);
	for (i = 0 ; i <= (genus / 2) ; i++)
	{
	    printf("%6d ", b[i]);
	    fflush(stdout);
	}
    }
}
