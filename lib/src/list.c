#include "list.h"

////////////////////////////////////////////
////////////////////////////////////////////
// LIST NODE STUFF
////////////////////////////////////////////
////////////////////////////////////////////

list_node *list_node_new(void *pData)
{
    list_node *pNewNode;

    pNewNode = (list_node *) malloc(sizeof(list_node));
    pNewNode->pData = pData;
    pNewNode->pPrev = NULL;
    pNewNode->pNext = NULL;

    return pNewNode;
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// LIST STUFF
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


list *list_new(bool (*compare_data)(void *, void *), 
	       void *(*copy_data)(void *), void (*destroy_data)(void *),
	       void (*display_list)(void *))
{
    list *pNewList;

    pNewList = (list *) malloc(sizeof(list));

    pNewList->pHead = NULL;
    pNewList->pTail = NULL;
    pNewList->compare_data = compare_data;
    pNewList->copy_data = copy_data;
    pNewList->destroy_data = destroy_data;
    pNewList->display_list = display_list;
    pNewList->length = 0;

    return pNewList;
}

void list_while_do(list *pList, char (*Condition)(void *),
		   void (*ActionFunction_of_data)(void *))
{
}

void list_do_each(list *pList, void (*ActionFunction)(void *))
{
    list_node *pCurrentNode;
 
    pCurrentNode = pList->pHead;
    if (!(list_length(pList) == 0))
    {
	ActionFunction(pCurrentNode->pData);
	while(pCurrentNode->pNext != NULL)
	{
	    pCurrentNode = pCurrentNode->pNext;
	    ActionFunction(pCurrentNode->pData);
	}
    }
}


void list_kill_each_if_helper(list *pList, list_node *pNode, 
			      bool (*condition)(void *))
{
    list_node *pNextNode;

    if (pNode != NULL)
    {
	pNextNode = pNode->pNext;

	if (condition(pNode->pData))
	{
	    list_kill_node(pList, pNode);
	    list_kill_each_if_helper(pList, pNextNode, condition);
	}

	else
	    list_kill_each_if_helper(pList, pNextNode, condition);
    }
}

void list_kill_each_if(list *pList, bool (*condition)(void *))
{
    if (list_length(pList) != 0)
	list_kill_each_if_helper(pList, list_head(pList), condition);
}


bool list_true_for_some(list *pList, bool (*condition)(void *))
{
    bool answer = FALSE;
    list_node *pCurrentNode;

    pCurrentNode = pList->pHead;
    if (!(list_length(pList) == 0))
    {
	answer = condition(pCurrentNode->pData);
	while((pCurrentNode->pNext != NULL) && (answer == FALSE))
	{
	    pCurrentNode = pCurrentNode->pNext;
	    answer = condition(pCurrentNode->pData);
	}
    }

    return answer;
}
    
bool list_true_for_all(list *pList, bool (*condition)(void *))
{
    bool answer = TRUE;
    list_node *pCurrentNode;

    pCurrentNode = pList->pHead;
    if (!(list_length(pList) == 0))
    {
	answer = condition(pCurrentNode->pData);
	while((pCurrentNode->pNext != NULL) && (answer == TRUE))
	{
	    pCurrentNode = pCurrentNode->pNext;
	    answer = condition(pCurrentNode->pData);
	}
    }

    return answer;
}
    
void list_debone(list *pList)
{
    list_node *pCurrentNode, *pNextNode;

    pCurrentNode = pList->pHead;
    while (pCurrentNode != NULL)
    {
	pNextNode = pCurrentNode->pNext;
	free(pCurrentNode);
	pCurrentNode = pNextNode;
    }
    free(pList);
}

void list_kill(list *pList)
{
    list_do_each(pList, pList->destroy_data);
    list_debone(pList);
}

list_node *list_kill_node(list *pList, list_node *pListNode)
{
    list_node *pNewNode;

    if (pListNode != NULL)
	pNewNode = pListNode->pNext;

    if (list_length(pList) != 0)
    {
	pList->destroy_data(pListNode->pData);
	if (pListNode->pPrev != NULL)
	    pListNode->pPrev->pNext = pListNode->pNext;
	else
	    pList->pHead = pListNode->pNext;
	if (pListNode->pNext != NULL)
	    pListNode->pNext->pPrev = pListNode->pPrev;
	else
	    pList->pTail = pListNode->pPrev;
	free(pListNode);
	pListNode = NULL;
	pList->length--;
    }
    return pNewNode;
}


void list_extract_node(list *pList, list_node *pListNode)
{
    if (list_length(pList) != 0)
    {
	if (pListNode->pPrev != NULL)
	    pListNode->pPrev->pNext = pListNode->pNext;
	else
	    pList->pHead = pListNode->pNext;
	if (pListNode->pNext != NULL)
	    pListNode->pNext->pPrev = pListNode->pPrev;
	else
	    pList->pTail = pListNode->pPrev;
	pList->length--;
    }
}


void list_push(list *pList, void *pData)
{
    list_node *pNewNode;
    pNewNode = list_node_new(pData);
    if (list_length(pList) == 0)
    {
	pList->pHead = pNewNode;
	pList->pTail = pNewNode;
	pList->length++;
    }
    else
    {
	pNewNode->pPrev = pList->pTail;
	pList->pTail->pNext = pNewNode;
	pList->pTail = pNewNode;
	pList->length++;
    }
}   

void list_push_before(list *pList, list_node *pListNode, void *pData)
{
    list_node *pNewNode;
    pNewNode = list_node_new(pData);
    if (list_node_is_head(pListNode))
    {
	pListNode->pPrev = pNewNode;
	pList->pHead = pNewNode;
	pNewNode->pNext = pListNode;
	pList->length++;
    }
    else
    {
	pNewNode->pNext = pListNode;
	pNewNode->pPrev = pListNode->pPrev;
	pListNode->pPrev->pNext = pNewNode;
	pListNode->pPrev = pNewNode;
	pList->length++;
    }
}   


void list_push_node(list *pList, list_node *pNode)
{
    if (list_length(pList) == 0)
    {
	pList->pHead = pNode;
	pList->pTail = pNode;
	pNode->pNext = NULL;
	pNode->pPrev = NULL;
	pList->length++;
    }
    else
    {
	pNode->pPrev = pList->pTail;
	pList->pTail->pNext = pNode;
	pNode->pNext = NULL;
	pList->pTail = pNode;
	pList->length++;
    }
}   

void list_push_head(list *pList, void *pData)
{
    list_node *pNewNode;
    pNewNode = list_node_new(pData);
    if (list_length(pList) == 0)
    {
	pList->pHead = pNewNode;
	pList->pTail = pNewNode;
	pList->length++;
    }
    else
    {
	pNewNode->pNext = pList->pHead;
	pList->pHead->pPrev = pNewNode;
	pList->pHead = pNewNode;
	pList->length++;
    }
}   


list *list_concat(list *pList1, list *pList2)
{
    list *pResult;

    if (list_empty(pList1))
    {
	list_kill(pList1);
	pResult = pList2;
    }
    else if (list_empty(pList2))
    {
	list_kill(pList2);
	pResult = pList1;
    }
    else
    {	
    pList1->pTail->pNext = pList2->pHead;
    pList2->pHead->pPrev = pList1->pTail;
    pList1->pTail = pList2->pTail;
    pList1->length = pList1->length + pList2->length;
    free(pList2);
    pResult = pList1;
    }

    return(pResult);
}

bool list_transfer(list *pList1, list *pList2)
{
    bool return_value;
    list_node *pNode;

    if (list_empty(pList2))
	return_value = FALSE;
    else
    {
	return_value = TRUE;
        pNode = list_head(pList2);
	list_extract_node(pList2, pNode);
	list_push_node(pList1, pNode);
    }
    return return_value;
}


list_node *list_get_node(list *pList, smallint i)
{
    smallint place;
    list_node *pNode;

    pNode = list_head(pList);

    for (place = 0; 
	 (place < i) && (place < (list_length(pList) - 1)); 
	 place++)
    {
	pNode = pNode->pNext;
    }

    return pNode;
}


list *list_complement(list *pList, smallint i)
{
    list_node *pNode;
    list *pComplement;

    pComplement = list_copy(pList);
    pNode = list_get_node(pComplement, i);

    list_kill_node(pComplement, pNode);

    return pComplement;
}


list *list_copy(list *pList)
{
    list *pCopy;
    list_node *pNode;

    pCopy = list_new(pList->compare_data, pList->copy_data, 
		     pList->destroy_data, pList->display_list);

    for (pNode = pList->pHead ; pNode != NULL ; pNode = pNode->pNext)
    {
	void *pDataCopy;
	pDataCopy = pList->copy_data(pNode->pData);
	list_push(pCopy, pDataCopy);
    }

    return pCopy;
}



void list_ordered_push(list *pList, void *pData, lessthan_order_type less_than)
{
    list_node *pLocationNode;
    
    if (list_empty(pList))
	list_push(pList, pData);
    else
    {
	pLocationNode = pList->pHead;
	while((less_than(pLocationNode->pData, pData)) &&
	      (!list_node_is_tail(pLocationNode)))
	    pLocationNode = pLocationNode->pNext;

	if ((list_node_is_tail(pLocationNode)) &&
	    (less_than(pLocationNode->pData, pData)))
	    list_push(pList, pData);
	else
	    list_push_before(pList, pLocationNode, pData);
    }
}


//////////////////////////////////////////////////////////////////////
// THESE ARE FUNCTIONS WHICH DO NOTHING BUT HAVE THE FORM OF THE
// STANDARD REQUIRED FUNCTIONS FOR MAKING LISTS. USE FOR LISTS WHEN
// FUNCTION IS NOT NEEDED.
//////////////////////////////////////////////////////////////////////
bool do_nothing_compare_data(void *a, void *b)
{
}

void *do_nothing_copy_data(void *a)
{
}

void do_nothing_destroy_data(void *a)
{
}

void do_nothing_display_list(void *l)
{
}


//////////////////////////////////////////////////////////////////////
// THE FOLLOWING ARE FOR CREATING META-LISTS. THESE ARE LISTS WHOSE
// DATA POINTER TARGETS ARE THEMSELVES LISTS. WE HAVE A COUPLE OF
// CHOICES OF HOW WE IMPLEMENT THESE.
//
// CONVENTIONS : 
//    -compare is do nothing
//    -display is list displays seperated by new lines.
//
// CHOICES :
//    1. TRUE METALISTS
//          -copy does list_copy
//          -destroy does list_kill
//
//    2. SHELL METALISTS
//          -copy does list_skeleton_copy
//          -destroy does list_debone
//////////////////////////////////////////////////////////////////////

void display_list_void(void *pList)
{
    list_display((list *) pList);
    printf("\n");
}

void display_meta_list_void(void *pMetaList)
{
    list_do_each((list *) pMetaList, display_list_void);
}

bool set_equals_void(void *pSet1, void *pSet2)
{
    return set_equals((set *) pSet1, (set *) pSet2);
}

////////////////////////////////////////////////////////////////
// TRUE METALISTS
////////////////////////////////////////////////////////////////

void list_kill_void(void *pList)
{
    list_kill((list *) pList);
}

void *list_copy_void(void *pList)
{
    list *pCopy;
    pCopy = list_copy((list *) pList);
    return pCopy;
}

list *metalist_new()
{
    list *pNewList;
    pNewList = list_new(set_equals_void, list_copy_void, 
			list_kill_void, display_meta_list_void);
    return pNewList;
}

void metalist_ordered_push(list *pMetaList, void *pList)
{
    list_node *pListLocationNode;
    
    if (list_empty(pMetaList))
	list_push(pMetaList, pList);
    else
    {
	pListLocationNode = pMetaList->pHead;
	while((list_length((list *) (pListLocationNode->pData)) <
	       list_length((list *) pList)) 
	      && 
	      (!list_node_is_tail(pListLocationNode)))
	    pListLocationNode = pListLocationNode->pNext;

	if ((list_node_is_tail(pListLocationNode))
	    &&
	    (list_length((list *) (pListLocationNode->pData)) <
	     list_length((list *) pList)))		
	    list_push(pMetaList, pList);

	else
	    list_push_before(pMetaList, pListLocationNode, pList);
    }
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// SET STUFF
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////         


bool set_is_member(set *pSet, void *pData)
{
    bool answer_so_far = FALSE;
    set_node *pNode;

    for (pNode = pSet->pHead ; 
	 ((pNode != NULL) && (answer_so_far == FALSE)) ;
	 pNode = pNode->pNext)

	if (pSet->compare_data(pNode->pData, pData))
	    answer_so_far = TRUE;
    
    return answer_so_far;
}


bool set_is_subset(set *pSet1, set *pSet2)
{
    bool answer_so_far = TRUE;
    set_node *pNode;
    
    for (pNode = pSet1->pHead ; 
	 ((pNode != NULL) && (answer_so_far == TRUE)) ;
	 pNode = pNode->pNext)

	if (!(set_is_member(pSet2, pNode->pData)))
	    answer_so_far = FALSE;
    
    return answer_so_far;
}


bool set_equals(set *pSet1, set *pSet2)
{
    bool answer;

    answer = ((set_is_subset(pSet1, pSet2)) && (set_is_subset(pSet2, pSet1)));

    return answer;
}


bool set_push(set *pSet, void *pData)
{
    bool result = TRUE;
    if (!(set_is_member(pSet, pData)))
	list_push(pSet, pData);
    else
	result = FALSE;

    return result;
}

bool set_ordered_push(set *pSet, void *pData, lessthan_order_type less_than)
{
    bool result = TRUE;
    if (!(set_is_member(pSet, pData)))
	list_ordered_push(pSet, pData, less_than);
    else
	result = FALSE;

    return result;
}

void set_remove_element(set *pSet, void *pElementData)
{
    set_node *pNode, *pNextNode;

    pNode = set_head(pSet);

    while (pNode != NULL)
    {
	if (set_compare_data(pSet, set_node_data(pNode), pElementData))
	{
	    pNextNode = set_node_next(pNode);
	    set_node_kill(pSet, pNode);
	    pNode = pNextNode;
	}
	else
	    pNode = set_node_next(pNode);
    }
}


set *set_subset_complement(set *pSet, set *pSubset)
{
    set *pComplement;

    set_node *pNode;

    pComplement = set_copy(pSet);

    for (pNode = pSubset->pHead ; 
	 pNode != NULL ;
	 pNode = pNode->pNext)
	
	set_remove_element(pComplement, pNode->pData);

    return pComplement;
}

set *set_empty_subset(set *pSet)
{
    set *pNew;

    pNew = set_new(pSet->compare_data, pSet->copy_data, pSet->destroy_data,
		   pSet->display_list);

    return pNew;
}

void set_powerset_helper(set *pPowerSet, set *pSet, set *pSubset)
{
    set *pSet2;
    set *pSubset2;

    if (set_empty(pSet))
    {
	// here we assume that there are no repeated elements.
	set_force_push(pPowerSet, pSubset);
	set_kill(pSet);
    }
    else
    {
	pSet2 = set_copy(pSet);
	pSubset2 = set_copy(pSubset);
	set_force_transfer(pSubset2, pSet2);
	set_powerset_helper(pPowerSet, pSet2, pSubset2);

	set_node_kill(pSet, set_head(pSet));
	set_powerset_helper(pPowerSet, pSet, pSubset);
    }
}


set *set_powerset(set *pSet)
{
    set *pPowerSet;
    set *pSubset;

    pPowerSet = metaset_new();
    pSubset = set_empty_subset(pSet);
    
    set_powerset_helper(pPowerSet, set_copy(pSet), pSubset);
    
    return pPowerSet;
}

void set_force_push_to_each(set *pSets, void *pData)
{
    set_node *pNodeOfSet;

    for (pNodeOfSet = pSets->pHead ; 
	 pNodeOfSet != NULL;
	 pNodeOfSet = pNodeOfSet->pNext)

	set_force_push((set *) (pNodeOfSet->pData), 
		       (((set *) (pNodeOfSet->pData))->copy_data)(pData));
}

set *set_subsets(set *pSet, smallint n)
{
    set *pSubsets;
    set *pCdr;
    set *pSomeSubsets;
    void *pHeadData;
    set_node *pHead;

    if (n == 0)
    {
	pSubsets = metaset_new();
	set_force_push(pSubsets, set_empty_subset(pSet));
    }
    else if (n > set_length(pSet))
    {
	pSubsets = metaset_new();
    }
    else
    {
	pCdr = set_copy(pSet);
	pHead = set_head(pCdr);
	pHeadData = (pSet->copy_data)(pHead->pData);
	list_kill_node(pCdr, pHead);

	pSomeSubsets = set_subsets(pCdr, n - 1);

	set_force_push_to_each(pSomeSubsets, pHeadData);

	pSubsets = set_concat(pSomeSubsets, set_subsets(pCdr, n));

	(pSet->destroy_data)(pHeadData);
	set_kill(pCdr);
    }
    return pSubsets;
}

bool set_subsets_true_for_some_helper(set **ppSubset, set *pSubset, set *pSet, 
				      bool (*condition)(set *, void *),
				      void *pData, smallint n)
{
    bool answer;
    set *pCdr;
    set *pSomeSubsets;
    void *pHeadData;
    set_node *pHead;

    if (n == 0)
    {
	if (condition(pSubset, pData))
	{
	    answer = TRUE;
	    *ppSubset = pSubset;
	}
	else
	{
	    answer = FALSE;
	    set_kill(pSubset);
	}
    }
    else if (n > set_length(pSet))
    {
	answer = FALSE;
	set_kill(pSubset);
    }
    else
    {
	pCdr = set_copy(pSet);	
	pHead = set_head(pCdr);
	pHeadData = (pSet->copy_data)(pHead->pData);
	list_kill_node(pCdr, pHead);


	if (set_subsets_true_for_some_helper(ppSubset, set_copy(pSubset), 
					     pCdr, condition, pData, n))
	{
	    answer = TRUE;
	    (pSet->destroy_data)(pHeadData);
	}
	else
	{
	    set_force_push(pSubset, pHeadData);
	    answer = set_subsets_true_for_some_helper(ppSubset, 
						      set_copy(pSubset), pCdr,
						      condition, pData, n - 1);
	}
	set_kill(pCdr);
	set_kill(pSubset);
    }
    return answer;
}

bool set_subsets_true_for_some(set **ppSubset, set *pSet, 
			       bool (*condition)(set *, void *pData), 
			       void *pData, smallint n)
{
    set *pSubset;
    bool answer;
    pSubset = set_empty_subset(pSet);
    answer = set_subsets_true_for_some_helper(ppSubset, pSubset, pSet, 
					      condition, pData, n);
    return answer;
}

bool set_maximal_subset(set **ppSubset, set *pSet,
			bool (*condition)(set *pSubset, void *pData), 
			void *pData, int limit)
{
    bool found_one = FALSE;
    smallint n;

    for (n = set_length(pSet) ; ((n >= (set_length(pSet) - limit)) && 
				 (!found_one)) ; n--)
	found_one = 
	    set_subsets_true_for_some(ppSubset, pSet, condition, pData, n);

    for (n = limit ; ((n >= 0) && (!found_one)) ; n--)
	found_one = 
	    set_subsets_true_for_some(ppSubset, pSet, condition, pData, n);
    return found_one;

}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// MAXIMAL LATTICE STUFF
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////         


bool mlat_is_dominated(mlat *pMlat, set *pSet)
{
    bool answer = FALSE;

    mlat_node *pMNode;

    for (pMNode = pMlat->pHead ;
	 ((pMNode != NULL) && (answer == FALSE)) ;
	 pMNode = pMNode->pNext)

	if (set_is_subset(pSet, (set *) (pMNode->pData)))
	    answer = TRUE;

    return answer;
}

bool mlat_push(mlat *pMlat, set *pData)
{
    bool success = TRUE;
    if (!mlat_is_dominated(pMlat, pData))
	list_push(pMlat, pData);
    else
	success = FALSE;
    return success;
}


mlat *mlat_generate(set *pSet, void *pData,
		    bool (*condition)(set *pSubset, void *pData))
{
    smallint n;
    mlat *pMlat;
    set *pSubsets;
    set_node *pSubsetNode;

    pMlat = mlat_new();

    for (n = set_length(pSet) ; n >= 0 ; n--)
    {
	pSubsets = set_subsets(pSet, n);
	if (!set_empty(pSubsets))
	    for (pSubsetNode = set_head(pSubsets) ;
		 pSubsetNode != NULL ; 
		 pSubsetNode = pSubsetNode->pNext)
		if (!mlat_is_dominated(pMlat, (set *) pSubsetNode->pData))
		{
		    if (condition((set *) pSubsetNode->pData, pData))
			mlat_force_push(pMlat, 
					set_copy((set *) pSubsetNode->pData));
		}
	set_kill(pSubsets);
    }

    return pMlat;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// MULTISET STUFF
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////         


medint multiset_is_member(multiset *pMultiset, void *pData)
{
    medint answer_so_far = 0;
    
    list_node *pNode;

    for (pNode = pMultiset->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)

	if (pMultiset->compare_data(pData, pNode->pData))
	    answer_so_far++;

    return answer_so_far;
}


bool multiset_is_submultiset(multiset *pMultiset1, multiset *pMultiset2)
{
    bool answer_so_far = TRUE;
    list_node *pNode;

    for (pNode = pMultiset1->pHead ;
	 ((pNode != NULL) && (answer_so_far == TRUE)) ;
	 pNode = pNode->pNext)
	
	if ((multiset_is_member(pMultiset2, pNode->pData)) <
	    (multiset_is_member(pMultiset1, pNode->pData)))
	    answer_so_far = FALSE;
    
    return answer_so_far;
}


bool multiset_equals(multiset *pMultiset1, multiset *pMultiset2)
{
    bool answer;

    answer = ((multiset_is_submultiset(pMultiset1, pMultiset2)) && 
	      (multiset_is_submultiset(pMultiset2, pMultiset1)));

    return answer;
}


void multiset_remove_element(multiset *pMultiset, void *pElementData)
{
    multiset_node *pNode, *pNextNode;
    bool done = FALSE;
    pNode = multiset_head(pMultiset);

    while (!done)
    {
	if (multiset_compare_data(pMultiset, multiset_node_data(pNode), 
				  pElementData))
	{
	    pNextNode = multiset_node_next(pNode);
	    multiset_node_kill(pMultiset, pNode);
	    done = TRUE;
	}
	else
	    pNode = multiset_node_next(pNode);
    }
}


multiset *multiset_submultiset_complement(multiset *pMultiset, 
					  multiset *pSubmultiset)
{
    multiset *pComplement;
    list_node *pNode;

    pComplement = multiset_copy(pMultiset);

    for (pNode = pSubmultiset->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)

	multiset_remove_element(pComplement, pNode->pData);

    return pComplement;
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// METAMULTISET STUFF
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

bool multiset_equals_void(void *pMultiset1, void *pMultiset2)
{
    return multiset_equals((multiset *) pMultiset1, (multiset *) pMultiset2);
}

set *metamultiset_new()
{
    return list_new(multiset_equals_void, list_copy_void, list_kill_void,
		    display_meta_list_void);
}


void multiset_powerset_helper(set *pPowerSet, multiset *pMultiset, 
			      multiset *pSubmultiset)
{
    multiset *pMultiset2;
    multiset *pSubmultiset2;

    if (multiset_empty(pMultiset))
    {
	if (!set_push(pPowerSet, pSubmultiset))
	    multiset_kill(pSubmultiset);
	multiset_kill(pMultiset);
    }
    else
    {
	pMultiset2 = multiset_copy(pMultiset);
	pSubmultiset2 = multiset_copy(pSubmultiset);
	multiset_transfer(pSubmultiset2, pMultiset2);
	multiset_powerset_helper(pPowerSet, pMultiset2, pSubmultiset2);

	multiset_node_kill(pMultiset, multiset_head(pMultiset));
	multiset_powerset_helper(pPowerSet, pMultiset, pSubmultiset);
    }
}


set *multiset_powerset(multiset *pMultiset)
{
    set *pPowerSet;
    multiset *pSubmultiset;
    
    pPowerSet = metamultiset_new();
    pSubmultiset = multiset_empty_submultiset(pMultiset);
    
    multiset_powerset_helper(pPowerSet, multiset_copy(pMultiset), 
			     pSubmultiset);
	
    return pPowerSet;
}

void multiset_subsets_helper(set *pSubsets, multiset *pMultiset, 
			      multiset *pSubmultiset, smallint size)
{
    multiset *pMultiset2;
    multiset *pSubmultiset2;

    if (multiset_empty(pMultiset))
    {
	if (multiset_length(pSubmultiset) != size)
	    multiset_kill(pSubmultiset);
	else if (!set_push(pSubsets, pSubmultiset))
	    multiset_kill(pSubmultiset);
	multiset_kill(pMultiset);
    }
    else
    {
	if (multiset_length(pSubmultiset) < size)
	{
	    pMultiset2 = multiset_copy(pMultiset);
	    pSubmultiset2 = multiset_copy(pSubmultiset);
	    multiset_transfer(pSubmultiset2, pMultiset2);
	    multiset_subsets_helper(pSubsets, pMultiset2, pSubmultiset2, size);
	}

	multiset_node_kill(pMultiset, multiset_head(pMultiset));
	multiset_subsets_helper(pSubsets, pMultiset, pSubmultiset, size);
    }
}


set *multiset_subsets(multiset *pMultiset, smallint size)
{
    set *pSubsets;
    multiset *pSubmultiset;
    
    pSubsets = metamultiset_new();
    pSubmultiset = multiset_empty_submultiset(pMultiset);
    
    multiset_subsets_helper(pSubsets, multiset_copy(pMultiset), 
			     pSubmultiset, size);

    return pSubsets;
}




/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// LINE STUFF
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


line *line_new(smallint maxlength)
{
    line *pNewLine;

    pNewLine = (line *) malloc(sizeof(line));
    pNewLine->data = (medint *) calloc(sizeof(medint), maxlength);
    pNewLine->length = 0;
    pNewLine->maxlength = maxlength;

    return pNewLine;
}


void line_kill(line *pLine)
{
    free(pLine->data);
    free(pLine);
}


medint __line_data_error_()
{
    printf("can't read past end of line!\n");
    return 0;
}


/////////////////////////////////////////////////////////////////////////
// pushes data to the end of list.
/////////////////////////////////////////////////////////////////////////
void line_push(line *pLine, medint d)
{
    if (line_length(pLine) < line_maxlength(pLine))
    {
	(pLine->data)[line_length(pLine)] = d;
	pLine->length++;
    }
    else
	printf("can't push to line - line is full.\n");
}


void line_display(line *pLine)
{
    smallint counter;

    for (counter = 0 ; counter < (line_length(pLine) - 1) ; counter++)
	printf("%3d ", line_data(pLine, counter));

    printf("%3d", line_data(pLine, line_length(pLine) - 1 ));
}

void line_display_file(FILE *outfile, line *pLine)
{
    smallint counter;

    for (counter = 0 ; counter < (line_length(pLine) - 1) ; counter++)
	fprintf(outfile, "%3d ", line_data(pLine, counter));

    fprintf(outfile, "%3d", line_data(pLine, line_length(pLine) - 1 ));
}


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
// MEDINT LISTS
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

medint *medint_new()
{
    medint *pNew; 
    pNew = (medint *) malloc(sizeof(medint));
    return pNew;
}

bool medint_compare_void(void *pNum1, void *pNum2)
{
    bool answer;
    answer = (*((medint *) pNum1) == *((medint *) pNum2)) ? TRUE : FALSE;
    return answer;
}

void *medint_copy_void(void *pNum)
{
    medint *pCopy;
    pCopy = medint_new();
    *pCopy = *((medint *) pNum);
    return pCopy;
}

void medint_destroy(void *pNum)
{
    medint *pMNum;
    if (pNum != NULL)
    {
	pMNum = (medint *) pNum;
	free(pMNum);
    }
}

void medint_display(void *pNum)
{
    printf("%d ", *((medint *) pNum));
}

void medint_errdisplay(void *pNum)
{
    fprintf(stderr, "%d ", *((medint *) pNum));
}

void medint_list_display(void *pList)
{
    printf("[");
    if (list_length((list *) pList) == 0)
	printf("EMPTY ");
    else
	list_do_each(pList, medint_display);
    printf("\b]");
}

void medint_list_errdisplay(list *pList)
{
    fprintf(stderr, "[");
    if (list_length(pList) == 0)
	fprintf(stderr, "EMPTY ");
    else
	list_do_each(pList, medint_errdisplay);
    fprintf(stderr, "\b]");
}

list *medint_list_new()
{
    list *pNewList;

    pNewList = list_new(medint_compare_void, medint_copy_void, medint_destroy,
			medint_list_display);

    return pNewList;
}

medint medint_list_sum(list *pList)
{
    medint answer;

    list_node *pNode;

    answer = 0;

    for (pNode = pList->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)

	answer += *((medint *) (pNode->pData));

    return answer;
}

list *medint_list_read(char *s)
{
    list *pNew;
    pNew = medint_list_new();

    while (s[0] != '\0')
    {
	medint *m;
	int i;
	
	for(i = 0 ; ((('0' <= s[i]) && ('9' >= s[i])) || (s[i] == '-')) ;
	    i++);

	
	m = medint_new();
	*m = atoi(s);

	list_push(pNew, m);
	s = &(s[i+1]);
    }

    return pNew;
}
