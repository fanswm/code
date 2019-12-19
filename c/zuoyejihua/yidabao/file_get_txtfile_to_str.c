/* get file neirong, save to: str_of_file.
	the str_of_file must be large */
void file_get_txtfile_to_str(const char *filename, char *str_of_file)
{
    int flen;
    FILE *fp;

    fp = fopen(filename, "r");
    fseek(fp, 0L, SEEK_END);    /* set pos:"file" END */
    flen = ftell(fp);           /* get file bytes */

    if(str_of_file == NULL)
    {
        fclose(fp);
        printf("fanswm_debug: get_file_to_str: Error: str_of_file == NULL\n");
        return;
    }
    else
    {
        fseek(fp, 0L, SEEK_SET);/* set pos:"file" START */
        fread(str_of_file, flen, 1, fp);    /* read file all by ones */
        str_of_file[flen] = '\0';       /* string END flag */
        fclose(fp);
    }
}

/*test start
int main(void)
{
    char str[1024];
    file_get_txtfile_to_str("d:\\test.txt", str);
    printf("str: %s\n", str);
    getch();
}
test end*/
