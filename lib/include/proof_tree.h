#ifndef PROOF_TREE_DEFINED_
#define PROOF_TREE_DEFINED_

#include "list.h"
#include "restriction.h"

typedef enum statustype
{
    YES, NO, MAYBE
} statustype;

typedef set ptnode_set, ptarrow_set;

typedef struct proof_tree_node
{
    statustype status;
    seq *pSeq;
    ptarrow_set *pArrows;
} ptnode;

typedef struct proof_tree_arrow
{
    statustype status;
    t_set *pIncluded;
    bool spawned;
    ptnode_set *pProgeny;
} ptarrow;

typedef struct proof_tree
{
    ptnode *pRoot;
    ptnode_set *pNodes;
    smallint genus;
    fdata_list *pFdatum;

    int num_nodes_checked;
    int num_nodes_rechecked;
    bool spawning;
} ptree;


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
// PROOF TREE NODES
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

extern ptnode *ptnode_make(smallint genus, seq *pSeq);



extern void ptnode_kill(ptnode *pNode);

extern void ptnode_display(ptnode *pNode);

extern bool ptnode_equals(ptnode *pNode1, ptnode *pNode2);

extern bool ptnode_lessthan(void *pNode1, void *pNode2);

extern void list_ordered_push(list *pList, void *pData, 
			      lessthan_order_type less_than);

#define ptnode_set_push(s, n) list_ordered_push((s), (n), ptnode_lessthan)

extern ptnode_set *ptnode_set_new();

#define ptnode_set_kill set_kill
#define ptnode_set_kill_node set_kill_node
#define ptnode_set_debone set_debone
#define ptnode_set_length set_length
#define ptnode_set_empty set_empty
#define ptnode_set_push_head set_push_head
#define ptnode_set_concat set_concat
#define ptnode_set_copy set_copy
#define ptnode_set_copy_skeleton set_copy_skeleton
#define ptnode_set_display set_display
#define ptnode_set_force_transfer set_transfer
#define ptnode_set_while_do set_while_do
#define ptnode_set_do_each set_do_each
#define ptnode_set_head set_head
#define ptnode_set_complement set_complement
#define ptnode_set_get_node set_get_node
#define ptnode_set_force_push set_push
#define ptnode_set_compare_data set_compare_data
#define ptnode_set_true_for_some set_true_for_some
#define ptnode_set_true_for_all set_true_for_all
#define ptnode_set_kill_each_if set_kill_each_if

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
// PROOF TREE ARROWS
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

extern ptarrow *ptarrow_make(t_set *pTset);

extern bool ptarrow_equals(ptarrow *pArrow1, ptarrow *pArrow2);

extern void ptarrow_kill(ptarrow *pArrow);

extern void ptarrow_display(ptarrow *pArrow);

extern bool ptarrow_equals(ptarrow *pArrow1, ptarrow *pArrow2);

extern ptarrow_set *ptarrow_set_new();

extern bool ptarrow_lessthan(void *pArrow1, void *pArrow2);

extern void list_ordered_push(list *pList, void *pData, 
			      lessthan_order_type less_than);

#define ptarrow_set_push(s, a) set_ordered_push((s), (a), ptarrow_lessthan)



#define ptarrow_set_kill set_kill
#define ptarrow_set_kill_node set_kill_node
#define ptarrow_set_debone set_debone
#define ptarrow_set_length set_length
#define ptarrow_set_empty set_empty
#define ptarrow_set_push_head set_push_head
#define ptarrow_set_concat set_concat
#define ptarrow_set_copy set_copy
#define ptarrow_set_copy_skeleton set_copy_skeleton
#define ptarrow_set_display set_display
#define ptarrow_set_force_transfer set_transfer
#define ptarrow_set_while_do set_while_do
#define ptarrow_set_do_each set_do_each
#define ptarrow_set_head set_head
#define ptarrow_set_complement set_complement
#define ptarrow_set_get_node set_get_node
#define ptarrow_set_force_push set_push
#define ptarrow_set_compare_data set_compare_data
#define ptarrow_set_true_for_some set_true_for_some
#define ptarrow_set_true_for_all set_true_for_all
#define ptarrow_set_kill_each_if set_kill_each_if

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
// PROOF TREES
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

extern ptree *ptree_new(smallint genus, fdata_list *pFdatum);

extern void ptree_reset(ptree *pTree);

extern void ptree_kill(ptree *pTree);

// the spawning variable controls whether ptree_check will grow new
// branches when nescessary (spawning case) or not (nospawning case).

// note that checking a divisor whose proof is already is embedded in
// the tree is faster with nospawn than with spawn.

#define ptree_spawn(t) (t)->spawning = TRUE

#define ptree_nospawn(t) (t)->spawning = FALSE




////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
// CHECKING ROUTINES
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

// Checks if divisor can be shown nef using current tree.
// bool ptree_works(ptree *pTree, divisor *pDiv);

#define ptree_works(t, d) ptnode_works(t->pRoot, t, d)

extern bool ptnode_works(ptnode *pNode, ptree *pTree, divisor *pDiv);

// Checks if divisor can be shown nef using current tree. Grows new branches
// to existing tree when nescessary.
// bool ptree_check_and_spawn(ptree *pTree, divisor *pDiv);

#define ptree_check_and_spawn(t, d) ptnode_check_and_spawn(t->pRoot, t, d)


extern bool ptnode_check_and_spawn(ptnode *pNode, ptree *pTree, divisor *pDiv);



/*
// checks if the triple set for the arrow works for one of the given formulas
extern bool ptnode_check_arrow(ptnode *pNode, ptarrow *pArrow, divisor *pDiv);

// does the above for each arrow from the given node
extern bool ptnode_some_arrow_works(ptnode *pNode, divisor *pDiv, 
				    fdata_list *pFdatum);



extern bool ptarrow_works(ptarrow *pArrow, divisor *pDiv, fdata_list *pFdatum);



extern bool ptnode_arrow_valid(ptnode *pNode, ptarrow *pArrow, divisor *pDiv,
			       fdata_list *pFdatum);

extern bool ptnode_new_maximal_works(ptnode *pNode, divisor *pDiv, 
				     fdata_list *pFdatum, t_set *pMaximal);

extern bool ptnode_new_maximals_work(ptnode *pNode, divisor *pDiv, 
				     fdata_list *pFdatum, t_mlat *pMaximals);

*/
#endif
