#include<stdio.h>

int GENUS;
int half_g;
int num_eqns;
int printing;

int reduce(int i)
{
  int dummy;

  if (i > half_g)
    dummy = GENUS - i;
      else dummy = i;

  return dummy;
}

void makeineq(int i, int j, int k)
{
  int red_i, red_j, red_k, red_ij, red_ik, red_jk, red_ijk, l;
  int dummy;

  red_i=reduce(i);
  red_j=reduce(j);
  red_k=reduce(k);
  red_ij=reduce(i+j);
  red_ik=reduce(i+k);
  red_jk=reduce(k+j);
  red_ijk=reduce(i+j+k);

  l=1;

  while(l <= half_g)
    {
      dummy=0;
      if (l == red_i)
	dummy--;
      if (l == red_j)
	dummy--;
      if (l == red_k)
	dummy--;
      if (l == red_ijk)
	dummy--;
      if (l == red_ij)
	dummy++;
      if (l == red_ik)
	dummy++;
      if (l == red_jk)
	dummy++;
      if ((printing == 1) && (l != 1))
	  printf("%d ",dummy);
      l++;
    }  
  if (printing == 1)
      printf("\n");
  num_eqns++;
}

void makeineqs()
{
  int i = 1;
  int j = 1;
  int k = 1;

  while(i <= GENUS-1)
    {
      j=i;
      while((j <= GENUS-1) && (i + j <= GENUS-1))
	{
	  k=j;
	  while((k <= GENUS-1) && (i + k <= GENUS-1) &&
		(j + k <= GENUS-1) && (i + j + k <= GENUS-1))
	    {
	      makeineq(i, j, k);
	      k++;
	    }
	  j++;
	}
      i++;
    }
}

void makeinequalities()
{
    makeineqs();
}

void reducetester()
{
    int i = 1;
    
    while(i <= GENUS-1)
    {
	printf("\n reducing %d with respect to %d gives %d \n", i, 
	       GENUS, reduce(i));
	i++;
    }
}

main(int argc, char *argv[])
{
    if (argc == 1 ) 
    {
	printf("--------------------------------------------\n");
	printf("Usage : %s <genus>\n", argv[0]);
	printf("Or    : %s <genus> <output_file> (Not yet implemented)\n", 
	       argv[0]);
	printf("--------------------------------------------\n");
    }
    else 
    {
	GENUS = atoi(argv[1]);
	half_g = GENUS/2;
	num_eqns = 0;

	printing = 0;
	makeinequalities();
	printing = 1;
	printf("flagcone_%d \n", GENUS);
	printf("*flagcone of curves of genus %d \n", GENUS);
	printf("H-representation \n");
	printf("begin \n");
	printf("%d %d rational \n", num_eqns, half_g - 1);
	makeinequalities();
	printf("end \n");
	
    }
}









