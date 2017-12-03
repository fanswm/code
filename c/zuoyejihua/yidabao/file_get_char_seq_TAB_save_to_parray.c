/*********************************************************************** 
从一个分隔符是TAB或ENTER的文件filename中，读取每一项，存到数组：to_array,这个数组的
每一项是一个字符串，字符串的长度为MAX_LENTH, 共读出多少项，存入geted_sum
	read infile whitch seq by '\n' or '\t',
	each string save to (*to_array)[MAX_LENTH],
	how many save to *geted_sum,
***************************************************************************/
void file_get_char_seq_TAB_save_to_parray(char (*to_array)[MAX_LENTH], \
					int *geted_sum, \
					const char *filename)
{
	FILE *f;
	char ch;
	char str[MAX_LENTH], *p_str;
	char (*p_array)[MAX_LENTH];
	int j, i;
	
	p_str = str;
	p_array = to_array;
	i = 0;
	
	f = fopen(filename, "r");
	
	if((f = fopen(filename,"r")) == NULL)
	{
		printf("Cannot open input_file:%s.\n", filename);
		*geted_sum = 0;
		return;
	}
	
	ch = fgetc(f);	
	while(!feof(f))
	{
		while(ch != '\t'  && ch != '\n')
		{
			*p_str = ch;
			p_str++;
			ch = fgetc(f);
		}
		*p_str = '\0';
		if(strlen(str) > 3)
		{
			if(i >= MAX_COUNT)
			{
				printf("Your input items is too many!\nbreak!\n");
				*geted_sum = i - 1;
				return;
			}
			strcpy(p_array[i], str);
			i++;
		}
		p_str = str;
		ch = fgetc(f);
	}	
	fclose(f);
	*geted_sum = i;
}