#define RESULT_STR_LENTH   200

/* include <string.h>

   search "item" from FIRST line in filename."item" must be only in the line.
   search "search" start by SECOND line.
   FIRST line is 0 row;
   FIRST item is 0 clo;

   return:
   if finded:
            return 1;
            "search" at *row_result row, col_result col.
        else
            return 0;
            *row_result col_result all by 0;
    
    file type:
    
    item1   item2   item3   item4...
    str1    str2    str3    str4
    str5    str6    str7    str8
    ...
    
    file seq MUST by '\t'
*************************************************/
size_t file_search_str_of_item_from_file(size_t *row_result, \
                                                size_t *col_result, \
                                                const char *search, \
                                                const char *item, \
                                                const char *filename)
{
    FILE *fp;
    char ch, *p;
    size_t step, row;
    size_t have;
    int i;
    char str[RESULT_STR_LENTH] = {'\0'};

    step = 0;
    have = 0;

    p = str;
    if((fp = fopen(filename, "r")) == NULL)
    {
        printf("open addressbook failed! Please contact Administrator.\n");
        *row_result = 0;
        *col_result = 0;
        return 0;
    }

    while( (ch = fgetc(fp)) != '\n')   /* where is the search *item at? */
    {
        while(ch != '\t' && ch != '\n')
        {
            *p = ch;
            p++;
            ch = fgetc(fp);
        }
        *p = '\0';

        if( !strcmp(str, item) )
        {
            have = 1;   /* have *item */
            break;
        }
        else
        {
            step++;     /* how much item */
            p = str;
        }

        if(ch == '\n')      /* avoid '\n' then 'fgetc' */
        {
            break;
        }
    }

    /* if 'item' was not finded */
    if(!have )
    {
        *row_result = 0;
        *col_result = 0;
        return 0;
    }

    if(ch != '\n')
    {
        while( (ch = fgetc(fp)) != '\n' && !feof(fp) )       /* skip this row(0) other char */
            ;
    }

    *col_result = step;

    row = 1;
    have = 0;                   /* search from row: 1 */
    while( !feof(fp) )
    {
        while( (ch = fgetc(fp) ) != '\n' && !feof(fp) )          /*search every row*/
        {
            i = 0;
            while(i < step  && ch != '\n')
            {
                while(ch != '\t' && !feof(fp))    /* skip step-1 of '\t' AT every row */
                {
                    ch = fgetc(fp);
                }
                i++;
                /*counrent char is '\t' */
                ch = fgetc(fp);
            }

            p = str;            /* this pointer init */
            while( ch != '\t' && ch != '\n' && !feof(fp) )
            {
                *p = ch;
                p++;
                ch = fgetc(fp);
            }
            *p = '\0';

            /* skip this row other char */
            while(ch != '\n' && !feof(fp))
            {
                ch = fgetc(fp);
            }

            if(!strcmp(search, str) )
            {
                have = 1;
                break;
            }
            else
            {
                row++;
            }
        }

        if(have)     /* finded */
        {
            break;
        }
    }

    if(!have)
    {
        *row_result = 0;
        *col_result = 0;
        return 0;
    }

    *row_result = row;
    fclose(fp);

    return have;
}


/*int main(void)
{
    size_t i,j,*p1,*p2;
    p1 = &i;
    p2 = &j;

    file_search_str_of_item_from_file(p1, p2, "str3", "item3", "D:\\test.txt");
    printf("i = %d, j = %d\n", i, j);
    getch();
}*/

/*
D:\\test.txt:

item1    item2    item3    item4
str1    str2    str3    str4
str5    str6    str7    str8


*/

