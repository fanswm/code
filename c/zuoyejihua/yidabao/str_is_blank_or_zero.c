/****************************************
 if ch == ' ','\t','\n', return 1
********************************************/
unsigned char char_is_blank(const char ch)
{
        return (ch == ' ' || ch == '\t' || ch == '\n') ? 1 : 0;
}

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
