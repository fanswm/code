#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _MYNUMBER_H_
#define _MYNUMBER_H_
#include "mynumber.h"
#endif

#ifndef _MYTYPE_H_
#define _MYTYPE_H_
#include "mytype.h"
#endif

/********************************************
    1900-1-31 is 1900-1-1
    Min: 1900
    Max: 2049
    total: 150 years
	
	
	前4位，即0在这一年是润年时才有意义，它代表这年润月的大小月，为1则润大月，为0则润小月。
	first4, if this year is leap year, then if first4=1: leap_month_days=30;else leap_month_days=29.
	中间12位，即4bd，每位代表一个月，为1则为大月，为0则为小月。
	mid12: 1: 30; 0: 29.
	最后4位，即8，代表这一年的润月月份，为0则不润。首4位要与末4位搭配使用。
	last4 = leap_month_name. but if leap=0, nothing.

	第一个数是:1900年1月31日正月初一开始

****************************************************/
unsigned long china_calendar_year_condition[] =
{
    0x04bd8,0x04ae0,0x0a570,0x054d5,0x0d260,0x0d950,0x16554,0x056a0,0x09ad0,0x055d2,
    0x04ae0,0x0a5b6,0x0a4d0,0x0d250,0x1d255,0x0b540,0x0d6a0,0x0ada2,0x095b0,0x14977,
    0x04970,0x0a4b0,0x0b4b5,0x06a50,0x06d40,0x1ab54,0x02b60,0x09570,0x052f2,0x04970,
    0x06566,0x0d4a0,0x0ea50,0x06e95,0x05ad0,0x02b60,0x186e3,0x092e0,0x1c8d7,0x0c950,
    0x0d4a0,0x1d8a6,0x0b550,0x056a0,0x1a5b4,0x025d0,0x092d0,0x0d2b2,0x0a950,0x0b557,
    0x06ca0,0x0b550,0x15355,0x04da0,0x0a5d0,0x14573,0x052d0,0x0a9a8,0x0e950,0x06aa0,
    0x0aea6,0x0ab50,0x04b60,0x0aae4,0x0a570,0x05260,0x0f263,0x0d950,0x05b57,0x056a0,
    0x096d0,0x04dd5,0x04ad0,0x0a4d0,0x0d4d4,0x0d250,0x0d558,0x0b540,0x0b5a0,0x195a6,
    0x095b0,0x049b0,0x0a974,0x0a4b0,0x0b27a,0x06a50,0x06d40,0x0af46,0x0ab60,0x09570,
    0x04af5,0x04970,0x064b0,0x074a3,0x0ea50,0x06b58,0x055c0,0x0ab60,0x096d5,0x092e0,
    0x0c960,0x0d954,0x0d4a0,0x0da50,0x07552,0x056a0,0x0abb7,0x025d0,0x092d0,0x0cab5,
    0x0a950,0x0b4a0,0x0baa4,0x0ad50,0x055d9,0x04ba0,0x0a5b0,0x15176,0x052b0,0x0a930,
    0x07954,0x06aa0,0x0ad50,0x05b52,0x04b60,0x0a6e6,0x0a4e0,0x0d260,0x0ea65,0x0d530,
    0x05aa0,0x076a3,0x096d0,0x04bd7,0x04ad0,0x0a4d0,0x1d0b6,0x0d250,0x0d520,0x0dd45,
    0x0b5a0,0x056d0,0x055b2,0x049b0,0x0a577,0x0a4b0,0x0aa50,0x1b255,0x06d20,0x0ada0
};

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
				unsigned int day);				

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
					unsigned int day2);
					

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
					unsigned long *last4);
					

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
                                        unsigned int *leap_month_name);
                                        

/********************************************
    show the "condition_code" is which china_year.
    and show every month days.
    
    required function:
	china_calendar_year_condition[];
	time_china_calendar_count_month_days();
****************************************************/
unsigned int time_show_china_calendar_days_by_condition(unsigned long condition_code);

/********************************************
    how many days is the china calendar year have?
    required function:
        size_t number_count_1(unsigned long num);
        void time_china_calendar_sub_params(unsigned long, unsigned long *, unsigned long *, unsigned long *);
****************************************************/
unsigned long time_count_sum_days_of_china_calendar_by_condition(unsigned long condition_code);

/********************************************
    Example:
	condition: 4abd	29	30	...	30	0	sum:	384
    
    required function:
	time_china_calendar_count_month_days();
	time_count_sum_days_of_china_calendar_by_condition();
****************************************************/
void time_write_china_month_days_to_file_by_condition(FILE *fp,
						unsigned long condition_code);
						

/********************************************
    Example:
	condition: 4abd	29	30	...	30	0	sum:	384
    
    required function:
	china_calendar_year_condition[];
	time_china_calendar_count_month_days();
****************************************************/
void time_write_every_china_month_days_to_file(const char *filename);


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
                            			unsigned int day);
                            			

/****************************************************
        2050-1-22 >= year >=1900.1.31
        else: return 0;
	requied function:
		time_date_is_early_to_base();
*****************************************************/
MyBoolType time_date_is_support_by_china_calendar(unsigned int year,
							unsigned int month,
							unsigned day);
							

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
                                            unsigned int day);

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
						unsigned int china_day);

/***************************************************
	legal date:
		1900-1-1 to 3000-12-31
	return:
		ok: 1;
		error: 0.
*****************************************************/
MyBoolType time_is_legal_date(unsigned int year,
                                unsigned int month,
                            	unsigned int day);

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
					unsigned int china_day);

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
                                         unsigned int *china_day);
                                         
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
				unsigned int *china_day);

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
						unsigned int china_day2);

/*************************************************************
	require function:
		time_date_is_china_calendar;
		time_date_is_support_by_china_calendar();
*****************************************************************/
void time_date_is_china_calendar_by_input(void);

/*************************************************************
	require function:
		time_date_is_china_calendar;
		time_date_is_support_by_china_calendar();
*****************************************************************/
void time_china_date_is_date_by_input(void);

/************************************************************
	support: 1900-1-1 to 2999-12-31
	return:
		support: 1;
		not support: 0
***************************************************************/
MyBoolType time_date_is_support_by_count_week(unsigned int year,
						unsigned int month,
						unsigned int day);

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
				unsigned int day);

/********************************************
	how many days is the china calendar year have?
	required function:
		size_t number_count_1(unsigned long num);
		void time_china_calendar_sub_params(unsigned long, 
			unsigned long *, unsigned long *, unsigned long *);
****************************************************/
unsigned long time_count_days_of_china_calendar_year_by_condition(unsigned long condition_code);

/****************************************************
 return:
	leapyear: 1;
	not leapyear 0
********************************************************/
MyBoolType time_is_leap_year(unsigned int year);

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
					unsigned int day);

/*****************************************************
    count days of the year:year1
	the day is di ji tian of year.
	
    result:
        OK: sumday;
		failed: -1
******************************************************/

double time_date_ordinal_of_year(unsigned int year1, \
				unsigned int month1, \
				unsigned int day1);


MyBoolType time_is_leapyear(size_t year);

/******************************************
	yaer:month include days?
	return days;
	require function:
		size_t time_is_leapyear(size_t year);
********************************************/
size_t time_days_in_month(size_t year, size_t month);

/* #include <time.h>
   get local time and format to mysql style. 
****************************************************/
void time_get_local_format_mysql_style(char *datetime);

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
size_t time_head_of_year_is_week(size_t year);

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
MyBoolType time_input_date(int *year, int *month, int *day);



