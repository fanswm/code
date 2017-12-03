#define RESULT_MAX_COUNT	5
#define BUF_SIZE	1024

/* include <string.h>

   find "search" from "filename",
   only find first RESULT_MAX_COUNT result, 
   save row and col of "search" 
   to row[RESULT_MAX_COUNT] and col[RESULT_MAX_COUNT].
   
   return:
	row[RESULT_MAX_COUNT] and col[RESULT_MAX_COUNT].
   
   file type MUST seq by '\t'
************************************************************/
size_t file_get_str_row_col_from_file(double row[RESULT_MAX_COUNT], \
                                    size_t col[RESULT_MAX_COUNT], \
                                    const char *search, \
                                    const char *filename)
{
    FILE *fp;
    size_t have, c, *pc;
    double r, *pr;
    int i;
    char *p, ch, buf[BUF_SIZE] = {'\0'};

    if((fp = fopen(filename,"r")) == NULL)
    {
        printf("file_get_str_row_col_from_file:\n\
            \tError:\n\topen file: %s failed! Please connect Administrator.\n",\
            filename);
        *row = 0;
        *col = 0;
        return -1;
    }

    for(i = 0; i < RESULT_MAX_COUNT; i++)
    {
        row[i] = 0;
        col[i] = 0;
    }       /* init */

    pr = row;       /* result */
    pc = col;

    p = buf;
    i = 0;          /* count */
    have = 0;
    r = 0;
    c = 0;
    while(!feof(fp))
    {
        ch = fgetc(fp);
        while(ch != '\t' && ch != '\n' && !feof(fp))
        {
            *p = ch;
            p++;
            ch = fgetc(fp);
        }
        *p = '\0';
        p = buf;

        if(ch == '\t')
        {
            c++;
        }
        if(ch == '\n')
        {
            c = 0;
            r++;
        }

        if(!strcmp(buf, search) )
        {
            have = 1;
            *pr = r;
            pr++;
            *pc = c - 1;
            pc++;
            i++;

            if(i == RESULT_MAX_COUNT)      /* only first RESULT_MAX_COUNT result */
            {
                return 1;
            }
        }
    }

    fclose(fp);
    return have;
}

/*int main(void)
{
    double a[5];
    size_t b[5];
    file_get_str_row_col_from_file(a,b,"str7", "D:\\test.txt");
    printf("a: %f\n b: %d\n",a[0], b[0]);
    getch();
}*/