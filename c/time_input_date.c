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
unsigned char time_input_date(int *year, int *month, int *day)
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