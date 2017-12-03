/* connect variable char save to str:"to"
        number: count_char
        #include <stdarg.h>
*****************************************************/
void str_cat_any_char_to_str( char *to, size_t count_char, ... )
{
	va_list argptr;
	va_start( argptr, count_char );

    for( ; count_char > 0; count_char-- )
	{
		*to = va_arg(argptr, const char);
		to++;
	}
	*to = '\0';

	va_end( argptr );
}
