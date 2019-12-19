#define RESULT_STR_LENTH    200
#define ITEMS_COUNT         4

/* include <string.h>

   file is seq by '\t', find row col item save to str:"to".
   FIRST line is 0 row;
   FIRST item is 0 clo;

   return:
   ok: 1
   else: 0
    
    file type:
    
    item1   item2   item3   item4...
    str1    str2    str3    str4
    str5    str6    str7    str8
    ...
    
    file seq MUST by '\t'
*************************************************/
size_t file_get_str_by_row_col(char *to,\
                const size_t row,\
                const size_t col,\
                const char *filename)
{
    FILE *fp;
    size_t have;
    int i;
    char ch, *p, str[RESULT_STR_LENTH] = {'\0'};

    if(col >= ITEMS_COUNT)
    {
        *to = '\0';
        printf("ERROR: you find col = %d is large than ITEMS_COUNT\n", col);
        return 0;
    }

    have = 0;

    p = str;
    if((fp = fopen(filename,"r")) == NULL)
    {
        printf("ERROR: open addressbook failed! Please contact Administrator.\n");
        *to = '\0';
        return 0;
    }

    /*fseek(fp, 0L, SEEK_SET); */

    i = 0; /* row */
    ch = fgetc(fp);
    while(i < row && !feof(fp))
    {
        if(ch == '\n')
        {
            i++;
        }
        ch = fgetc(fp);
    }

    if(i == row)
    {
        have = 1;
    }
    else
    {
        have = 0;
        return 0;
    }

    i = 0;   /* col */
    while(i < col  && (ch = fgetc(fp)) != '\n' && !feof(fp))
    /* if i < col, skip every char */
    {
        if(ch == '\t')
        {
            i++;
        }
    }

    ch = fgetc(fp);/* now, ch is first char of result */
    while(ch != '\t' && ch != '\n' && !feof(fp))
    {
        *p = ch;
        p++;
        ch = fgetc(fp);
    }
    *p = '\0';

    strcpy(to, str);/* copy result to str:"to" */

    fclose(fp);

    return have;
}


/*int main(void)
{
    char str[RESULT_STR_LENTH],*p;
    size_t have;
    p = str;


    have = file_get_str_by_row_col(p,2,2, "D:\\test.txt");
    printf("have = %d\nstr is: %s\n",have, str);
    getch();
}*/

/*
D:\\test.txt:

item1    item2    item3    item4
str1    str2    str3    str4
str5    str6    str7    str8


*/

