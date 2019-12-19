#define BUF_SIZE 200

/* read line of FILE *from, save to str "to". */
void file_get_line_save_to_str_by_fp(char *to, FILE *from)
{
    char ch;
    int i = 0;
    
    ch = getc(from);	
    while(ch != '\n' && ch != EOF && i < BUF_SIZE )
    {
        *to++ = ch;
        ch = getc(from);
        i++;	
    }
    *to = '\0';
}