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


