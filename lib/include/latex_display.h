#include "proof.h"


//////////////////////////////////////////////////////////////////////
// BIG_ARITHMETIC
//////////////////////////////////////////////////////////////////////

extern void bq_display_file_latex(FILE *outfile, bq_t *pRat);

extern void bform_display_file_latex(FILE *outfile, bfunctiontype *pFormula);


extern void binterval_display_file_latex(FILE *outfile, binterval *pI);

//////////////////////////////////////////////////////////////////
// displays as above to the given file (assumed to be open for
// writing). uses latex format (without $).
//////////////////////////////////////////////////////////////////
extern void div_latex_display_file(FILE *outfile, divisor *pDiv);


extern void proof_step_display_human_file_latex(FILE *outfile, 
						proof_step *pStep, 
						divisor *pDiv, 
						fdata_list *pFdatum);

extern void proof_human_display_file_latex(FILE *outfile, proof *pProof, 
					   divisor *pDiv, fdata_list *pFdatum);



////////////////////////////////////////////////////////////////////
// SEQUENCES
////////////////////////////////////////////////////////////////////

extern void seq_display_file_latex(FILE *outfile, seq *pSeq);

//////////////////////////////////////////////////////////////////////
// COEFFICIENTS
//////////////////////////////////////////////////////////////////////


extern void coeff_display_file_latex(FILE *outfile, divisor *pDiv, triple *pT, 
				     formula_c_type formula, bq_t *pX);

extern void coeffs_display_file_latex(FILE *outfile, divisor *pDiv, 
				      t_set *pTset, formula_c_type formula, 
				      bq_t *pX);

extern void coeff_display_file_latex_general(FILE *outfile, divisor *pDiv, 
					     triple *pT,
					     formula_c_type formula);

extern void coeffs_display_file_latex_general(FILE *outfile, divisor *pDiv, 
					      t_set *pTset, 
					      formula_c_type formula);


