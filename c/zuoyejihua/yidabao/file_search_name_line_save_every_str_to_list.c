/* search for *name from first col of filename, 
   return (result rows)
   first row = 0
   not foun: return -1;
   require function: list_append; */
FileSizeType file_search_name_line_save_every_str_to_list(pList_node *save,\
				const char *name,\
				const char *filename)
{
	FILE *fp;
	FileSizeType row;
	unsigned char found;
	char ch, *p, str[STR_BUFF_SZIE] = {'\0'};
	
	assert(save != NULL 
		&& name != NULL 
		&& filename != NULL);
	
	if((fp = fopen(filename,"r")) == NULL)
	{
		printf("ERROR: open %s failed!\n", filename);
		return 0;
	}

	row = 0;
	found = 0;
	ch = fgetc(fp);
	while(!feof(fp))
	{
		while(ch != '\n' && !feof(fp))/* search every line */
		{
			p = str;
			while(ch != '\t' 
				&& ch != '\n' 
				&& !feof(fp))/* search firstword of every line */
			{
				*p = ch;
				p++;
				ch = fgetc(fp);
			}
			*p = '\0';
			
			if(strcmp(name, str) == 0)
			{
				found = 1;
				break;
			}
			ch = fgetc(fp);	/* skip '\t' '\n' */
			
		}
		row++;
		ch = fgetc(fp); /* skip '\t' or '\n' */
		if(found == 1)
		{
			break;
		}
	}
	if(found == 0)/* not found */
	{
		fclose(fp);
		save = NULL;
		return -1;
	}
	
	list_append(save, str);
	
	while(ch != '\n' && !feof(fp))
	{
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
		list_append(save, str);
		
		if(ch == '\t')/* flirt '\n' */
		{
			ch = fgetc(fp);/* skip '\t' */
		}
	}

	fclose(fp);
	return row;	
}
