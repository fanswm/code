#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/********************************************
	how many "1" is the "num" have?
****************************************************/
size_t number_count_1(unsigned long num);

/*#include <stdio.h>
#include <time.h>
  get a rand number: 0 - (max - 1)
  #include <time.h>
*****************************************/
unsigned int number_create_rand_zero_to_max(unsigned int max);

/* create two rand number under max
   save to: *x, *y
   #include <time.h> */
void number_create_tow_rand_max(int *x, int *y, int max);
