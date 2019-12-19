/* write str append to file: FILE *fp
   and fclose(fp) 
*********************************************/
void file_write_str_append(char *str, FILE *fp)
{
    fwrite(str, strlen(str), 1, fp);
    fwrite("\n", 1, 1, fp);
    fclose(fp);
}