%{ // -*-c-*-
#undef yywrap
#define yywrap() 1

typedef struct numlist {
    struct numlist *next;
    int val;
} numlist;

extern int mygcd(int a, int b);
extern void display_reduced(numlist *l);

numlist *list;
int num;
%}

%%
(" "*[0-9]+) {
    sscanf(yytext, "%d", &num);
    fflush(stdout);
    {
	numlist *newlist;
	newlist = (numlist *) malloc(sizeof(numlist));
	newlist->next = list;
	newlist->val = num;
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

extern void display_ratios(numlist *l, int factor);

void display_ratios(numlist *l, int factor)
{
    int ratio;
    if (l != NULL)
    {
	display_ratios(l->next, factor);

	if (factor != 0)
	{
	    ratio = l->val / factor;
	    printf("%5d ", ratio);
	}
	else
	{
	    printf("%5d ", l->val);
	}
    }
}

void display_reduced(numlist *l)
{
    int i;
    int gcd;
    numlist *node;

    if (l != NULL)
	gcd = l->val;

    for (node = l ; node != NULL ; node = node->next)
    {
	if (node->val != 0)
	    gcd = mygcd(node->val, gcd);
    }

    display_ratios(l, gcd);
    printf("\n");
}

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



