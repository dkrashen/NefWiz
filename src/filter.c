#include "filter.h"

#define BUFFER_SIZE 1000


void finish(int sig);


bool ezfilter_shows_nef(divisor *pDiv, filtertype filter)
{
    bool answer;

    if (filter.label == 'e')
	answer = easy_filter_shows_nef(pDiv, filter.value);
    else 
	answer = FALSE;

    return answer;
}


static void get_genus(int *genus)
{
    int c;

    char found_genus = 0;

    void check_for_comment()
	{
	    int c;
	    
	    c = getchar();
	    if (c != '*')
		putchar(c);
	    else
	    {
		char in_comment = 1;
		printf("\n/");
		printf("*");
		
		while (in_comment)
		{
		    while ((c = getchar()) != '*');
		    {
			if ((c = getchar()) == '/')
			    in_comment = 0;
			else
			    printf("%c", c);
		    }
		}
		
		printf("*");
		printf("/\n");
		
	    }
	}
    
    c = getchar();

    while ((c != EOF) && (!found_genus))
    {
	if (c == '/')
	    check_for_comment();
	
	if (c == 'g')
	{
	    scanf("%d", genus);
	    fflush(stdout);
	    found_genus = 1;
	}
	
	c = getchar();
    }
    
    if (!found_genus)
    {
	fprintf(stderr, "couldn't find genus in data file!\n");
	exit(1);
    }  
}

static void go_to_file_start(FILE *infile)
{
    int c;
    char trash[10];
    char found_start = 0;

    void check_for_comment()
	{
	    int c;
	    
	    c = fgetc(infile);
	    if (c != '*')
		ungetc(c, infile);
	    else
	    {
		char in_comment = 1;

		while (in_comment)
		{
		    if ((c = fgetc(infile)) == '/')
			in_comment = 0;
		}
	    }
	}

    c = fgetc(infile);
    while ((c != EOF) && (!found_start))
    {
	if (c == '/')
	    check_for_comment();
	if (c == 's')
	    found_start = 1;
	
	c = fgetc(infile);
    }
    
    if (!found_start)
    {
	fprintf(stderr, "couldn't find start of data file.\n");
	exit(1);
    }

    // clear to the next line.
//    fgets(trash, 10, infile);
    scanf("\n");
}

void filter_file(FILE *infile, FILE *outfile, int genus, filtertype filter)
{
    int i;
    divisor *pDiv;
    fdata_list *pFdatum;
    int num_rogues = 0;
    proof_set *pProofs;
    ptree *pTree;
    bool finish_now = FALSE;
    char current_line[BUFFER_SIZE];
    int num_div = 0;
    char c;

    bool file_over = FALSE;

    ///////////////////////////////////////////////////////////////
    // we initialize the pProofs variable for flag
    ///////////////////////////////////////////////////////////////

    pFdatum = fdata_configure_list();
    pProofs = proof_set_new();
    pTree = ptree_new(genus, pFdatum);
    
    fprintf(outfile, "g\n%d\n\n", genus);

    go_to_file_start(infile);

    fprintf(outfile, "s\n");

    while (!file_over)
    {
	fgets(current_line, BUFFER_SIZE, infile);
	if (current_line[0] == 'e')
	    file_over = TRUE;
	else
	{
//	    fprintf(stderr, 
//		    "\nfiltering divisor %d : \n%s", num_div, current_line);
	    num_div++;
	    pDiv = div_read(current_line, genus);
	    if (filter.label == 'f')
	    {
		if (!flag_shows_nef(pDiv, pTree, pFdatum))
		{
		    div_display_file(outfile, pDiv);
		    fprintf(outfile, "\n");
		    num_rogues++;
		}
	    }
	    else if (!ezfilter_shows_nef(pDiv, filter))
	    {
		div_display_file(outfile, pDiv);
		fprintf(outfile, "\n");
		num_rogues++;
	    }
	    div_kill(pDiv);
	}
    }

    fprintf(outfile, "e\n");

    while((c = fgetc(infile)) != EOF)
	fprintf(outfile, "%c", c);

    fprintf(outfile, "\n/");
    fprintf(outfile, "*");
    fprintf(outfile, "\ngenus %d", genus);
    fprintf(outfile, "\nstarting num divisors : %d", num_div);
    fprintf(outfile, "\nfiltered through %c%d", filter.label, filter.value);
    fprintf(outfile, "\nnumber of rogue divisors : %d", num_rogues);
    if (filter.label == 'f')
	fprintf(outfile, 
		"\nproof tree has %d nodes", ptnode_set_length(pTree->pNodes));
    fprintf(outfile, "\n");
    fprintf(outfile, "*");
    fprintf(outfile, "/\n\n");
}

main(int argc, char *argv[])
{
    char input_filename[1000];
    char output_filename[1000];
    int num_div = 0;
    int genus = 0;
    FILE *infile, *outfile;
    filtertype filter;

    if (argc == 1)
    {
	fprintf(stderr, "\n\nUsage:\n\n  %s <filter data>\n\n", argv[0]);
	fprintf(stderr, "Where <filter data> consists of a filter name.\n\n"
		"The possible filters are e1, e2, e3, e4, e5, e6, e8, and "
		"f0.\n"
		"The 'e' filters check whether or not the divisor is nef\n"
		"based on certain numerical conditions, \n"
		"and the filter 'f0' checks if a divisor is nef using the \n"
		"flag restriction algorithm.\n\n");
	fprintf(stderr, "The input for this program should be in the form\n"
		"of a file containing a list of F-divisors in wiz-format:\n\n"
		"to convert a list of divisors to wiz format, you should use\n"
		"the program 'cones/bin/format-wiz' (which requires you to \n"
		"enter the genus).\n\n"
		"For example, if using make_cones, you have created a file\n"
		"of divisors called 'cones/mg_extremal-18', you can filter\n"
		"if using the filter 'e6' by using the command line:\n\n"
		"cat cones/mg_extremal-18 | cones/bin/format_wiz 18 | "
		"filter e6\n\n"
		"the resulting output will also be in wiz-format, and so \n"
		"this process can be repeated using more |'s.\n\n"
		"For example, to take the results of the above filter and \n"
		"filter again through e8 and then f0, you can use the \n"
		"command line:\n"
		"cat cones/mg_extremal-18 | cones/bin/format_wiz 18 | "
		"filter e6 | filter e8 | filter f0\n\n");
	exit(1);
    }

    sscanf(argv[1], "%c%d", &(filter.label), &(filter.value));

    get_genus(&genus);
    filter_file(stdin, stdout, genus, filter);
}

