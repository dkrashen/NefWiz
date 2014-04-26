%{ // -*-c-*-
#undef yywrap
#define yywrap() 1

typedef struct numlist {
    struct numlist *next;
    int num;
    int den;
} numlist;

extern void display_reduced(numlist *l);
numlist *list;
int num;
int den; 
%}

%%
(" "*)([0-9]+"/"[0-9]+) {
    sscanf(yytext, "%d/%d", &num, &den);
    {
	numlist *newlist;
	newlist = (numlist *) malloc(sizeof(numlist));
	newlist->next = list;
	newlist->num = num;
	newlist->den = den;
	list = newlist;
    }
}
(" "*([0-9]+" ")) {
    sscanf(yytext, "%d", &num);
    den = 1;
    {
	numlist *newlist;
	newlist = (numlist *) malloc(sizeof(numlist));
	newlist->next = list;
	newlist->num = num;
	newlist->den = den;
	list = newlist;
    }
}
" " ;
\n {
    numlist *node, *nextnode;
    node = list;
    display_reduced(list);
    while(node != NULL)
    {
	nextnode = node->next;
	free(node);
	node = nextnode;
    }
    list = NULL;
}
%%

main(int argc, char *argv[])
{
    list = NULL;

    yylex();
}

extern void display_cleared(numlist *l, int factor);

void display_cleared(numlist *l, int factor)
{
    if (l != NULL)
    {
	int reduced_factor;
	display_cleared(l->next, factor);
	reduced_factor = factor / l->den;
	printf("%5d ", reduced_factor * l->num);
    }
}

void display_reduced(numlist *l)
{
    int i;
    int den;
    numlist *node;

    if (l != NULL)
	den = l->den;

    for (node = l ; node != NULL ; node = node->next)
    {
	den = mylcm(den, node->den);
    }

    display_cleared(l, den);
    printf("\n");
}

extern int mygcd(int a, int b);

int mygcd(int a, int b)
{
    int r, d, answer;

    if (b == 0)
	answer = a;
    else
    {
	d = a / b;
	r = a - b * d;
	if (r == 0)
	    answer = b;
	else
	    answer = mygcd(b, r);
    }
    return answer;
}

int mylcm(int a, int b)
{
    int answer;
    int d = mygcd(a, b);

    if (d != 0)
	answer = (a / d) * b;
    else
	answer = 0;

    return answer;
}
