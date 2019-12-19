
/* return:
	leapyear: 1;
	not leapyear 0   */
unsigned char time_is_leap_year(unsigned int year)
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

int main(void)
{
    double a;
    
    a = time_date_ordinal_of_year(2016, 10, 7);
    printf("a = %.0f\n", a);
    getchar();
}
