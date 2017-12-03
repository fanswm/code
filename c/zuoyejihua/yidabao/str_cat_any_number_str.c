
/* include <stdarg.h> 
   include <string.h>

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