/* get every str of *from(sep by 'one', 'tow', 'three')
   save to List_node *save 
   return count of str 
   
   require function: char_is_the_any_char() 
   micro: BUFF_SZIE */
size_t str_get_every_str_save_to_list_sep_by_char(pList_node *save,\
				const char *from,\
				const char one,\
				const char two,\
				const char three)
{
	size_t count;
	const char *p;
	char *s, str[BUFF_SZIE] = {'\0'};
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