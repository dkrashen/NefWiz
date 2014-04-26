#include "proof_tree.h"

#include "flag.h"

void statustype_display(statustype status)
{
    if (status == YES)
	printf("YES");
    else if (status == NO)
	printf("NO");
    else if (status == MAYBE)
	printf("MAYBE");
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
// PROOF TREE NODES
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

ptnode *ptnode_make_old(smallint genus, seq *pSeq)
{
    ptnode *pNewNode;
    pNewNode = (ptnode *) malloc(sizeof(ptnode));
    pNewNode->status = MAYBE;
    pNewNode->pSeq = seq_copy(pSeq);
    pNewNode->pArrows = ptarrow_set_new();

    return pNewNode;
}

ptnode *ptnode_make(smallint genus, seq *pSeq)
{
    t_set *pFullTset;
    ptnode *pNewNode;
    pNewNode = (ptnode *) malloc(sizeof(ptnode));
    pNewNode->status = MAYBE;
    pNewNode->pSeq = seq_copy(pSeq);
    pNewNode->pArrows = ptarrow_set_new();

    pFullTset = t_set_associated_to_seq(genus, pSeq);
    
    ptarrow_set_push(pNewNode->pArrows, ptarrow_make(pFullTset));
    t_set_kill(pFullTset);

    return pNewNode;
}

ptnode *ptnode_copy(ptnode *pNode)
{
    ptnode *pCopy;
    pCopy = (ptnode *) malloc(sizeof(ptnode));
    pCopy->status = pNode->status;
    pCopy->pSeq = seq_copy(pNode->pSeq);
    pCopy->pArrows = ptarrow_set_copy(pNode->pArrows);
}

void ptnode_kill(ptnode *pNode)
{
    if (pNode->pArrows != NULL)
	ptarrow_set_kill(pNode->pArrows);
    if (pNode->pSeq != NULL)
	seq_kill(pNode->pSeq);
    free(pNode);
}

void ptnode_display(ptnode *pNode)
{
//    printf("\n--");
//    statustype_display(pNode->status);
    printf("Sequence : ");
    seq_display(pNode->pSeq);
}

bool ptnode_equals(ptnode *pNode1, ptnode *pNode2)
{
    return seq_equals(pNode1->pSeq, pNode2->pSeq);
}

bool ptnode_lessthan(void *pNode1, void *pNode2)
{
    bool answer;
    answer = (seq_length(((ptnode *) pNode1)->pSeq) <
	      seq_length(((ptnode *) pNode2)->pSeq)) ? 
	TRUE : FALSE;
    return answer;
}


void ptnode_kill_void(void *pNode)
{
    ptnode_kill((ptnode *) pNode);
}

void ptnode_display_void(void *pNode)
{
    ptnode_display((ptnode *) pNode);
}

void ptnode_display_set_void(void *pNodeSet)
{
    ptnode_set_do_each((ptnode_set *) pNodeSet, ptnode_display_void);
}

bool ptnode_equals_void(void *pNode1, void *pNode2)
{
    return ptnode_equals((ptnode *) pNode1, (ptnode *) pNode2);
}

void *ptnode_copy_void(void *pNode)
{
    ptnode *pCopy;
    pCopy = ptnode_copy((ptnode *) pNode);
    return pCopy;
}

ptnode_set *ptnode_set_new()
{
    return set_new(ptnode_equals_void, ptnode_copy_void, ptnode_kill_void,
		    ptnode_display_set_void);
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
// PROOF TREE ARROWS
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

ptarrow *ptarrow_make(t_set *pIncluded)
{
    ptarrow *pNewArrow;
    pNewArrow = (ptarrow *) malloc(sizeof(ptarrow));
    pNewArrow->status = MAYBE;
    pNewArrow->pIncluded = t_set_copy(pIncluded);
    pNewArrow->pProgeny = ptnode_set_new();
    pNewArrow->spawned = FALSE;

    return pNewArrow;
}
 
ptarrow *ptarrow_copy(ptarrow *pArrow)
{
    ptarrow *pCopy;
    pCopy = (ptarrow *) malloc(sizeof(ptarrow));
    pCopy->status = pArrow->status;
    pCopy->pIncluded = t_set_copy(pArrow->pIncluded);
    pCopy->pProgeny;
}

void ptarrow_kill(ptarrow *pArrow)
{
    if (pArrow->pProgeny != NULL)
	ptnode_set_kill(pArrow->pProgeny);
    if (pArrow->pIncluded != NULL)
	t_set_kill(pArrow->pIncluded);
    free(pArrow);
}

void ptarrow_display(ptarrow *pArrow)
{
    printf("--");
    statustype_display(pArrow->status);
    printf("\n--");
    printf("Included %d triples.\n", t_set_length(pArrow->pIncluded));
}

bool ptarrow_equals(ptarrow *pArrow1, ptarrow *pArrow2)
{
    return t_set_equals(pArrow1->pIncluded, pArrow2->pIncluded);
}

bool ptarrow_lessthan(void *pArrow1, void *pArrow2)
{
    bool answer;
    answer = (t_set_length(((ptarrow *) pArrow1)->pIncluded) >
	      t_set_length(((ptarrow *) pArrow2)->pIncluded)) ? 
	TRUE : FALSE;
    return answer;
}


bool ptarrow_t_set_equals(ptarrow *pArrow, t_set *pTset)
{
    return t_set_equals(pArrow->pIncluded, pTset);
}

void ptarrow_kill_void(void *pArrow)
{
    ptarrow_kill((ptarrow *) pArrow);
}

void ptarrow_display_void(void *pArrow)
{
    ptarrow_display((ptarrow *) pArrow);
}

void ptarrow_display_set_void(void *pArrowSet)
{
    ptarrow_set_do_each((ptarrow_set *) pArrowSet, ptarrow_display_void);
}

bool ptarrow_equals_void(void *pArrow1, void *pArrow2)
{
    return ptarrow_equals((ptarrow *) pArrow1, (ptarrow *) pArrow2);
}

void *ptarrow_copy_void(void *pArrow)
{
    ptarrow *pCopy;
    pCopy = ptarrow_copy((ptarrow *) pArrow);
    return pCopy;
}


ptarrow_set *ptarrow_set_new()
{
    ptarrow_set *pArrows;

    pArrows = 
	set_new(ptarrow_equals_void, ptarrow_copy_void, ptarrow_kill_void, 
		ptarrow_display_set_void);
    
    return pArrows;
}

ptarrow_set *ptarrow_set_new_prime()
{
    ptarrow_set *pArrows;
    ptarrow *pArrow;
    t_set *pEmptyIncluded;
    
    pEmptyIncluded = t_set_new();
    pArrow = ptarrow_make(pEmptyIncluded);
    t_set_kill(pEmptyIncluded);

    pArrows = 
	set_new(ptarrow_equals_void, ptarrow_copy_void, ptarrow_kill_void, 
		ptarrow_display_set_void);
    
    ptarrow_set_push(pArrows, pArrow);

    return pArrows;
}

bool ptnode_t_set_is_member(ptnode *pNode, t_set *pTset)
{
    list_node *pArrowListNode;
    bool answer = FALSE;

    for (pArrowListNode = (pNode->pArrows)->pHead ;
	 ((pArrowListNode != NULL) && (!answer)) ;
	 pArrowListNode = pArrowListNode->pNext)
	
	answer = ptarrow_t_set_equals((ptarrow *) (pArrowListNode->pData),
				      pTset);

    return answer;
}




////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
// PROOF TREES
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

ptree *ptree_new(smallint genus, fdata_list *pFdatum)
{

    seq *pInitialSeq;
    t_set *pFullTset;
    ptree *pNewTree;

    pNewTree = (ptree *) malloc(sizeof(ptree));
    pNewTree->genus = genus;
    pNewTree->num_nodes_checked = 0;
    pNewTree->num_nodes_rechecked = 0;
    pNewTree->spawning = FALSE;
    pNewTree->pFdatum = fdata_list_copy(pFdatum);
    pNewTree->pRoot = ptnode_make(genus, pInitialSeq = seq_new());
    pNewTree->pNodes = ptnode_set_new();
    ptnode_set_push(pNewTree->pNodes, pNewTree->pRoot);

    pFullTset = t_set_associated_to_seq(genus, pInitialSeq);
    
//    ptarrow_set_push(pNewTree->pRoot->pArrows, ptarrow_make(pFullTset));
    t_set_kill(pFullTset);

    seq_kill(pInitialSeq);

    return pNewTree;
}


extern void ptarrow_reset(ptarrow *pArrow);

extern void ptnode_reset(ptnode *pNode);

void ptarrow_reset(ptarrow *pArrow)
{
    if (pArrow->status != MAYBE)
    {
	set_node *pNodeSetNode;
	pArrow->status = MAYBE;
	
	for (pNodeSetNode = pArrow->pProgeny->pHead ;
	     pNodeSetNode != NULL ;
	     pNodeSetNode = pNodeSetNode->pNext)

	    ptnode_reset((ptnode *) (pNodeSetNode->pData));
    }
}

void ptnode_reset(ptnode *pNode)
{
    if (pNode->status != MAYBE)
    {
	set_node *pSetNode;
	pNode->status = MAYBE;
	
	for (pSetNode = pNode->pArrows->pHead ;
	     pSetNode != NULL ;
	     pSetNode = pSetNode->pNext)

	    ptarrow_reset((ptarrow *) (pSetNode->pData));
    }
}

void ptree_reset(ptree *pTree)
{
    pTree->num_nodes_checked = 0;
    pTree->num_nodes_rechecked = 0;
    ptnode_reset(pTree->pRoot);
}

void ptree_show_spawn(ptree *pTree)
{
    switch (pTree->spawning)
    {
	case TRUE: 
	    printf("spawn");
	    break;
	case FALSE:
	    printf("nospawn");
	    break;
    }
}

void ptree_kill(ptree *pTree)

{
    ptnode_set_debone(pTree->pNodes);
    fdata_list_kill(pTree->pFdatum);
    ptnode_kill(pTree->pRoot);
    free(pTree);
}

// returns a pointer to the node with the sequence, if the node is in the
// tree and returns NULL otherwise.
ptnode *ptree_find_seq(ptree *pTree, seq *pSeq)
{
    ptnode *pNode = NULL;
    bool found = FALSE;
    
    set_node *pSetNode;
    
    for (pSetNode = pTree->pNodes->pHead ;
	 ((pSetNode != NULL) && (!found)) ;
	 pSetNode = pSetNode->pNext)
    {
	if (seq_equals(pSeq, ((ptnode *) (pSetNode->pData))->pSeq))
	{
	    found = TRUE;
	    pNode = (ptnode *) ((ptnode *) (pSetNode->pData));
	}
    }
    return pNode;
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
// BASIC SPAWNING
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

bool ptnode_mlat_included(ptnode *pNode, t_mlat *pMlat)
{
    bool answer = TRUE;
    set_node *pMlatNode;

    for (pMlatNode = pMlat->pHead ;
	 ((pMlatNode != NULL) && (answer)) ;
	 pMlatNode = pMlatNode->pNext)

	answer = ptnode_t_set_is_member(pNode, (t_set *) (pMlatNode->pData));

    return answer;
}


void ptarrow_force_push_seq(ptarrow *pArrow, seq *pSeq, ptree *pTree)
{
    ptnode *pNewNode;

    pNewNode = ptree_find_seq(pTree, pSeq);
    if (pNewNode == NULL)
	pNewNode = ptnode_make(pTree->genus, pSeq);

    ptnode_set_force_push(pArrow->pProgeny, pNewNode);
}

bool ptnode_set_seq_is_member(ptnode_set *pNodes, seq *pSeq)
{
    bool answer = FALSE;
    set_node *pSetNode;

    for (pSetNode = pNodes->pHead ;
	 ((pSetNode != NULL) && (!answer)) ;
	 pSetNode = pSetNode->pNext)

	answer = seq_equals(pSeq, ((ptnode *) (pSetNode->pData))->pSeq);

    return answer;
}


void ptarrow_add_seq(ptarrow *pArrow, ptree *pTree, seq *pSeq)
{
    ptnode *pNode;
    
    pNode = ptree_find_seq(pTree, pSeq);

    if (pNode != NULL)
	ptnode_set_push(pArrow->pProgeny, pNode);
    else
    {
	pNode = ptnode_make(pTree->genus, pSeq);
	ptnode_set_push(pArrow->pProgeny, pNode);
	ptnode_set_push(pTree->pNodes, pNode);
    }
}

void ptarrow_spawn(ptarrow *pArrow, ptree *pTree, t_set *pTset)
{
    if (pArrow->spawned == FALSE)
    {
	set_node *pSetNode;
	seq_set *pSeqSet;
	pArrow->spawned = TRUE;
	pSeqSet = seq_set_to_check(pTset, pArrow->pIncluded, pTree->genus);

	for (pSetNode = pSeqSet->pHead ;
	     pSetNode != NULL ;
	     pSetNode = pSetNode->pNext)

	    ptarrow_add_seq(pArrow, pTree, (seq *) (pSetNode->pData));

	seq_set_kill(pSeqSet);
    }
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
// CHECKING AND DYNAMIC CREATION ROUTINES
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

bool ptarrow_works(ptarrow *pArrow, ptree *pTree, divisor *pDiv, 
			     t_set *pTset)
{
    bool answer;
    set_node *pSetNode;

    switch (pArrow->status)
    {
	case YES:
	    printf("true from previous calculation.\n");
	    answer = TRUE;
	    break;
	case NO:
	    printf("false from previous calculation.\n");
	    answer = FALSE;
	    break;
	case MAYBE:

	    ptarrow_spawn(pArrow, pTree, pTset);

	    answer = TRUE; // set to true until something fails.

	    {	    
		set_node *pSetNode;
		for (pSetNode = pArrow->pProgeny->pHead ;
		     ((pSetNode != NULL) && (answer)) ;
		     pSetNode = pSetNode->pNext)
		    
		    answer = ptnode_works((ptnode *) (pSetNode->pData), 
					  pTree, pDiv);
	    }

	    if (answer)
		pArrow->status = YES;
	    else
		pArrow->status = NO;
	    break;
    }
    return answer;
}

bool ptnode_push_and_check(ptnode *pNode, ptree *pTree, divisor *pDiv, 
			     t_set *pTset, t_set *pIncluded)
{
    bool answer;
    ptarrow *pNewArrow;
    
    pNewArrow = ptarrow_make(pIncluded);

    if (!ptarrow_set_push(pNode->pArrows, pNewArrow))
    {
	answer = FALSE;
	ptarrow_kill(pNewArrow);
    }
    else
	answer = ptarrow_works(pNewArrow, pTree, pDiv, pTset);

    return answer;
}


bool ptnode_spawn_and_check(ptnode *pNode, ptree *pTree, divisor *pDiv)
{
    t_set *pTset;
    t_mlat *pMlat;
    bool answer = FALSE; // false until we find a good maximal
    
    set_node *pMlatNode;

    pTset = t_set_associated_to_seq(div_genus(pDiv), pNode->pSeq);
    pMlat = t_mlat_some_maximals(pDiv, pTset, pTree->pFdatum, 
				 seq_length(pNode->pSeq));

    for (pMlatNode = pMlat->pHead ;
	 ((pMlatNode != NULL) && (!answer)) ;
	 pMlatNode = pMlatNode->pNext)

	answer = ptnode_push_and_check(pNode, pTree, pDiv, pTset, 
				       (t_set *) (pMlatNode->pData));

    t_set_kill(pTset);
    mlat_kill(pMlat);

    return answer;
}


bool ptnode_arrow_valid(ptnode *pNode, ptarrow *pArrow, divisor *pDiv,
			fdata_list *pFdatum)
{
    bool answer;
    t_set *pTset;

    pTset = t_set_associated_to_seq(div_genus(pDiv), pNode->pSeq);

    answer =
	t_set_subset_some_applicable_formula_ok(pDiv, pTset, 
						pArrow->pIncluded, pFdatum,
						seq_length(pNode->pSeq));
    t_set_kill(pTset);

    return answer;
}

bool ptnode_works_small(ptnode *pNode, divisor *pDiv)
{
    bool answer;
    smallint a, z;

    a = seq_length(pNode->pSeq);
    z = div_genus(pDiv) - seq_sum(pNode->pSeq);

    if (a + z <= CURRENT_F_BOUND)
    {
	answer = TRUE;
    }
    else
	answer = FALSE;

    return answer;
}


bool ptnode_works(ptnode *pNode, ptree *pTree, divisor *pDiv)
{
    bool answer;

    switch (pNode->status)
    {
	case YES :
	    pTree->num_nodes_rechecked++;
	    answer = TRUE;
	    break;
	case NO :
	    answer = FALSE;
	    break;
	case MAYBE :
//	    medint_list_errdisplay(pNode->pSeq);
	    pTree->num_nodes_checked++;
	    if (ptnode_works_small(pNode, pDiv))
	    {
		answer = TRUE;
		pNode->status = YES;
	    }
	    else
	    {
		set_node *pSetNode;
		answer = FALSE; // false unless we find a good arrow.

		for (pSetNode = pNode->pArrows->pHead ;
		     ((pSetNode != NULL) && (!answer)) ;
		     pSetNode = pSetNode->pNext)
		{ // check current arrow.
		    bool valid;
		    t_set *pTset;
		    bool works = FALSE;
		    pTset = t_set_associated_to_seq
			(div_genus(pDiv), pNode->pSeq);
		    
		    valid = ptnode_arrow_valid(pNode, 
					       (ptarrow *) (pSetNode->pData), 
					       pDiv, pTree->pFdatum);
		    if (valid)
			works = ptarrow_works((ptarrow *) (pSetNode->pData), 
					      pTree, pDiv, pTset);

		    if (valid && works)
			answer = TRUE;
		    else
			answer = FALSE;

		    t_set_kill(pTset);
		}
		if (answer)
		    pNode->status = YES;
		else if (pTree->spawning)
		{
		    answer = ptnode_spawn_and_check(pNode, pTree, pDiv);
		    if (answer)
			pNode->status = YES;
		    else
			pNode->status = NO;
		}
		else
		{
		    pNode->status = NO;
		    answer = FALSE;
		}
	    }
	    break;
    }
    return answer;
}
