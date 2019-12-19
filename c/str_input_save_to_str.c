#define INPUT_BUF_SIZE	10
/****************************************************
    input string by keyboard(end by '\n'), save to "str";
    MUST less than INPUT_BUF_SIZE - 1
    if INPUT_BUF_SIZE, then: return INPUT_BUF_SIZE - 1 chars.
******************************************************/
void str_input_save_to_str(char *str)
{
	char *p = str;
	char ch;
	int i = 0;
	
	while( 
			( (ch = getc()) != '\n') 
			&& i < INPUT_BUF_SIZE  
		)
	{
		*p = ch;	
		putc(ch);
		
		i++;
		if(i == INPUT_BUF_SIZE)
		{
			printf("\nerror: your input is too long!\n");
			continue;
		}
		p++;
	}
	*p = '\0';
	putc('\n');
}

/*int main(void)
{
    char *p, str[INPUT_BUF_SIZE];
    p = str;
    
    str_input_save_to_str(p);
    printf("P is:  %s\n", p);
    getc();
}*/
