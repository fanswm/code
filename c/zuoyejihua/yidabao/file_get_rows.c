/* get filename file rows
have 1 row, return 1(not 0) 
include EMPTY lines
***********************************/
FileSizeType file_get_rows(const char *filename)
{
	FILE *fp;
	FileSizeType get_rows, sum_chars;
	char ch, pre;

	if( (fp = fopen(filename, "r")) == NULL)
	{
		printf("open filename: %s failed! Please connect Administrator.\n", filename);
		return 0;
	}

	ch = fgetc(fp);

	get_rows = 0;
	sum_chars = 0;
	while(!feof(fp))
	{
		if(ch == '\n')
		{
			get_rows++;
		}
		sum_chars++;
		pre = ch;
		ch = fgetc(fp);
	}

	if(sum_chars > 0 && pre != '\n')
	{
		get_rows++;
	}

	fclose(fp);
	return get_rows;
}
