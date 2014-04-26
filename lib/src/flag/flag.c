
#include "flag.h"

// RUN-TIME OPTIONS

static int MAXLEVEL;
static int CURRENTLEVEL;


// FORMULA DATA LISTS

fdata_list *fdata_configure_list()
{
    fdata_list *pFdatum;

    pFdatum = fdata_list_new();
	    
#include "current_flag_configuration.c"
    
    return pFdatum;
}

void fdata_clear_list(fdata_list *pFdatum)
{
    fdata_list_kill(pFdatum);
}


///////////////////////////////////////////////
///////////////////////////////////////////////
// MAIN ALGORITHM PROCUDURES
///////////////////////////////////////////////
///////////////////////////////////////////////


bool flag_shows_nef(divisor *pDiv, ptree *pTree, fdata_list *pFdatum) 
{
    
    
    bool answer;

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

//    fprintf(stderr, "\nnum checked : %d  num rechecked : %d tree size : %d",
//	    pTree->num_nodes_checked, pTree->num_nodes_rechecked, 
//	    ptnode_set_length(pTree->pNodes));
//   fprintf(stderr, "\n--------------------\n\n"); 
//    fflush(stderr);
    ptree_reset(pTree);
    
    return answer;
}

bool old_flag_shows_nef(divisor *pDiv, int maxlevel) 
{
    bool answer;
    seq *pInitialSeq;

    seq_set *pSuccessful_restriction_sequences;
    proof *pCurrent_Proof;
    proof_set *pProofs;

    fdata_list *pFdatum;

    pFdatum = fdata_configure_list();



    ///////////////////////////////
    // configure global variables
    ///////////////////////////////
    pSuccessful_restriction_sequences = seq_set_new();  
    pCurrent_Proof = proof_new();

    ///////////////////////////////
    ///////////////////////////////
    div_display(pDiv);
    printf("\n");
//    fflush(stdout);

    printf("proofs so far (%d). \n", proof_set_length(pProofs));

    if (proof_set_some_works(pProofs, pDiv, pFdatum))
    {
	printf("an old proof worked!\n");
	answer = TRUE;
	proof_kill(pCurrent_Proof);
    }
    else
    {
	pInitialSeq = seq_new();
	
	answer = 
	    seq_restrictions_work(pDiv, pInitialSeq, pCurrent_Proof,
				  pSuccessful_restriction_sequences, pFdatum);


	seq_kill(pInitialSeq);
	
	if (answer)
	{
	    printf("\n----------------------------------------\n");
	    printf("got a new proof. \n");
//	    proof_display(pCurrent_Proof);
	    proof_set_force_ordered_push(pProofs, pCurrent_Proof);
	    
	}
	else
	{
	    proof_kill(pCurrent_Proof);
	}
	
    }
    
    ///////////////////////////////
    // clear global variables
    ///////////////////////////////
    seq_set_kill(pSuccessful_restriction_sequences);
    
    return answer;
}


bool seq_restrictions_work(divisor *pDiv, seq *pSeq, proof *pCurrent_Proof, 
			   seq_set *pSuccessful_restriction_sequences, 
			   fdata_list *pFdatum)
{
    bool works = FALSE;
    t_mlat *pMaximals;
    t_set *pTset;

    smallint a, z;

    a = seq_length(pSeq);
    z = div_genus(pDiv) - seq_sum(pSeq);
  
    ///////////////////////////////////////////////////////////////
    // if a + z <= F bound then we know it's NEF
    ///////////////////////////////////////////////////////////////
    
    if (a + z <= CURRENT_F_BOUND)
    {
	proof_step *pNewStep;
	pNewStep = 
	    proof_step_make(div_genus(pDiv), pSeq, 
			    t_set_associated_to_seq(div_genus(pDiv), pSeq));
	pNewStep->other_reason = TRUE;
	pNewStep->reason = F_BOUND;
	proof_force_push_head(pCurrent_Proof, pNewStep);
	works = TRUE;
    }   
 
    else if (seq_set_is_member(pSuccessful_restriction_sequences, pSeq))
	works = TRUE;
    else
    {
	mlat_node *pNode;
	pTset = t_set_associated_to_seq(div_genus(pDiv), pSeq);
	pMaximals = t_mlat_some_maximals(pDiv, pTset, pFdatum, a);

	for (pNode = pMaximals->pHead ;
	     ((pNode != NULL) && (works == FALSE)) ;
	     pNode = pNode->pNext)
	{

	    works = 
		maximal_t_subset_works(pDiv, (t_set *) (pNode->pData), pTset,
				       pCurrent_Proof, 
				       pSuccessful_restriction_sequences, 
				       pFdatum);
	    if (works)
	    {
		proof_step *pNewStep;
		pNewStep = proof_step_make(div_genus(pDiv), pSeq, 
					   (t_set *) (pNode->pData));
		proof_force_push_head(pCurrent_Proof, pNewStep);
	    }
	}

	if (works)
	    seq_set_force_push(pSuccessful_restriction_sequences, 
			       seq_copy(pSeq));
	
    }
    return works;
}


// aka maximal_t_subset_works(divisor *, t_set *pIncluded, t_set *pTset);
bool restrictions_on_triples_show_nef(divisor *pDiv, t_set *pTset, 
				      t_set *pIncluded, proof *pCurrent_Proof,
				      seq_set 
				      *pSuccessful_restriction_sequences,
				      fdata_list *pFdatum)
{
    bool answer;

    //given triples together with complementary triples
    seq_set *pSeqSet;

    pSeqSet = seq_set_to_check(pTset, pIncluded, div_genus(pDiv));

    answer = seq_set_restrictions_work(pDiv, pSeqSet, pCurrent_Proof, 
				       pSuccessful_restriction_sequences,
				       pFdatum);

    seq_set_kill(pSeqSet);

    return answer;
}


bool seq_set_restrictions_work(divisor *pDiv, seq_set *pSeqSet, 
			       proof *pCurrent_Proof, 
			       seq_set *pSuccessful_restriction_sequences,
			       fdata_list *pFdatum)
{
    bool answer = TRUE;
    set_node *pNode;

    for (pNode = pSeqSet->pHead ;
	 ((pNode != NULL) && (answer == TRUE)) ;
	 pNode = pNode->pNext)

	answer = seq_restrictions_work(pDiv, (seq *) (pNode->pData), 
				       pCurrent_Proof,
				       pSuccessful_restriction_sequences, 
				       pFdatum);

    return answer;
}

