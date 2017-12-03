/* every line of file, sep by '\t'
   get ROW row save to list: *save
   first row = 1
   return count of str
   if not found row:
   return 0   */
FileSizeType file_get_row_of_str_save_to_list(pList_node *save,\
				const FileSizeType row,\
				const char *filename)
{
	FILE *fp;
	FileSizeType found_strs, rows;
	char ch, *p, str[STR_BUFF_SZIE] = {'\0'};
	
	assert(save != NULL && filename != NULL);
	
	rows = file_get_rows(filename);
	printf("get rows = %ld\n", rows);
	if(row > rows)
	{
		printf("the file: %s\n rows = %ld, but row = %ld\n",\
				filename, rows, row);
		*save = NULL;
		return 0;
	}
	
	if((fp = fopen(filename,"r")) == NULL)
	{
		printf("ERROR: open %s failed!\n", filename);
		*save = NULL;
		return 0;
	}

	found_strs = 0;
	rows = 1;/* first line */
	
	while(row > 1 && rows < row && !feof(fp))/* search every line */
	{
		ch = fgetc(fp);
		if(ch == '\n')
		{
			++rows;
		}
	}/* ch == '\n' or first char */
	
	if(row > 1)
	{
		ch = fgetc(fp);	
	}
	
	while(ch != '\n' && !feof(fp))
	{
		p = str;
		while(ch != '\t' && ch != '\n' && !feof(fp))
		{
			*p = ch;
			p++;
			ch = fgetc(fp);
		}/* ch == '\t' or '\n' or EOF */
		*p = '\0';
		
		found_strs++;
		list_append(save, str);

		if(ch == '\n')
		{
			break;
		}
		ch = fgetc(fp);
	}
	fclose(fp);
	return found_strs;	
}
