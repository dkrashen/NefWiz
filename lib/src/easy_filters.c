#include "easy_filters.h"

int condition1_shows_nef(struct divisor *pDiv) 
{
    int temp = 1;
    int counter;
    
    for (counter = 1 ; counter <= (div_maxdelta(pDiv)) ; counter++) {
	if ((div_delta(pDiv, counter) < div_delta(pDiv, 0)) && 
	    (div_delta(pDiv, counter) != 0))
	    temp = 0;
    }
    return temp;
}

int condition2_shows_nef(struct divisor *pDiv) 
{
    int temp = 1;
    int counter;
    
    for (counter = 1 ; counter <= (pDiv->maxdelta) ; counter++) {
	if (((div_delta(pDiv, counter) < div_delta(pDiv, 1)) || 
	     (div_delta(pDiv, counter) > 2 * div_delta(pDiv, 1))) &&
	    (div_delta(pDiv, counter) != 0))
	    temp = 0;
    }
    return temp;
}

int condition3_shows_nef(struct divisor *pDiv) 
{
    int temp = 1;
    int counter;
    
    for (counter = 1 ; counter <= (pDiv->maxdelta) ; counter++) {
	if ((div_delta(pDiv, counter) > div_delta(pDiv, 1)))
	    temp = 0;
    }
    return temp;
}

int condition3a_shows_nef(struct divisor *pDiv) 
{
    int temp = 1;
    int counter;
    
    for (counter = 1 ; counter <= (pDiv->maxdelta) ; counter++) {
	if ((3 * div_delta(pDiv, counter) > 4 * div_delta(pDiv, 1)))
	    temp = 0;
    }
    return temp;
}

int condition4_shows_nef(struct divisor *pDiv) 
{
    int temp = 1;
    int i;
    int g;
    g = pDiv->genus;
    for (i = 2 ; i < pDiv->maxdelta ; i++) {
	if (div_delta(pDiv, i) * (g - 1) != 
	    i * (g - i) * div_delta(pDiv, 1))
	    temp = 0;
    }
    return temp;
}

int condition5_shows_nef(divisor *pDiv)
{
    bool valid = TRUE;
    smallint i;
    int epsilon;
    medint b_max, b_min, b_1;
    smallint g = div_genus(pDiv);
    int answer;

    b_1 = div_delta(pDiv, 1);


    b_min = div_delta(pDiv, 1);
    for (i = 3 ; i <= div_maxdelta(pDiv) ; i++)
    {
	b_min = min(b_min, div_delta(pDiv, i));
    }

    b_max = div_delta(pDiv, 1);
    for (i = 3 ; i <= div_maxdelta(pDiv) ; i++)
    {
	b_max = max(b_max, div_delta(pDiv, i));
    }

    if (2 * b_min - b_max >= 0)
	answer = TRUE;
    else
	answer = FALSE;

    return answer;
}

int condition6_shows_nef(divisor *pDiv)
{
    bool answer = FALSE;
    smallint i;

    if ((div_genus(pDiv) % 2) == 0)
    {
	for (i = 0 ; 
	     (i < div_maxdelta(pDiv)) && (answer == FALSE) ; 
	     i++)
	{
	    if (div_delta(pDiv, i) == 0)
		answer = TRUE;
	}
    }
    else
    {
	for (i = 0 ; 
	     (i <= div_maxdelta(pDiv)) && (answer == FALSE) ; 
	     i++)
	{
	    if (div_delta(pDiv, i) == 0)
		answer = TRUE;
	}
    }
    return answer;
}

bool condition7_shows_nef(divisor *pDiv)
{
    smallint b_min, b_max;
    bool answer;
    int i;

    b_min = div_delta(pDiv, 1);
    for (i = 2 ; i <= div_maxdelta(pDiv) ; i++)
    {
	b_min = min(b_min, div_delta(pDiv, i));
    }

    b_max = div_delta(pDiv, 2);
    for (i = 3 ; i <= div_maxdelta(pDiv) ; i++)
    {
	b_max = max(b_max, div_delta(pDiv, i));
    }

    if (b_max <= 2 * b_min)
	answer = TRUE;
    else
	answer = FALSE;

    return answer;
}

int condition8_shows_nef(divisor *pDiv)
{
    bool answer;
    smallint i, g;

    g = div_genus(pDiv);

    answer = TRUE;
    for (i = 2 ; (i <= div_maxdelta(pDiv)) && (answer) ; i++)
    {
	int term;
	term = (i * (g - i) * (div_delta(pDiv, 1) - div_delta(pDiv, 0)) + 
		(g - 1) * (div_delta(pDiv, 0) - div_delta(pDiv, i)));

	if (term < - div_delta(pDiv, 0) * (g - 1))
	    answer = FALSE;
	if (term > 0)
	    answer = FALSE;
    }

    return answer;
}


bool easy_filter_shows_nef(divisor *pDiv, int filternum)
{
    bool answer;

    if (filternum == 1)
	answer = condition1_shows_nef(pDiv);
    else if (filternum == 2)
	answer = condition2_shows_nef(pDiv);
    else if (filternum == 3)
	answer = condition3_shows_nef(pDiv);
    else if (filternum == 4)
	answer = condition4_shows_nef(pDiv);
    else if (filternum == 5)
	answer = condition5_shows_nef(pDiv);
    else if (filternum == 6)
	answer = condition6_shows_nef(pDiv);
    else if (filternum == 9)
	answer = condition3a_shows_nef(pDiv);
    else if (filternum == 7)
	answer = condition7_shows_nef(pDiv);
    else if (filternum == 8)
	answer = condition8_shows_nef(pDiv);
    else 
	answer = FALSE;

    return answer;
}

