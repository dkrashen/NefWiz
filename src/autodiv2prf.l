%{ // -*-c-*-
#undef yywrap
#define yywrap() 1

#include "filter.h"

#define BUFFER_SIZE 

divisor *pDiv;

int genus;

extern bool get_proof(divisor *pDiv);


%}

%%
^.*\n {
    pDiv = div_read(yytext, genus);
    printf("divisor : ");
    div_display(pDiv);
    printf("\n");
    if (!div_is_f(pDiv))
	printf("\ndivisor is not an F-divisor (and is therefore not nef).\n");
    else if (!get_proof(pDiv))
	printf("\nno proof found.\n");
    fflush(stdout);
}
%%

bool get_proof(divisor *pDiv)
{
    bool answer;
    seq *pInitialSeq;

    seq_set *pSuccessful_restriction_sequences;
    proof *pCurrent_Proof;
    proof_set *pProofs;

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
	printf("\n----------------------------------------\n");
	proof_human_display(pCurrent_Proof, pDiv, pFdatum);
	printf("\n----------------------------------------\n");
    }
    
    ///////////////////////////////
    ///////////////////////////////

    seq_set_kill(pSuccessful_restriction_sequences);
    
    return answer;
}

main(int argc, char *argv[])
{
    proof *pProof;

    if (argc == 1)
    {
	printf("\nusage:\n\n  %s <genus>\n\n", argv[0]);
	printf("\nThis program takes a list of divisors in \\overline{M_g}\n"
	       "and outputs for each one a proof that it is nef\n"
	       "(if possible). Since the output from this program can be \n"
	       "long, it is reccomended that it is run with the aid of a \n"
	       "program such as 'less' or otherwise that the resulting \n"
	       "output is put into a seperate file.\n\n");
	printf("For example, if the file : cones/flag2mg_extremal-10\n"
	       "contains the a collection of divisors in \\overline{M_10}\n"
	       "we could display to the screen the proofs that these \n"
	       "divisors are nef by using the command line:\n"
	       "\nautodiv2proof 10 < cones/flag2mg_extremal-10 | less\n"
	       "\nor we could put them into the file 'genus10proofs' by\n"
	       "using the command line:\n"
	       "\nautodiv2proof 10 < cones/flag2mg_extremal-10 > "
	       "genus10proofs\n\n");
	printf("The input for this program must be a plain list of divisors\n"
	       "i.e., not in wiz-format. To remove wiz-formatting from a \n"
	       "list, you must use the utility cones/bin/rm_format\n\n"
	       "for example, to take a list of divisors in the file\n"
	       "\ncones/flag2mg_extremal-15\n\n"
	       "and filter it through filters e1 and e2, and then display\n"
	       "proofs for the remaining divisors, you could use the command\n"
	       "line:\n\n"
	       "cat cones/flag2mg_extremal-15 | cones/bin/format_wiz 15 | \n"
	       "filter e1 | filter e2 | cones/bin/rm_format | autodiv2prf 15\n"
	       "\nSince the output of this command will likely be very long,\n"
	       "you might either place the result into a file or display the\n"
	       "results using 'less' or 'more' as above");
	exit(1);
    }
    else
	genus = atoi(argv[1]);

    yylex();
}

