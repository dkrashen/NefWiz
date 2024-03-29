#include "latex_display.h"



//////////////////////////////////////////////////////////////////////
// BIG_ARITHMETIC
//////////////////////////////////////////////////////////////////////

void bq_display_file_latex(FILE *outfile, 
			     bq_t *pRat) {
    bzu_t *pOne;
    pOne = base_to_big(1);
    
    if (pRat->sign == NEG)
	fprintf(outfile, "-");
    if (!bzu_eq(pRat->pDen, pOne))
    {
	fprintf(outfile, "\\frac{");
	bzu_display_file(outfile, pRat->pNum);
	fprintf(outfile, "}{");
	bzu_display_file(outfile, pRat->pDen);
	fprintf(outfile, "}");
    }
    else
	bzu_display_file(outfile, pRat->pNum);
    
    bzu_kill(pOne);
}

void bform_display_file_latex(FILE *outfile, bfunctiontype *pFormula)
{
    bzu_t *pOne;
    pOne = base_to_big(1);
    
    bq_display_file_latex(outfile, pFormula->pAlpha);
    fprintf(outfile, " + ");

    if (pFormula->pBeta->sign == NEG)
	fprintf(outfile, "-");
    
    fprintf(outfile, "\\frac{");
    bzu_display_file(outfile, pFormula->pBeta->pNum);
    fprintf(outfile, "}{");
    if (!bzu_eq(pFormula->pBeta->pDen, pOne))
	bzu_display_file(outfile, pFormula->pBeta->pDen);
    fprintf(outfile, " c");
    fprintf(outfile, "}");

    bzu_kill(pOne);
}

void binterval_display_file_latex(FILE *outfile, binterval *pI) 
{
    if (binterval_empty(pI))
	fprintf(outfile, "\\emptyset");
    else {
	if (pI->no_lb == 1)
	    fprintf(outfile, "(-\\infty");
	else {
	    fprintf(outfile, "[");
	    bq_display_file_latex(outfile, pI->pLb);
	}
	fprintf(outfile, ", ");
	if (pI->no_ub)
	    fprintf(outfile, "\\infty)");
	else {
	    bq_display_file_latex(outfile, pI->pUb);
	    fprintf(outfile, "]");
	}
    }
}

//////////////////////////////////////////////////////////////////////
// DIVISORS
//////////////////////////////////////////////////////////////////////

void div_latex_display_file(FILE *outfile, divisor *pDiv)
{
    smallint counter;

    // First print coefficient of lambda
    if (pDiv->lambda != 1)
	fprintf(outfile, " %d \\lambda\n", pDiv->lambda);
    else
	fprintf(outfile, " \\lambda\n", pDiv->lambda);
    
    // Next print the delta's using line commands
    for (counter = 0 ; counter < line_length(pDiv->pDelta) ; counter++)
	if (line_data(pDiv->pDelta, counter) != 1)
	    fprintf(outfile, " - %d \\delta_%d\n", 
		    line_data(pDiv->pDelta, counter), counter);
	else
	    fprintf(outfile, " - \\delta_%d\n", 
		    line_data(pDiv->pDelta, counter), counter);

}



////////////////////////////////////////////////////////////////////
// SEQUENCES
////////////////////////////////////////////////////////////////////

void seq_display_file_latex(FILE *outfile, seq *pSeq)
{
    list_node *pNode;
    if (seq_empty(pSeq))
	fprintf(outfile, "\\emptyset");
    else
    {
	fprintf(outfile, "[");
	for (pNode = pSeq->pHead ;
	     pNode != NULL ;
	     pNode = pNode->pNext)
	{
	    fprintf(outfile, "%d", *((medint *) pNode->pData));
	    if (pNode->pNext != NULL)
		fprintf(outfile, ", ");
	}
	fprintf(outfile, "]");
    }
}


//////////////////////////////////////////////////////////////////////
// PROOFS
//////////////////////////////////////////////////////////////////////

void proof_step_display_human_file_latex(FILE *outfile, 
					 proof_step *pStep, divisor *pDiv, 
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

	fprintf(outfile, "\n$A = ");
	seq_display_file_latex(outfile, pStep->pSeq);
	fprintf(outfile, "$\n\\bigskip\n");

	fprintf(outfile, "using the formula ");

	for (pNode = pFdataApp->pHead ;
	     ((pNode != NULL) && (!found_one)) ;
	     pNode = pNode->pNext)
	{
	    found_one = t_set_subset_formula_ok
		(pDiv, pTset, pStep->pIncluded, (fdata *) (pNode->pData));
	    if (found_one)
		pFdata = (fdata *) (pNode->pData);
	}

	fdata_display_file(outfile, pFdata);
	if (pFdata->type == 'c')
	{
	    pInterval = t_set_subset_formula_c_interval
		(pDiv, pTset, pStep->pIncluded, pFdata);

	    fprintf(outfile, "\n\n\\begin{gather*}\n");
	    fprintf(outfile, "v^* D = ");
	    bq_display_file_latex(outfile, pInterval->pLb);
	    fprintf(outfile, "\\Big(K_{\\overline{M}_{0, %d}} + ", 
		    seq_a(pStep->pSeq) + seq_z(pStep->pSeq, div_genus(pDiv)));
	    coeffs_display_file_latex(outfile, pDiv, pTset, pFdata->formula_c, 
				      pInterval->pLb);
	    fprintf(outfile, "\\Big)\n");
	    fprintf(outfile, "\\end{gather*}\n");
	    binterval_kill(pInterval);
	    fflush(stdout);
	}
	else
	{
	    if (t_set_length(pExcluded) != 0)
	    {
		printf("The coefficients which are not in "
		       "0 are as follows:\n");
		t_set_display(pExcluded);
	    }
	    else
		printf("all coefficients are 0\n");

	}

	printf("we now need to check the following sequences: \n");
	pSeqs = seq_set_to_check(pTset, pStep->pIncluded, div_genus(pDiv));
	seq_set_display(pSeqs);
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


// this will later be : 
// proof_interactive_display_file_latex(...);
//
// it will be the first step in an interactive process which creates and 
// displays a proof.
void proof_human_display_file_latex(FILE *outfile, proof *pProof,
				    divisor *pDiv, fdata_list *pFdatum)
{
    proof_node *pNode;
    proof_step *pStep1;

    pStep1 = (proof_step *) (pNode->pData);

    fprintf(outfile, "The following is a proof that the divisor: \n");
    fprintf(outfile, "$$D = ");
    div_latex_display_file(outfile, pDiv);
    fprintf(outfile, "$$");
    fprintf(outfile, "on $\\overline{M}_{%d} $ is nef.\n\\bigskip\n",
	    div_genus(pDiv));
    fprintf(outfile, "By (\\ref{GKM}, Thm .7), it is enough to show that ");
    fprintf(outfile, "the $F$-divisor $f^*(D)$ on $\\overline{M}_{0, %d}$ ",
	    div_genus(pDiv));
    fprintf(outfile, "is nef (c.f. the introduction for the definition of "
	    "the morphism $f$)");
    fprintf(outfile, "\n\nThe nefwizard's first step was to find an interval "
	    "$[a, b]$ such that for $x \\in [a, b]$, the \\textbf{big x - "
	    "average} (c.f. the introduction for definition) of $f^*(D)$ is "
	    "of the form :");
    fprintf(outfile, "\n$$f^*(D) = x K_{\\overline{M}_{0, %d}} + E,$$\n",
	    div_genus(pDiv));
    fprintf(outfile, "where $E$ is an effective sum of boundary. This "
	    "interval is : ");
    
}


//////////////////////////////////////////////////////////////////////
// COEFFICIENTS
//////////////////////////////////////////////////////////////////////


void coeff_0_display_file_latex_general(FILE *outfile, divisor *pDiv, 
					triple *pT, formula_0_type formula)
{
    bz_t *pVal;
    binterval *pInterval;
    
    pVal = formula(pDiv, pT);
    fprintf(outfile, "\\left(");
    bz_display_file(outfile, pVal);
    fprintf(outfile, "\\right)");

    if (seq_empty(pT->pB) && seq_empty(pT->pBc))
    {
	fprintf(outfile, "D_{%d}", pT->y);
    }
    else
    {
	fprintf(outfile, "\\Delta^{Z, %d}_{A, ", pT->y);
	seq_display_file_latex(outfile, pT->pB);
	fprintf(outfile, "}");
    }
}

void coeffs_0_display_file_latex_general(FILE *outfile, divisor *pDiv, 
					 t_set *pTset, formula_0_type formula)
{
    set_node *pNode;

    int num_on_line = 0;
    int max_per_line = 5; // this should be used in a multline environment

    for (pNode = pTset->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
    {
	num_on_line++;
	coeff_0_display_file_latex_general(outfile, pDiv, 
					   (triple *) (pNode->pData), 
					   formula);
	if (pNode->pNext != NULL)
	{	    
	    if ((num_on_line % max_per_line) == 0)
		fprintf(outfile, " \\\\ ");
	    fprintf(outfile, " + \n");
	}
    }
    fprintf(outfile, " . ");
}

void coeff_display_file_latex_general(FILE *outfile, divisor *pDiv, 
				      triple *pT, formula_c_type formula)
{
    bfunctiontype *pFunction;
    binterval *pInterval;

    pFunction = formula(pDiv, pT);
    fprintf(outfile, "\\left(");
    bform_display_file_latex(outfile, pFunction);
    fprintf(outfile, "\\right)");

    if (seq_empty(pT->pB) && seq_empty(pT->pBc))
    {
	fprintf(outfile, "D_{%d}", pT->y);
    }
    else
    {
	fprintf(outfile, "\\Delta^{Z, %d}_{A, ", pT->y);
	seq_display_file_latex(outfile, pT->pB);
	fprintf(outfile, "}");
    }
}


void coeffs_display_file_latex_general(FILE *outfile, divisor *pDiv, 
				       t_set *pTset, formula_c_type formula)
{
    set_node *pNode;

    int num_on_line = 0;
    int max_per_line = 3; // this should be used in a multline environment

    for (pNode = pTset->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
    {
	num_on_line++;
	coeff_display_file_latex_general(outfile, pDiv, 
					 (triple *) (pNode->pData), 
					 formula);
	if (pNode->pNext != NULL)
	{	    
	    if ((num_on_line % max_per_line) == 0)
		fprintf(outfile, " \\\\ ");
	    fprintf(outfile, " + \n");
	}
    }
    fprintf(outfile, " . ");
}

void coeff_display_file_latex(FILE *outfile, divisor *pDiv, triple *pT, 
			      formula_c_type formula, bq_t *pX)
{
    bfunctiontype *pFunction;
    binterval *pInterval;
    bq_t *pVal;

    pFunction = formula(pDiv, pT);

    pVal = bform_eval(pFunction, pX);
    bq_display_file_latex(outfile, pVal);
    bq_kill(pVal);
    fprintf(outfile, "\\Delta^{Z, %d}_{A, ", pT->y);
    seq_display_file_latex(outfile, pT->pB);
    fprintf(outfile, "}");
}

void coeffs_display_file_latex(FILE *outfile, divisor *pDiv, t_set *pTset, 
			      formula_c_type formula, bq_t *pX)
{
    set_node *pNode;

    int num_on_line = 0;
    int max_per_line = 4; // this should be used in a multline environment

    for (pNode = pTset->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)
    {
	num_on_line++;
	coeff_display_file_latex(outfile, pDiv, (triple *) (pNode->pData), 
				 formula, pX);
	if (pNode->pNext != NULL)
	{	    
	    fprintf(outfile, " + \n");
	    if ((num_on_line % max_per_line) == 0)
		fprintf(outfile, " \\\\ ");
	}
    }
}


