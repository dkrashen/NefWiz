#ifndef RESTRICTION_LOADED
#define RESTRICTION_LOADED

#include<math.h>

#include "divisor.h"
#include "big_arithmetic.h"
#include "list.h"

//////////////////////////////////////////////////////////////
// this is the largest number n for which the F conjecture
// on M_{0, n} is true. we use this to decide which coeffs 
// (triples) need to be checked when they are generated. 
//////////////////////////////////////////////////////////////
#define CURRENT_F_BOUND 6

///////////////////////////////////////////////////////////////
// sequences, aka restriction sequences represent the sets
// A, B, A-B in the problem. These are multisets - repitition
// is allowed and meaningful. These are implemented as
// medint lists in basic_lists.h
///////////////////////////////////////////////////////////////
typedef multiset seq, seq_t;
typedef set seq_set, seq_s_t;
typedef set_node seq_node;

///////////////////////////////////////////////////////////////
// Triples and triple sets represent the basic data types.
// triple sets should not have repetitions and should be
// carefully implemented with this in mind.
//////////////////////////////////////////////////////////////
typedef struct triple 
{
    seq *pB;  
    seq *pBc; 
    medint y;
    smallint g;
    smallint z;
} triple;

typedef set t_set;
typedef mlat t_mlat;

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// RESTRICTION SEQUENCES
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// since these are implemented as medint lists, seq_kill destroys data
// (doesn't debone.)

#define seq_new medint_list_new
#define seq_kill list_kill
#define seq_kill_node list_kill_node
#define seq_debone list_debone
#define seq_length list_length
#define seq_empty list_empty
#define seq_push_head list_push_head
#define seq_push list_push
#define seq_concat list_concat
#define seq_copy list_copy
#define seq_copy_skeleton list_copy_skeleton
#define seq_display list_display
#define seq_while_do list_while_do
#define seq_do_each list_do_each
#define seq_sum medint_list_sum
#define seq_is_member multiset_is_member
#define seq_is_subseq multiset_is_submultiset
#define seq_equals multiset_equals
#define seq_powerset multiset_powerset
#define seq_subseqs multiset_subsets
#define seq_subseq_complement multiset_submultiset_complement

#define seq_read medint_list_read

#define seq_a(s) seq_length(s)
#define seq_z(s, g) g - seq_sum(s)


////////////////////////////////////////////////////////////////
// compares the sequences to see which would likely be easier
// to restrict to. currently compares length only.
////////////////////////////////////////////////////////////////
extern bool seq_lessthan(void *pSeq1, void *pSeq2);


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// SEQUENCE SETS (sets of sequences)
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// this generates a seq_set (metalist). Compare is seq_equals
// (multiset_equals) as above.
///////////////////////////////////////////////////////////////////
extern seq_set *seq_set_new();

#define seq_set_is_member set_is_member
#define seq_set_is_sublat set_is_subset
#define seq_set_equals set_equals
#define seq_set_kill set_kill
#define seq_set_kill_node set_kill_node
#define seq_set_debone set_debone
#define seq_set_length set_length
#define seq_set_empty set_empty
#define seq_set_concat set_concat
#define seq_set_copy set_copy
#define seq_set_copy_skeleton set_copy_skeleton
#define seq_set_display set_display
#define seq_set_while_do set_while_do
#define seq_set_do_each set_do_each
#define seq_set_head set_head
#define seq_set_push set_push
#define seq_set_true_for_some set_true_for_some
#define seq_set_true_for_all set_true_for_all
#define seq_set_get_node set_get_node
#define seq_set_force_push list_push


extern seq_set *seq_set_associated_to_t_set(t_set *pTset);


extern seq_set *seq_set_to_check(t_set *pTset, t_set *pIncluded, 
				 smallint genus);




////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// TRIPLES
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

extern triple *triple_makeAB(smallint genus, smallint y, seq *pA, seq *pB);
extern triple *triple_makeBBc(smallint genus, smallint y, seq *pB, seq *pBc); 
extern void triple_kill(triple *pT);
extern void triple_display(triple *pT);

#define triple_copy(t) triple_makeBBc((t)->g, (t)->y, (t)->pB, (t)->pBc)
#define triple_complementary(t) \
 triple_makeBBc((t)->g, (t)->z - (t)->y, (t)->pBc, (t)->pB)

////////////////////////////////////////////////////////////
// these macros retrieve the basic data from the triple :
// its sequence, complementary sequence, y value, z value, 
// and genus.
////////////////////////////////////////////////////////////
#define triple_B(t) ((t)->pB)
#define triple_Bc(t) ((t)->pBc)
#define triple_y(t) ((t)->y)
#define triple_z(t) ((t)->z)
#define triple_g(t) ((t)->g)

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// TRIPLE SETS
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

extern bool t_eq(void *pT1, void *pT2);
extern void *t_copy(void *pT);
extern void t_destroy(void *pT);
extern void t_set_display_void_(void *pTset);

#define t_set_new() (list_new(t_eq, t_copy, t_destroy, t_set_display_void_))

#define t_set_head set_head
#define t_set_kill set_kill
#define t_set_kill_node set_kill_node
#define t_set_debone set_debone
#define t_set_length set_length
#define t_set_empty set_empty
#define t_set_concat set_concat
#define t_set_copy set_copy
#define t_set_copy_skeleton set_copy_skeleton
#define t_set_display set_display
#define t_set_while_do set_while_do
#define t_set_do_each set_do_each
#define t_set_true_for_some set_true_for_some
#define t_set_true_for_all set_true_for_all
#define t_set_is_member set_is_member
#define t_set_is_subset set_is_subset
#define t_set_equals set_equals
#define t_set_push set_push
#define t_set_force_push set_force_push
#define t_set_subset_complement set_subset_complement


////////////////////////////////////////////////////////////////
// compares the triple sets to see which would likely be easier
// to restrict to. currently compares length only.
////////////////////////////////////////////////////////////////
extern bool t_set_lessthan(void *pTset1, void *pTset2);

extern smallint t_set_maximum_complementary_length(smallint t_set_length);

///////////////////////////////////////////////////////////////////////
// creates a triple set of all the elements in the given set together
// with their complementary triples
///////////////////////////////////////////////////////////////////////
extern t_set *t_set_complementary_pairs(t_set *pTset, smallint genus);

///////////////////////////////////////////////////////////////////////
// creates a triple set consisting of the coefficients associated to
// the restriction sequence.
///////////////////////////////////////////////////////////////////////
extern t_set *t_set_associated_to_seq(smallint genus, seq *pSeq);


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// formulas come in two types : zero and c
// 
// for a zero formula to show that a given triple set works, we
// must see that the formula is nonnegative on each triple, and then
// restrict to each triple for which the value is nonzero.
//
// for a c formula, things works in almost the same way, however we 
// only need to restrict to a triple if the value of the formula is 
// strictly larger than 1.
//
//
//
// the formulas come naturally in pairs consisting of a '0' and a 'c'
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// return a formula of the form     alpha + beta/c
typedef bfunctiontype *(*formula_c_type)(divisor *, triple *);

// return signed big integers
typedef bz_t *(*formula_0_type)(divisor *, triple *);

// a condition to check whether or not the formula applies
typedef bool (*formula_condition_type)(smallint a);

////////////////////////////////////////////////////////////////
// keep track of formulas together with a condition which says
// when the formula applies. used as global variables in the
// flag filter.
////////////////////////////////////////////////////////////////
typedef struct formula_data
{
    // this is either 0 or c, depending on the type of data stored
    char type;

    char label[100];

    formula_0_type formula_0;
    formula_c_type formula_c;

    // true if formula applies, false otherwise
    formula_condition_type condition;
} fdata, fdata_t;

typedef list fdata_list, fdata_l_t;


extern fdata *fdata_make_0(char label[], formula_0_type formula_0, 
			   formula_condition_type formula_condition);

extern fdata *fdata_make_c(char label[], formula_c_type formula_c, 
			   formula_condition_type formula_condition);

extern fdata *fdata_copy(fdata *pFdata);

extern void fdata_kill(fdata *pFdata);

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// FORMULA DATA LISTS : hold formula data. data entries are not
// killed. list_kill only destroys struct allocation.
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
extern bool do_nothing_compare_data(void *a, void *b);
extern void fdata_destroy(void *a);
extern void fdata_display_list_void(void *l);
extern void *fdata_copy_void(void *pFdata);

extern void fdata_display_file(FILE *outfile, fdata *pFdata);

#define fdata_list_new() list_new(do_nothing_compare_data, \
 fdata_copy_void, fdata_destroy, fdata_display_list_void)

#define fdata_list_kill list_kill
#define fdata_list_copy list_copy
#define fdata_list_kill_node list_kill_node
#define fdata_list_length list_length
#define fdata_list_empty list_empty
#define fdata_list_push_head list_push_head
#define fdata_list_while_do list_while_do
#define fdata_list_do_each list_do_each
#define fdata_list_head list_head
#define fdata_list_complement list_complement
#define fdata_list_get_node list_get_node
#define fdata_list_push list_push
#define fdata_list_display list_display
#define fdata_list_true_for_some list_true_for_some
#define fdata_list_true_for_all list_true_for_all
#define fdata_list_kill_each_if list_kill_each_if


extern fdata_list *fdata_list_applicable_formulas(divisor *pDiv, t_set *pTset,
						  fdata_list *pFdataList, 
						  smallint a);


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// TOOLS FOR 0 FORMULAS
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

extern bool formula_nonnegative(divisor *pDiv, t_set *pTset, 
				bz_t *(*formula)(divisor *, triple *));

extern t_set *zero_triples(divisor *pDiv, t_set *pTset, 
			   bz_t *(*formula)(divisor *, triple *));


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// TOOLS FOR C FORMULAS
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// returns the intersection of all the [0,1] intervals for given tripleset
////////////////////////////////////////////////////////////////////////////
extern binterval *included_triples_interval(divisor *pDiv, 
					    t_set *pIncluded_Triples,
					    formula_c_type formula);

//////////////////////////////////////////////////////////////////////////////
// returns the intersection of all the positive intervals for given tripleset
//////////////////////////////////////////////////////////////////////////////
extern binterval *positive_triples_interval(divisor *pDiv, t_set *pTriples, 
					    formula_c_type formula);



///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
// TRIPLE SET / FORMULA STUFF
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

// displays coefficient data such as :
//    positive interval
//    [0,1] interval
//    explicit formula
extern void coeff_display_everything(divisor *pDiv, triple *pT, 
				     formula_c_type formula, bq_t *pX);

extern void coeffs_display_everything(divisor *pDiv, t_set *pTset, 
				      formula_c_type formula, bq_t *pX);


////////////////////////////////////////////////////////////////////////////
// the following function assumes the formula's condition is satisfied.
// to save time, we generally run this only on 'applicable' formulas.
// for 'c' formulas, this means that the positive interval is nonempty,
// and for '0' formulas, this means that it is nonnegative. 
////////////////////////////////////////////////////////////////////////////
extern bool t_set_subset_formula_ok(divisor *pDiv, t_set *pTset, 
				    t_set *pIncluded_Triples, fdata *pFdata);

extern binterval *t_set_subset_formula_c_interval(divisor *pDiv, t_set *pTset, 
						  t_set *pIncluded_Triples, 
						  fdata *pFdata);

extern bool t_set_subset_some_applicable_formula_ok(divisor *pDiv, 
						    t_set *pTset, 
						    t_set *pIncluded_Triples, 
						    fdata_list *pFdataList,
						    smallint a);

extern bool t_set_subset_some_formula_ok(divisor *pDiv, t_set *pTset, 
					 t_set *pIncluded_Triples, 
					 fdata_list *pFdataList);

extern bool fdata_negative(divisor *pDiv, t_set *pTset, fdata *pFdata);


/////////////////////////////////////////////////////////////////////////
// returns a select few maximal subsets to check. Current setting:
// one maximal from the c_formulas, and one maximal from the 0 formulas.
/////////////////////////////////////////////////////////////////////////
extern t_mlat *t_mlat_some_maximals(divisor *pDiv, t_set *pTset, 
				    fdata_list *pFdatum, smallint a);




/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//
//  SPECIFIC FORMULAS:
//
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

extern bfunctiontype *formula_46_c(divisor *pDiv, triple *pT);
extern bz_t *formula_46_0(divisor *pDiv, triple *pT);
extern bool formula_46_applicable(smallint a);

extern bfunctiontype *formula_45_c(divisor *pDiv, triple *pT);
extern bz_t *formula_45_0(divisor *pDiv, triple *pT);
extern bool formula_45_applicable(smallint a);

extern bfunctiontype *formula_56_c(divisor *pDiv, triple *pT);
extern bz_t *formula_56_0(divisor *pDiv, triple *pT);
extern bool formula_56_applicable(smallint a);

extern bfunctiontype *formula_47_c(divisor *pDiv, triple *pT);
extern bz_t *formula_47_0(divisor *pDiv, triple *pT);
extern bool formula_47_applicable(smallint a);

extern bfunctiontype *formula_26_c(divisor *pDiv, triple *pT);
extern bz_t *formula_26_0(divisor *pDiv, triple *pT);
extern bool formula_26_applicable(smallint a);

extern bfunctiontype *formula_16_c(divisor *pDiv, triple *pT);
extern bz_t *formula_16_0(divisor *pDiv, triple *pT);
extern bool formula_16_applicable(smallint a);

extern bfunctiontype *formula_36_c(divisor *pDiv, triple *pT);
extern bz_t *formula_36_0(divisor *pDiv, triple *pT);
extern bool formula_36_applicable(smallint a);

extern bfunctiontype *formula_27_c(divisor *pDiv, triple *pT);
extern bz_t *formula_27_0(divisor *pDiv, triple *pT);
extern bool formula_27_applicable(smallint a);

extern bfunctiontype *formula_37_c(divisor *pDiv, triple *pT);
extern bz_t *formula_37_0(divisor *pDiv, triple *pT);
extern bool formula_37_applicable(smallint a);

extern bfunctiontype *formula_25_c(divisor *pDiv, triple *pT);
extern bz_t *formula_25_0(divisor *pDiv, triple *pT);
extern bool formula_25_applicable(smallint a);

extern bfunctiontype *formula_35_c(divisor *pDiv, triple *pT);
extern bz_t *formula_35_0(divisor *pDiv, triple *pT);
extern bool formula_35_applicable(smallint a);

extern bfunctiontype *formula_17_c(divisor *pDiv, triple *pT);
extern bz_t *formula_17_0(divisor *pDiv, triple *pT);
extern bool formula_17_applicable(smallint a);

extern bfunctiontype *formula_15_c(divisor *pDiv, triple *pT);
extern bz_t *formula_15_0(divisor *pDiv, triple *pT);
extern bool formula_15_applicable(smallint a);


#endif

