#include "divisor.h"

//////////////////////////////////////////////////////////
// PRELIMINARIES
//////////////////////////////////////////////////////////

#define MAX_BUFFER_ 1000

static medint get_num()
{
  char buffer[MAX_BUFFER_];
  smallint counter;
  medint value;
  buffer[0] = fgetc(stdin);

  // read until we find a digit             

  while ((isdigit(buffer[0]) == 0) && (buffer[0] != '-')) {
    buffer[0] = fgetc(stdin);
  }
  
  // Now read until we find a non-digit
  counter = 0;
  while (isdigit(buffer[counter]) != 0) {
    counter++;
    buffer[counter] = fgetc(stdin);
  }


  // We now insert an end of string character to the buffer,
  // which will also overwrite the final invalid character read
  
  buffer[counter] = '\0';

  // Finally, we give the value to the integer variable pointed to
  
  sscanf(buffer, "%d", &value);

  return value;
}



static void number_reader(int *num_ptr) {
  char buffer[MAX_BUFFER_];
  int counter;
  buffer[0] = fgetc(stdin);

  /* read until we find a digit              */

  while ((isdigit(buffer[0]) == 0) && (buffer[0] != '-')) {
    buffer[0] = fgetc(stdin);
  }
  
  /* Now read until we find a non-digit */
  counter = 0;
  while (isdigit(buffer[counter]) != 0) {
    counter++;
    buffer[counter] = fgetc(stdin);
  }


  /* We now insert an end of string character to the buffer,
     which will also overwrite the final invalid character read    */
  
  buffer[counter] = '\0';

  /* Finally, we give the value to the integer variable pointed to */
  
  sscanf(buffer, "%d", num_ptr);
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////



divisor *div_new(smallint genus)
{
    divisor *pNewDiv;
    smallint maxdelta = genus / 2;

    pNewDiv = (divisor *) malloc(sizeof(divisor));

    pNewDiv->genus = genus;
    pNewDiv->pDelta = line_new(maxdelta + 1);

    pNewDiv->maxdelta = maxdelta;

    return pNewDiv;
}

void div_kill(divisor *pDiv)
{
    line_kill(pDiv->pDelta);
    free(pDiv);
}

static int first_num_in_string(char s[])
{
    int i;
    
    for (i = 0 ; !isdigit(s[i]) ; i++);

    return i;
}

static int next_num_in_string(char s[])
{
    int i, j;
    
    for (i = 0 ; isdigit(s[i]) ; i++);
    for (j = i ; !isdigit(s[j]) ; j++);
    
    return j;
}

void div_display(divisor *pDiv)
{
    // First print coefficient of lambda
    printf("%4d ", pDiv->lambda);
    
    // Next print the delta's using line commands
    line_display(pDiv->pDelta);
}



void div_display_file(FILE *outfile, divisor *pDiv)
{
    // First print coefficient of lambda
    fprintf(outfile, "%4d ", pDiv->lambda);
    
    // Next print the delta's using line commands
    line_display_file(outfile, pDiv->pDelta);
}

divisor *div_read(char s[], smallint genus)
{
    int current_delta;
    int i;
    int data;
    divisor *pRead;
    smallint maxdelta;

    pRead = div_new(genus);

    maxdelta = genus / 2;

    i = first_num_in_string(s);
    s = &(s[i]);

    sscanf(s, "%d", &(pRead->lambda));

    for (current_delta = 0 ; current_delta <= maxdelta ; current_delta++)
    {
	i = next_num_in_string(s);
	s = &(s[i]);
	sscanf(s, "%d", &data);
	line_push(pRead->pDelta, data);
    }

    return pRead;
}

divisor *div_vread(char *s[], smallint genus)
{
    int current_delta;
    int i;
    int data;
    divisor *pRead;
    smallint maxdelta;

    pRead = div_new(genus);

    maxdelta = genus / 2;

    sscanf(s[0], "%d", &(pRead->lambda));

    for (current_delta = 0 ; current_delta <= maxdelta ; current_delta++)
    {
	sscanf(s[current_delta+1], "%d", &data);
	fflush(stdout);
	line_push(pRead->pDelta, data);
    }

    return pRead;
}

void div_lrs_input(divisor *pDiv)
{
    smallint counter;
    
    // We first clear the divisor
    div_clear(pDiv);
    
    // First number should be the coefficient of lambda
    pDiv->lambda = get_num();
    
    // Next should be the coefficients of delta which go from 0 to maxdelta
    for (counter = 0 ; counter <= div_maxdelta(pDiv) ; counter++)
	line_push(pDiv->pDelta, get_num());

}


medint div_sum_delta_in_list(divisor *pDiv, list *pList)
{
    medint answer = 0;

    list_node *pNode;

    for (pNode = pList->pHead ;
	 pNode != NULL ;
	 pNode = pNode->pNext)

	answer += div_delta(pDiv, *((medint *) (pNode->pData)));

    return answer;
}

//////////////////////////////////////////////////////////////////////
// STUFF TO CHECK IF F
//////////////////////////////////////////////////////////////////////
int reduce(int genus, int i)
{
  int dummy;

  if (i > (genus / 2))
    dummy = genus - i;
      else dummy = i;

  return dummy;
}

char type_1_true(divisor *pDiv)
{
    char answer;

    if (pDiv->lambda - 12*div_delta(pDiv, 0) + div_delta(pDiv, 1) >= 0)
	answer = 1;
    else
    {
	answer = 0;
//	printf("type 1 failed\n");
    }

    return answer;
}

char type_2_true(divisor *pDiv)
{
    int i;
    char answer = 1;

    for (i = 0 ; i <= (div_genus(pDiv) / 2) ; i++)
    {
	if (div_delta(pDiv, i) < 0)
	{
//	    printf("type 2 failed for i = %d\n", i);
	    answer = 0;
	}
    }

    return answer;
}

char type_3_true(divisor *pDiv)
{
    int i;
    char answer = 1;

    for (i = 1 ; i <= (div_genus(pDiv) / 2) ; i++)
    {
	if (2 * div_delta(pDiv, 0) - div_delta(pDiv, i) < 0)
	{
//	    printf("type 3 failed for i = %d\n", i);
	    answer = 0;
	}
    }

    return answer;
}



char type_4_true(divisor *pDiv)
{
    int i, j;
    char answer = 1;

    for (i = 1 ; i <= (div_genus(pDiv) - 1) ; i++)
	for (j = 1 ; (i + j) <= (div_genus(pDiv) - 1) ; j++)
	{
	    if ((div_delta(pDiv, reduce(div_genus(pDiv), i)) + 
		 div_delta(pDiv, reduce(div_genus(pDiv), j)) - 
		 div_delta(pDiv, reduce(div_genus(pDiv), i + j))) < 0)
	    {
//		printf("type 4 failed for i = %d, j = %d\n", i, j);
		answer = 0;
	    }
	}

    return answer;
}


char type_5_true(divisor *pDiv)
{
    int i, j, k;
    char answer = 1;

    for (i = 1 ; i <= (div_genus(pDiv) - 1) ; i++)
	for (j = 1 ; j <= (div_genus(pDiv) - 1) ; j++)
	    for (k = 1 ; (i + j + k) <= (div_genus(pDiv) - 1) ; j++)
	{
	    if ((div_delta(pDiv, reduce(div_genus(pDiv), i)) + 
		 div_delta(pDiv, reduce(div_genus(pDiv), j)) + 
		 div_delta(pDiv, reduce(div_genus(pDiv), k)) + 
		 div_delta(pDiv, reduce(div_genus(pDiv), i + j + k)) - 
		 div_delta(pDiv, reduce(div_genus(pDiv), i + j)) - 
		 div_delta(pDiv, reduce(div_genus(pDiv), i + k)) - 
		 div_delta(pDiv, reduce(div_genus(pDiv), j + k))) < 0)
	    {
//		printf("type 5 failed for i = %d, j = %d, k = %d\n", i, j, k);
		answer = 0;
	    }
	}
    
    return answer;
}



bool div_is_f(divisor *pDiv)
{
    bool answer;
    if (type_1_true(pDiv) &&
	type_2_true(pDiv) &&
	type_3_true(pDiv) &&
	type_4_true(pDiv) &&
	type_5_true(pDiv))
	answer = TRUE;
    else
	answer = FALSE;
}

