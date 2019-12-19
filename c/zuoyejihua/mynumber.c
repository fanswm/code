#include "mynumber.h"

/********************************************
	how many "1" is the "num" have?
****************************************************/
size_t number_count_1(unsigned long num)
{
	size_t count;
	unsigned long n;
	n = num;
	
	count = 0;
	while(n > 0)
	{
		if(n & 1)
		{
			count++;
		}
		n >>= 1;
	}
	return count;
}

/*int main(void)
{
	printf("3 have 1: %d\n", num_count_1(185));
}*/

/*#include <stdio.h>
#include <time.h>*/

/*************************************
  get a rand number: 0 - (max - 1)
  #include <time.h>
*****************************************/
unsigned int number_create_rand_zero_to_max(unsigned int max)
{
	int i, t, j;
	srand( (unsigned)time( NULL ) );
	t = rand() % max;
	return t;
}
/*
int main(void)
{
	int i, t;
	for(i = 0; i < 10; i++)
	{
		srand( (unsigned)time( NULL ) );
		t = rand() % 88;
		printf("%d\n", t);
	}
	getch();
}*/

/* create two rand number under max
   save to: *x, *y
   #include <time.h> */
void number_create_tow_rand_max(int *x, int *y, int max)
{
	srand( (unsigned)time( NULL ) );
	*x = rand() % max;
	*y = rand() % max;
}
