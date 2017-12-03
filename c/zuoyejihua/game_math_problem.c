/* create two rand number under max
   save to: *x, *y
   #include <time.h> */
void number_create_tow_rand_max(int *x, int *y, int max)
{
	srand( (unsigned)time( NULL ) );
	*x = rand() % max;
	*y = rand() % max;
}

/* create two rand number under MAX,
   calculation this, OK: V,  */
void game_math_problem()
{
	int daoshu, max, i;
	int a, b, result, *m, *n;
	int count = 0;

	m = &a;
	n = &b;

	printf("please input daoshu:\n");
	scanf("%d",&daoshu);
	printf("please input max:\n");
	scanf("%d",&max);

	for(i = 0; i < daoshu; i++)
	{
		number_create_tow_rand_max(m, n, max);
		printf("%d  + %d  = ", a, b);
		scanf("%d", &result);

		if(result == a + b)
		{
			count++;
			printf("V\n");
		}
		else
		{
			printf("X ");
			printf(": %d\n", a+b);
		}
	}
}
