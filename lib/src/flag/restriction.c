#include "restriction.h"

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
// SEQUENCES
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

seq *seq_associated_to_triple(triple *pTriple)
{
    seq *pSeq;
    medint *pCurrent_entry;
    medint *pLast_entry;
    list_node *pNode;

    pSeq = seq_new();

    for (pNode = (triple_Bc(pTriple))->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
    {
	pCurrent_entry = (medint *) medint_copy(pNode->pData);
	multiset_push(pSeq, pCurrent_entry);
    }
 
    pLast_entry = medint_new();
    *pLast_entry = 
	triple_y(pTriple) + medint_list_sum(triple_B(pTriple));
    
    multiset_push(pSeq, pLast_entry);

    return pSeq;
}

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
// SEQUENCE SETS
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

bool seq_equals_void(void *pS1, void *pS2)
{
    return seq_equals((seq *) pS1, (seq *) pS2);
}


seq_set *seq_set_new()
{
    seq_set *pNewSeqSet;

    pNewSeqSet = metalist_new();
    pNewSeqSet->compare_data = seq_equals_void;

    return pNewSeqSet;
}


seq_set *seq_set_associated_to_t_set(t_set *pTset)
{
    seq_set *pSeqSet;

    set_node *pNode;

    pSeqSet = seq_set_new();
    
    for (pNode = pTset->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
    {
	seq *pSeq;
	pSeq = seq_associated_to_triple((triple *) (pNode->pData));
	if (!seq_set_push(pSeqSet, pSeq))
	    seq_kill(pSeq);
    }

    return pSeqSet;
}




/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
// TRIPLES
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

triple *triple_makeAB(smallint genus, smallint y, seq *pA, seq *pB) 
{
    triple *pNewTriple;
    pNewTriple = (triple *) malloc(sizeof(triple));
    pNewTriple->pB = seq_copy(pB);
    pNewTriple->pBc = seq_subseq_complement(pA, pB);
    pNewTriple->g = genus;
    pNewTriple->y = y;
    pNewTriple->z = genus - seq_sum(pA);

    return pNewTriple;
}


triple *triple_makeBBc(smallint genus, smallint y, seq *pB, seq *pBc) 
{
    triple *pNewTriple;
    pNewTriple = (triple *) malloc(sizeof(triple));
    pNewTriple->pB = seq_copy(pB);
    pNewTriple->pBc = seq_copy(pBc);
    pNewTriple->g = genus;
    pNewTriple->y = y;
    pNewTriple->z = genus - seq_sum(pB) - seq_sum(pBc);
    
    return pNewTriple;
}


void triple_display(triple *pT)
{
    printf("\n");
    printf("B = ");
    seq_display(pT->pB);
    printf("\n");
    printf("Bc = ");
    seq_display(pT->pBc);
    printf("\ny = %d\n", pT->y);
}

void triple_kill(triple *pT)
{
    seq_kill(pT->pB);
    seq_kill(pT->pBc);
    free(pT);
}


/////////////////////////////////////////////////////////////
// TRIPLE SETS
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

bool t_eq(void *pTrip1, void *pTrip2)
{
    bool answer = FALSE;
    triple *pT1, *pT2;

    pT1 = (triple *) pTrip1;
    pT2 = (triple *) pTrip2;
	
    if (pT1->y == pT2->y)
    {
	if (!seq_equals(pT1->pB, pT2->pB))
	    answer = FALSE;
	else if (!seq_equals(pT1->pBc, pT2->pBc))
	    answer = FALSE;
	else
	    answer = TRUE;
    }
    
    if (pT1->y == (pT2->z - pT2->y))
    {
	if (!seq_equals(pT1->pB, 
			 pT2->pBc))
	    answer = FALSE;
	else if (!seq_equals(pT1->pBc, 
			     pT2->pB))
	    answer = FALSE;
	else
	    answer = TRUE;
    }

    return answer;
}

void *t_copy(void *pTrip)
{
    triple *pCopy;
    triple *pT;
    pT = (triple *) pTrip;

    pCopy = triple_makeBBc(pT->g, pT->y, pT->pB, pT->pBc);

    return pCopy;
}

void t_destroy(void *pT)
{
    seq_kill(((triple *) pT)->pB);
    seq_kill(((triple *) pT)->pBc);
    free(pT);
}

void t_display(void *pT)
{
    printf("\n");
    printf("B = ");
    seq_display(((triple *) pT)->pB);
    printf("\n");
    printf("Bc = ");
    seq_display(((triple *) pT)->pBc);
    printf("\ny = %d\n", ((triple *) pT)->y);
}


void t_set_display_void_(void *pTset)
{
    printf("\n-------------------");
    t_set_do_each((t_set *) pTset, t_display);
    printf("-------------------\n");
}

t_set *t_set_complementary_pairs(t_set *pTset, smallint genus)
{
    t_set *pComplement;
    set_node *pNode;
    
    pComplement = t_set_new();

    // push complementary pairs
    for (pNode = pTset->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
    {
	triple *pTrip1, *pTrip2;
	
	pTrip1 = triple_copy((triple *) (pNode->pData));
	if (!t_set_push(pComplement, pTrip1))
	    triple_kill(pTrip1);
	
	pTrip2 = triple_complementary((triple *) (pNode->pData));
	if (!t_set_push(pComplement, pTrip2))
	    triple_kill(pTrip2);
    }
    
    return pComplement;
}

t_set *t_set_associated_to_seq(smallint genus, seq *pSeq) 
{
    t_set *pTset;

    // s is the size of the set indexing the boundary component.
    smallint a, z, s, y;

    a = seq_length(pSeq);
    z = genus - seq_sum(pSeq);
    pTset = t_set_new();

    if (z >= 2)
    {
	for (s = 2 ; s <= (a + z) / 2 ; s++)
	    for (y = 0 ; y <= min(z, s) ; y++)
	    {
		seq_set *pSeqs;
		seq_node *pNode;
		pSeqs = seq_subseqs(pSeq, s - y);
		for (pNode = pSeqs->pHead ;
		     pNode != NULL ;
		     pNode = pNode->pNext)
		{
		    bool answer;
		    triple *pT;
		    pT = triple_makeAB(genus, y, pSeq, (seq *) (pNode->pData));
		    if (!(answer = t_set_push(pTset, pT)))
			triple_kill(pT);
		}
		seq_set_kill(pSeqs);
	    }
    }
    
    return pTset;
}

seq_set *seq_set_to_check(t_set *pTset, t_set *pIncluded, smallint genus)
{
    t_set *pT_complement;
    t_set *pFullTset;
    seq_set *pSeqSet;
    
    pT_complement = t_set_subset_complement(pTset, pIncluded);
    pFullTset = t_set_complementary_pairs(pT_complement, genus);
    pSeqSet = seq_set_associated_to_t_set(pFullTset);

    t_set_kill(pFullTset);
    t_set_kill(pT_complement);

    return pSeqSet;
}

smallint t_set_maximum_complementary_length(smallint t_set_length)
{
    double floating_length;
    smallint max;

    if (t_set_length > 10)
    {
	floating_length = (double) t_set_length;
	max = (5.0 / (log(floating_length)));
//	printf("maximum is %d\n(log was %f)\n", max, 
//  	       natural_log(floating_length));
// 	fflush(stdout);
    }
    else
	max = t_set_length;
    return max;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// FORMULA DATA
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

fdata *fdata_make_0(char label[], formula_0_type formula_0, 
			   formula_condition_type condition)
{
    fdata *pFdata;
    pFdata = (fdata *) malloc(sizeof(fdata));
    sscanf(label, "%s", pFdata->label);
    pFdata->type = '0';
    pFdata->formula_0 = formula_0;
    pFdata->condition = condition;
    return pFdata;
}

fdata *fdata_make_c(char label[], formula_c_type formula_c, 
			   formula_condition_type condition)
{
    fdata *pFdata;
    pFdata = (fdata *) malloc(sizeof(fdata));
    sscanf(label, "%s", pFdata->label);
    pFdata->type = 'c';
    pFdata->formula_c = formula_c;
    pFdata->condition = condition;
    return pFdata;
}


fdata *fdata_copy(fdata *pFdata)
{
    fdata *pCopy;
    if (pFdata->type == '0')
	pCopy = fdata_make_0(pFdata->label, 
			     pFdata->formula_0, pFdata->condition);
    else
	pCopy = fdata_make_c(pFdata->label,
			     pFdata->formula_c, pFdata->condition);
    return pCopy;
}

void fdata_kill(fdata *pFdata)
{
    free(pFdata);
}

bool fdata_equals(fdata *pFdata1, fdata *pFdata2)
{
    bool answer;

    if ((pFdata1->type == pFdata2->type) &&
	(pFdata1->condition == pFdata2->condition))
    {
	if (pFdata1->type == 'c')
	{
	    if (pFdata1->formula_c == pFdata2->formula_c)
		answer = TRUE;
	    else
		answer = FALSE;
	}
	else
	{
	    if (pFdata1->formula_0 == pFdata2->formula_0)
		answer = TRUE;
	    else
		answer = FALSE;
	}
    }
    else
	answer = FALSE;

    return answer;
}

void fdata_display(fdata *pFdata)
{
    int formula;
    char type;
    printf("%s %c", pFdata->label, pFdata->type);
}

void fdata_display_file(FILE *outfile, fdata *pFdata)
{
    int formula;
    char type;
    fprintf(outfile, "%s %c", pFdata->label, pFdata->type);
}





//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// FORMULA DATA LISTS
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

bool trivial_condition(divisor *pDiv, t_set *pTset)
{
    return TRUE;
}

void fdata_destroy(void *a)
{
    fdata *pFdata;
    pFdata = (fdata *) a;
    free(pFdata);
}

void *fdata_copy_void(void *pFdata)
{
    return fdata_copy((fdata *) pFdata);
}

void fdata_display_list_void(void *pFdata_list)
{
    list_node *pNode;

    for (pNode = ((fdata_list *) pFdata_list)->pHead ;
	 pNode != NULL;
	 pNode = pNode->pNext)

	fdata_display((fdata *) (pNode->pData));

    printf("\n");
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// TOOLS FOR 0 FORMULAS
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

bool formula_nonnegative(divisor *pDiv, t_set *pTset, formula_0_type formula)
{
    bool answer;
    set_node *pNode;

    if (t_set_empty(pTset))
	answer = TRUE;
    else
    {
	answer = TRUE;
	for (pNode = pTset->pHead;
	     ((pNode != NULL) && (answer));
	     pNode = pNode->pNext)
	{
	    bz_t *pFormula;
	    pFormula = formula(pDiv, (triple *) (pNode->pData));
	    answer = bz_is_nonnegative(pFormula);
	    bz_kill(pFormula);
	}
    }
    return answer;
}



t_set *zero_triples(divisor *pDiv, t_set *pTset, formula_0_type formula)
{
    t_set *pResult;
    set_node *pNode;

    pResult = t_set_new();

    for (pNode = pTset->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
    {
	bz_t *pSbig;
	pSbig = formula(pDiv, (triple *) (pNode->pData));
	if (bz_is_zero(pSbig))
	    t_set_push(pResult, triple_copy((triple *) (pNode->pData)));
	bz_kill(pSbig);
    }

    return pResult;
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// TOOLS FOR C FORMULAS
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

binterval *included_triples_interval(divisor *pDiv, t_set *pIncluded_Triples,
				     formula_c_type formula)
{
    binterval *pIntersection;
    set_node *pNode;
    pIntersection = binterval_positive_axis();

    for (pNode = pIncluded_Triples->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
    {
	bfunctiontype *pFormula;
	binterval *pCurrentInterval, *pNextInterval;
	if (!binterval_empty(pIntersection))
	{
	    pFormula = formula(pDiv, (triple *) (pNode->pData)); 
	    pCurrentInterval = binterval_solve_zero_one(pFormula);
	    bform_kill(pFormula);
	    
	    pNextInterval = binterval_intersect(pCurrentInterval, 
						pIntersection);
	    binterval_kill(pIntersection);
	    binterval_kill(pCurrentInterval);
	    pIntersection = pNextInterval;
	}
	
    }
    
    return pIntersection;
}
		    


binterval *included_triple_interval(divisor *pDiv, triple *pT,
				    formula_c_type formula)
{
    set_node *pNode;
    binterval *pInterval;

    bfunctiontype *pFormula;
    pFormula = formula(pDiv, pT); 
    pInterval = binterval_solve_zero_one(pFormula);
    bform_kill(pFormula);
    
    return pInterval;
}
		    

binterval *positive_triple_interval(divisor *pDiv, triple *pT,
				    formula_c_type formula)
{
    set_node *pNode;
    binterval *pInterval;

    bfunctiontype *pFormula;
    pFormula = formula(pDiv, pT); 
    pInterval = binterval_solve_positive(pFormula);
    bform_kill(pFormula);
    
    return pInterval;
}
		    
void coeff_display_everything(divisor *pDiv, triple *pT, 
			      formula_c_type formula, bq_t *pX)
{
    bfunctiontype *pFunction;
    binterval *pInterval;

    triple_display(pT);

    printf("\nformula : ");
    pFunction = formula(pDiv, pT);
    bform_display(pFunction);

    if (pX != NULL)
    {
	bq_t *pVal;
	printf("\nformula at x = ");
	fflush(stdout);
	bq_display(pX);
	fflush(stdout);
	printf(" is ");
	pVal = bform_eval(pFunction, pX);
	bq_display(pVal);
	bq_kill(pVal);
    }

    bform_kill(pFunction);

    printf("\nzero-one interval : ");
    pInterval = included_triple_interval(pDiv, pT, formula);
    binterval_display(pInterval);
    binterval_kill(pInterval);
    printf("\npositive interval : ");
    pInterval = positive_triple_interval(pDiv, pT, formula);
    binterval_display(pInterval);
    fflush(stdout);
    binterval_kill(pInterval);
    printf("\n");
    fflush(stdout);
}

void coeffs_display_everything(divisor *pDiv, t_set *pTset, 
			      formula_c_type formula, bq_t *pX)
{
    set_node *pNode;

    for (pNode = pTset->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
	coeff_display_everything(pDiv, (triple *) (pNode->pData), formula, pX);
}


binterval *positive_triples_interval(divisor *pDiv, t_set *pTriples, 
				     formula_c_type formula)
{
    binterval *pIntersection;
    set_node *pNode;
    pIntersection = binterval_positive_axis();

    for (pNode = pTriples->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
    {
	bfunctiontype *pFormula;
	binterval *pCurrentInterval, *pNextInterval;
	
	if (!binterval_empty(pIntersection))
	{
	    pFormula = formula(pDiv, (triple *) (pNode->pData)); 
	    
	    pCurrentInterval = binterval_solve_positive(pFormula);
	    
	    pNextInterval = binterval_intersect(pCurrentInterval, 
						pIntersection);
	    
	    binterval_kill(pIntersection);
	    binterval_kill(pCurrentInterval);
	    pIntersection = pNextInterval;
	    bform_kill(pFormula);
	}
    }
    
    return pIntersection;
}


bool positive_triples_interval_is_empty(divisor *pDiv, t_set *pTriples, 
					formula_c_type formula)
{
    bool answer;
    binterval *pPosInterval;
    pPosInterval = positive_triples_interval(pDiv, pTriples, formula);
    answer = binterval_empty(pPosInterval);
    binterval_kill(pPosInterval);
    return answer;
}




///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// TRIPLE SET STUFF
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

// assumes the formula's condition is satisfied.
// to save time, we generally run this only on 'applicable' formulas.
// for 'c' formulas, this means that the positive interval is nonempty,
// and for '0' formulas, this means that it is nonnegative. 
bool t_set_subset_formula_ok(divisor *pDiv, t_set *pTset, 
			     t_set *pIncluded_Triples, fdata *pFdata)
{
    bool answer;

    if (pFdata->type == 'c')
    {
	binterval *pPosInterval, *p01Interval, *pIntersection;
	
	pPosInterval = 
	    positive_triples_interval(pDiv, pTset, pFdata->formula_c);
	
	p01Interval =
	    included_triples_interval(pDiv, pIncluded_Triples, 
				      pFdata->formula_c);
	
	pIntersection = binterval_intersect(pPosInterval, p01Interval);

	binterval_kill(pPosInterval);
	binterval_kill(p01Interval);

	answer = (!binterval_empty(pIntersection));

	binterval_kill(pIntersection);
    }

    else if (pFdata->type == '0')
    {
	if (formula_nonnegative(pDiv, pTset, pFdata->formula_0))
	{
	    t_set *pZeroTriples;

	    pZeroTriples = zero_triples(pDiv, pTset, pFdata->formula_0);

	    answer = t_set_is_subset(pIncluded_Triples, pZeroTriples);

	    t_set_kill(pZeroTriples);
	}
    }
    
    return answer;
}

binterval *t_set_subset_formula_c_interval(divisor *pDiv, t_set *pTset, 
					   t_set *pIncluded_Triples, 
					   fdata *pFdata)
{
    bool answer;
    binterval *pPosInterval, *p01Interval, *pIntersection;
    
    pPosInterval = 
	positive_triples_interval(pDiv, pTset, pFdata->formula_c);
    
    p01Interval =
	included_triples_interval(pDiv, pIncluded_Triples, 
				  pFdata->formula_c);
    
    pIntersection = binterval_intersect(pPosInterval, p01Interval);
    
    binterval_kill(pPosInterval);
    binterval_kill(p01Interval);
    
    answer = (!binterval_empty(pIntersection));
    
    return pIntersection;
}



bool t_set_subset_some_formula_ok(divisor *pDiv, t_set *pTset, 
				  t_set *pIncluded_Triples, 
				  fdata_list *pFdataList)
{
    bool answer = FALSE;
    list_node *pNode;
    
    for (pNode = pFdataList->pHead ;
	 ((pNode != NULL) && (!answer)) ;
	 pNode = pNode->pNext)

	answer = 
	    t_set_subset_formula_ok(pDiv, pTset, pIncluded_Triples, 
				    (fdata *) (pNode->pData));

    return answer;
}


bool t_set_subset_some_applicable_formula_ok(divisor *pDiv, t_set *pTset, 
					     t_set *pIncluded_Triples, 
					     fdata_list *pFdataList,
					     smallint a)
{
    fdata_list *pFdataApp;
    bool answer;

    pFdataApp = fdata_list_applicable_formulas(pDiv, pTset, pFdataList, a);
    
    answer = t_set_subset_some_formula_ok(pDiv, pTset, pIncluded_Triples,
					  pFdataApp);
    fdata_list_kill(pFdataApp);


    return answer;
;}
					       

bool fdata_negative(divisor *pDiv, t_set *pTset, fdata *pFdata)
{
    bool answer;

    if (pFdata->type == 'c')
	answer = positive_triples_interval_is_empty(pDiv, pTset, 
						    pFdata->formula_c);
    else if (pFdata->type == '0')
	answer = (!formula_nonnegative(pDiv, pTset, pFdata->formula_0));

    return answer;
}

fdata_list *fdata_list_applicable_formulas(divisor *pDiv, t_set *pTset,
					   fdata_list *pFdataList, smallint a)
{
    fdata_list *pFdatumApplicable;
    list_node *pNode;

    pFdatumApplicable = fdata_list_new();
    for (pNode = pFdataList->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
    {
	bool fail;
	fail = ((!((fdata *) (pNode->pData))->condition(a)) ||
		fdata_negative(pDiv, pTset, (fdata *) (pNode->pData)));
	if (!fail)
	    fdata_list_push(pFdatumApplicable, 
			    pFdatumApplicable->copy_data(pNode->pData));
    }
    
    return pFdatumApplicable;
}

typedef struct t_maxl_data_t {
    divisor *pDiv;
    t_set *pTset;
    t_set *pTsubset;
    fdata_list *pFdatum;
} t_maxl_data_t;

t_maxl_data_t *t_maxl_data_new(divisor *pDiv, t_set *pTset, 
			       fdata_list *pFdatum)
{
    t_maxl_data_t *pData;
    pData = (t_maxl_data_t *) malloc(sizeof(t_maxl_data_t));
    pData->pDiv = pDiv;
    pData->pTset = pTset;
    pData->pFdatum = pFdatum;
    return pData;
}

void t_maxl_data_free(t_maxl_data_t *pData)
{
    free(pData);
}

bool t_set_subset_ok(t_set *pTsubset, void *pMaxlData)
{
    bool answer;
    t_maxl_data_t *pData;
    pData = (t_maxl_data_t *) pMaxlData;
    answer = t_set_subset_some_formula_ok(pData->pDiv, pData->pTset, 
					  pTsubset,
					  pData->pFdatum);
    return answer;
}
    


t_mlat *t_mlat_some_maximals(divisor *pDiv, t_set *pTset, fdata_list *pFdatum,
			     smallint a)
{
    fdata_list *pFdatumApplicable;
    t_mlat *pNewTMlat;
    t_set *pSubset;
    t_maxl_data_t *pMaxlData;

    pNewTMlat = mlat_new();

    pFdatumApplicable = 
	fdata_list_applicable_formulas(pDiv, pTset, pFdatum, a);
    pMaxlData = t_maxl_data_new(pDiv, pTset, pFdatumApplicable);

    if (!fdata_list_empty(pFdatumApplicable))
    {
	if (set_maximal_subset(&pSubset, pTset, t_set_subset_ok, pMaxlData,
			       t_set_maximum_complementary_length
			       (t_set_length(pTset))))
	{
	    if (!mlat_push(pNewTMlat, pSubset))
		t_set_kill(pSubset);
	}


    }
	    
    fdata_list_kill(pFdatumApplicable);

    return pNewTMlat;    
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//
//  SPECIFIC FORMULAS:
//
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

#include "specific_declarations.c"
