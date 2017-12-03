#define FILE_NAME_LEN	200

/* include <ctype.h>

   filename is bad windows filename?
    return:
        badname: 1; 
        truename: 0
    filename example:
        "c:\\dir1\dir\file.txt"
    bad name:
        ":\dir1\file.txt"
        "\\dir1\file.txt"
        "C:\\dir1\filetxt"
************************************************/
size_t str_is_bad_win_file_name(const char *filename)
{
    const char *p;
    char ch;
    size_t maohao, fanxiegang, dian, have_error;        
    /* include ':' or '\\' or  '.'  or have_error */
    
    size_t first_char_is_alpha;
    maohao = 0;
    fanxiegang = 0;
    dian = 0;
    have_error = 0;
    first_char_is_alpha = 0;

    p = filename;
    ch = *p;
    if(isalpha(ch))
    {
        first_char_is_alpha = 1;
    }
    p++;
    while(*p)
    {
        ch = *p;
        if(ch == '*' || ch == '?')  /* have_error */
        {
            have_error = 1;
        }

        if(ch == ':')   /* maohao */
        {
            maohao++;
        }
        if(ch == '\\')  /* fanxiegang */
        {
            fanxiegang++;
        }
        if(ch == '.')   /* dian */
        {
            dian++;
        }
        p++;
    }

    if( (maohao == 1 && fanxiegang && dian && first_char_is_alpha ) && !have_error)
    {
        have_error = 0;
    }
    else
    {
        have_error = 1;
    }

    return have_error;
}

/*
  windows file name for example:
	"C:\\dir\filename.extension"
		path = "C:\\dir\"	save to "to_path"
		filename = "filename"	save to "filename"
		extension = "extension"	save to "extension"
  if failed:
	all is '\0'
*********************************************************/
void str_get_item_from_windows_path_name(char *to_path, \
					char *filename, \
					char *extension, \
					const char *window_path_name)
{
    char *pos, *p, *pos2;
    char buf[FILE_NAME_LEN];
    size_t ok, bad_char;

    bad_char = str_is_bad_win_file_name(window_path_name);

    if(bad_char)
    {
        *to_path = '\0';
        *filename = '\0';
        *extension = '\0';
        printf("Error: The file name include bad_char!\n");   /*  windows_path_name include bad char */
        return;
    }

    p = buf;
    strcpy(p, window_path_name);
    pos = strrchr(p, '\\');
    pos++;                          /* skip '\\' */
    *pos = '\0';
    strcpy(to_path, p);         /* to_path compleate */

    p = buf;
    pos = strrchr(window_path_name, '\\');
    pos++;                          /* skip '\\' */
    strcpy(p, pos);
    pos = strrchr(p, '.');
    *pos = '\0';                    /* set '.' to '\0' */
    strcpy(filename, buf);          /* filename compleate */

    pos = strrchr(window_path_name, '.');
    pos++;
    strcpy(extension, pos);       /* extension compleate */
}

/*int main(void)
{
    char path[FILE_NAME_LEN], *filename[FILE_NAME_LEN], *extension[FILE_NAME_LEN];
    str_get_item_from_windows_path_name(path, filename, extension, "c:\\dir1\\testfile.txt");
    printf("path: %s\n filename: %s\n extension: %s",path, filename, extension);
    getchar();
}*/