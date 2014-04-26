%{ // -*-c-*-
#undef yywrap
#define yywrap() 1

extern char compare(char *s1, char *s2);

char line[100];

char found; 

%}

%%
^.*\n {
    if (compare(line, yytext) == 1)
    {
	found = 1;
	yyterminate();
    }
}
%%

main(int argc, char *argv[])
{
    char c = 'a';
    int i= 0;

    if (argc < 2)
    {
	printf("usage : %s <filename>\n", argv[0]);
	exit(1);
    }

    while (c != EOF)
    {
	found = 0;
	i = 0;
	c = getchar();
	while ((c != '\n') && (c != EOF))
	{
	    line[i] = c;
	    c = getchar();
	    i++;
	}
	if (c == EOF)
	    exit(0);
	line[i] = c;
	line[i+1] = '\0';
	
	yyin = fopen(argv[1], "r");
	yylex();
	fclose(yyin);
	if (!found)
	    printf("missing : %s", line);
	else
	    printf("found : %s", line);
    }
}

char compare(char *s1, char *s2)
{
    int i;
    char answer = 1;

    for (i = 0 ; ((s1[i] != '\0') && (s2[i] != '\0')) ; i++)
	if (s1[i] != s2[i])
	    answer = 0;

    return answer;
}
