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

