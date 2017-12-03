#include <stdio.h>

size_t time_is_leapyear(size_t year)
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
	
	return (size_t (sumday+1) % 7);	
}

int main(void)
{
	size_t w;
	
	w = time_head_of_year_is_week(2016);
	printf("is: %d\n", w);
}

