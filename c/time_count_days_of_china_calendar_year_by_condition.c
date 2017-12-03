/********************************************
	how many days is the china calendar year have?
	required function:
		size_t num_count_1(unsigned long num);
		void time_china_calendar_sub_params(unsigned long, unsigned long *, unsigned long *, unsigned long *);
****************************************************/
unsigned long time_count_days_of_china_calendar_year_by_condition(unsigned long condition_code)
{
	unsigned long con, f4, l4, m12;
	unsigned long *f, *l, *m;
	unsigned long sum = 0;
	
	f = &f4;
	l = &l4;
	m = &m12;
	
	time_china_calendar_sub_params(condition_code, f, m, l);
	sum = (unsigned long) ( num_count_1(m12) ) + 12 * 29;
	if(l4)
	{
		sum += (29 + f4);
	}
	return sum;
}

/*
int main(void)
{
	printf("days: %d\n", time_count_days_of_china_calendar_year_by_condition(0x15176) );
}*/

