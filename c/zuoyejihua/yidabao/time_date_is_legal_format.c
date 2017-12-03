/*#include <stdio.h>*/

/****************************************************
 return:
	leapyear: 1;
	not leapyear 0
********************************************************/
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

/****************************************************
 year month day: is legal format?
 1583<year<3000
 return:
	legal: 1;
	no: 0
 require function:
	time_is_leap_year();
********************************************************/
unsigned char time_date_is_legal_format(unsigned int year,\
										unsigned int month,\
										unsigned int day)
{
	unsigned char leap;
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