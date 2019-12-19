#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define INPUT_BUF_SIZE	200
#define FILE_NAME_LEN	200


unsigned int is_blank(char ch)
{
	return( (ch == ' ' || ch == '\t') ? 1 : 0 );
}

/*****************************************************
 This program whill format C file, as: 
	head: '\t';
	indentation
 ******************************************************/
void file_format_c_file(char *filename, char *newfilename)
{
	FILE *f, *newfile;

	int i;
	int count_indentation, count_ch, count_enter;
	int is_line_head, sign_flag, single_indentation; 
	char ch, pre_ch, next_ch;

	if((f = fopen(filename,"r")) == NULL)
	{
		printf("open %s error!\n", filename);
		return;
	}

	if((newfile = fopen(newfilename,"w")) == NULL)
	{
		printf("open %s error!\n", newfilename);
		return;
	}

	count_indentation = 0;
	count_ch = 0;
	count_enter = 0;
	single_indentation = 0;
	sign_flag = 0;		/* have ';' or '#' or '{' or '}' , then sign_flag = 1*/
	
	ch = fgetc(f);
	if(!feof(f))		/* except sizeof file is 0 */
	{
		pre_ch = ch;
		next_ch = fgetc(f);
	}
	
	is_line_head = 1;
	while(!feof(f))
	{
		if(single_indentation)		/* processing single line indentation. */
		{
			fprintf(newfile, "%c", '\t');
			/*printf("fenhao.\n");*/
			single_indentation = 0;
		}
		for(i = 0; i < count_indentation; i++)		/* write '\t' count_indentation */
		{
			fprintf(newfile, "%c", '\t');
		}
			
		while( ch != '\n' && !feof(f))
		{
			if(isgraph(ch))		/* after read first graph char, is_line_head is FALSE */
			{
				is_line_head = 0;
				if(count_enter)		/* if length of line is lianxu 0, count_enter++ */
				{
					count_enter = 0;/* miss first graph char,then count_enter = 0 */
				}
			}

			/* jump 'blank' and 'tab' of every line head */
			if(is_line_head)
			{
				while(is_blank(ch))
				{
					pre_ch = ch;
					ch = next_ch;
					next_ch = fgetc(f);	/* jump blank */
				}
			}

			if(ch == '{')
			{
				if(pre_ch != '\n')		/* if before '{' not '\n',then '\n'*/
				{
					fprintf(newfile, "%c", '\n');
				}
				
				fprintf(newfile, "%c", ch);	/* write '{' */
				count_indentation++;				
				
				pre_ch = ch;
				ch = next_ch;
				next_ch = fgetc(f);
			}
			else if(ch == ';')
			{
				sign_flag = 1;
				fprintf(newfile, "%c", ch);				
				
				pre_ch = ch;
				ch = next_ch;
				next_ch = fgetc(f);
			}
			else if(ch == '}')
			{
				if(pre_ch != '\n')		/* if before '{' not '\n',then '\n'*/
				{
					fprintf(newfile, "%c", '\n');
				}
				sign_flag = 1;
				fprintf(newfile, "%c", ch);	/* write soujin and '}' */		

				pre_ch = ch;
				ch = next_ch;
				next_ch = fgetc(f);
			}
			else if(ch == '#')
			{
				fprintf(newfile, "%c", ch);
				sign_flag = 1;
				pre_ch = ch;
				ch = next_ch;
				next_ch = fgetc(f);
			}
			else
			{
				fprintf(newfile, "%c", ch);
				count_ch++;				
				
				pre_ch = ch;
				ch = next_ch;
				next_ch = fgetc(f);
			}
		}
		
		/*printf("pre_ch = %c; ch = %c; next_ch = %c\n", pre_ch, ch, next_ch);*/
		
		if(!count_ch)	/* count_ch == 0 */
		{
			sign_flag = 1;	/* after zero line, not indentation */
			count_enter++;
		}
		count_ch = 0;
		
		if(ch == '{' || next_ch == '{')
		{
			sign_flag = 1; 	/* next_ch == '{', not indentation */
		}
		
		if(count_enter <= 1)	/* lianxu > 2 zero line, print 1 zero line only */
		{
			fprintf(newfile, "%c", '\n');	/* end of this line */
		}
		
		is_line_head = 1;
		if(sign_flag)
		{
			single_indentation = 0;
		}
		else
		{
			single_indentation = 1;
		}
		sign_flag = 0;
		
		pre_ch = ch;
		ch = next_ch;
		next_ch = fgetc(f);
		
		if(ch == '}')
		{
			sign_flag = 1;
			count_indentation--;
			if(count_indentation <= 0)
			{
				count_indentation = 0;
			}
		}
	}
	fclose(f);
	fclose(newfile);
}

/****************************************************
    input string by keyboard(end by '\n'), save to "str";
    MUST less than INPUT_BUF_SIZE - 1
    if INPUT_BUF_SIZE, then: return INPUT_BUF_SIZE - 1 chars.
******************************************************/
void str_input_save_to_str(char *str)
{
	char *p = str;
	char ch;
	int i = 0;
	
	while( 
			( (ch = getchar()) != '\n') 
			&& i < INPUT_BUF_SIZE  
		)
	{
		*p = ch;	
		putchar(ch);
		
		i++;
		if(i == INPUT_BUF_SIZE)
		{
			printf("\nerror: your input is too long!\n");
			continue;
		}
		p++;
	}
	*p = '\0';
	putchar('\n');
}

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

/* include <ctype.h>

   pathname is legle windows pathname?
    return:
        badname: 0; 
        truename: 1;
    filename example:
        "c:\\dir1\dir\file.txt"
    bad name:
        ":\dir1\file.txt"
        "\\dir1\file.txt"
        "C:\\dir1\filetxt"
************************************************/
size_t str_is_legle_win_path(const char *pathname)
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

    p = pathname;
    ch = *p;
    if(isalpha(ch))
    {
        first_char_is_alpha = 1;
    }
    p++;
    while(*p)
    {
        ch = *p;
        if(ch == '*' || ch == '?')  /* legle path name not include '*' or '?'. else: have_error */
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

    if( (maohao == 1 && fanxiegang && !dian && first_char_is_alpha ) && !have_error)
    {
        have_error = 0;
    }
    else
    {
        have_error = 1;
    }

    return !have_error;
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

/*************************************************
 except BUG: 
	(1) path name is too long!
	(2) "new_filename" is exit
	(3) single '\' not recognition
	(4) function: file_format_c_file() arithmetic is error.
 require function:
	void str_get_item_from_windows_path_name(char *to_path, \
					char *filename, \
					char *extension, \
					const char *window_path_name);
	size_t str_is_legle_win_path(const char *pathname);
	size_t str_is_bad_win_file_name(const char *filename);
	void str_input_save_to_str(char *str);
	void file_format_c_file(char *filename, char *newfilename);
	unsigned int is_blank(char ch);
*****************************************************/
void file_format_c_file_with_input_name(void)
{
	char *fullname, *path, *filename, *tmp, *extension;
	char full[FILE_NAME_LEN], p[FILE_NAME_LEN], fn[FILE_NAME_LEN], e[FILE_NAME_LEN];
	size_t flag = 1;
	char t[FILE_NAME_LEN] = {'\0'};
	
	fullname = full;
	path = p;
	filename = fn;
	extension = e;
	tmp = t;
	
	printf("Please input infile full path(windowns seq by '\\''\\'), finish by ENTER:\n");
	str_input_save_to_str(fullname);
	flag = str_is_bad_win_file_name(fullname);
	while(flag)
	{
		printf("Your fullname have error, try again:\n");
		str_input_save_to_str(fullname);
		flag = str_is_bad_win_file_name(fullname);
	}
	if(!flag)
	{
		printf("Now, infile finish: %s\n", fullname);
	}
	
	str_get_item_from_windows_path_name(path, filename, extension, fullname);
	if(strcmp(extension, "c") != 0 && strcmp(extension, "C") != 0 )	/* Not an C file */
	{
		printf("Warning: your input is not C file!\n");
	}
	
	/*printf("New filename is start by \"new_\"\n");*/
	strcpy(tmp, path);
	strcat(tmp, "new_");
	strcat(tmp, filename);
	strcat(tmp, ".");
	strcat(tmp, extension);
	/*printf("new filename is: %s\n", tmp);*/
	file_format_c_file(fullname, tmp);
}

int main(void)
{
	file_format_c_file_with_input_name();
}


/*
	This file would formate C file like:
	#include...
	int main()
	{
		int i;
		...;
		if(...)
			...;
		while(...)
		{
			...;
		}
	}
*/
