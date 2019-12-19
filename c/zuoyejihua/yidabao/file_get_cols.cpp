/* first COL = 1
   return count of str
   if not found col:
   return 0   */
FileSizeType file_get_cols(const char *filename)
{
	FILE *fp;
	char ch, pre;
	int i;
	FileSizeType sum_chars;
	assert(filename != NULL);
	
	if((fp = fopen(filename, "r")) == NULL)
	{
		printf("ERROR: open %s failed!\n", filename);
		return 0;
	}

	i = 0;
	sum_chars = 0;
	ch = fgetc(fp);
	while(ch != '\n' && !feof(fp))
	{
		if(ch == '\t')
		{
			i++;
		}
		sum_chars++;
		pre = ch;
		ch = fgetc(fp);
	}
	if(sum_chars > 0 
		&& (pre != '\n' && pre != '\t'))
	{
		i++;
	}
	fclose(fp);
	return i;	
}
