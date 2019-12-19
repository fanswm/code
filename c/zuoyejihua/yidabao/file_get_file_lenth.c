/* get "filename" file length by "mode".
    mode:"r"  or "rb"
    return "0" or "+num": OK!

    "-num": failed!

    return file lenth, include '\t' '\n', ' ' */
double file_get_file_lenth(const char *filename,\
                        const char *mode)
{
    double flen;
    FILE *fp;

    if( strcmp(mode, "r") == 0 || strcmp(mode, "rb") == 0)
    {
        ;
    }
    else
    {
        printf("fanswm_debug: get_file_lenth: error mode!\n");
        return -1;
    }

    if((fp = fopen(filename, mode) ) == NULL)
    {
        printf("fanswm_debug: get_file_lenth: Error: open file failed\n");
        return -1;
    }
    fseek(fp, 0L, SEEK_END);        /* set pos:"file" END */
    flen = ftell(fp);               /* get file bytes */

    fclose(fp);
    return flen;
}

