#ifndef BIG_ARITHMETIC_LOADED
#define BIG_ARITHMETIC_LOADED

#include "list.h"

typedef medint base_integer_type, baseint, bint;

typedef enum sign_t {
  POS, NEG
} sign_t;

#define MAX_BIGINT_DIGIT 9

// unsigned big integer (mainly used internally only)
typedef list bzu_t;

typedef list_node big_digit;

// signed big integer
typedef struct bz_t {
  bzu_t *pMagnitude;
  sign_t sign;
} bz_t;

// big rational numbers
typedef struct bq_t {
  sign_t sign;
  bzu_t *pNum;
  bzu_t *pDen;
} bq_t;

typedef struct binterval {
  bool no_lb;
  bool no_ub;
  bq_t *pUb;
  bq_t *pLb;
} binterval;

typedef struct bfunctiontype {
  bq_t *pAlpha;
  bq_t *pBeta;
} bfunctiontype;


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// BASEINT FUNCTIONS
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

extern baseint *base_new();
extern bool base_compare(void *pNum1, void *pNum2);
extern void *base_copy(void *pNum);
extern void base_destroy(void *pNum);
extern void base_display(void *pNum);
extern void base_list_display(void *pList);



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// BIGINT FUNCTIONS 
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

#define bzu_new() list_new(base_compare, base_copy, base_destroy, \
                           base_list_display)

#define bzu_kill(b) list_kill(b)

#define bzu_copy(b) list_copy(b)

#define bzu_display(b) list_display(b)

#define bzu_is_zero(b) list_empty(b)

extern void bzu_display_file(FILE *outfile, bzu_t *pBig);

extern void bzu_canonicalize(bzu_t *pBig);

extern bzu_t *base_to_big(baseint b);

extern bzu_t *make_bigint(baseint a);
extern bzu_t *bzu_plus(bzu_t *pBig1, bzu_t *pBig2);
extern bzu_t *bzu_minus(bzu_t *pBig1, bzu_t *pBig2);
extern bzu_t *bzu_times(bzu_t *pBig1, bzu_t *pBig2);
extern bzu_t *bzu_divide(bzu_t *pA, bzu_t *pD);
extern bzu_t *bzu_gcd(bzu_t *pA, bzu_t *pB);
extern bzu_t *bzu_times_base(bzu_t *pBig, baseint b);
extern bool bzu_eq(bzu_t *pBig1, bzu_t *pBig2);
extern bool bzu_leq(bzu_t *pBig1, bzu_t *pBig2);
extern bool bzu_geq(bzu_t *pBig1, bzu_t *pBig2);
extern bzu_t *bzu_scan();
extern bzu_t *bzu_read();


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// BIGINT LISTS
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


extern bool bzu_compare(void *pBig1, void *pBig2);
extern void *bzu_copy_void(void *pBig);
extern void bzu_kill_void(void *pBig);
extern void bzu_list_display(void *pBigList);

#define bzu_list_new() list_new(bzu_compare, bzu_copy_void, bzu_kill_void, \
				bzu_list_display)

#define bzu_list_kill(l) list_kill(l)

extern bzu_t *bzu_list_sum(list *pBigList);



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// SIGNED BIGINT FUNCTIONS
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

extern bz_t *base_to_sbig(baseint b);
extern bz_t *bz_copy(bz_t *pSbig);
extern bz_t *bz_plus(bz_t *pSbig1, bz_t *pSbig2);
extern bz_t *bz_plus_g(bz_t *pSbig1, bz_t *pSbig2);
extern bz_t *bz_minus(bz_t *pSbig1, bz_t *pSbig2);
extern bz_t *bz_times(bz_t *pSbig1, bz_t *pSbig2);
extern bz_t *bz_times_base(bz_t *pSbig, baseint b);
extern bool bz_leq(bz_t *pSbig1, bz_t *pSbig2);
extern bool bz_geq(bz_t *pSbig1, bz_t *pSbig2);
extern void bz_display(bz_t *pSbig);
extern bool bz_is_zero(bz_t *pSbig);
extern bool bz_is_nonnegative(bz_t *pSbig);
extern void bz_display_file(FILE *outfile, bz_t *pSbig);

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// SBIGINT LISTS
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

extern bool bz_compare(void *pSbig1, void *pSbig2);
extern void *bz_copy_void(void *pSbig);
extern void bz_kill_void(void *pSbig);
extern void bz_display_void(void *pSbig);
extern void bz_list_display(void *pSbigList);

#define bz_list_new() list_new(bz_compare, bz_copy_void,\
                                 bz_kill_void, bz_list_display)

#define bz_list_kill(l) list_kill(l)



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// BIG RATIONAL NUMBERS
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


// assignes copies of original data. 
extern bq_t *bq_make(bz_t *pNum, bz_t *pDen);
extern bq_t *bq_new();
extern void bq_reduce(bq_t *pRat);
extern void bq_kill(bq_t *pRat);

///////////////////////////////////////////////////
// bzu_t *bq_den(bq_t *pRat);
// bzu_t *bq_num(bq_t *pRat);
//
//      macros below:
///////////////////////////////////////////////////
#define bq_den(b) ((b)->pDen)
#define bq_num(b) ((b)->pNum)

///////////////////////////////////////////////////
// sign_t bq_sign(bq_t *pRat); macro below
///////////////////////////////////////////////////
#define bq_sign(b) ((b)->sign)


extern void bq_canonicalize(bq_t *pRat);


extern void bq_negate(bq_t *pRat);
extern bq_t *bq_copy(bq_t *pRat);
extern bool bq_leq(bq_t *pRat1, bq_t *pRat2);
extern bool bq_geq(bq_t *pRat1, bq_t *pRat2);
extern bq_t *bq_max(bq_t *pRat1, bq_t *pRat2);
extern bq_t *bq_min(bq_t *pRat1, bq_t *pRat2);
extern bq_t *bq_times(bq_t *pRat1, bq_t *pRat2);
extern bq_t *bq_plus(bq_t *pRat1, bq_t *pRat2);
extern bq_t *bq_minus(bq_t *pRat1, bq_t *pRat2);
extern void bq_display(bq_t *pRat);
extern bz_t *bq_signed_num(bq_t *pRat);
extern bz_t *bq_signed_den(bq_t *pRat);
extern void free_signed_num_den(bz_t *pSbig);
extern void signed_num_den_list_kill(list *pSNDL);

extern void bq_display_file_latex(FILE *outfile, bq_t *pRat);


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// BRAT LISTS
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


extern bool bq_compare(void *pBrat1, void *pBrat2);
extern void *bq_copy_void(void *pBrat);
extern void bq_kill_void(void *pBrat);
extern void bq_list_display(void *pBratList);

#define bq_list_new() list_new(bq_compare, bq_copy_void,\
                                 bq_kill_void, bq_list_display)

#define bq_list_kill(l) list_kill(l)



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// RATIONAL INTERVAL ARITHMETIC
// we use the convention that for intervals, assigned endpoints are always
// copies (not originals). That is to say, the bratl #'s in the endpoints
// can be killed by interval killing procedures without affecting those
// numbers in the rest of the program.
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

extern binterval *binterval_new();
extern void binterval_kill(binterval *pBI);
extern void binterval_list_kill(list *pBintervalList);
extern void binterval_unbound(binterval *pI);
extern void binterval_set_lb(binterval *pI, bq_t *pLb);
extern void binterval_set_ub(binterval *pI, bq_t *pUb);
extern binterval *binterval_make(bq_t *pLb, bq_t *pUb);
extern binterval *binterval_copy(binterval *pInterval);
extern void binterval_assign(binterval *pI1, binterval *pI2);
extern binterval *binterval_positive_axis();
extern bool binterval_empty(binterval *pI);
extern binterval *binterval_intersect(binterval *pI1, binterval *pI2);
extern void binterval_display(binterval *pI);


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// BINTERVAL LISTS
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


extern bool binterval_compare(void *pBinterval1, void *pBinterval2);
extern void *binterval_copy_void(void *pBinterval);
extern void binterval_kill_void(void *pBinterval);
extern void binterval_list_display(void *pBintervalList);

#define binterval_list_new() list_new(binterval_compare, binterval_copy_void,\
                                 binterval_kill_void, binterval_list_display)

#define binterval_list_kill(l) list_kill(l)



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// The following functions takes two rational numbers       
// alpha and beta and finds the largest interval such that  
// the function alpha + beta / x is between 0 and 1 in this 
// interval (but interval is always assumed to be to the    
// right of the origin.)                                    
//////////////////////////////////////////////////////////////
extern void bzu_find_valid_interval(bq_t *alpha_p, bq_t *beta_p, 
				    binterval *I_p);

///////////////////////////////////////////////////////////////////
// This function is slightly misnamed. the answer it gives is     
// might not be mathematically correct at 0. It will give the     
// closed interval [0, whatever] as an answer even though all the 
// functions given will have poles at 0! Be warned...             
// It also ignores solutions on the left of the origin            
// In fact, after a little thought, this will always give an      
// interval to the right of the origin, period.                   
////////////////////////////////////////////////////////////////////
extern void bzu_find_positive_interval(bq_t *a_p, bq_t *b_p, binterval *I_p);


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// BIG FORMULA
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


extern bfunctiontype *bform_make(bq_t *pAlpha, bq_t *pBeta);
extern bq_t *bform_solve_for_0(bfunctiontype *pFormula);
extern bq_t *bform_solve_for_1(bfunctiontype *pFormula);
extern binterval *binterval_solve_zero_one(bfunctiontype *pFormula);
extern binterval *binterval_solve_positive(bfunctiontype *pFormula);
extern void bform_display(bfunctiontype *pFormula);
extern void bform_kill(bfunctiontype *pFormula);

extern bq_t *bform_eval(bfunctiontype *pFormula, bq_t *pX);

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////
//               GARBAGE COLLECTION                              //
///////////////////////////////////////////////////////////////////
//
//   we define here alternative computation functions which place their
//   results onto a garbage list. The results which should be kept need
//   to be copied, and the remaining ones are freed from memory be the
//   empty_garbage command.
//   
// COMMAND LIST :      GARBAGE VERSION         ORIGINAL VERSION
//                     bplus                   bzu_plus
//		       bminus                  bzu_minus
//		       btimes                  bzu_times
//		       sbplus                  bz_plus
//		       sbminus                 bz_minus
//		       sbtimes                 bz_times
//		       snum                    bq_signed_num
//		       sden                    bq_signed_den
//		       base2sbig               base_to_sbig
//		       bintersect              binterval_intersect
//		       
/////////////////////////////////////////////////////////////////////////


//   BIGINT GARBAGE

list *pBzu_garbage_;
list *pBz_garbage_;
list *pBinterval_garbage_;

extern bzu_t *bplus(bzu_t *px, bzu_t *py);
extern bzu_t *btimes(bzu_t *px, bzu_t *py);
extern bzu_t *bminus(bzu_t *px, bzu_t *py);
extern bz_t *sbplus(bz_t *px, bz_t *py);
extern bz_t *sbtimes(bz_t *px, bz_t *py);
extern bz_t *sbminus(bz_t *px, bz_t *py);
extern bz_t *snum(bq_t *pBrat);
extern bz_t *sden(bq_t *pBrat);
extern bz_t *base2sbig(baseint b);
extern binterval *bintersect(binterval *pI1, binterval *pI2);

#define start_garbage \
pBzu_garbage_ = bzu_list_new();\
pBz_garbage_ = bz_list_new();\
pBinterval_garbage_ = binterval_list_new();
 
#define empty_garbage \
list_kill(pBzu_garbage_);\
list_kill(pBz_garbage_);\
list_kill(pBinterval_garbage_)


#endif
