/* any of args == dist: return 1;else:0
	args: const char
        number: count_char
        #include <stdarg.h>
*****************************************************/
size_t char_is_the_any_char(const char dist, size_t count_char, ...)
{
	size_t include_char;
	va_list ap;
	va_start( ap, count_char);
	
	include_char = 0;
	for( ; count_char > 0; count_char-- )
	{
		if(dist == va_arg(ap, int) )
		{
			include_char = 1;
			//break;//是否得调用完？
		}		
	}
	va_end(ap);
	return include_char;
}