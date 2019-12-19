/* get filename file rows
have 1 row, return 1(not 0) 
include EMPTY lines
***********************************/
double file_get_rows(const char *filename)
{
    FILE *fp;
    double get_rows;
    char ch;

    if( (fp = fopen(filename, "r")) == NULL)
    {
        printf("open filename: %s failed! Please connect Administrator.\n", filename);
        return 0;
    }

    ch = fgetc(fp);
    if(ch)
    {
	get_rows = 1;
    }
    else
    {
	get_rows = 0;
    }
    while(!feof(fp))
    {
        if(ch == '\n')
        {
            get_rows++;
        }
        ch = fgetc(fp);
    }

    fclose(fp);

    return get_rows;
}

/*
  FIRST line is 0;
  get "row" line save to "to".
****************************************************/
size_t file_get_line_save_to_str_by_row(char *to, \
					size_t row,\
					const char *filename)
{
    FILE *fp;
    size_t have, i;
    double rows;
    char ch, *tmp = to;

    if( (fp = fopen(filename, "r") ) == NULL)
    {
        printf("file_get_line_save_to_str_by_row:\n\
            \tError:\n\topen filename: %s failed! Please contact Administrator.\n",\
            filename);
        *to = '\0';
        return 0;
    }

    rows = file_get_rows(filename);

    if(rows == 0.0 || row > rows)
    {
        printf("file_get_line_save_to_str_by_row:\n \
                    \tError:\n\t The file: %s is empty or row too large!\n", filename);
        *to = '\0';
        return 0;
    }

    have = 0;
    i = 1;	/* because FIRST lien is 1 */
    ch = fgetc(fp);
    while(i < row && !feof(fp))	/* skip row-1 lines */
    {
        if(ch == '\n')
        {
            i++;
        }
        ch = fgetc(fp);
    }

    while(ch != '\n')	/* get row line save to "to" */
    {
        *to = ch;
        ch = fgetc(fp);
        to++;
    }
    *to = '\0';

    fclose(fp);
    return 1;

}

/*int main(void)
{
    char tmp[1024];
    
    file_get_line_save_to_str_by_row(tmp, 2, "D:\\test.txt");
    printf("tmp: %s\n", tmp);
    getch();
}*/