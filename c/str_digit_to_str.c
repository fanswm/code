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

/*****************************
	digit to string:
	example:
		digit: -12345 -> string:"-12345"
	digit:
		type: long
	require function:
		char *str_reverse(char *str);
	replace:
		sprintf();
******************************/
void str_digit_to_str(char *to, long digit)
{
	long d;
	char *t = to;
	
	if(digit < 0)
	{
		d = -digit;
	}
	else
	{
		d = digit;
	}
	
	while(d)
	{
		*t = d % 10 + '0';
		t++;
		d /= 10;
	}
	*t++ = '-';
	*t = '\0';
	
	str_reverse(to); 
}

/*int main(void)
{
	char str[1024], *t;
	
	t = str;
	str_digit_to_str(t, -12345);
	printf("str: %s\n", t);
	getch();
}*/