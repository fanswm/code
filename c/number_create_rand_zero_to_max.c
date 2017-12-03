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

