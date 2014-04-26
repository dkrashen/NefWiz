#include "filter.h"

#define BUFFER_SIZE 1000

static bool get_proof(divisor *pDiv)
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
    char divisor_data[1000];
    int genus;

    divisor *pDiv;
    proof *pProof;

    if (argc == 1)
    {
	printf("\nusage:\n\n  %s <genus>\n\n", argv[0]);
	printf("\nThis program takes a divisor in \\overline{M_g}\n"
	       "and outputs for each one a proof that it is nef\n"
	       "(if possible).\n\n");
	exit(1);
    }
    else
	genus = atoi(argv[1]);

    fprintf(stderr, "Enter a divisor in the form :\n");
    fflush(stderr);
    fprintf(stderr, "    lambda delta_0 delta_1 ... delta_%d\n : ", genus / 2);
    fgets(divisor_data, 1000, stdin);
    
    pDiv = div_read(divisor_data, genus);

    if (!div_is_f(pDiv))
	printf("\ndivisor is not an F-divisor (and is therefore not nef).\n");
    else if (!get_proof(pDiv))
	printf("\nno proof found.\n");
}

