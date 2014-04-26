#ifndef FILTERS_LOADED_
#define FILTERS_LOADED_
#include<stdio.h>
#include<string.h>

#include "proof.h"
#include "proof_tree.h"
#include "restriction.h"

#include "divisor.h"

#include "easy_filters.h"
#include "flag.h"


typedef struct filtertype
{
    char label; // e for easy filters,
                // f for flag

    int value;  // specifies number of easy filter
                // or depth for flag (this is not implemented right now)
} filtertype;


//extern bool flag_shows_nef(divisor *pDiv, ptree *pTree, fdata_list *pFdatum);

#endif
