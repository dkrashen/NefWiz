#ifndef FLAG_LOADED_
#define FLAG_LOADED_

#include <signal.h>

#include "divisor.h"
#include "list.h"
#include "restriction.h"
#include "big_arithmetic.h"
#include "proof.h"
#include "proof_tree.h"

//////////////////////////////////////////////////////////////
// this is the largest number n for which the F conjecture
// on M_{0, n} is true. this is defined in restriction.h
//////////////////////////////////////////////////////////////
// #define CURRENT_F_BOUND


extern fdata_list *fdata_configure_list();


extern void fdata_clear_list();


extern bool triples_work(divisor *pDiv, t_set *pTset, fdata **ppFdata,
			 t_set **ppIncluded);


///////////////////////////////////////////////
///////////////////////////////////////////////
// MAIN ALGORITHM PROCUDURES
///////////////////////////////////////////////
///////////////////////////////////////////////

extern bool flag_shows_nef(divisor *pDiv, ptree *pTree, fdata_list *pFdatum);

/////////////////////////////////////////////////////////////////////
// takes the associated triples to the sequence and gets some 
// maximal subsets using t_mlat_some_maximals. if 
// restrictions work for any of these, the sequence and the maximal
// subset are added to current proof and function returns TRUE.
/////////////////////////////////////////////////////////////////////
extern bool seq_restrictions_work(divisor *pDiv, seq *pSeq, 
				  proof *pCurrent_Proof, 
				  seq_set *pSuccessful_restriction_sequences,
				  fdata_list *pFdatum);


extern bool restrictions_on_triples_show_nef(
    divisor *pDiv, t_set *pTset, t_set *pIncluded, proof *pCurrent_Proof,
    seq_set *pSuccessful_restriction_sequences, fdata_list *pFdatum);

/////////////////////////////////////////////////////////////////////////
// checks if seq_works for some element of list.
/////////////////////////////////////////////////////////////////////////
extern bool seq_set_restrictions_work(divisor *pDiv, seq_set *pSeqSet, 
				  proof *pCurrent_Proof, 
				  seq_set *pSuccessful_restriction_sequences,
				  fdata_list *pFdatum);



#define maximal_t_subset_works(div, tsubset, tset, current_proof, \
 successful_seqs, fdatum) \
  restrictions_on_triples_show_nef((div), (tset), (tsubset), (current_proof), \
  (successful_seqs), (fdatum))



#endif

