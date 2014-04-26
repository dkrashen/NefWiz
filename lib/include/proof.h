#ifndef PROOF_LOADED_
#define PROOF_LOADED_

#include "restriction.h"

typedef enum reason
{
    F_BOUND
} reason_t;

typedef struct proof_step
{
    smallint genus;
    seq *pSeq;
    t_set *pIncluded;
    bool other_reason;
    reason_t reason;
} proof_step;

typedef list_node proof_node;

typedef list proof, proof_t;

typedef set proof_set, proof_s_t;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

extern proof_step *proof_step_make(smallint genus, seq *pSeq, 
				   t_set *pIncluded);

extern void proof_step_kill(proof_step *pStep);

extern proof_step *proof_step_copy(proof_step *pStep);

extern bool proof_step_compare(proof_step *pStep1 ,proof_step *pStep2);

extern void proof_step_display(proof_step *pStep);

extern bool proof_step_check(proof_step *pStep, divisor *pDiv, 
			     fdata_list *pFdatum);

extern proof *proof_new();

extern void proof_display(proof *pProof);

extern void proof_human_display(proof *pProof, divisor *pDiv, 
				fdata_list *pFdatum);

extern void proof_step_display_human_file_latex(FILE *outfile, 
						proof_step *pStep, 
						divisor *pDiv, 
						fdata_list *pFdatum);

extern void proof_human_display_file_latex(FILE *outfile, proof *pProof, 
					   divisor *pDiv, fdata_list *pFdatum);

#define proof_kill set_kill
#define proof_kill_node set_kill_node
#define proof_debone set_debone
#define proof_length set_length
#define proof_empty set_empty
#define proof_push_head set_push_head
#define proof_force_push_head list_push_head
#define proof_concat set_concat
#define proof_copy set_copy
#define proof_copy_skeleton set_copy_skeleton
#define proof_force_transfer set_transfer
#define proof_while_do set_while_do
#define proof_do_each set_do_each
#define proof_head set_head
#define proof_tail set_tail
#define proof_complement set_complement
#define proof_get_node set_get_node
#define proof_force_push set_force_push
#define proof_push set_push
#define proof_compare_data set_compare_data
#define proof_true_for_some set_true_for_some
#define proof_true_for_all set_true_for_all
#define proof_kill_each_if set_kill_each_if

extern bool proof_check(proof *pProof, divisor *pDiv, fdata_list *pFdatum);



extern void proof_set_display(proof *pProof_Set);


#define proof_set_new metaset_new
#define proof_set_kill set_kill
#define proof_set_kill_node set_kill_node
#define proof_set_debone set_debone
#define proof_set_length set_length
#define proof_set_empty set_empty
#define proof_set_push_head set_push_head
#define proof_set_concat set_concat
#define proof_set_copy set_copy
#define proof_set_copy_skeleton set_copy_skeleton
#define proof_set_force_transfer set_transfer
#define proof_set_while_do set_while_do
#define proof_set_do_each set_do_each
#define proof_set_head set_head
#define proof_set_tail set_tail
#define proof_set_complement set_complement
#define proof_set_get_node set_get_node
#define proof_set_force_push set_force_push
#define proof_set_force_ordered_push metalist_ordered_push
#define proof_set_push set_push
#define proof_set_compare_data set_compare_data
#define proof_set_true_for_some set_true_for_some
#define proof_set_true_for_all set_true_for_all
#define proof_set_kill_each_if set_kill_each_if

extern bool proof_set_some_works(proof_set *pProofs, divisor *pDiv, 
				 fdata_list *pFdatum);



#endif
