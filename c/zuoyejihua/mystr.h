#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef _MYCHAR_H_
#define _MYCHAR_H_
#include "mychar.h"
#endif

#ifndef _MYLIST_H_
#define _MYLIST_H_
#include "mylist.h"
#endif

#define STR_BUFF_SIZE	1024
#define FILE_NAME_LEN	200
#define INPUT_BUFF_SIZE	10
#define FILE_NAME_LEN	200

/* connect variable char save to str:"to"
        number: count_char
        #include <stdarg.h>
*****************************************************/
void str_cat_any_char_to_str( char *to, int count_char, ... );

/* #include <stdarg.h> 
   #include <string.h>
   cat number "count"  str and save to "tostr";
   return:
	OK: 1	failed: 0
************************************ */
unsigned int str_cat_any_number_str( char *tostr, int count, ... );

/**********************************************************
	del head and tail blank, middle blank keep single.
	#include <string.h>
	#include <stdlib.h>
*************************************************************/
char *str_del_head_and_tail_blank_middle_keep_one(char *to, const char *from);
/*int main(void)
{
	char *p, str[1024];
	p = str;
	str_del_head_and_tail_blank_middle_keep_one(p, "  fan yue   hui  .");
	printf("%s\n", p);
	getch();
}*/

/*****************************
	reverse the string:
		"abcde" -> "edcba"
	return pointer of the string.
******************************/
char *str_reverse(char *str);

/*****************************
	digit to string:
	example:
		digit: -12345 -> string:"-12345"
	digit:
		type: long
	require function:
		char *str_reverse(char *str);
	replace:
		sprintf();
******************************/
void str_digit_to_str(char *to, long digit);

/* show char of str, like UNIX od */
void str_display_char_like_unix_od(const char *str);

/* free SUM **pp 
	#include <stdlib.h> */
void str_free_sum_ppointer(char **pp, size_t sum);

/* get every str of *from(sep by 'one', 'tow', 'three')
   save to List_node *save 
   return count of str 
   
   require function: char_is_the_any_char() 
   micro: STR_BUFF_SIZE */
size_t str_get_every_str_save_to_list_sep_by_char(pList_node *save,\
				const char *from,\
				const char one,\
				const char two,\
				const char three);

/* include <ctype.h>

   filename is bad windows filename?
    return:
        badname: 1; 
        truename: 0
    filename example:
        "c:\\dir1\dir\file.txt"
    bad name:
        ":\dir1\file.txt"
        "\\dir1\file.txt"
        "C:\\dir1\filetxt"
************************************************/
size_t str_is_bad_win_file_name(const char *filename);

/*
  windows file name for example:
	"C:\\dir\filename.extension"
		path = "C:\\dir\"	save to "to_path"
		filename = "filename"	save to "filename"
		extension = "extension"	save to "extension"
  if failed:
	all is '\0'
*********************************************************/
void str_get_item_from_windows_path_name(char *to_path, \
					char *filename, \
					char *extension, \
					const char *window_path_name);
					
/****************************************************
    input string by keyboard(end by '\n'), save to "str";
    MUST less than INPUT_BUFF_SIZE - 1
    if INPUT_BUFF_SIZE, then: return INPUT_BUFF_SIZE - 1 chars.
******************************************************/
void str_input_save_to_str(char *str);

/****************************************************
        input string by keyboard;
        save to *str, MAX number is: INPUT_BUFF_SIZE
		
		#defineINPUT_BUF_SIZE 200
******************************************************/
void str_input_str_by_keyboard(char *str);

/*********************************************************
        after nth char of str(from ldft to rigth),
        insert char:"insert" after nth char;
        return head pointer.

        #include <string.h>
        #define BUF_SIZE        1024
**************************************************************/
char *str_insert_n_blank_to_str(char *from, char insert, unsigned int n);

/* *str include not like blank, return 0
  require function: char_is_blank()	*/
int str_is_blank_or_zero(const char *str);

/*****************************
	reverse the string:
		"abcde" -> "edcba"
	return pointer of the string.
******************************/
char *str_reverse(char *str);

/* get every str of *from(sep by 'one', 'tow', 'three')
   save to List_node *save 
   return count of str 
   
   require function: 
	char_is_the_any_char() 
   micro: 
	STR_BUFF_SZIE 	*/
size_t str_get_every_str_save_to_list_sep_by_char(pList_node *save,\
				const char *from,\
				const char one,\
				const char two,\
				const char three);
				


