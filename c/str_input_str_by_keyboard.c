

/****************************************************
        input string by keyboard;
        save to *str, MAX number is: INPUT_BUF_SIZE
		
		#defineINPUT_BUF_SIZE 200
******************************************************/
void str_input_str_by_keyboard(char *str)
{
	char *p = str;
	char ch;
	int i = 0;

	while(
			( (ch = getch()) != '\r')
			&& i < INPUT_BUF_SIZE
		)
	{
		*p = ch;
		putch(ch);

		i++;
		if(i ==INPUT_BUF_SIZE)
		{
			printf("FUN:str_input_str_by_keyboard:\nerror: your input is too long!\n");
			continue;
		}
		p++;
	}
	*p = '\0';
	putch('\n');
}
