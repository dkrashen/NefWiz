%{ // -*-c-*-
#undef yywrap
#define yywrap() 1

#include "filter.h"
#include "proof.h"
#include "latex_display.h"

#define BUFFER_SIZE 


extern void display_main_menu();
extern void display_dvi_proof(divisor *pDiv, proof *pProof);
extern void show_initial_info(divisor *pDiv);
extern void show_initial_info_latex(divisor *pDiv);
extern bool get_proof(divisor *pDiv);
extern void get_tree_info(divisor *pDiv);
divisor *pDiv;
int genus;
ptree *pTree;
proof *pCurrent_Proof;
proof_set *pProofs; 
fdata_list *pFdatum;

%}

%x QUERY_TREE
%x POST_TREE_MENU
%x INITIAL_INFO_QUERY
%x QUERY_PROOF_INTERACTIVE
%x PROOF_INTERACTIVE
%x PROOF_DISPLAY_MENU
%s DIV_READ

%%

[0-9]+\n {
    genus = atoi(yytext);
    pTree = ptree_new(genus, pFdatum);
    BEGIN DIV_READ;
    display_main_menu();
}

<DIV_READ>^(" "|[0-9]|-|\t)+\n {
    pDiv = div_read(yytext, genus);
    printf("divisor : ");
    div_display(pDiv);
    printf("\n");
    fflush(stdout);
    if (div_is_f(pDiv))
    {
	printf("this is an F-divisor\n");
	show_initial_info(pDiv);
	BEGIN INITIAL_INFO_QUERY;
	printf("would you like to see typeset output?\n");
    }
    else
    {
	printf("this is not an F-divisor\n");
	BEGIN 0;
    }
}

<INITIAL_INFO_QUERY>^.*\n {
    if (yytext[0]=='y')
	show_initial_info_latex(pDiv);
    BEGIN QUERY_TREE;
    printf("\nwould you like to check for a proof using the restriction algorithm (y/n)?\n");
}

<QUERY_TREE>^.*\n {
    if (yytext[0] == 'y')
	get_tree_info(pDiv);

	BEGIN POST_TREE_MENU;

	printf("I.   To go through the restriction algorithm \n"
	       "       interactively, type '1'\n");
	printf("II.  To see a list of restrictions checked by\n"
	       "       the nef wizard, type '2'\n");
	printf("III. To return to the main menu, type '3'\n");
	printf("\n\n > ");

}

<POST_TREE_MENU>^.*\n {
    switch (atoi(yytext))
    {
	case 1:
	    get_proof(pDiv);
	    printf("Choose one of the following display options:\n\n");
	    printf("1  - typeset output displayed in a dvi window.\n");
	    printf("2  - verbose typeset output displayed in a dvi window.\n");
	    printf("3  - plain text output.\n");
	    printf("4  - verbose plain text output.\n");
	    printf("\n > ");
	    BEGIN PROOF_DISPLAY_MENU;
	    break;
	case 2:
	    printf("coming soon.\n");
	    display_main_menu();
	    BEGIN 0;
	    break;
	default:
	    display_main_menu();
	    BEGIN 0;
    }
}

<POST_TREE_MENU>.*\n ;

<PROOF_DISPLAY_MENU>^.*\n {
    switch (atoi(yytext))
    {
	case 1:
	    display_dvi_proof(pDiv, pCurrent_Proof);
	    break;
    }
    display_main_menu();
    BEGIN 0;
}


<PROOF_INTERACTIVE>^.*\n {
    BEGIN 0;
}
    


%%

void display_main_menu()
{
    printf("enter a divisor\n");
}

void show_initial_info(divisor *pDiv)
{
    FILE *initial_info;
    
    if (condition1_shows_nef(pDiv))
    {
	printf("\nDivisor satisfies:\n");
	printf("b_i >= b_0 or b_i = 0 for each i\n");
	printf("and is therefore nef.\n");
    }
    if (condition2_shows_nef(pDiv))
    {
	printf("\nDivisor satisfies:\n");
	printf("2 b_1 >= b_i >= b_1 or b_i = 0 for i > 1\n");
	printf("and is therefore nef.\n");
    }
    if (condition3_shows_nef(pDiv))
    {
	printf("\nDivisor satisfies:\n");
	printf("b_i <= b_1 for each i > 0\n");
	printf("and is therefore nef.\n");
    }
    if (condition4_shows_nef(pDiv))
    {
	printf("\nDivisor satisfies:\n");
	printf("b_i * (g - 1) = i * (g - i) * b_1 for i > 1\n");
	printf("and is therefore nef (pulls back to 0 in flag map).\n");
    }
    if (condition6_shows_nef(pDiv))
    {
	printf("\nDivisor satisfies:\n");
	if (div_genus(pDiv) % 2 == 0)
	{
	    printf("b_i = 0 for some i >= 0, i < g/2 (g even)\n");
	    printf("and is therefore nef.\n");
	}
	else
	{
	    printf("b_i = 0 for some i >= 0, (g odd)\n");
	    printf("and is therefore nef.\n");
	}
    }
    if (condition8_shows_nef(pDiv))
    {
	printf("\nDivisor satisfies:\n");
	printf("- b_0 * (g-1) < i (g - i) (b_1 - b_0) + (g - 1) "
	       "(b_0 - b_1) < 0 \nfor each i > 0\n");
	printf("and is therefore nef.\n");
    }
}
 
void show_initial_info_latex(divisor *pDiv)
{
    FILE *initial_info;
    
    
    ////////////////////////////////////////////
    // latex display
    ////////////////////////////////////////////
    
    initial_info = fopen("data/initial_info.tex", "w");
    
    fprintf(initial_info, "\n\\documentclass[12pt]{letter}\n"
	    "\\usepackage{amsmath,amsthm,amsfonts,amscd,amssymb}"
	    "\\begin{document}\n");
    
    fprintf(initial_info, "Divisor : \n$$");
    div_latex_display_file(initial_info, pDiv);
    fprintf(initial_info, "$$\n");
    
    if (condition1_shows_nef(pDiv))
    {
	fprintf(initial_info, "\nDivisor satisfies:\n");
	fprintf(initial_info, "$b_i \\geq b_0$ or $b_i = 0$ for each $i$\n");
	fprintf(initial_info, "and is therefore nef.\n");
    }
    if (condition2_shows_nef(pDiv))
    {
	fprintf(initial_info, "\nDivisor satisfies:\n");
	fprintf(initial_info, "$2 b_1 \\geq b_i \\geq b_1$ or $b_i = 0$ for $i > 1$\n");
	fprintf(initial_info, "and is therefore nef.\n");
    }
    if (condition3_shows_nef(pDiv))
    {
	fprintf(initial_info, "\nDivisor satisfies:\n");
	fprintf(initial_info, "$b_i \\leq b_1$ for each $i > 0$\n");
	fprintf(initial_info, "and is therefore nef.\n");
    }
    if (condition4_shows_nef(pDiv))
    {
	fprintf(initial_info, "\nDivisor satisfies:\n");
	fprintf(initial_info, "$b_i * (g - 1) = i * (g - i) * b_1$ for $i > 1$\n");
	fprintf(initial_info, "and is therefore nef (pulls back to 0 in flag map).\n");
    }
    if (condition6_shows_nef(pDiv))
    {
	fprintf(initial_info, "\nDivisor satisfies:\n");
	if (div_genus(pDiv) % 2 == 0)
	{
	    fprintf(initial_info, "$b_i = 0$ for some $i \\geq 0, i < g/2$ ($g$ even)\n");
	    fprintf(initial_info, "and is therefore nef.\n");
	}
	else
	{
	    fprintf(initial_info, "$b_i = 0$ for some $i \\geq 0$, ($g$ odd)\n");
	    fprintf(initial_info, "and is therefore nef.\n");
	}
    }
    if (condition8_shows_nef(pDiv))
    {
	fprintf(initial_info, "\nDivisor satisfies:\n");
	fprintf(initial_info, "$- b_0 * (g-1) < i (g - i) (b_1 - b_0) + (g - 1) "
	       "(b_0 - b_1) < 0$ \nfor each $i > 0$\n");
	fprintf(initial_info, "and is therefore nef.\n");
    }

    fprintf(initial_info, "\\end{document}\n");
    
    fclose(initial_info);

    system("cd data ; latex initial_info.tex ; rm initial_info.aux initial_info.log");
    system("xdvi data/initial_info.dvi &");
}

void get_tree_info(divisor *pDiv)
{
    bool answer;
    char reply[100];
    ///////////////////////////////
    ///////////////////////////////
    
    ptree_reset(pTree);
    ptree_nospawn(pTree);
    answer = ptree_works(pTree, pDiv);
    
    if (answer == FALSE)
    {
	ptree_reset(pTree);
	ptree_spawn(pTree);
	answer = ptree_works(pTree, pDiv);
    }
    
    if (!answer)
	printf("no proof found.\n");
    
    else
    {
	printf("a proof was found with %d restrictions\n", 
	       pTree->num_nodes_checked);
	printf("(total number of restrictions done so far = %d)\n",
	       ptnode_set_length(pTree->pNodes));
	printf("\n");
	ptree_reset(pTree);
    }
}

void display_dvi_proof(divisor *pDiv, proof *pProof)
{
    FILE *proof_file;
    
    proof_file = fopen("data/proof_file.tex", "w");
    fprintf(proof_file, "\n\\documentclass[12pt]{letter}\n"
	    "\\usepackage{amsmath,amsthm,amsfonts,amscd,amssymb}"
	    "\\begin{document}\n");

    proof_human_display_file_latex(proof_file, 
				   pCurrent_Proof, pDiv, pFdatum);
    fprintf(proof_file, "\n\\end{document}\n");
    fclose(proof_file);
    system("cd data ; latex proof_file.tex ; rm proof_file.aux proof_file.log");
    system("xdvi data/proof_file.dvi &");
}
    
    

bool get_proof(divisor *pDiv)
{
    bool answer;
    seq *pInitialSeq;

    seq_set *pSuccessful_restriction_sequences;

    pFdatum = fdata_configure_list();

    ///////////////////////////////
    ///////////////////////////////

    pSuccessful_restriction_sequences = seq_set_new();  
    pCurrent_Proof = proof_new();

    ///////////////////////////////
    ///////////////////////////////

    pInitialSeq = seq_new();
    
    answer = 
	seq_restrictions_work(pDiv, pInitialSeq, pCurrent_Proof,
			      pSuccessful_restriction_sequences, pFdatum);
    
    seq_kill(pInitialSeq);
    
    ///////////////////////////////
    ///////////////////////////////

    seq_set_kill(pSuccessful_restriction_sequences);
    
    return answer;
}

main(int argc, char *argv[])
{
    printf("\nwelcome to the nefwiz calculator. "
	   "which genus would you like to work with?\n");

    pFdatum = fdata_configure_list();

    yylex();
//    system("rm -r -f data/*");
}

/*

    if (yytext[0] == 'y')
    {
	bool answer;
	seq *pInitialSeq;
	
	seq_set *pSuccessful_restriction_sequences;
	fdata_list *pFdatum;
	
	pFdatum = fdata_configure_list();
	
	///////////////////////////////
	///////////////////////////////
	
	pSuccessful_restriction_sequences = seq_set_new();  
	pCurrent_Proof = proof_new();

	///////////////////////////////
	///////////////////////////////

	pInitialSeq = seq_new();
	
	answer = 
	    seq_restrictions_work(pDiv, pInitialSeq, pCurrent_Proof,
				  pSuccessful_restriction_sequences, pFdatum);
	
	seq_kill(pInitialSeq);
	
	if (answer)
	{
	    FILE *proof_file;
	    
	    proof_file = fopen("data/proof_file", "w");
	    fprintf(proof_file, "\n\\documentclass[12pt]{letter}\n"
		    "\\begin{document}\n");
	    proof_human_display_file_latex(proof_file, 
					   pCurrent_Proof, pDiv, pFdatum);
	    fprintf(proof_file, "\n\\end{document}\n");
	    fclose(proof_file);
	}
	
	///////////////////////////////
	///////////////////////////////
	
	seq_set_kill(pSuccessful_restriction_sequences);
	
	return answer;
    }
    
    BEGIN PROOF_INTERACTIVE;
}

*/
