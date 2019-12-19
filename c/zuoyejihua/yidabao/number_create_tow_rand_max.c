/* create two rand number under max
   save to: *x, *y
   #include <time.h> */
void number_create_tow_rand_max(int *x, int *y, int max)
{
	srand( (unsigned)time( NULL ) );
	*x = rand() % max;
	*y = rand() % max;
}
