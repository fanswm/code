#include "mytime.h"

/* return:
    leapyear: 1;
    not leapyear 0   */
unsigned int time_is_leap_year(unsigned int year)
{
	if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/********************************************
    date early to base_date: 	1;
    date equal to base_date: 	0;
    else:			-1;
****************************************************/
int time_date_is_early_to_base(unsigned int base_year,
				unsigned int base_month,
				unsigned int base_day,
				unsigned int year,
				unsigned int month,
				unsigned int day)
{
	int f;
	if(year > base_year)
	{
		f = -1;
	}
	else if(year == base_year)
	{
		if(month > base_month)
		{
			f = -1;
		}
		else if(month == base_month)
		{
			if(day > base_day)
			{
				f = -1;
			}
			else if(day == base_day)
			{
				f = 0;
			}
			else
			{
				f = 1;
			}
		}
		else
		{
			f = 1;
		}
	}
	else
	{
		f = 1;
	}
	return f;
}

/*****************************************************
    count days of date1 to date2
    year1 month1 day1 MUST LESS than yaer2 month2 day2;
    not count head, and count tail;
    result:
        OK: sumday;
        failed: -1
******************************************************/

long time_count_days_date1_to_date2(unsigned int year1,
					unsigned int month1,
					unsigned int day1,
					unsigned int year2,
					unsigned int month2,
					unsigned int day2)
{
    long sday;

    unsigned int y1, m1, d1, y2, m2, d2;
    int i;
    unsigned int leap;

    unsigned int a[2][13] = {
                    {0,31,28,31,30,31,30,31,31,30,31,30,31},
                    {0,31,29,31,30,31,30,31,31,30,31,30,31}
        		};

    y1 = year1; m1 = month1; d1 = day1;
    y2 = year2; m2 = month2; d2 = day2;

    sday = 0;   /* init 0 */

    leap = time_is_leap_year(y1);

    if(y2 == y1)    /* if same year */
    {
        if(m2 == m1)
    	{
            if(d2 < d1)
    		{
                printf("error: second day less than first day.\n");
                return -1;
    		}
        	else
    		{
                sday += (d2 - d1);	/* over */
    		}
    	}
        else if(m2 < m1)
    	{
            printf("error: second month less than first month.\n");
            return -1;
    	}
        else
    	{
            sday += ( a[leap][m1] - d1 );   /* count days of first month */
            for(i = m1 + 1; i < m2; i++)    /* count month1+1 to month-1 days */
    		{
                sday += a[leap][i];
    		}
            sday += d2; /* count days of month2 */
            /* over */
    	}
    }
    else if(y2 < y1)
    {
        printf("error: second year less than first yaer.\n");
        return -1;
    }
    else
    {
        /*leap = time_is_leap_year(y1);*/
        sday += (a[leap][m1] - d1); /* count days of month1 */
        for(i = m1 + 1; i <= 12; i++)   /* count days of month1+1 to 12month */
    	{
            sday += a[leap][i];
        }       /* count days of year1 over */

        /* count days of year2 begin */
        leap = time_is_leap_year(y2);
        for(i = 1; i < m2; i++)     /* count days of 1month to month2-1 */
    	{
            sday += a[leap][i];
    	}
        sday += d2; /* count days of month2 */
        /* count second year over */

        /* count year1+1 to year2-1 begin*/
        for(i = y1 + 1; i < y2; i++)
    	{
            leap = time_is_leap_year(i);
            sday += (365 + leap);
        }   /* count year1+1 to year2-1 over*/
    }
    return sday;
}

/********************************************
    from is the source condition code;
    0x04bd8
    前4位，即0在这一年是润年时才有意义，它代表这年润月的大小月，为1则润大月，为0则润小月。
    中间12位，即4bd，每位代表一个月，为1则为大月，为0则为小月。
    最后4位，即8，代表这一年的润月月份，为0则不润。首4位要与末4位搭配使用。
****************************************************/
void time_china_calendar_sub_params(unsigned long condition_code,
					unsigned long *first4,
					unsigned long *mid12,
					unsigned long *last4)
{
    unsigned long from, f4, l4, m12;

    from = condition_code;
    l4 = from & 0xf;
    from >>= 4;
    m12 = from & 0xfff;
    from >>= 12;
    f4 = from & 0xf;
    *first4 = f4;
    *mid12 = m12;
    *last4 = l4;
}

/**************************************************************
 *days is a pointer of array which have 13 items.
 days[0] for save how many days is leap month.
 days[1] - days[12] for save every month days.
 leap_month_name.
    requied function:
        void time_china_calendar_sub_params(unsigned long, unsigned long *, unsigned long *, unsigned long *);
 ****************************************************************/
void time_china_calendar_count_month_days(unsigned long condition_code,
                                	unsigned int *days,
                                        unsigned int *leap_month_name)
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
	
    if(last4)
	{
		*leap_month_name = (unsigned int)last4 + 12;	/* +12 mean: leap! */
	}
	else
	{
		*leap_month_name = 0;
	}

    p = days;
    for(i = 0; i < 12; i++)
    {
        p[12 - i] = (unsigned int)(mid12 & 1) + 29;
        mid12 >>= 1;
    }
    leap_month_name ? (p[0] = 29 + first4) : (p[0] = 0);
}

/********************************************
    show the "condition_code" is which china_year.
    and show every month days.
    
    required function:
	china_calendar_year_condition[];
	time_china_calendar_count_month_days();
****************************************************/
unsigned int time_show_china_calendar_days_by_condition(unsigned long condition_code)
{
	int i;
	unsigned int year, days[13], leap_month_name, *leap, sum;
	
	leap = &leap_month_name;
	sum = 0;
	
	for(i = 0; i < 150; i++)
	{
		if(condition_code == china_calendar_year_condition[i])
		{
			break;
		}
	}
	year = 1900 + i;
	time_china_calendar_count_month_days(condition_code, days, leap);
	printf("china_calendar_year_condition: %x  china_year: %u\n", condition_code, year);
	for(i = 1; i <= 12; i++)
	{
		sum += days[i];
		printf("%d_%d_%d\t", i, days[i], sum);
		if(i == (leap_month_name - 12))
		{
			sum += days[0];
			printf("%d_%d_%d\t",leap_month_name, days[0], sum);
		}
		if(i == 6)
			printf("\n");
	}
	printf("\n");
	
	return year;
}

/********************************************
    how many days is the china calendar year have?
    required function:
        size_t number_count_1(unsigned long num);
        void time_china_calendar_sub_params(unsigned long, unsigned long *, unsigned long *, unsigned long *);
****************************************************/
unsigned long time_count_sum_days_of_china_calendar_by_condition(unsigned long condition_code)
{
    unsigned long con, f4, l4, m12;
    unsigned long *f, *l, *m;
    unsigned long sum = 0;

    f = &f4;
    l = &l4;
    m = &m12;

    time_china_calendar_sub_params(condition_code, f, m, l);
    sum = (unsigned long) ( number_count_1(m12) ) + 12 * 29;
    if(l4)
    {
        sum += (29 + f4);
    }
    return sum;
}

/********************************************
    Example:
	condition: 4abd	29	30	...	30	0	sum:	384
    
    required function:
	time_china_calendar_count_month_days();
	time_count_sum_days_of_china_calendar_by_condition();
****************************************************/
void time_write_china_month_days_to_file_by_condition(FILE *fp,
						unsigned long condition_code)
{
	int i;
	unsigned int days[13], leap_month_name, *leap;
	unsigned long sum;
	
	leap = &leap_month_name;
	
	time_china_calendar_count_month_days(condition_code, days, leap);
	
    sum = time_count_sum_days_of_china_calendar_by_condition(condition_code);
	fprintf(fp, "condition: %x\t", condition_code);
	for(i = 1; i <= 12; i++)
	{
		fprintf(fp, "%d\t", days[i]);
	}
	
	if(leap_month_name > 12)
	{
		fprintf(fp, "%d\t%d\t", days[0], leap_month_name - 12);
	}
	else
	{
		fprintf(fp, "%d\t%d\t", 0, 0);
	}
	fprintf(fp, "sum:\t%u\n", sum);
}

/********************************************
    Example:
	condition: 4abd	29	30	...	30	0	sum:	384
    
    required function:
	china_calendar_year_condition[];
	time_china_calendar_count_month_days();
****************************************************/
void time_write_every_china_month_days_to_file(const char *filename)
{
	int i;
	FILE *fp;
	unsigned int year;
	unsigned long con;
	
	if((fp = fopen(filename,"w+")) == NULL)
	{
		printf("Error: create %s error!\n", filename);
		return;
	}
	for(i = 0; i < 150; i++)
	{
		year = 1900 + i;
		con = china_calendar_year_condition[i];
		fprintf(fp, "year:\t%d\t", year);
		time_write_china_month_days_to_file_by_condition(fp, con);
	}
	fclose(fp);
}

/********************************************
    legal_china_calendar_year_date:
        1900 <= year <= 2049;
        1 <= month <= 12;
        leap_month = leap_month_name + 12;
        13 <= leap_month <= 24: 13,14,15,...23,24;
        1 <= day <= 30;
    required function:
        void time_china_calendar_count_month_days(unsigned long condition_code,\
                                			unsigned int *days,
                                            unsigned int *leap_month_name\
            							);
	time_date_is_early_to_base();
	china_calendar_year_condition[];
****************************************************/
MyBoolType time_is_legal_china_calendar_date(unsigned int year,
                                		unsigned int month,
                            			unsigned int day)
{
    unsigned int days[13], leap_month_name, *leap;
    unsigned long con;
    
    if(time_date_is_early_to_base(1900, 1, 1, year, month, day) == 1 
	|| time_date_is_early_to_base(2049, 12, 29, year, month, day) < 0)
    {
	printf("Error: the year MUST between 1900-1-1 and 2049-12-29!\n");
        return 0;	
    }

    leap = &leap_month_name;
    con = china_calendar_year_condition[year - 1900];
    time_china_calendar_count_month_days(con, days, leap);

    if(month > 12)
    {
        if(leap_month_name)
    	{
		if(month != leap_month_name)
		{
			printf("Error: the leap_month_name is error!\n");
			return 0;
    		}
		if(day > days[0])
    		{
			printf("Error: the leap_month day is error! day is %d; day[0] is %d\n", day, days[0]);
			return 0;
    		}
    	}
        else
    	{
		printf("Error: the month name is error!\n");
		return 0;
    	}
    }
    else
    {
        if(day > days[month])
    	{
            printf("Error: the day is error!\n");
            return 0;
    	}
    }
    return 1;
}

/****************************************************
        2050-1-22 >= year >=1900.1.31
        else: return 0;
	requied function:
		time_date_is_early_to_base();
*****************************************************/
MyBoolType time_date_is_support_by_china_calendar(unsigned int year,
							unsigned int month,
							unsigned day)
{
        MyBoolType f;
        (
		time_date_is_early_to_base(1900, 1, 30, year, month, day) >= 0 
		|| time_date_is_early_to_base(2050, 1, 22, year, month, day) == -1 
	) ? (f = 0) : (f = 1);
	
        return f;
}

/****************************************************
        origin: 1900.1.31
	1900-1-31: return 1;
        require function:
                unsigned char time_date_is_support_by_china_calendar(
                                                unsigned int year,
                                                unsigned int month,
                                                unsigned day);
                unsigned long time_count_days_date1_to_date2(
                                                unsigned int year1,
                                                unsigned int month1,
                                                unsigned int day1,
                                                unsigned int year2,
                                                unsigned int month2,
                                                unsigned int day2)
        return：
                yes: days of the current date from origin.
                error: -1
*****************************************************/
long time_date_how_far_from_china_calendar_origin(unsigned int year,
                                            unsigned int month,
                                            unsigned int day)
{
        long sum = 0;

        if(!time_date_is_support_by_china_calendar(year, month, day))
        {
                printf("Error: the date is not support by china calendar!\n");
                return -1;
        }

        sum = time_count_days_date1_to_date2(1900, 1, 31, year, month, day);
        return sum;
}

/****************************************************
        origin: 1900.1.1
	1900-1-1: return 30;
        require function:
		china_calendar_year_condition[];
                time_is_legal_china_calendar_date();
                time_count_sum_days_of_china_calendar_by_condition();
		time_china_calendar_count_month_days();
        return：
                yes: china_date of the current date from 1900-1-1.
                error: -1
*****************************************************/
long time_china_date_how_far_from_19000101(unsigned int china_year,
						unsigned int china_month,
						unsigned int china_day)
{
	int i;
	unsigned long con;
	unsigned int days[13], leap_month_name, *leap, month;
	long sum = 30;
	
	if(!time_is_legal_china_calendar_date(china_year, china_month, china_day))
	{
		printf("Error: The china date: %d-%d-%d is illegal!\n", china_year, china_month, china_day);
		return -1;
	}
	
	leap = &leap_month_name;
	
	for(i = 0; i < (china_year - 1900); i++)
	{
		con = china_calendar_year_condition[i];
		sum += time_count_sum_days_of_china_calendar_by_condition(con);
	}
	con = china_calendar_year_condition[china_year - 1900];
	time_china_calendar_count_month_days(con, days, leap);
	
	(china_month > 12) ? \
		(month = china_month - 12) : (month = china_month);
	
	for(i = 1; i < month; i++)
	{
		sum += days[i];
	}
	
	if(china_month == leap_month_name)
	{
		sum += days[leap_month_name - 12];
	}
	else if(china_month == (leap_month_name - 12))
	{
		;
	}
	else if(china_month > (leap_month_name - 12) )
	{
		sum += days[0];
	}
	else
	{
		;
	}		
	
	sum += (china_day - 1);
	
	return sum;	
}

/***************************************************
	legal date:
		1900-1-1 to 3000-12-31
	return:
		ok: 1;
		error: 0.
*****************************************************/
MyBoolType time_is_legal_date(unsigned int year,
                                unsigned int month,
                            	unsigned int day)
{
	unsigned char leap, f;
	unsigned int a[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if(year < 1900 || year > 2999)
	{
		return 0;
	}
	leap = time_is_leap_year(year);
	if(month == 2)
	{
		if(day < 1 || day > a[2] + leap)
		{
			return 0;
		}
	}
	else if(month < 1 || month > 12)
	{
		return 0;
	}
	else
	{
		if(day < 1 || day > a[month])
		{
			return 0;
		}
	}
	
	return 1;	
}


/****************************************************

        require function:
		time_china_date_how_far_from_19000101();
		time_is_legal_china_calendar_date();
        return：
		OK: 1;
		error: 0;
*****************************************************/
MyBoolType time_china_date_is_date(unsigned int *year,
					unsigned int *month,
					unsigned int *day,
					unsigned int china_year,
					unsigned int china_month,
					unsigned int china_day)
{
	unsigned char leap;
	long far_to_origin, tmp;
	int i;
	unsigned int a[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	far_to_origin = time_china_date_how_far_from_19000101(china_year, china_month, china_day) + 1;	/* MUST +1 */

	if(far_to_origin == -1 \
		|| !time_is_legal_china_calendar_date(china_year, china_month, china_day))
	{
		printf("Error: Your input %d-%d-%d is NOT support!\n", china_year, china_month, china_day);
		*year = 0;
		*month = 0;
		*day = 0;
		return 0;
	}
	
	tmp = 365 + time_is_leap_year(1900);
	i = 0;
	while(far_to_origin > tmp)
	{
		far_to_origin -= tmp;
		i++;
		tmp = 365 + time_is_leap_year(1900 + i);
	}
	*year = 1900 + i;
	leap = time_is_leap_year(1900 + i);
	
	tmp = a[1];
	i = 1;
	while(far_to_origin > tmp)
	{
		far_to_origin -= tmp;
		i++;
		if(i == 2)
		{
			tmp = a[i] + leap;
		}
		else
		{
			tmp = a[i];
		}
	}
	*month = i;
	*day = far_to_origin;
	return 1;
}

/********************************************
    how many days is the china calendar year have?
	zheng_yue MUST ALWAYS NOT leap_month.
	oridinal = 1: china_year: 1900-1-1
	
	1900-1-1 <= china_year <= 2049-12-29
	1900-1-31 <= year <= 2050-1-22
	
	MUST 54779 >= oridinal >= 1;
	
    required function:
        size_t number_count_1(unsigned long num);
        void time_china_calendar_sub_params(unsigned long, unsigned long *, unsigned long *, unsigned long *);
	china_calendar_year_condition[];
****************************************************/
void time_ordinal_days_is_china_calendar(unsigned long oridinal,
                                         unsigned int *china_year,
                                         unsigned int *china_month,
                                         unsigned int *china_day)
{
        unsigned int days[13], leap_month_name, *leap;
        unsigned long sday, from;
        int i;

        leap = &leap_month_name;

        i = 0;
        from = oridinal;
	if(oridinal > 54779 || oridinal < 1)
	{
		printf("Error: Your oridinal: \"%u\" is NOT support!\n", oridinal);
		*china_year = 0;
		*china_month = 0;
		*china_day = 0;
		return;
	}
		/* This time, the china_calendar_year_condition[i] is 1900's */
        sday = time_count_sum_days_of_china_calendar_by_condition(china_calendar_year_condition[i]);
        while(from > sday)
        {
                from -= sday;
                i++;
                sday = time_count_sum_days_of_china_calendar_by_condition(china_calendar_year_condition[i]);
        }

        *china_year = 1900 + i;	/* result 1 */
        time_china_calendar_count_month_days(china_calendar_year_condition[i], days, leap);
		/* This time, days[13]: leap_month_days, 1,2,3,..11, 12 days, *leap = leap_month_name */
		/* and "from" is sheng_yu days of *china_year */

        i = 1;	/* start by zheng_yue */
        sday = days[i];
        while(from > sday)
        {
                from -= sday;
		i++;
                if(leap_month_name)
                {
                        if(i == (leap_month_name - 12 + 1) )
                        {
				if(from > days[0])
				{
					from -= days[0];
				}
				else
				{
					*china_month = leap_month_name;	/* result 2: add 12 mean: leap! */
					*china_day = from;		/* result 3 */
					return;
				}
                        }
                }
                sday = days[i];
        }
	*china_month = i;
	*china_day = from;
	return;
}

/********************************************
    how many days is the china calendar year have?
	zheng_yue MUST ALWAYS NOT leap_month.
	oridinal = 1: china_year: 1900, 1, 1
	"oridinal" MUST >= 1;
	
    required function:
        time_date_how_far_from_china_calendar_origin();
        time_ordinal_days_is_china_calendar();
****************************************************/
void time_date_is_china_calendar(unsigned int year,
				unsigned int month,
				unsigned int day,
				unsigned int *china_year,
				unsigned int *china_month,
				unsigned int *china_day)
{
	unsigned int cyear, cmonth, cday, *y, *m, *d;
	unsigned long oridinal;
	
	y = &cyear;
	m = &cmonth;
	d = &cday;
	
	oridinal = time_date_how_far_from_china_calendar_origin(year, month, day) + 1;
	time_ordinal_days_is_china_calendar(oridinal, y, m, d);
	*china_year = cyear;
	*china_month = cmonth;
	*china_day = cday;	
}


/*************************************************************
	#include <stdlib.h>
	count days of china_date1 to china_date2;
	count head not count tail;
	return:
		ok: days;
		error: -1;
	require function:
		time_is_legal_china_calendar_date();
		time_china_date_how_far_from_19000101();
*****************************************************************/
long time_count_days_chinadate1_to_chinadate2(unsigned int china_year1,
						unsigned int china_month1,
						unsigned int china_day1,
						unsigned int china_year2,
						unsigned int china_month2,
						unsigned int china_day2)
{
	long sum, tmp;
	unsigned char yes1, yes2;
	yes1 = time_is_legal_china_calendar_date(china_year1, china_month1, china_day1);
	yes2 = time_is_legal_china_calendar_date(china_year2, china_month2, china_day2);
	if(!yes1 || !yes2)
	{
		printf("Error: illegal china_date\n");
		return -1;
	}
	tmp = time_china_date_how_far_from_19000101(china_year1, china_month1, china_day1);
	sum = time_china_date_how_far_from_19000101(china_year2, china_month2, china_day2);
	
	return abs(sum - tmp);	/* #include <stdlib.h> */
}

/*************************************************************
	require function:
		time_date_is_china_calendar;
		time_date_is_support_by_china_calendar();
*****************************************************************/
void time_date_is_china_calendar_by_input(void)
{
	unsigned char yes;
	unsigned int year, month, day;
	unsigned int china_year, china_month, china_day;
	unsigned int *cy, *cm, *cd;
	cy = &china_year;
	cm = &china_month;
	cd = &china_day;
	
	printf("Please input year:\n");
	scanf("%d", &year);
	printf("Please input month:\n");
	scanf("%d", &month);
	printf("Please input day:\n");
	scanf("%d", &day);
	
	yes = time_date_is_support_by_china_calendar(year, month, day);
	if(!yes)
	{
		printf("Your input date: %d-%d-%d \
			is not support by china calendar or Error.\n",
			year, month, day);
		return;
	}
	else
	{
		time_date_is_china_calendar(year, month, day, cy, cm, cd);
	}
	printf("Your input date %d-%d-%d\n", year, month, day);
	printf("equal china date: %d-%d-%d\n", china_year, china_month, china_day);
	return;
}

/*************************************************************
	require function:
		time_date_is_china_calendar;
		time_date_is_support_by_china_calendar();
*****************************************************************/
void time_china_date_is_date_by_input(void)
{
	unsigned int china_year, china_month, china_day;
	unsigned int year, month, day;
	unsigned int *y, *m, *d;
	y = &year;
	m = &month;
	d = &day;
	
	printf("Please input china_year:\n");
	scanf("%d", &china_year);
	printf("Please input china_month:\n");
	scanf("%d", &china_month);
	printf("Please input china_day:\n");
	scanf("%d", &china_day);
	
	time_china_date_is_date(y, m, d, china_year, china_month, china_day);
	printf("Your input china date %d-%d-%d\n", china_year, china_month, china_day);
	printf("equal date: %d-%d-%d\n", year, month, day);
	return;
}

/************************************************************
	support: 1900-1-1 to 2999-12-31
	return:
		support: 1;
		not support: 0
***************************************************************/
MyBoolType time_date_is_support_by_count_week(unsigned int year,
						unsigned int month,
						unsigned int day)
{
	MyBoolType f;
	(
		time_date_is_early_to_base(1899, 12, 31, year, month, day) >= 0	/* before 1900-1-1 */
			|| time_date_is_early_to_base(2999, 12, 31, year, month, day) == -1 	/* later 3000-1-1 */
	) ? (f = 0) : (f = 1);
	
    return f;
}

/**********************************************
	return:
		oK: week: 1-7
		error: 0
	origin:
		1900-1-1: monday: 1
	requied function:
		time_is_legal_date();
		time_date_is_support_by_count_week();
*************************************************/
unsigned int time_date_is_week(unsigned int year,
				unsigned int month,
				unsigned int day)
{
	unsigned int week;
	long sum;
	
	if( !time_is_legal_date(year, month, day) 
		|| !time_date_is_support_by_count_week(year, month, day))
	{
		printf("Error: your date is not support!\n");
		return 0;
	}
	sum = time_count_days_date1_to_date2(1900, 1 , 1, year, month, day);
	week = sum % 7 + 1;
	
	return week;	
}

/*int main(void)
{
    int a, b, c;
    int *x, *y, *z;
    
    x = &a;
    y = &b;
    z = &c;
    
    a = time_count_days_date1_to_date2(2015, 12, 31, 2016, 12, 31);
    printf("a = %d\n",a);
    getch();
}*/


/********************************************
	how many days is the china calendar year have?
	required function:
		size_t number_count_1(unsigned long num);
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
	sum = (unsigned long) ( number_count_1(m12) ) + 12 * 29;
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

/****************************************************
 year month day: is legal format?
 1583<year<3000
 return:
	legal: 1;
	no: 0
 require function:
	time_is_leap_year();
********************************************************/
MyBoolType time_date_is_legal_format(unsigned int year,\
										unsigned int month,\
										unsigned int day)
{
	MyBoolType leap;
	unsigned int a[2][13] = {
                    {0,31,28,31,30,31,30,31,31,30,31,30,31},
                    {0,31,29,31,30,31,30,31,31,30,31,30,31}
        		};

	leap = time_is_leap_year(year);
	if( year < 1583 || year > 3000
			|| month < 1 || month > 12
			|| day < 1 || day > a[leap][month] )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*****************************************************
    count days of the year:year1
	the day is di ji tian of year.
	
    result:
        OK: sumday;
		failed: -1
******************************************************/

double time_date_ordinal_of_year(unsigned int year1, \
								unsigned int month1, \
								unsigned int day1)
{
    double sday;
    int i; 
    unsigned char leap;
    
    unsigned int a[2][13] = {
                    {0,31,28,31,30,31,30,31,31,30,31,30,31},
                    {0,31,29,31,30,31,30,31,31,30,31,30,31}
        		};
    
	if(!time_date_is_legal_format(year1,month1,day1))
	{
		printf("Error: Your input is error! return -1!\n");
		return -1;
	}
    
    sday = 0;   /* init 0 */
    
    leap = time_is_leap_year(year1);
    for(i = 1; i < month1; i++)
	{
		sday += a[leap][i];
	}
	sday += day1;
	
    
    return sday;
}

/*
int main(void)
{
    double a;
    
    a = time_date_ordinal_of_year(2016, 10, 7);
    printf("a = %.0f\n", a);
    getchar();
}
*/

MyBoolType time_is_leapyear(size_t year)
{
	if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/******************************************
	yaer:month include days?
	return days;
	require function:
		size_t time_is_leapyear(size_t year);
********************************************/
size_t time_days_in_month(size_t year, size_t month)
{
    size_t day, leap;
    leap = time_is_leapyear(year);
    switch(month)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		day = 31;
		break;
        case 4: case 6: case 9: case 11: 
		day = 30;
		break;
        case 2:
		day = 28 + leap;
		break;
	default:
		break;
    }
    return day;
}

/*int main()
{
    size_t y,m;
    scanf("%d %d",&y,&m);
    printf("%d\n",time_days_in_month(y,m));
    getch();
}*/

/* #include <time.h>
   get local time and format to mysql style. 
****************************************************/
void time_get_local_format_mysql_style(char *datetime)
{
    time_t timer;
    struct tm *gmt;

    timer = time(NULL);
    gmt = localtime(&timer);
    if(gmt->tm_year + 1900 < 9999)
    {
        strftime(datetime, 21, "%Y-%m-%d %H:%M:%S", gmt);
        printf("%s\n", datetime);
    }
    return;
}

/*int main(void)
{
	char str[1024];
	time_get_local_format_mysql_style(str);
	printf("str: %s\n", str);
	getch();
}*/


/***************************************** 
    head of year: mon:1, day: 1
    is week?
    0: sunday;
    1: monday;
    
    year NOT biger than 1900;
    require function:
	time_is_leapyear(size_t yaer)
	
    1900-1-1 is monday;
 ********************************************/
size_t time_head_of_year_is_week(size_t year)
{
	int sumday, i;
	sumday = 0;
	i = 1900;
	
	for(;i < year; i++)
	{
		if(time_is_leapyear(i) )
		{
			sumday += 366;
		}
		else
		{
			sumday += 365;
		}
	}
	
	return ((size_t) ((sumday+1) % 7));	
}
/*
int main(void)
{
	size_t w;
	
	w = time_head_of_year_is_week(2016);
	printf("is: %d\n", w);
}*/

/****************************************
 input year(1583-3000),month(1-12),day(1-31)
   save to: *year, *month, *day.
   seq by ' ' or '\n'
   
   return:
   ok: 1;
   failed: 0;
   reqire function: 
		time_is_leap_year(); 
		time_date_is_legal_format()
***********************************************/
MyBoolType time_input_date(int *year, int *month, int *day)
{
	int y,m,d;

	printf("please input year(4),month(2),day(2), seq by ' ' or '\\n':\n");
	scanf("%d %d %d",year, month, day);
	y = *year;
	m = *month;
	d = *day;

	if(time_date_is_legal_format(y, m, d) )
	{
		return 1;
	}
	else
	{
		printf("Error: your input error, please check!\n");
		*year = 0;
		*month = 0;
		*day = 0;
		return 0;
	}
}

/*int main(void)
{
	int a, b, c;
	int *x, *y, *z;

	x = &a;
	y = &b;
	z = &c;

	time_input_date(x,y,z);
	printf("a = %d, b = %d, c = %d\n", a, b, c);
	getch();
}*/


