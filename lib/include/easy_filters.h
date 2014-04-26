#ifndef DIVISOR_LOADED
#include "divisor.h"
#endif

//////////////////////////////////////////////////////////////////
// condition1_shows_nef -- takes a divisor (pointer) and       
//                   verifies whether it is NEF by condition 1 
//                                                             
// condition 1 checks that for each i,                          
// delta_i coeff is >= delta_0 coeff                           
// or delta_i coeff =0                                         
/////////////////////////////////////////////////////////////////
extern int condition1_shows_nef(struct divisor *div_ptr);



///////////////////////////////////////////////////////////////////
// condition 2 shows nef:
//
// divisor is nef if for each i, 
//
// 2 * b_1 >= b_i >= b_1
// 
// or 
//
// b_i = 0
//
///////////////////////////////////////////////////////////////////
extern int condition2_shows_nef(struct divisor *div_ptr);


///////////////////////////////////////////////////////////////
// condition 3 shows nef:
// 
// divisor is nef if
//
//   b_i <= b_1 for all i>=1
//
///////////////////////////////////////////////////////////////
extern int condition3_shows_nef(struct divisor *div_ptr);

extern int condition3a_shows_nef(struct divisor *div_ptr);

/***************************************************************
 * condition4_shows_nef -- checks to see if a divisor pulls    *
 *                               back to zero (flag map)       *
 * checks that for each i between 2 and g/2 (floor), that      *
 * bi * (g - 1) = i * (g - i) * b1                             *
 ***************************************************************/
extern int condition4_shows_nef(struct divisor *div_ptr);


/***************************************************************
 * condition5_shows_nef -- checks to see if a divisor pulls    *
 *    back to 0 with respect to the rational map               *
 ***************************************************************/
extern int condition5_shows_nef(divisor *pDiv);


////////////////////////////////////////////////////////////////
// checks if any of the coefficients of the delta are = to 0
// and genus is odd or
// if even then b_i = 0 for i < g/2 then nef
////////////////////////////////////////////////////////////////
extern int condition6_shows_nef(divisor *pDiv);


////////////////////////////////////////////////////////////////
//
// pDiv is nef if  
//
//       max{b_i | i >= 2} <= min{b_i | i >= 1}
//
////////////////////////////////////////////////////////////////
extern bool condition7_shows_nef(divisor *pDiv);


////////////////////////////////////////////////////////////////
//
// pDiv is nef if :
//
// for 2 <= i <= g/2,
//
//   -b_0 * (g-1) < i * (g - i) * (b_1 - b_0) + (g - 1) * (b_0 - b_1) < 0
//
////////////////////////////////////////////////////////////////
extern int condition8_shows_nef(divisor *pDiv);

extern bool easy_filter_shows_nef(divisor *pDiv, int filternum);








