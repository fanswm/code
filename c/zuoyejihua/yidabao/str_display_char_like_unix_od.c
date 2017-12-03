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
