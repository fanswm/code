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

/*int main(void)
{
    char tmp[1024];

    printf("tmp: %f\n", file_get_rows("D:\\test.txt"));
    getch();
}*/


