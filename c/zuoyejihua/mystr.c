#include "mystr.h"

#ifndef _MYCHAR_H_
#define _MYCHAR_H_
#include "mychar.h"
#endif

/* connect variable char save to str:"to"
        number: count_char
        #include <stdarg.h>
*****************************************************/
void str_cat_any_char_to_str( char *to, int count_char, ... )
{
	va_list ap;
	va_start( ap, count_char);

	for( ; count_char > 0; count_char-- )
	{
		*to = va_arg(ap, int);
		to++;
	}
	*to = '\0';

	va_end(ap);
}


/* #include <stdarg.h> 
   #include <string.h>

   cat number "count"  str and save to "tostr";
   return:
	OK: 1	failed: 0
************************************ */
unsigned int str_cat_any_number_str( char *tostr, int count, ... )
{
    char *p;
    unsigned int i;
    
    va_list argptr;
    va_start( argptr, count );	
    
    p = tostr;
    i = 0;
    for( ; count > 0; count-- )
    {
        if(i == 0)
    	{
            strcpy(p, va_arg( argptr, char* ));
        	i++;
    	}
        else
    	{
            strcat(p, va_arg( argptr, char* ));
        }		
    }
    
    va_end( argptr );
    
    return(i);
}

/*int main(void)
{
    char str[1024];
    str_cat_any_number_str(str, 7, "fan ", "yue ", "hui ", "is ", "a ", "good ", "man.");
    printf("str: %s\n", str);
    getch();
}*/

/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>*/

/**********************************************************
	del head and tail blank, middle blank keep single.
	#include <string.h>
	#include <stdlib.h>
*************************************************************/
char *str_del_head_and_tail_blank_middle_keep_one(char *to, const char *from)
{
        const char *pfrom;
        char *pto, *p, *pth, *plastblk;
        int isblk, l;

	if(!from)
	{
		return NULL;
	}
        isblk = 0;
        l = strlen(from) + 1;

        pto = (char *) malloc(l);
        memset(pto, '\0', l);

        p = pto;
        pfrom = from;
        while(*pfrom == ' ')	/* del head blank */
        {
                pfrom++;
        }
        while(*pfrom)
        {
                if(*pfrom == ' ')
                {
                        isblk = 1;
                        plastblk = pto;
                        *pto++ = *pfrom++;
                        while(*pfrom == ' ')
                        {
                                pfrom++;
                        }
                }
                else
                {
                        isblk = 0;
                	*pto++ = *pfrom++;
                }
        }
        if(isblk)
        {
                *plastblk = '\0';
        }

	strcpy(to, p);
	free(p);
	p = NULL;
	return to;
}

/*int main(void)
{
	char *p, str[1024];
	p = str;
	str_del_head_and_tail_blank_middle_keep_one(p, "  fan yue   hui  .");
	printf("%s\n", p);
	getch();
}*/

void str_digit_to_str(char *to, long digit)
{
	long d;
	char *t = to;
	
	if(digit < 0)
	{
		d = -digit;
	}
	else
	{
		d = digit;
	}
	
	while(d)
	{
		*t = d % 10 + '0';
		t++;
		d /= 10;
	}
	*t++ = '-';
	*t = '\0';
	
	str_reverse(to); 
}

/*int main(void)
{
	char str[1024], *t;
	
	t = str;
	str_digit_to_str(t, -12345);
	printf("str: %s\n", t);
	getch();
}*/

/* show char of str, like UNIX od */
void str_display_char_like_unix_od(const char *str)
{
	const char *p = str;
	while(*p)
	{
		if(*p == ' ')
		{
			printf("\\b ");
		}
		else if(*p == '\t')
		{
			printf("\\t ");
		}
		else if(*p == '\n')
		{
			printf("\\n ");
		}
		else
		{
			printf("%c ", *p);
		}
		p++;
	}
	printf("\n");
}

/* free SUM **pp 
	#include <stdlib.h> */
void str_free_sum_ppointer(char **pp, size_t sum)
{
	char **p1, **p2;
	p1 = pp;
	
	while(sum > 0 && p1)
	{
		printf("func: %s: %s\n", __FUNCTION__, *p1);
		free(*p1);
		p2 = p1;
		free(p1);
		sum--;
		p1 = p2;
		p1++;
	}
}

/* get every str of *from(sep by 'one', 'tow', 'three')
   save to List_node *save 
   return count of str 
   
   require function: char_is_the_any_char() 
   micro: STR_BUFF_SIZE */
size_t str_get_every_str_save_to_list_sep_by_char(pList_node *save,\
				const char *from,\
				const char one,\
				const char two,\
				const char three)
{
	size_t count;
	const char *p;
	char *s, str[STR_BUFF_SIZE] = {'\0'};
	p = from;
	s = str;
	count = 0;
	
	assert(save != NULL && from != NULL);
	
	while(*p != '\0')
	{
		s = str;
		while(!char_is_the_any_char(*p, 3, one, two, three)\
			&& *p != '\0')
		{
			*s = *p;
			s++;
			p++;
		}
		*s = '\0';
		list_append(save, str);
		count++;
		
		if(*p != '\0')
		{
			p++;/* skip 'one' 'tow' 'three' */
		}
	}
	return count;	
}

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
					const char *window_path_name)
{
    char *pos, *p, *pos2;
    char buf[FILE_NAME_LEN];
    size_t ok, bad_char;

    bad_char = str_is_bad_win_file_name(window_path_name);

    if(bad_char)
    {
        *to_path = '\0';
        *filename = '\0';
        *extension = '\0';
        printf("Error: The file name include bad_char!\n");   /*  windows_path_name include bad char */
        return;
    }

    p = buf;
    strcpy(p, window_path_name);
    pos = strrchr(p, '\\');
    pos++;                          /* skip '\\' */
    *pos = '\0';
    strcpy(to_path, p);         /* to_path compleate */

    p = buf;
    pos = strrchr(window_path_name, '\\');
    pos++;                          /* skip '\\' */
    strcpy(p, pos);
    pos = strrchr(p, '.');
    *pos = '\0';                    /* set '.' to '\0' */
    strcpy(filename, buf);          /* filename compleate */

    pos = strrchr(window_path_name, '.');
    pos++;
    strcpy(extension, pos);       /* extension compleate */
}

/*int main(void)
{
    char path[FILE_NAME_LEN], *filename[FILE_NAME_LEN], *extension[FILE_NAME_LEN];
    str_get_item_from_windows_path_name(path, filename, extension, "c:\\dir1\\testfile.txt");
    printf("path: %s\n filename: %s\n extension: %s",path, filename, extension);
    getchar();
}*/

/****************************************************
    input string by keyboard(end by '\n'), save to "str";
    MUST less than INPUT_BUFF_SIZE - 1
    if INPUT_BUFF_SIZE, then: return INPUT_BUFF_SIZE - 1 chars.
******************************************************/
void str_input_save_to_str(char *str)
{
	char *p = str;
	char ch;
	int i = 0;
	
	while( (ch = getchar()) != '\n' && i < INPUT_BUFF_SIZE )
	{
		*p = ch;	
		putchar(ch);
		
		i++;
		if(i == INPUT_BUFF_SIZE)
		{
			printf("\nerror: your input is too long!\n");
			continue;
		}
		p++;
	}
	*p = '\0';
	printf("\n");
}

/*int main(void)
{
    char *p, str[INPUT_BUFF_SIZE];
    p = str;
    
    str_input_save_to_str(p);
    printf("P is:  %s\n", p);
    getc();
}*/



/****************************************************
        input string by keyboard;
        save to *str, MAX number is: INPUT_BUFF_SIZE
		
		#defineINPUT_BUF_SIZE 200
******************************************************/
void str_input_str_by_keyboard(char *str)
{
	char *p = str;
	char ch;
	int i = 0;

	while(
			( (ch = getchar()) != '\r')
			&& i < INPUT_BUFF_SIZE
		)
	{
		*p = ch;
		putchar(ch);

		i++;
		if(i ==INPUT_BUFF_SIZE)
		{
			printf("FUN:str_input_str_by_keyboard:\nerror: your input is too long!\n");
			continue;
		}
		p++;
	}
	*p = '\0';
	putchar('\n');
}

/*********************************************************
        after nth char of str(from ldft to rigth),
        insert char:"insert" after nth char;
        return head pointer.

        #include <string.h>
        #define STR_BUFF_SIZE        1024
**************************************************************/
char *str_insert_n_blank_to_str(char *from, char insert, unsigned int n)
{
	char *t1, *t2, to[STR_BUFF_SIZE];
	int i = 0;

	t1 = from;
	t2 = to;

	for(i = 1; i <= n; i++)
	{
		if( !(*t1) )			/*如果是空字符,则停止*/
		{
			break;
		}
		*t2 = *t1;
		t2++;
		t1++;
	}
	*t2 = insert;
	t2++;

	while(*t1++)
	{
		*t2 = *t1;
		t2++;
	}

	*t2 = '\0';
	strcpy(from,to);
	return from;
}
/*
int main()
{

	char *a, aa[20] = "123456789";
	char *b,bb[13];


	a = aa;
	b = bb;

	b = insert_n_blank_to_str(a,3);
	printf("old is:%s,new is:%s\n",a, b);

}*/


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
	legle filename:
		first char is alpha;
		second char is ':';
		next char is '\\';
		include char '.';
************************************************/
size_t str_is_bad_win_file_name(const char *filename)
{
    const char *p;
    char ch;
    size_t maohao, fanxiegang, dian, have_error;        
    /* include ':' or '\\' or  '.'  or have_error */
    
    size_t first_char_is_alpha;
    maohao = 0;
    fanxiegang = 0;
    dian = 0;
    have_error = 0;
    first_char_is_alpha = 0;

    p = filename;
    ch = *p;
    if(isalpha(ch))
    {
        first_char_is_alpha = 1;
    }
    p++;
    while(*p)
    {
        ch = *p;
        if(ch == '*' || ch == '?')  /* have_error */
        {
            have_error = 1;
        }

        if(ch == ':')   /* maohao */
        {
            maohao++;
        }
        if(ch == '\\')  /* fanxiegang */
        {
            fanxiegang++;
        }
        if(ch == '.')   /* dian */
        {
            dian++;
        }
        p++;
    }

    if( (maohao == 1 && fanxiegang && dian && first_char_is_alpha ) && !have_error)
    {
        have_error = 0;
    }
    else
    {
        have_error = 1;
    }

    return have_error;
}

/*int main(void)
{
    size_t t;
    t = str_is_bad_win_file_name("C:\\test.txt");
    printf("t = %d\n",t);
    getchar();
}*/

/* *str include not like blank, return 0
  require function: char_is_blank()	*/
int str_is_blank_or_zero(const char *str)
{
        const char *p;
        int is_blk_or_zero = 1;

        if(!p)
        {
        	return 1;
        }

        p = str;
        while(*p)
        {
                if(*p == '.')
                {
                        p++;
                        continue;
                }
                if(*p != '0' && !char_is_blank(*p))
                {
                        is_blk_or_zero = 0;
                }
                p++;
        }
        return is_blk_or_zero;
}

/*****************************
	reverse the string:
		"abcde" -> "edcba"
	return pointer of the string.
******************************/
char *str_reverse(char *str)
{
	char *p1, *p2;
	char tmp;
	size_t i, len;
	
	p1 = str;
	p2 = str;
	len = 0;
	
	while(*p2)
	{
		len++;
		p2++;
	}
	p2--;
	
	for(i = 1; i <= (len / 2); i++)
	{
		tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
	p1 = str;
	return p1;
}

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

/*int main(void)
{
	char *str = "abcde";
	
	printf("is: %s\n", str_reverse(str));
	printf("str: %s\n", str);
	getch();
}*/
