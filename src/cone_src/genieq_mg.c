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

void maketype1()
{
  int i = 2;

  if (printing)
      printf("1 -12 1 ");
  
  while (i <= half_g)
  {
      if (printing == 1)
	  printf("0 ");
      i++;
  }
  if (printing == 1)
      printf("\n");
  num_eqns++;
}

void maketype2()
{
  int i=1;
  int j;

  while(i <= half_g)
    {
      j=1;
      if (printing == 1)
	  printf("0 2 ");
      while(j < i)
      {
	  if (printing == 1)
	      printf("0 ");
	  j++;
      }
      if (printing == 1)
	  printf("-1 ");
      j = i+1;
      while(j <= half_g)
      {
	  if (printing == 1)
	      printf("0 ");
	  j++;
      }
      i++;
      if (printing == 1)
	  printf("\n");
      num_eqns++;
    } 
}

void maketype3()
{
    int i=1;
    int j;
    
    while(i <= half_g)
    {
	j=1;
	if (printing == 1)
	    printf("0 0 ");
	while(j < i)
	{
	    if (printing == 1)
		printf("0 ");
	    j++;
	}
	if (printing == 1)
	    printf("1 ");
	j=i+1;
	while(j <= half_g)
	{
	    if (printing == 1)
		printf("0 ");
	    j++;
	}
	i++;
	if (printing == 1)
	    printf("\n");
	num_eqns++;
    }
}

void makereducedtype4(int i, int j)
{
  int red_i, red_j, red_ij, k;
  int dummy;

  red_i=reduce(i);
  red_j=reduce(j);
  red_ij=reduce(i+j);

  k=1;

  if (printing == 1)
      printf("0 0 ");
  
  while(k <= half_g)
    {
      dummy=0;
      if (k == red_i)
	dummy++;
      if (k == red_j)
	dummy++;
      if (k == red_ij)
	dummy--;
      if (printing == 1)
	  printf("%d ",dummy);
      k++;
    }  
  if (printing == 1)
      printf("\n");
  num_eqns++;
}
  

void maketype4()
{
  int i = 1;
  int j = 1;

  while(i <= GENUS-1)
    {
      j=i;
      while((j <= GENUS-1) && (i + j <= GENUS-1))
	{
	  makereducedtype4(i, j);
	  j++;
	}
      i++;
    }  
}

void makereducedtype5(int i, int j, int k)
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
  if (printing == 1)
      printf("0 0 ");
  
  while(l <= half_g)
    {
      dummy=0;
      if (l == red_i)
	dummy++;
      if (l == red_j)
	dummy++;
      if (l == red_k)
	dummy++;
      if (l == red_ijk)
	dummy++;
      if (l == red_ij)
	dummy--;
      if (l == red_ik)
	dummy--;
      if (l == red_jk)
	dummy--;
      if (printing == 1)
	  printf("%d ",dummy);
      l++;
    }  
  if (printing == 1)
      printf("\n");
  num_eqns++;
}

void maketype5()
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
	      makereducedtype5(i, j, k);
	      k++;
	    }
	  j++;
	}
      i++;
    }
}

void makeinequalities()
{
    maketype1();
    maketype2();
    maketype3();
    maketype4();
    maketype5();
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
	printf("fcone_%d \n", GENUS);
	printf("*fcone of curves of genus %d \n", GENUS);
	printf("H-representation \n");
	printf("begin \n");
	printf("%d %d rational \n", num_eqns, half_g + 2);
	makeinequalities();
	printf("end \n");
	
    }
}









