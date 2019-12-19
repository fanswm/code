/**************************************************************
 *days is a pointer of array which have 13 items.
 days[0] for save how many days is leap month.
 days[1] - days[12] for save every month days.
 leap_month_name.
	requied function:
		void time_china_calendar_sub_params(unsigned long, unsigned long *, unsigned long *, unsigned long *);
 ****************************************************************/
void time_china_calendar_count_month_days(unsigned long condition_code,\
					unsigned int *days,\
					unsigned int *leap_month_name\)	
{
	unsigned long first4, last4, mid12;
	unsigned long *f, *m, *l;
	unsigned int flag, month, *p;
	int i;
	
	f = &first4;
	m = &mid12;
	l = &last4;
	p = days;
	
	/* init days[13] */
	for(i = 0; i < 13; i++)
	{
		*p++ = 0;
	}
	
	time_china_calendar_sub_params(condition_code, f, m, l);
	*leap_month_name = (unsigned int)last4;
	
	p = days;
	for(i = 0; i < 12; i++)
	{
		p[12 - i] = (unsigned int)(mid12 & 1) + 29;
		mid12 >>= 1;
	}
	leap_month_name ? (p[0] = 29 + first4) : (p[0] = 0);
}

