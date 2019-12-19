/* every line of file, sep by '\t'
   get COL col save to list: *save
   first COL = 1
   return count of str
   if not found col:
   return 0   */
FileSizeType file_get_col_of_str_save_to_list(pList_node *save,\
				const FileSizeType col,\
				const char *filename)
{
	FILE *fp;
	FileSizeType found_strs, i;
	char ch, *p, str[STR_BUFF_SZIE] = {'\0'};
	
	assert(save != NULL && filename != NULL);
	
	i = file_get_cols(filename);
	if(col > i)
	{
		printf("the file: %s\n cols = %ld, but col = %ld\n",\
				filename, i, col);
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
	
	ch = fgetc(fp);
	while(!feof(fp))
	{
		while(ch != '\n' && !feof(fp))/* search every line */
		{
			i = 1;
			while(i < col 
				&& ch != '\t' 
				&& ch != '\n' 
				&& !feof(fp))
			{
				if(ch == '\t')
				{
					i++;
				}
				ch = fgetc(fp);
			}/* found start of col */
			/* this time:ch == '\t' || ch == '\n' */
			
			if(col > 1)
			{
				ch = fgetc(fp);
			}
		
			p = str;
			while(ch != '\t' 
				&& ch != '\n' 
				&& !feof(fp))
			{
				*p = ch;
				p++;
				ch = fgetc(fp);
			}
			*p = '\0';
			found_strs++;
			list_append(save, str);
			/* this time:ch == '\t' || ch == '\n' */
						
			if(ch != '\n' && !feof(fp))
			{
				while(ch != '\n')
				{
					if(feof(fp))
					{
						break;
					}
					ch = fgetc(fp);
				}
			}/* if not end, skip other char of the line */
			if(ch == '\n')
			{
				ch = fgetc(fp);/* skip '\n' */
			}
		}
	}
	fclose(fp);
	return found_strs;
}
