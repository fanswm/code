/*#include <stdio.h>*/

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

/*****************************************************
    count days of date1 to date2
    year1 month1 day1 MUST LESS than yaer2 month2 day2;
    not count head, and count tail;
    result:
        OK: sumday;
		failed: -1
******************************************************/

unsigned long time_count_days_date1_to_date2(unsigned int year1, unsigned int month1, unsigned int day1,\
                    unsigned int year2, unsigned int month2, unsigned int day2)
{
    unsigned long sday;

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
