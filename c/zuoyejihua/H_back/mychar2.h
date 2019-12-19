#include <stdio.h>
#include <stdarg.h>

/* if ch == ' ','\t','\n', return 1 */
unsigned char char_is_blank(const char ch);

/* any of args == dist: return 1;else:0
	args: const char
        number: count_char
        #include <stdarg.h>
*****************************************************/
size_t char_is_the_any_char(const char dist, size_t count_char, ...);
