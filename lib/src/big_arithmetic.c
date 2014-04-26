#include "big_arithmetic.h"

/////////////////////////////////////////////////////////////////////////
//   BASEINT FUNCTIONS -- NEED TO BE CHANGED WHEN IMPLEMENTATION CHANGES 
//   -----------CURRENT IMPLEMENTATION : REGULAR INTEGERS (int)  -------
/////////////////////////////////////////////////////////////////////////

baseint *base_new()
{
    baseint *pNew; 
    pNew = (baseint *) malloc(sizeof(baseint));
    return pNew;
}

bool base_compare(void *pNum1, void *pNum2)
{
    bool answer;
    answer = (*((baseint *) pNum1) == *((baseint *) pNum2)) ? TRUE : FALSE;
    return answer;
}

void *base_copy(void *pNum)
{
    baseint *pCopy;
    pCopy = base_new();
    *pCopy = *((baseint *) pNum);
    return pCopy;
}

void base_destroy(void *pNum)
{
    baseint *pMNum;
    if (pNum != NULL)
    {
	pMNum = (baseint *) pNum;
	free(pMNum);
    }
}

void base_display(void *pNum)
{
    printf("%d", *((baseint *) pNum));
}

void base_list_display(void *pList)
{
    if (list_empty((list *) pList))
	printf("0");
    else
	list_do_each((list *) pList, base_display);    
}


////////////////////////////////////////////////////////////////////////
//                    BIGINT FUNCTIONS                               
////////////////////////////////////////////////////////////////////////

void bzu_display_file(FILE *outfile, bzu_t *pBig)
{
    list_node *pNode;

    if (list_length(pBig) == 0)
	fprintf(outfile, "0");
    
    for (pNode = pBig->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)

	fprintf(outfile, "%d", *((baseint *) pNode->pData));
}

void bzu_canonicalize(bzu_t *pBig)
{
    if (!(list_empty(pBig)))
	if (*((baseint *) (pBig->pHead->pData)) == 0)
	{
	    list_kill_node(pBig, pBig->pHead);
	    bzu_canonicalize(pBig);
	}
}

bzu_t *base_to_big(baseint b) 
{
    bzu_t *pBig;
    baseint *pDigit;
    baseint b_remaining;
    
    b_remaining = b;
    pBig = bzu_new();
    
    while (b_remaining != 0) 
    {
	pDigit = base_new();
	*pDigit = b_remaining % (MAX_BIGINT_DIGIT + 1);
	list_push_head(pBig, pDigit);
	b_remaining -= *pDigit;
	if (b_remaining != 0)
	    b_remaining /=  (MAX_BIGINT_DIGIT + 1);
    }

    bzu_canonicalize(pBig);

    return pBig;
}
   
bzu_t *bzu_read() 
{
    list *pBuffer;
    baseint *pUser_entry;
    
    pBuffer = bzu_new();
    
    printf("Max digit size = %d\n", MAX_BIGINT_DIGIT);
    printf("Enter big integer digits seperated by spaces "
	   "(end with '-1')\n : ");
    pUser_entry = base_new();
    scanf("%d", pUser_entry);
    while (*pUser_entry != -1) 
    {
	if ((*pUser_entry >= 0) && (*pUser_entry <= MAX_BIGINT_DIGIT)) 
	{
	    list_push(pBuffer, pUser_entry);
	    pUser_entry = base_new();
	    scanf("%d", pUser_entry);
	}
    }
    
    bzu_canonicalize(pBuffer);
    
    return pBuffer;
}


baseint bzu_last_digit(bzu_t *pBig) 
{
    baseint digit = 0;
    if (!(list_empty(pBig)))
	digit = *((baseint *) pBig->pTail->pData);
    return digit;
}

baseint big_digit_value(big_digit *pDigit) 
{
    baseint digit = 0;
    if (pDigit != NULL)
	digit = *((baseint *) pDigit->pData);
    return digit;
}

bool bzu_eq(bzu_t *pBig1, bzu_t *pBig2) 
{
    bool answer;
    big_digit *pDigitNode1, *pDigitNode2;
    
    if (list_empty(pBig1))
	answer = (list_empty(pBig2));
    else if (list_empty(pBig2))
	answer = (list_empty(pBig1));
    else if (list_length(pBig1) < list_length(pBig2))
	answer = FALSE;
    else if (list_length(pBig2) < list_length(pBig1))
	answer = FALSE;
    else
    {
	pDigitNode1 = pBig1->pHead;
	pDigitNode2 = pBig2->pHead;
	
	while (((pBig1->compare_data)(pDigitNode1->pData, 
				      pDigitNode2->pData)) &&
	       (pDigitNode1->pNext != NULL))
	{
	    pDigitNode1 = pDigitNode1->pNext;
	    pDigitNode2 = pDigitNode2->pNext;
	}
	
	answer = (*((baseint *) (pDigitNode1->pData)) == 
		  *((baseint *) (pDigitNode2->pData))) ? TRUE : FALSE;
    }
    
    return answer;
}

bool bzu_leq(bzu_t *pBig1, bzu_t *pBig2) 
{
    bool answer;
    big_digit *pDigitNode1, *pDigitNode2;
    
    if (bzu_is_zero(pBig1))
	answer = TRUE;
    else if (list_length(pBig1) < list_length(pBig2))
	answer = TRUE;
    else if (list_length(pBig2) < list_length(pBig1))
	answer = FALSE;
    else
    {
	pDigitNode1 = pBig1->pHead;
	pDigitNode2 = pBig2->pHead;
	
	while (((pBig1->compare_data)(pDigitNode1->pData, 
				      pDigitNode2->pData)) &&
	       (pDigitNode1->pNext != NULL))
	{
	    pDigitNode1 = pDigitNode1->pNext;
	    pDigitNode2 = pDigitNode2->pNext;
	}
	
	answer = (*((baseint *) (pDigitNode1->pData)) <= 
		  *((baseint *) (pDigitNode2->pData))) ? TRUE : FALSE;
    }
    
    return answer;
}

bool bzu_geq(bzu_t *pBig1, bzu_t *pBig2) 
{
    bool answer;
    big_digit *pDigitNode1, *pDigitNode2;
    
    if (bzu_is_zero(pBig2))
	answer = TRUE;
    else if (list_length(pBig1) > list_length(pBig2))
	answer = TRUE;
    else if (list_length(pBig2) > list_length(pBig1))
	answer = FALSE;
    else
    {
	pDigitNode1 = pBig1->pHead;
	pDigitNode2 = pBig2->pHead;
	
	while (((pBig1->compare_data)(pDigitNode1->pData, 
				      pDigitNode2->pData)) &&
	       (pDigitNode1->pNext != NULL))
	{
	    pDigitNode1 = pDigitNode1->pNext;
	    pDigitNode2 = pDigitNode2->pNext;
	}
	
	answer = (*((baseint *) (pDigitNode1->pData)) >= 
		  *((baseint *) (pDigitNode2->pData))) ? TRUE : FALSE;

    }
    
    return answer;
}

bzu_t *bzu_plus(bzu_t *pBig1, bzu_t *pBig2) 
{
    baseint carry = 0;
    baseint digitsum, newdigit_value;
    baseint *pNewdigit;
    bzu_t *pSum;
    list_node *pBig1_CurrentDigit, *pBig2_CurrentDigit;
    
    pBig1_CurrentDigit = pBig1->pTail;
    pBig2_CurrentDigit = pBig2->pTail;
    
    pSum = bzu_new();
    
    while ((pBig1_CurrentDigit != NULL) || (pBig2_CurrentDigit != NULL)) 
    {
	
	digitsum = big_digit_value(pBig1_CurrentDigit) +
	    big_digit_value(pBig2_CurrentDigit) + carry;
	if (digitsum > MAX_BIGINT_DIGIT)
	    carry = (digitsum / (MAX_BIGINT_DIGIT + 1));
	else
	    carry = 0;
	newdigit_value = digitsum - (carry * (MAX_BIGINT_DIGIT +1));
	
	pNewdigit = base_new();
	*pNewdigit = newdigit_value;
	
	list_push_head(pSum, pNewdigit);
	
	if (pBig1_CurrentDigit != NULL)
	    pBig1_CurrentDigit = pBig1_CurrentDigit->pPrev;
	if (pBig2_CurrentDigit != NULL)
	    pBig2_CurrentDigit = pBig2_CurrentDigit->pPrev;
    }
    if (carry != 0) 
    {
	newdigit_value = carry;
	pNewdigit = base_new();
	*pNewdigit = newdigit_value;
	list_push_head(pSum, pNewdigit);
    }

    bzu_canonicalize(pSum);
    return pSum;
}


bzu_t *bzu_minus(bzu_t *pBig1, bzu_t *pBig2) 
{
    baseint carry;
    baseint digitdifference, newdigit_value;
    baseint *pNewdigit;
    bzu_t *pDifference;
    list_node *pBig1_CurrentDigit, *pBig2_CurrentDigit;
    
    pBig1_CurrentDigit = pBig1->pTail;
    pBig2_CurrentDigit = pBig2->pTail;
    
    pDifference = bzu_new();

    carry = 0;

    while ((pBig1_CurrentDigit != NULL) || (pBig2_CurrentDigit != NULL)) 
    {
	digitdifference = big_digit_value(pBig1_CurrentDigit) -
	    big_digit_value(pBig2_CurrentDigit) - carry;
	if (digitdifference < 0)
	    carry = 1;
	else
	    carry = 0;
	newdigit_value = digitdifference + (carry * (MAX_BIGINT_DIGIT +1));
	
	pNewdigit = base_new();
	*pNewdigit = newdigit_value;
	
	list_push_head(pDifference, pNewdigit);
	
	if (pBig1_CurrentDigit != NULL)
	    pBig1_CurrentDigit = pBig1_CurrentDigit->pPrev;
	if (pBig2_CurrentDigit != NULL)
	    pBig2_CurrentDigit = pBig2_CurrentDigit->pPrev;
    }
    if (carry != 0) 
    {
	newdigit_value = carry;
	pNewdigit = base_new();
	*pNewdigit = newdigit_value;
	list_push_head(pDifference, pNewdigit);
    }

    bzu_canonicalize(pDifference);
    return pDifference;
}

////////////////////////////////////
// BIGINT LISTS
////////////////////////////////////

bool bzu_compare(void *pBig1, void *pBig2)
{
    bool answer;
    answer = bzu_eq((bzu_t *) pBig1, (bzu_t *) pBig2);
    return answer;
}

void *bzu_copy_void(void *pBig)
{
    bzu_t *pCopy;
    pCopy = bzu_copy((bzu_t *) pBig);
    return pCopy;
}

void bzu_kill_void(void *pBig)
{
    bzu_kill((bzu_t *) pBig);

}

void bzu_display_void(void *pBig)
{
    bzu_display((bzu_t *) pBig);
    printf(" ");
}

void bzu_list_display(void *pBigList)
{
    list_do_each((list *) pBigList, bzu_display_void);
}



bzu_t *bzu_list_sum(list *pBigList) {
  bzu_t *pAnswer;

  list_node *pNode;
  
  pAnswer = bzu_new();

  for (pNode = pBigList->pHead ;
       pNode != NULL ;
       pNode = pNode->pNext)
  {
      bzu_t *pNewAnswer;
      pNewAnswer = bzu_plus(pNode->pData, pAnswer);
      bzu_kill(pAnswer);
      pAnswer = bzu_copy(pNewAnswer);
      bzu_kill(pNewAnswer);
  }

  return pAnswer;
}

////////////////////////////////////////////
// BACK TO BIGINTS.
////////////////////////////////////////////

bzu_t *bzu_times_base(bzu_t *pBig, baseint b) 
{
    baseint carry = 0;
    baseint digitprod, newdigit_value;
    baseint *pNewdigit;
    bzu_t *pProd;
    list_node *pBzu_CurrentDigit;
    
    pBzu_CurrentDigit = pBig->pTail;
    
    pProd = bzu_new();
    
    while (pBzu_CurrentDigit != NULL)
    {
	digitprod = (big_digit_value(pBzu_CurrentDigit) * b) + carry;
	if (digitprod > MAX_BIGINT_DIGIT)
	    carry = (digitprod / (MAX_BIGINT_DIGIT + 1));
	else
	    carry = 0;
	newdigit_value = digitprod - (carry * (MAX_BIGINT_DIGIT +1));
	
	pNewdigit = base_new();
	*pNewdigit = newdigit_value;
	
	list_push_head(pProd, pNewdigit);

	pBzu_CurrentDigit = pBzu_CurrentDigit->pPrev;
    }

    if (carry != 0) 
    {
	newdigit_value = carry;
	pNewdigit = base_new();
	*pNewdigit = newdigit_value;
	list_push_head(pProd, pNewdigit);
    }

    bzu_canonicalize(pProd);
    return pProd;
}

bzu_t *bzu_times(bzu_t *pBig1, bzu_t *pBig2) 
{
    bzu_t *pProd;
    list *pTable_to_sum;
    bzu_t *pSubProduct;
    big_digit *pBig2_CurrentDigit;
    big_digit *pCounter;
    baseint *pZero;

    pBig2_CurrentDigit = pBig2->pTail;
    pTable_to_sum = bzu_list_new();

    while (pBig2_CurrentDigit != NULL) 
    {
	pSubProduct = 
	    bzu_times_base(pBig1, 
			   *((baseint *) (pBig2_CurrentDigit->pData)));

	pCounter = pBig2_CurrentDigit;
	
	while (pCounter->pNext != NULL) 
	{
	    pZero = base_new();
	    *pZero = 0;
	    list_push(pSubProduct, pZero);
	    pCounter = pCounter->pNext;
	}
	list_push(pTable_to_sum, pSubProduct);
	pBig2_CurrentDigit = pBig2_CurrentDigit->pPrev;
    }

    pProd = bzu_list_sum(pTable_to_sum);
    list_kill(pTable_to_sum);

    return pProd;
}

bzu_t *bzu_divide(bzu_t *pA, bzu_t *pD) 
{
    bzu_t *pQuot;
    bzu_t *pDummy;
    bzu_t *pCurrentA;
    big_digit *pDigitA;
    big_digit *pDigitD;
    bzu_t *pNextA;
    baseint *pNew;
    
    int num_digits_to_add, counter;

    pQuot = base_to_big(0);
    pCurrentA = bzu_copy(pA);
    
    while (bzu_geq(pCurrentA, pD))
    {
	baseint factor;
	bzu_t *pBigFactor;
	bzu_t *pProd;
	big_digit *pDummyNode;

	pDigitA = pCurrentA->pHead;
	pDigitD = pD->pHead;
	
	factor = *((baseint *) (pDigitA->pData)) / 
	    *((baseint *) (pDigitD->pData));
	if (factor == 0) // need to use 2 digits of A
	{
	    baseint double_Adigits;
	    double_Adigits = *((baseint *) (pDigitA->pData)) * 
		(MAX_BIGINT_DIGIT + 1);
	    pDigitA = pDigitA->pNext;
	    double_Adigits += *((baseint *) (pDigitA->pData));
	    factor = double_Adigits / *((baseint *) (pDigitD->pData));
	}

	pBigFactor = base_to_big(factor);
	num_digits_to_add = 1 - list_length(pD);
	for (pDummyNode = pDigitA ; pDummyNode->pNext != NULL ; 
	     pDummyNode = pDummyNode->pNext)
	    num_digits_to_add++;
	for (counter = 0 ; counter < num_digits_to_add ; counter++)
	{
	    baseint *pZero;
	    pZero = base_new();
	    *pZero = 0;
	    list_push(pBigFactor, pZero);
	}
	bzu_canonicalize(pBigFactor);

	pProd = bzu_times_base(pD, factor);
	for (counter = 0 ; counter < num_digits_to_add ; counter++)
	{
	    baseint *pZero;
	    pZero = base_new();
	    *pZero = 0;
	    list_push(pProd, pZero);
	}
	bzu_canonicalize(pProd);

	if (!bzu_leq(pProd, pCurrentA))
	{
	    bzu_t *pNewBigFactor;
	    bzu_t *pOne;
	    
	    pOne = base_to_big(1);
	    pNewBigFactor = bzu_minus(pBigFactor, pOne);
	    bzu_kill(pOne);
	    bzu_kill(pBigFactor);
	    pBigFactor = pNewBigFactor;
	    
	    bzu_kill(pProd);
	    pProd = bzu_times(pBigFactor, pD);
	}
	
	pDummyNode = pBigFactor->pHead;
	while (!bzu_leq(pProd, pCurrentA))
	{
	    bzu_kill(pProd);
	    (*((baseint *) pDummyNode->pData))--;
	    bzu_canonicalize(pBigFactor);
	    pDummyNode = pBigFactor->pHead;
	    pProd = bzu_times(pD, pBigFactor);
	}

	pDummy = bzu_plus(pBigFactor, pQuot);
	bzu_kill(pQuot);
	pQuot = pDummy;

	pNextA = bzu_minus(pCurrentA, pProd);
	bzu_kill(pCurrentA);
	pCurrentA = pNextA;

	bzu_kill(pProd);
	bzu_kill(pBigFactor);
    }
    bzu_kill(pCurrentA);

    return pQuot;
}

bzu_t *bzu_gcd(bzu_t *pA, bzu_t *pB)
{
    bzu_t *pR, *pD, *pAnswer;

    if (bzu_is_zero(pB))
	pAnswer = bzu_copy(pA);
    else
    {
	bzu_t *pDummy;
	pD = bzu_divide(pA, pB);
	pDummy = bzu_times(pB, pD);
	pR = bzu_minus(pA, pDummy);
	bzu_kill(pD);
	bzu_kill(pDummy);
	if (bzu_is_zero(pR))
	    pAnswer = bzu_copy(pB);
	else
	    pAnswer = bzu_gcd(pB, pR);
	bzu_kill(pR);
    }
    return pAnswer;
}

void display_bigint(bzu_t *pBig) 
{
    list_display(pBig);
}

//////////////////////////////////////////////////////////////////////
//             SIGNED BIGINT FUNCTIONS                               
//////////////////////////////////////////////////////////////////////

bz_t *bz_new() 
{
    bz_t *pNew;
    pNew = (bz_t *) malloc(sizeof(bz_t));
    pNew->sign = POS;
    pNew->pMagnitude = NULL;
    return pNew;
}

void bz_kill(bz_t *pSbig) 
{
    if (pSbig != NULL) 
    {
	if (pSbig->pMagnitude != NULL)
	    bzu_kill(pSbig->pMagnitude);
	free(pSbig);
    }
}

bool bz_is_zero(bz_t *pSbig) {
  bool answer;
  answer = bzu_is_zero(pSbig->pMagnitude);
  return answer;
}

bool bz_is_nonnegative(bz_t *pSbig)
{
    bool answer;
    if (pSbig->sign == POS)
	answer = TRUE;
    else
	answer = FALSE;

    return answer;
}


void bz_canonicalize(bz_t *pSbig)
{
    if (bz_is_zero(pSbig))
	pSbig->sign = POS;
}

bz_t *bz_copy(bz_t *pSbig) {
  bz_t *pCopy;
  pCopy = bz_new();
  pCopy->sign = pSbig->sign;
  pCopy->pMagnitude = bzu_copy(pSbig->pMagnitude);
  return pCopy;
}

bz_t *base_to_sbig(baseint b) {
  bz_t *pResult;
  pResult = bz_new();
  if (b < 0) {
    pResult->sign = NEG;
    pResult->pMagnitude = base_to_big(-b);
  }
  else {
    pResult->sign = POS;
    pResult->pMagnitude = base_to_big(b);
  }
  bzu_canonicalize(pResult->pMagnitude);
  return pResult;
}

void bz_negate(bz_t *pSbig) {
  if (pSbig->sign == NEG)
    pSbig->sign = POS;
  else
    pSbig->sign = NEG;

  bz_canonicalize(pSbig);
} 

bool bz_ispos(bz_t *pSbig) {
  bool answer;
  if (pSbig->sign == POS)
    answer = TRUE;
  else
    answer = FALSE;
  return answer;
}

bz_t *bz_plus(bz_t *pSbig1, bz_t *pSbig2) {
  bz_t *pSum;
  pSum = bz_new();
  if ((pSbig1->sign == POS) && (pSbig2->sign == POS)) {
    pSum->sign = POS;
    pSum->pMagnitude = bzu_plus(pSbig1->pMagnitude, pSbig2->pMagnitude);
  }
  else if ((pSbig1->sign == NEG) && (pSbig2->sign == NEG)) {
    pSum->sign = NEG;
    pSum->pMagnitude = bzu_plus(pSbig1->pMagnitude, pSbig2->pMagnitude);
  }
  else if ((pSbig1->sign == POS) && (pSbig2->sign == NEG)) {
    if (bzu_geq(pSbig1->pMagnitude, pSbig2->pMagnitude)) {
      pSum->sign = POS;
      pSum->pMagnitude = bzu_minus(pSbig1->pMagnitude, pSbig2->pMagnitude);
    }
    else {
      pSum->sign = NEG;
      pSum->pMagnitude = bzu_minus(pSbig2->pMagnitude, pSbig1->pMagnitude);
    }
  }
  else if ((pSbig1->sign == NEG) && (pSbig2->sign == POS)) {
    if (bzu_leq(pSbig1->pMagnitude, pSbig2->pMagnitude)) {
      pSum->sign = POS;
      pSum->pMagnitude = bzu_minus(pSbig2->pMagnitude, pSbig1->pMagnitude);
    }
    else {
      pSum->sign = NEG;
      pSum->pMagnitude = bzu_minus(pSbig1->pMagnitude, pSbig2->pMagnitude);
    }
  }
  else 
    printf("Error in sbig plus\n");
  bz_canonicalize(pSum);
  return pSum;
}

bz_t *bz_minus(bz_t *pSbig1, bz_t *pSbig2) {
  bz_t *pDifference;
  bz_negate(pSbig2);
  pDifference = bz_plus(pSbig1, pSbig2);
  bz_negate(pSbig2);
  bz_canonicalize(pDifference);
  return pDifference;
}

void bz_display(bz_t *pSbig) {
  if (pSbig->sign == NEG)
    printf("-");
  bzu_display(pSbig->pMagnitude);
}

void bz_display_file(FILE *outfile, bz_t *pSbig) 
{
    if (pSbig->sign == NEG)
	fprintf(outfile, "-");
    bzu_display_file(outfile, pSbig->pMagnitude);
}

bz_t *bz_times(bz_t *pSbig1, bz_t *pSbig2) {
  bz_t *pProd;
  pProd = bz_new();

  if ((pSbig1->sign == POS) && (pSbig2->sign == POS))
    pProd->sign = POS;
  else if ((pSbig1->sign == NEG) && (pSbig2->sign == NEG))
    pProd->sign = POS;
  else if ((pSbig1->sign == POS) && (pSbig2->sign == NEG))
    pProd->sign = NEG;
  else if ((pSbig1->sign == NEG) && (pSbig2->sign == POS))
    pProd->sign = NEG;
  else 
    printf("Error in sbig times\n");

  pProd->pMagnitude = bzu_times(pSbig1->pMagnitude, pSbig2->pMagnitude);
  bz_canonicalize(pProd);
  return pProd;  
}

bool bz_leq(bz_t *pSbig1, bz_t *pSbig2) {
  bool answer;
  if ((pSbig1->sign == POS) && (pSbig2->sign == POS))
    answer = bzu_leq(pSbig1->pMagnitude, pSbig2->pMagnitude);
  else if ((pSbig1->sign == NEG) && (pSbig2->sign == NEG))
    answer = bzu_geq(pSbig1->pMagnitude, pSbig2->pMagnitude);
  else if ((bz_is_zero(pSbig1)) && (bz_is_zero(pSbig2)))
    answer = TRUE;
  else if ((pSbig1->sign == POS) && (pSbig2->sign == NEG))
    answer = FALSE;
  else if ((pSbig1->sign == NEG) && (pSbig2->sign == POS))
    answer = TRUE;
  else 
    printf("Error in sbig leq\n");
  return answer;
}
 
bool bz_geq(bz_t *pSbig1, bz_t *pSbig2) {
  bool answer;
  if ((pSbig1->sign == POS) && (pSbig2->sign == POS))
    answer = bzu_geq(pSbig1->pMagnitude, pSbig2->pMagnitude);
  else if ((pSbig1->sign == NEG) && (pSbig2->sign == NEG))
    answer = bzu_leq(pSbig1->pMagnitude, pSbig2->pMagnitude);
  else if ((bz_is_zero(pSbig1)) && (bz_is_zero(pSbig2)))
    answer = TRUE;
  else if ((pSbig1->sign == POS) && (pSbig2->sign == NEG))
    answer = TRUE;
  else if ((pSbig1->sign == NEG) && (pSbig2->sign == POS))
    answer = FALSE;
  else 
    printf("Error in sbig geq\n");
  return answer;
}

bool bz_eq(bz_t *pSbig1, bz_t *pSbig2) {
  bool answer;

  answer = (bzu_eq(pSbig1->pMagnitude, pSbig2->pMagnitude) &&
	    pSbig1->sign == pSbig2->sign);

  return answer;
}

//////////////////////////////////////
// SBIG LISTS
//////////////////////////////////////

bool bz_compare(void *pSbig1, void *pSbig2)
{
    bool answer;
    answer = bz_eq((bz_t *) pSbig1, (bz_t *) pSbig2);
    return answer;
}

void *bz_copy_void(void *pSbig)
{
    bz_t *pCopy;
    pCopy = bz_copy((bz_t *) pSbig);
    return pCopy;
}

void bz_kill_void(void *pSbig)
{
    bz_kill((bz_t *) pSbig);
}

void bz_display_void(void *pSbig)
{
    bz_display((bz_t *) pSbig);
    printf(" ");
}

void bz_list_display(void *pSbigList)
{
    list_do_each((list *) pSbigList, bz_display_void);
}


//////////////////////////////////////////////////////////////////
//             BIG RATIONAL NUMBERS                             
//////////////////////////////////////////////////////////////////

bq_t *bq_new()
{
  bq_t *pNewRatl;
  pNewRatl = (bq_t *) malloc(sizeof(bq_t));
  return pNewRatl;
}

bq_t *bq_make(bz_t *pNum, bz_t *pDen) {
  bq_t *pNewRatl;

  pNewRatl = (bq_t *) malloc(sizeof(bq_t));
  pNewRatl->pNum = bzu_copy(pNum->pMagnitude);
  pNewRatl->pDen = bzu_copy(pDen->pMagnitude);
  if ((pNum->sign == POS) && (pDen->sign == POS))
    pNewRatl->sign = POS;
  else if ((pNum->sign == NEG) && (pDen->sign == NEG))
    pNewRatl->sign = POS;
  else if ((pNum->sign == POS) && (pDen->sign == NEG))
    pNewRatl->sign = NEG;
  else if ((pNum->sign == NEG) && (pDen->sign == POS))
    pNewRatl->sign = NEG;
  
  bq_canonicalize(pNewRatl);

  return pNewRatl;
}

void bq_canonicalize(bq_t *pRat)
{
    if (bzu_is_zero(bq_num(pRat)))
    {
	bzu_kill(bq_den(pRat));
	pRat->pDen = base_to_big(1);
	pRat->sign = POS;
    }

    bq_reduce(pRat);
}

void bq_reduce(bq_t *pRat)
{
    bzu_t *pGCD, *pNewNum, *pNewDen;
    pGCD = bzu_gcd(pRat->pNum, pRat->pDen);
    pNewNum = bzu_divide(pRat->pNum, pGCD);
    pNewDen = bzu_divide(pRat->pDen, pGCD);
    bzu_kill(pRat->pNum);
    bzu_kill(pRat->pDen);
    pRat->pNum = pNewNum;
    pRat->pDen = pNewDen;
    bzu_kill(pGCD);
}

void bq_kill(bq_t *pRat) {
  if (pRat != NULL) {
    if (pRat->pNum != NULL)
      bzu_kill(pRat->pNum);
    if (pRat->pDen != NULL)
      bzu_kill(pRat->pDen);
    free(pRat);
  }
}

void bq_negate(bq_t *pRat) {
  if (pRat->sign == POS)
    pRat->sign = NEG;
  else
    pRat->sign = POS;
}

bq_t *bq_copy(bq_t *pRat) {
  bq_t *pCopy;
  pCopy = (bq_t *) malloc(sizeof(bq_t));
  pCopy->sign = pRat->sign;
  pCopy->pNum = bzu_copy(pRat->pNum);
  pCopy->pDen = bzu_copy(pRat->pDen);
  return pCopy;
}

bool bq_eq(bq_t *pRat1, bq_t *pRat2) {
  bool answer;
  
  bzu_t *pXterm1, *pXterm2;

  pXterm1 = bzu_times(bq_num(pRat1), bq_den(pRat2));
  pXterm2 = bzu_times(bq_num(pRat2), bq_den(pRat1));

  answer = ((bzu_eq(pXterm1, pXterm2)) && 
	    (bq_sign(pRat1) == bq_sign(pRat2)));

  bzu_kill(pXterm1);
  bzu_kill(pXterm2);

  return answer;
}

bz_t *bq_signed_num(bq_t *pRat) {
  bz_t *pResult;
  pResult = (bz_t *) malloc(sizeof(bz_t));
  pResult->sign = pRat->sign;
  pResult->pMagnitude = bzu_copy(bq_num(pRat));
  return pResult;
}

bz_t *bq_signed_den(bq_t *pRat) {
  bz_t *pResult;
  pResult = (bz_t *) malloc(sizeof(bz_t));
  pResult->sign = POS;
  pResult->pMagnitude = bzu_copy(bq_den(pRat));
  return pResult;
}


bool bq_leq(bq_t *pRat1, bq_t *pRat2) {
  bzu_t *pCrossterm1, *pCrossterm2;
  bool answer;
  start_garbage;
  if ((bq_sign(pRat1) == POS) && (bq_sign(pRat2) == POS)) {
    if (bzu_leq(btimes(bq_num(pRat1), bq_den(pRat2)), 
		btimes(bq_num(pRat2), bq_den(pRat1))))
      answer = TRUE;
    else
      answer = FALSE;
  }
  else if ((bq_sign(pRat1) == NEG) && (bq_sign(pRat2) == NEG)) {
    if (bzu_geq(btimes(bq_num(pRat1), bq_den(pRat2)), 
		btimes(bq_num(pRat2), bq_den(pRat1))))
      answer = TRUE;
    else
      answer = FALSE;
  }
  else if ((bq_sign(pRat1) == POS) && (bq_sign(pRat2) == NEG))
    answer = FALSE;
  else if ((bq_sign(pRat1) == NEG) && (bq_sign(pRat2) == POS))
    answer = TRUE;
  empty_garbage;
  return answer;
}

bool bq_geq(bq_t *pRat1, bq_t *pRat2) {
  bzu_t *pCrossterm1, *pCrossterm2;
  bool answer;
  start_garbage;

  if ((bq_sign(pRat1) == POS) && (bq_sign(pRat2) == POS)) {
    if (bzu_geq(btimes(bq_num(pRat1), bq_den(pRat2)), 
		btimes(bq_num(pRat2), bq_den(pRat1))))
      answer = TRUE;
    else
      answer = FALSE;
  }
  else if ((bq_sign(pRat1) == NEG) && (bq_sign(pRat2) == NEG)) {
    if (bzu_leq(btimes(bq_num(pRat1), bq_den(pRat2)), 
		btimes(bq_num(pRat2), bq_den(pRat1))))
      answer = TRUE;
    else
      answer = FALSE;
  }
  else if ((bq_sign(pRat1) == POS) && (bq_sign(pRat2) == NEG))
    answer = TRUE;
  else if ((bq_sign(pRat1) == NEG) && (bq_sign(pRat2) == POS))
    answer = FALSE;
  empty_garbage;

  return answer;
}

bool bq_lneq(bq_t *pRat1, bq_t *pRat2) {
  bool answer;
  answer = (!bq_geq(pRat1, pRat2));

  return answer;
}

bool bq_gneq(bq_t *pRat1, bq_t *pRat2) {
  bool answer;

  answer = !(bq_leq(pRat1, pRat2));

  return answer;
}


//////////////////////////////////////
// BRAT LISTS
//////////////////////////////////////

bool bq_compare(void *pBrat1, void *pBrat2)
{
    bool answer;
    answer = bq_eq((bq_t *) pBrat1, (bq_t *) pBrat2);
    return answer;
}

void *bq_copy_void(void *pBrat)
{
    bq_t *pCopy;
    pCopy = bq_copy((bq_t *) pBrat);
    return pCopy;
}

void bq_kill_void(void *pBrat)
{
    bq_kill((bq_t *) pBrat);
}

void bq_display_void(void *pBrat)
{
    bq_display((bq_t *) pBrat);
    printf(" ");
}

void bq_list_display(void *pBratList)
{
    list_do_each((list *) pBratList, bq_display_void);
}


bq_t *bq_max(bq_t *pRat1, bq_t *pRat2) {
  bq_t *pResult;
  
  if (bq_geq(pRat1, pRat2))
      pResult = bq_copy(pRat1);
  else
    pResult = bq_copy(pRat2);

  return pResult;
}

bq_t *bq_min(bq_t *pRat1, bq_t *pRat2) {
  bq_t *pResult;
  
  if (bq_leq(pRat1, pRat2))
    pResult = bq_copy(pRat1);
  else
    pResult = bq_copy(pRat2);

  return pResult;
}

bq_t *bq_invert(bq_t *pRat)
{
    bq_t *pInverse;
    pInverse = bq_new();
    pInverse->sign = pRat->sign;
    pInverse->pNum = bzu_copy(pRat->pDen);
    pInverse->pDen = bzu_copy(pRat->pNum);
    return pInverse;
}


bq_t *bq_divide(bq_t *pRat1, bq_t *pRat2)
{
    bq_t *pInv, *pAns;
    pInv = bq_invert(pRat2);
    pAns = bq_times(pRat1, pInv);
    bq_kill(pInv);
    return pAns;
}

bq_t *bq_times(bq_t *pRat1, bq_t *pRat2) {
  bq_t *pProd;
  pProd = (bq_t *) malloc(sizeof(bq_t));
  if ((pRat1->sign == POS) && (pRat2->sign == POS))
    pProd->sign = POS;
  else if ((pRat1->sign == NEG) && (pRat2->sign == NEG))
    pProd->sign = POS;
  else if ((pRat1->sign == POS) && (pRat2->sign == NEG))
    pProd->sign = NEG;
  else if ((pRat1->sign == NEG) && (pRat2->sign == POS))
    pProd->sign = NEG;
  else 
    printf("Error in brat times\n");
  pProd->pNum = bzu_times(pRat1->pNum, pRat2->pNum);
  pProd->pDen = bzu_times(pRat1->pDen, pRat2->pDen);
  bq_canonicalize(pProd);
  return pProd;
}

bq_t *bq_plus(bq_t *pRat1, bq_t *pRat2) {
  bq_t *pSum;
  bzu_t *pCrossterm1, *pCrossterm2, *pCommonDen;
  start_garbage;
  pSum = (bq_t *) malloc(sizeof(bq_t));
  pCrossterm1 = btimes(bq_num(pRat1), bq_den(pRat2));
  pCrossterm2 = btimes(bq_num(pRat2), bq_den(pRat1));
  pCommonDen = bzu_times(bq_den(pRat1), bq_den(pRat2));
  if ((pRat1->sign == POS) && (pRat2->sign == POS)) {
    pSum->sign = POS;
    pSum->pNum = bzu_plus(pCrossterm1, pCrossterm2);
    pSum->pDen = pCommonDen;
  }
  else if ((pRat1->sign == NEG) && (pRat2->sign == NEG)) {
    pSum->sign = NEG;
    pSum->pNum = bzu_plus(pCrossterm1, pCrossterm2);
    pSum->pDen = pCommonDen;
  }
  else if ((pRat1->sign == POS) && (pRat2->sign == NEG)) {
    if (bzu_geq(pCrossterm1, pCrossterm2)) {
      pSum->sign = POS;
      pSum->pNum = bzu_minus(pCrossterm1, pCrossterm2);
      pSum->pDen = pCommonDen;
    }
    else {
      pSum->sign = NEG;
      pSum->pNum = bzu_minus(pCrossterm2, pCrossterm1);
      pSum->pDen = pCommonDen;
    }
  }
  else if ((pRat1->sign == NEG) && (pRat2->sign == POS)) {
    if (bzu_geq(pCrossterm2, pCrossterm1)) {
      pSum->sign = POS;
      pSum->pNum = bzu_minus(pCrossterm2, pCrossterm1);
      pSum->pDen = pCommonDen;
    }
    else {
      pSum->sign = NEG;
      pSum->pNum = bzu_minus(pCrossterm1, pCrossterm2);
      pSum->pDen = pCommonDen;
    }
  }
  else 
    printf("Error in brat times\n");
  empty_garbage;
  bq_canonicalize(pSum);
  return pSum;  
}

bq_t *bq_minus(bq_t *pRat1, bq_t *pRat2) {
  bq_t *pDifference;
  bq_negate(pRat2);
  pDifference = bq_plus(pRat1, pRat2);
  bq_negate(pRat2);
  bq_canonicalize(pDifference);
  return pDifference;
}

void bq_display(bq_t *pRat) {
    bzu_t *pOne;
    pOne = base_to_big(1);
    
    if (pRat->sign == NEG)
	printf("-");
    bzu_display(pRat->pNum);
    if (!bzu_eq(pRat->pDen, pOne))
    {
	printf("/");
	bzu_display(pRat->pDen);
    }
    bzu_kill(pOne);
}


/////////////////////////////////////////////////////////////////////
//   BIGRATIONAL INTERVAL ARITHMETIC                                
/////////////////////////////////////////////////////////////////////

binterval *binterval_new() {
  binterval *pNewInterval;
  pNewInterval = (binterval *) malloc(sizeof(binterval));
  pNewInterval->no_ub = TRUE;
  pNewInterval->no_lb = TRUE;
  pNewInterval->pUb = NULL;
  pNewInterval->pLb = NULL;
  return pNewInterval;
}

void binterval_kill(binterval *pBI) {
  if (pBI != NULL) {
    if (pBI->pUb != NULL)
      bq_kill(pBI->pUb);
    if (pBI->pLb != NULL)
      bq_kill(pBI->pLb);
    free(pBI);
  }
}

void binterval_unbound(binterval *pI) {
  if (pI == NULL)
    printf("cannot unbound interval which has no allocated memory!\n");
  else {
    if (pI->pUb != NULL)
      bq_kill(pI->pUb);
    if (pI->pLb != NULL)
      bq_kill(pI->pLb);
    pI->no_ub = TRUE;
    pI->no_lb = TRUE;
  }
}

void binterval_set_lb(binterval *pI, bq_t *pLb) {
  if (pI == NULL)
    printf("cannot set lower bound on null interval!\n");
  else {
    pI->no_lb = FALSE;
    if (pI->pLb != NULL)
      bq_kill(pI->pLb);
    pI->pLb = bq_copy(pLb);
  }
}

void binterval_set_ub(binterval *pI, bq_t *pUb) {
  if (pI == NULL)
    printf("cannot set lower bound on null interval!\n");
  else {
    pI->no_ub = FALSE;
    if (pI->pUb != NULL)
      bq_kill(pI->pUb);
    pI->pUb = bq_copy(pUb);
  }
}

binterval *binterval_make(bq_t *pLb, bq_t *pUb) {
  binterval *pReturnInterval;

  pReturnInterval = binterval_new();
  binterval_set_lb(pReturnInterval, pLb);
  binterval_set_ub(pReturnInterval, pUb);

  return pReturnInterval;
}

binterval *binterval_new_empty() {
  binterval *pReturnInterval;
  bq_t *pZero, *pOne, *pSoln0, *pSoln1;
  bz_t *pSbZero, *pSbOne;
  binterval *pSolution;

  pSbZero = base_to_sbig(0);
  pSbOne = base_to_sbig(1);
  
  pZero = bq_make(pSbZero, pSbOne);
  pOne = bq_make(pSbOne, pSbOne);
  
  bz_kill(pSbZero);
  bz_kill(pSbOne);

  pReturnInterval = binterval_make(pOne, pZero);

  bq_kill(pZero);
  bq_kill(pOne);

  return pReturnInterval;
}
  

binterval *binterval_copy(binterval *pInterval) {
  binterval *pCopy;
  if (pInterval == NULL)
    pCopy = NULL;
  else {
    pCopy = binterval_new();
    if (!(pInterval->no_lb))
      binterval_set_lb(pCopy, pInterval->pLb);
    if (!(pInterval->no_ub))
      binterval_set_ub(pCopy, pInterval->pUb);
  }
  return pCopy;
}

void binterval_assign(binterval *pI1, binterval *pI2)
{
    if (pI2->no_lb)
	pI1->no_lb = TRUE;
    else
	binterval_set_lb(pI2, pI1->pLb);
    if (pI2->no_ub)
	pI1->no_ub = TRUE;
    else
	binterval_set_ub(pI2, pI1->pUb);
}


binterval *binterval_positive_axis() {
  binterval *pPositiveAxis;

  bq_t *pZero;
  bz_t *pSbZero, *pSbOne;

  pSbZero = base_to_sbig(0);
  pSbOne = base_to_sbig(1);
  pZero = bq_make(pSbZero, pSbOne);

  pPositiveAxis = binterval_new();
  binterval_set_lb(pPositiveAxis, pZero);

  bz_kill(pSbZero);
  bz_kill(pSbOne);
  bq_kill(pZero);

  return pPositiveAxis;
}

bool binterval_empty(binterval *pI) {
  bool answer;
  if ((pI->no_lb) || (pI->no_ub))
    answer = FALSE;
  else if (bq_leq(pI->pLb, pI->pUb))
    answer = FALSE;
  else
    answer = TRUE;
  return answer;
}

binterval *binterval_intersect(binterval *pI1, binterval *pI2) {
  binterval *pIntersection;
  bq_t *pLb, *pUb;
  
  if ((binterval_empty(pI1)) || (binterval_empty(pI2)))
    pIntersection = binterval_new_empty();
  else {

    pIntersection = binterval_new();
    /////////////////////////////////
    // SET LOWER BOUNDS:             
    /////////////////////////////////

    // if I1 has no lower bound, we take lower bound from I2 

    if (pI1->no_lb) {
      if (!(pI2->no_lb))
	binterval_set_lb(pIntersection, pI2->pLb);
    }    

    // if I2 has no lower bound we take from I1

    else if (pI2->no_lb)
      binterval_set_lb(pIntersection, pI1->pLb);

    // if they both have lower bounds, we take the maximum lower bound

    else {
      pLb = bq_max(pI1->pLb, pI2->pLb);
      binterval_set_lb(pIntersection, pLb);
      bq_kill(pLb);
    }
    
    /////////////////////////////////////
    //  SET UPPER BOUNDS:                
    /////////////////////////////////////

    // if I1 has no upper bound, we take upper bound from I2

    if (pI1->no_ub) {
      if (!(pI2->no_ub))
	binterval_set_ub(pIntersection, pI2->pUb);
    }

    // if I2 has no upper bound we take from I1
    
    else if (pI2->no_ub)
      binterval_set_ub(pIntersection, pI1->pUb);

    // if they both have upper bounds, we take the minimum upper bound

    else {
      pUb = bq_min(pI1->pUb, pI2->pUb);
      binterval_set_ub(pIntersection, pUb);
      bq_kill(pUb);
    }
  }
  return pIntersection;
}

void binterval_display(binterval *pI) {
  if (binterval_empty(pI))
    printf("empty");
  else {
    if (pI->no_lb == 1)
      printf("(-infinity");
    else {
      printf("[");
      bq_display(pI->pLb);
    }
    printf(", ");
    if (pI->no_ub)
      printf("infinity)");
    else {
      bq_display(pI->pUb);
      printf("]");
    }
  }
}

bool binterval_eq(binterval *pI1, binterval *pI2)
{
    bool answer;
    if (binterval_empty(pI1) && binterval_empty(pI2))
	answer = TRUE;
    else
    {
	if ((pI1->no_ub != pI2->no_ub) || (pI1->no_lb != pI2->no_lb))
	    answer = FALSE;
	else if ((pI1->no_lb == TRUE) && (pI1->no_ub == TRUE))
	    answer = TRUE;
	else if ((pI1->no_lb == TRUE) && (pI1->no_ub == FALSE))
	    answer = (bq_eq(pI1->pUb, pI2->pUb));
	else if ((pI1->no_lb == FALSE) && (pI1->no_ub == TRUE))
	    answer = (bq_eq(pI1->pLb, pI2->pLb));
	else
	    answer = ((bq_eq(pI1->pUb, pI2->pUb)) &&
		      (bq_eq(pI1->pLb, pI2->pLb))) ? TRUE : FALSE;
    }
    return answer;
}

//////////////////////////////////////
// BINTERVAL LISTS
//////////////////////////////////////

bool binterval_compare(void *pBinterval1, void *pBinterval2)
{
    bool answer;
    answer = binterval_eq((binterval *) pBinterval1, 
			  (binterval *) pBinterval2);
    return answer;
}

void *binterval_copy_void(void *pBinterval)
{
    binterval *pCopy;
    pCopy = binterval_copy((binterval *) pBinterval);
    return pCopy;
}

void binterval_kill_void(void *pBinterval)
{
    binterval_kill((binterval *) pBinterval);
}

void binterval_display_void(void *pBinterval)
{
    binterval_display((binterval *) pBinterval);
    printf(" ");
}

void binterval_list_display(void *pBintervalList)
{
    list_do_each((list *) pBintervalList, binterval_display_void);
}


///////////////////////////////////////////////////////////////////
//                      BIG FORMULA                               
///////////////////////////////////////////////////////////////////

bfunctiontype *bform_new() {
  bfunctiontype *pNewFormula;
  pNewFormula = (bfunctiontype *) malloc(sizeof(bfunctiontype));
  pNewFormula->pAlpha = NULL;
  pNewFormula->pBeta = NULL;
  return pNewFormula;
}

bfunctiontype *bform_make(bq_t *pAlpha, bq_t *pBeta) {
  bfunctiontype *pNewForm;
  pNewForm = bform_new();
  pNewForm->pAlpha = bq_copy(pAlpha);
  pNewForm->pBeta = bq_copy(pBeta);
  return pNewForm;
}

void bform_kill(bfunctiontype *pFormula) {
  if (pFormula != NULL) {
    if (pFormula->pAlpha != NULL)
      bq_kill(pFormula->pAlpha);
    if (pFormula->pBeta != NULL)
      bq_kill(pFormula->pBeta);
    free(pFormula);
  }  
} 

bq_t *bform_solve_for_0(bfunctiontype *pFormula) {
  bq_t *pSolution;
  bz_t *pSignedNum, *pSignedDen;
  start_garbage;
  

  pSignedNum = sbtimes(snum(pFormula->pBeta), sden(pFormula->pAlpha));
  bz_negate(pSignedNum);
  pSignedDen = sbtimes(sden(pFormula->pBeta), snum(pFormula->pAlpha));
  
  pSolution = bq_make(pSignedNum, pSignedDen);
  
  empty_garbage;

  return pSolution;
}

bq_t *bform_solve_for_1(bfunctiontype *pFormula) {
  bq_t *pSolution;
  bz_t *pSignedNum, *pSignedDen;
  start_garbage;
  
  pSignedNum = sbtimes(snum(pFormula->pBeta), sden(pFormula->pAlpha));
  bz_negate(pSignedNum);
  pSignedDen = sbtimes(sden(pFormula->pBeta), 
		      sbminus(snum(pFormula->pAlpha), sden(pFormula->pAlpha)));

  
  pSolution = bq_make(pSignedNum, pSignedDen);
  
  empty_garbage;

  return pSolution;
}



binterval *binterval_solve_zero_one(bfunctiontype *pFormula) {
  bq_t *pZero, *pOne, *pSoln0, *pSoln1;
  bz_t *pSbZero, *pSbOne;
  binterval *pSolution;

  pSbZero = base_to_sbig(0);
  pSbOne = base_to_sbig(1);

  pZero = bq_make(pSbZero, pSbOne);
  pOne = bq_make(pSbOne, pSbOne);

  bz_kill(pSbZero);
  bz_kill(pSbOne);

  pSoln0 = bform_solve_for_0(pFormula);
  pSoln1 = bform_solve_for_1(pFormula);


  ////////////////////////////////////////////////////////////
  // main cases : beta>0, beta<0, beta=0                   
  ////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////
  // beta = 0 first - this is just a constant function f(x) = alpha    
  //////////////////////////////////////////////////////////////////////
  if (bq_eq(pZero, pFormula->pBeta)) {
    if (bq_gneq(pFormula->pAlpha, pOne) || 
	(bq_lneq(pFormula->pAlpha, pZero)))
      pSolution = binterval_new_empty();
    else
      pSolution = binterval_positive_axis();
  }
  
  ////////////////////////////////////////////////////////////////
  // beta > 0 (function is decreasing)                           
  ////////////////////////////////////////////////////////////////
  else if (bq_gneq(pFormula->pBeta, pZero)) {
  

     ///////////////////////////////////////////////////////////////
     // five cases! depending on whether alpha < 0, = 0, in (0, 1),
     //  = 1,  > 1                                                 
     ///////////////////////////////////////////////////////////////

    if (bq_lneq(pFormula->pAlpha, pZero))
      /////////////////////////////////////////////////////////////
      // both solns are to the right of the origin                
      // and the one solution is on the left.                     
      /////////////////////////////////////////////////////////////
      pSolution = binterval_make(pSoln1, pSoln0);

    //////////////////////////////////////////////////////////////
    // the following covers the cases alpha = 0 or in (0, 1)     
    //////////////////////////////////////////////////////////////
    else if ((bq_eq(pFormula->pAlpha, pZero)) ||
	     ((bq_lneq(pFormula->pAlpha, pOne) &&
	       (bq_gneq(pFormula->pAlpha, pZero))))) {
      /////////////////////////////////////////////////////////////
      // function is one to the right of origin, never hits 0     
      // on the right HERE WE THROW AWAY THE NEGATIVE POSSIBLE    
      // SOLUTION!!!!!                                            
      /////////////////////////////////////////////////////////////
      pSolution = binterval_positive_axis();
      binterval_set_lb(pSolution, pSoln1);
    }
    
    ////////////////////////////////////////////////////////////////
    // final cases have no possible solutions.                    
    // (right of origin, that is...)                              
    ////////////////////////////////////////////////////////////////
    else
      pSolution = binterval_new_empty();
  }
  
  /////////////////////////////////////////////////////////////////
  // b < 0 (function is increasing)                              
  /////////////////////////////////////////////////////////////////
  else {
    
    ///////////////////////////////////////////////////////////////
    // five cases! depending on whether alpha < 0, = 0, in (0, 1),
    //  = 1, or > 1                                               
    ///////////////////////////////////////////////////////////////
    if (bq_gneq(pFormula->pAlpha, pOne))
      ////////////////////////////////////////////////////////////
      // both solns are to the right of the origin and solution 0 
      // is on the left                                           
      ////////////////////////////////////////////////////////////
      pSolution = binterval_make(pSoln0, pSoln1);

     //////////////////////////////////////////////////////////////
     // we consider the cases alpha = 1 , or in (0,1) together
     //////////////////////////////////////////////////////////////
    else if ((bq_eq(pFormula->pAlpha, pOne)) ||
	     ((bq_gneq(pFormula->pAlpha, pZero)) &&
	      (bq_lneq(pFormula->pAlpha, pOne)))) {
     //////////////////////////////////////////////////////////////
     // Function is positive to the right of soln0, never hits 1 
     // on the right HERE WE THROW AWAY THE NEGATIVE POSSIBLE    
     // SOLUTION!!!!!                                            
     //////////////////////////////////////////////////////////////
      pSolution = binterval_new();
      binterval_set_lb(pSolution, pSoln0);
    }
    
    ///////////////////////////////////////////////////////////////
    // final cases have no possible solutions.                    
    // (right of origin, that is...)                              
    ///////////////////////////////////////////////////////////////
    else 
      pSolution = binterval_new_empty();
  }
  bq_kill(pZero);
  bq_kill(pOne);
  bq_kill(pSoln0);
  bq_kill(pSoln1);

  return pSolution;
}



binterval *binterval_solve_positive(bfunctiontype *pFormula) {
  bq_t *pZero, *pOne, *pSoln0, *pSoln1;
  bz_t *pSbZero, *pSbOne;
  binterval *pSolution;

  pSbZero = base_to_sbig(0);
  pSbOne = base_to_sbig(1);

  pZero = bq_make(pSbZero, pSbOne);
  pOne = bq_make(pSbOne, pSbOne);

  bz_kill(pSbZero);
  bz_kill(pSbOne);

  pSoln0 = bform_solve_for_0(pFormula);
  pSoln1 = bform_solve_for_1(pFormula);


  /////////////////////////////////////////////////////////////
  // main cases : beta>0, beta<0, beta=0                     
  /////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////
  // beta = 0 first - this is just a constant function f(x) = alpha   
  ////////////////////////////////////////////////////////////////////
  if (bq_eq(pZero, pFormula->pBeta)) {
    if (bq_geq(pFormula->pAlpha, pZero))
      pSolution = binterval_positive_axis();
    else
      pSolution = binterval_new_empty();
  }
  
  /////////////////////////////////////////////////////////////////
  // beta > 0 (function is decreasing)                           
  /////////////////////////////////////////////////////////////////
  else if (bq_gneq(pFormula->pBeta, pZero)) {


      ///////////////////////////////////////////////////////////////
      // five cases! depending on whether alpha < 0, = 0, in (0, 1),
      // = 1,  > 1                                                 
      //////////////////////////////////////////////////////////////

    if (bq_lneq(pFormula->pAlpha, pZero))

	////////////////////////////////////////////////////////////
	// both solns are to the right of the origin                
	// and the one solution is on the left. positive interval   
	// bounded to the left by zero and to the right by soln 0.  
	// HERE WE DO A MATHEMATICAL FUDGE :  the value x = 0       
	// doesn't really work (it is an asymptote), but nonetheless
	// this will not affect our interval calculations, just by  
	// a case by case analysis of the types of possible         
	// intervals we are intersecting!                           
	////////////////////////////////////////////////////////////
      pSolution = binterval_make(pZero, pSoln0);

    ////////////////////////////////////////////////////////////////
    // the following covers the cases alpha = 0 or in (0, 1)      
    ////////////////////////////////////////////////////////////////
    else if ((bq_eq(pFormula->pAlpha, pZero)) ||
	     ((bq_lneq(pFormula->pAlpha, pOne) &&
	       (bq_gneq(pFormula->pAlpha, pZero))))) {

	/////////////////////////////////////////////////////////////
	// function is one to the right of origin, never hits 0     
        // on the right. It's always positive right of the origin,  
        // so full interval works.                                  
	/////////////////////////////////////////////////////////////
	pSolution = binterval_positive_axis();
    }
    
    /////////////////////////////////////////////////////////////////
    // final cases have are positive   
    // always to the right of the origin. full interval works.    
    /////////////////////////////////////////////////////////////////
    else
      pSolution = binterval_positive_axis();
  }
  
  /////////////////////////////////////////////////////////////////
  // b < 0 (function is increasing)                              
  /////////////////////////////////////////////////////////////////
  else {
    
      //////////////////////////////////////////////////////////////
      // five cases! depending on whether alpha < 0, = 0, in (0, 1),
      // = 1, or > 1                                               
      //////////////////////////////////////////////////////////////
    if (bq_gneq(pFormula->pAlpha, pOne)) {
	/////////////////////////////////////////////////////////////
        // both solns are to the right of the origin and solution 0 
	// is on the left. soln 0 bounds the positive interval on   
	// the left, and it is unbounded on the right               
	////////////////////////////////////////////////////////////
      pSolution = binterval_new();
      binterval_set_lb(pSolution, pSoln0);
    }

    ////////////////////////////////////////////////////////////////
    // we consider the cases alpha = 1 , or in (0,1) together     
    ////////////////////////////////////////////////////////////////
    else if ((bq_eq(pFormula->pAlpha, pOne)) ||
	     ((bq_gneq(pFormula->pAlpha, pZero)) &&
	      (bq_lneq(pFormula->pAlpha, pOne)))) {
	////////////////////////////////////////////////////////////
	// function is positive to the right of soln0               
	////////////////////////////////////////////////////////////   
      pSolution = binterval_new();
      binterval_set_lb(pSolution, pSoln0);
    }
    
    ///////////////////////////////////////////////////////////////
    // final cases have no possible solutions.                    
    // and are negative to the right of the origin.               
    ///////////////////////////////////////////////////////////////
    else 
	pSolution = binterval_new_empty();
  }

  bq_kill(pZero);
  bq_kill(pOne);
  bq_kill(pSoln0);
  bq_kill(pSoln1);

  return pSolution;
}

void bform_display(bfunctiontype *pFormula) {
  bq_display(pFormula->pAlpha);
  printf(" + (");
  bq_display(pFormula->pBeta);
  printf(")/x");
}

bq_t *bform_eval(bfunctiontype *pFormula, bq_t *pX)
{
    bq_t *pAns;
    bq_t *pDummy;
    pDummy = bq_divide(pFormula->pBeta, pX);
    pAns = bq_plus(pFormula->pAlpha, pDummy);
    bq_kill(pDummy);
    return pAns;
}



bzu_t *bplus(bzu_t *px, bzu_t *py) {
  bzu_t *p_bigint_buffer;
  p_bigint_buffer = bzu_plus(px, py);
  list_push(pBzu_garbage_, p_bigint_buffer);
  return p_bigint_buffer;
}
bzu_t *btimes(bzu_t *px, bzu_t *py) {
  bzu_t *p_bigint_buffer;
  p_bigint_buffer = bzu_times(px, py);
  list_push(pBzu_garbage_, p_bigint_buffer);
  return p_bigint_buffer;
}
bzu_t *bminus(bzu_t *px, bzu_t *py) {
  bzu_t *p_bigint_buffer;
  p_bigint_buffer = bzu_minus(px, py);
  list_push(pBzu_garbage_, p_bigint_buffer);
  return p_bigint_buffer;
}
bz_t *sbplus(bz_t *px, bz_t *py) {
  bz_t *p_bz_t_buffer;
  p_bz_t_buffer = bz_plus(px, py);
  list_push(pBz_garbage_, p_bz_t_buffer);
  return p_bz_t_buffer;
}
bz_t *sbtimes(bz_t *px, bz_t *py) {
  bz_t *p_bz_t_buffer;
  p_bz_t_buffer = bz_times(px, py);
  list_push(pBz_garbage_, p_bz_t_buffer);
  return p_bz_t_buffer;
}
bz_t *sbminus(bz_t *px, bz_t *py) {
  bz_t *p_bz_t_buffer;
  p_bz_t_buffer = bz_minus(px, py);
  list_push(pBz_garbage_, p_bz_t_buffer);
  return p_bz_t_buffer;
}
bz_t *snum(bq_t *pBrat) {
  bz_t *p_snum_buffer;
  p_snum_buffer = bq_signed_num(pBrat);
  list_push(pBz_garbage_, p_snum_buffer);
  return p_snum_buffer;
}
bz_t *sden(bq_t *pBrat) {
  bz_t *p_sden_buffer;
  p_sden_buffer = bq_signed_den(pBrat);
  list_push(pBz_garbage_, p_sden_buffer);
  return p_sden_buffer;
}
bz_t *base2sbig(baseint b) {
  bz_t *p_base2bz_buffer;
  p_base2bz_buffer = base_to_sbig(b);
  list_push(pBz_garbage_, p_base2bz_buffer);
  return p_base2bz_buffer;
}
binterval *bintersect(binterval *pI1, binterval *pI2) {
  binterval *p_bintersect_buffer;
  p_bintersect_buffer = binterval_intersect(pI1, pI2);
  list_push(pBinterval_garbage_, p_bintersect_buffer);
  return p_bintersect_buffer;
}

