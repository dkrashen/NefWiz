#include "proof.h"

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// PROOF STEP
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

proof_step *proof_step_make(smallint genus, seq *pSeq, t_set *pIncluded)
{
    proof_step *pNewStep;
    pNewStep = (proof_step *) malloc(sizeof(proof_step));

    pNewStep->genus = genus;
    pNewStep->pSeq = seq_copy(pSeq);
    pNewStep->pIncluded = t_set_copy(pIncluded);
    pNewStep->other_reason = FALSE;

    return pNewStep;
}

void proof_step_kill(proof_step *pStep)
{
    if (pStep->pSeq != NULL)
	seq_kill(pStep->pSeq);
    if (pStep->pIncluded != NULL)
	t_set_kill(pStep->pIncluded);
    free(pStep);
}

proof_step *proof_step_copy(proof_step *pStep)
{
    proof_step *pNew;
    pNew = proof_step_make(pStep->genus, pStep->pSeq, pStep->pIncluded);
    return pNew;
}

bool proof_step_compare(proof_step *pStep1, proof_step *pStep2)
{
    bool answer;

    if ((pStep1->genus == pStep2->genus) &&
	seq_equals(pStep1->pSeq, pStep2->pSeq) &&
	t_set_equals(pStep1->pIncluded, pStep2->pIncluded))
	answer = TRUE;

    else
	answer = FALSE;
        
    return answer;
}

void proof_step_display(proof_step *pStep)
{
    t_set *pTset;

    pTset = t_set_associated_to_seq(pStep->genus, pStep->pSeq);

    seq_display(pStep->pSeq);
    printf("\n");

    printf("need to restrict to %d out of %d coefficients : \n",
	   t_set_length(pTset) - t_set_length(pStep->pIncluded), 
	   t_set_length(pTset));
    printf("\n\n");

    t_set_kill(pTset);
}



void proof_step_display_human(proof_step *pStep, divisor *pDiv, 
			      fdata_list *pFdatum)
{
    bool answer;
    t_set *pTset;
    seq_set *pSeqs;
    fdata_list *pFdataApp;
    fdata *pFdata;
    t_set *pExcluded;
    list_node *pNode;
    bool found_one = FALSE;
    binterval *pInterval;

    if (!pStep->other_reason)
    {
	pTset = t_set_associated_to_seq(div_genus(pDiv), pStep->pSeq);
	pFdataApp = fdata_list_applicable_formulas(pDiv, pTset, pFdatum, 
						   seq_length(pStep->pSeq));
	
	pExcluded = t_set_subset_complement(pTset, pStep->pIncluded);
	printf("Restriction sequence : ");
	seq_display(pStep->pSeq);
	printf("\n\nFor the %d coefficients associated to this sequence\n",
	       t_set_length(pTset));

	printf("we use the formula ");
	
	for (pNode = pFdataApp->pHead ;
	     ((pNode != NULL) && (!found_one)) ;
	     pNode = pNode->pNext)
	{
	    found_one = t_set_subset_formula_ok
		(pDiv, pTset, pStep->pIncluded, (fdata *) (pNode->pData));
	    if (found_one)
		pFdata = (fdata *) (pNode->pData);
	}
	
	fdata_display(pFdata);
	
	printf("\n");
	

	if (pFdata->type == 'c')
	{
	    pInterval = t_set_subset_formula_c_interval
		(pDiv, pTset, pStep->pIncluded, pFdata);
	    printf("with c in the interval ");
	    binterval_display(pInterval);
	    printf("\n");
	    if (t_set_length(pExcluded) != 0)
	    {
		printf("\nThe coefficients which are not in [0, 1] are as follows:\n");
		t_set_display(pExcluded);
	    }
	    else
	    {
		printf("all coefficients are in [0, 1]\n");
		printf("and therefore the boundary restriction for the "
		       "sequence:\n");
		seq_display(pStep->pSeq);
		printf("\nis successful.\n");


	    }
	    
	    printf("\n---------\n");
	    printf("all coefficient data : \n");
	    coeffs_display_everything(pDiv, pTset, pFdata->formula_c, 
				      pInterval->pLb);
	    binterval_kill(pInterval);
	    fflush(stdout);
	}
	else
	{
	    if (t_set_length(pExcluded) != 0)
	    {
		printf("The coefficients which are not in 0 are as follows:\n");
		t_set_display(pExcluded);
	    }
	    else
		printf("all coefficients are 0\n");

	}

	pSeqs = seq_set_to_check(pTset, pStep->pIncluded, div_genus(pDiv));
	if (seq_set_length(pSeqs) == 0)
	{
	    printf("there are no more subrestrictions to check for the "
		   "restriction sequence:\n");
	    seq_display(pStep->pSeq);
	    printf("\n");
	}
	else
	{
	    printf("we now need to check the following sequences: \n");
	    seq_set_display(pSeqs);
	}
	seq_set_kill(pSeqs);

	t_set_kill(pExcluded);
	t_set_kill(pTset);

	fdata_list_kill(pFdataApp);
    }
    else
    {
	switch (pStep->reason)
	{
	    case F_BOUND:
		printf("Restriction sequence : ");
		seq_display(pStep->pSeq);
		printf("\nsince the F-conjecture is true on M_{0, n} ");
		printf("for n <= %d,\n", CURRENT_F_BOUND);
		       printf("it follows that this restriction gives "
		       "something nef.\n");
	}
    }
    printf("-------------------------------------------------\n\n");
}

bool proof_step_check(proof_step *pStep, divisor *pDiv, fdata_list *pFdatum)
{
    bool answer;
    t_set *pTset;
    
    pTset = t_set_associated_to_seq(div_genus(pDiv), pStep->pSeq);
    
    answer = 
	t_set_subset_some_applicable_formula_ok
	(pDiv, pTset, pStep->pIncluded, pFdatum, seq_length(pStep->pSeq));
    
    t_set_kill(pTset);

    return answer;
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// PROOFS
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

void proof_step_kill_void(void *pStep)
{
    proof_step_kill((proof_step *) pStep);
}

void *proof_step_copy_void(void *pStep)
{
    return proof_step_copy((proof_step *) pStep);
}

bool proof_step_compare_void(void *pStep1, void *pStep2)
{
    return proof_step_compare((proof_step *) pStep1, (proof_step *) pStep2);
}

void proof_step_display_void(void *pStep)
{
    proof_step_display((proof_step *) pStep);
}

void proof_step_display_list_void(void *pProof)
{
    proof_do_each((proof *) pProof, proof_step_display_void);
}

proof *proof_new()
{
    return list_new(proof_step_compare_void, proof_step_copy_void,
		    proof_step_kill_void, proof_step_display_list_void);
}


void proof_display(proof *pProof)
{
    printf("\n**********************Proof*****************************\n");
    set_display(pProof);
    printf("     proof has length %d", proof_length(pProof));
    printf("\n******************End Proof*****************************\n");
}


void proof_human_display(proof *pProof, divisor *pDiv, fdata_list *pFdatum)
{
    proof_node *pNode;

    for (pNode = pProof->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
	
	proof_step_display_human
	    ((proof_step *) (pNode->pData), pDiv, pFdatum);
}


bool proof_check(proof *pProof, divisor *pDiv, fdata_list *pFdatum)
{
    bool answer = TRUE;
    proof_node *pNode;

    printf("\nin proof check\n");
    for (pNode = pProof->pHead ;
	 ((pNode != NULL) && (answer)) ;
	 pNode = pNode->pNext)
	
	answer = 
	    proof_step_check((proof_step *) (pNode->pData), pDiv, pFdatum);

    if (answer)
	proof_display(pProof);

    return answer;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// PROOF SETS
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

void proof_set_display(proof_set *pProof_Set)
{
    set_node *pNode;
               
    for (pNode = pProof_Set->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)

	proof_display((proof *) (pNode->pData));
}


bool proof_set_some_works(proof_set *pProofs, divisor *pDiv, 
			  fdata_list *pFdatum)
{
    bool answer = FALSE;
    set_node *pNode;

    printf("\nin proof set some works\n");
    for (pNode = pProofs->pHead ;
	 ((pNode != NULL) && (answer == FALSE)) ;
	 pNode = pNode->pNext)

	answer = proof_check((proof *) (pNode->pData), pDiv, pFdatum);

    return answer;
}
