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

/*int main(void)
{
	char *str = "abcde";
	
	printf("is: %s\n", str_reverse(str));
	printf("str: %s\n", str);
	getch();
}*/