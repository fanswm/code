#include "myfile.h"

/*  create "addressBook" by name:filename. if not have:create.

    if OK, return 1;
    else return 0       */
size_t file_create_file(const char *filename)
{
    FILE *book;

    if((book = fopen(filename,"r")) == NULL)
    {
        printf("Cannot open addressbook file. now try created!\n");

        if((book = fopen(filename,"w")) == NULL)
        {
            printf("Create addressbook failed! Please contact Administrator.\n");
            return 0;
        }
        else
        {
            printf("Create addressbook OK!\n");
            fclose(book);
            return 1;
        }
    }
    else
    {
        printf("open addressbook OK!\n");
        fclose(book);
        return 1;
    }
}

MyBoolType is_blank(char ch)
{
	return( (ch == ' ' || ch == '\t') ? 1 : 0 );
}

void format_c_file(char *filename, char *newfilename)
{
	FILE *f, *newfile;

	FileSizeType i;
	FileSizeType count_indentation, count_ch, count_enter;
	FileSizeType is_line_head, sign_flag, single_indentation; 
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
			printf("fenhao.\n");
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
		
		printf("pre_ch = %c; ch = %c; next_ch = %c\n", pre_ch, ch, next_ch);
		
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

/*********************************************************************** 
从一个分隔符是TAB或ENTER的文件filename中，读取每一项，存到数组：to_array,这个数组的
每一项是一个字符串，字符串的长度为MAX_LENTH, 共读出多少项，存入geted_sum
	read infile whitch seq by '\n' or '\t',
	each string save to (*to_array)[STR_BUFF_SIZE],
	how many save to *geted_sum,
***************************************************************************/
void file_get_char_seq_TAB_save_to_parray(char (*to_array)[STR_BUFF_SIZE], \
					int *geted_sum, \
					const char *filename)
{
	FILE *f;
	char ch;
	char str[STR_BUFF_SIZE], *p_str;
	char (*p_array)[STR_BUFF_SIZE];
	int j, i;
	
	p_str = str;
	p_array = to_array;
	i = 0;
	
	f = fopen(filename, "r");
	
	if((f = fopen(filename,"r")) == NULL)
	{
		printf("Cannot open input_file:%s.\n", filename);
		*geted_sum = 0;
		return;
	}
	
	ch = fgetc(f);	
	while(!feof(f))
	{
		while(ch != '\t'  && ch != '\n')
		{
			*p_str = ch;
			p_str++;
			ch = fgetc(f);
		}
		*p_str = '\0';
		if(strlen(str) > 3)
		{
			if(i >= MAX_COUNT_STR_OF_FILE)
			{
				printf("Your input items is too many!\nbreak!\n");
				*geted_sum = i - 1;
				return;
			}
			strcpy(p_array[i], str);
			i++;
		}
		p_str = str;
		ch = fgetc(f);
	}	
	fclose(f);
	*geted_sum = i;
}

/* get "filename" file length by "mode".
    mode:"r"  or "rb"
    return "0" or "+num": OK!

    "-num": failed!

    return file lenth, include '\t' '\n', ' ' */
FileSizeType file_get_file_lenth(const char *filename,\
                        const char *mode)
{
    FileSizeType flen;
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


/* read line of FILE *from, save to str "to". */
void file_get_line_save_to_str_by_fp(char *to, FILE *from)
{
    char ch;
    int i = 0;
    
    ch = getc(from);	
    while(ch != '\n' && ch != EOF && i < STR_BUFF_SIZE )
    {
        *to++ = ch;
        ch = getc(from);
        i++;	
    }
    *to = '\0';
}

/* get filename file rows
have 1 row, return 1(not 0) 
include EMPTY lines
***********************************/
FileSizeType file_get_rows(const char *filename)
{
	FILE *fp;
	FileSizeType get_rows, sum_chars;
	char ch, pre;

	if( (fp = fopen(filename, "r")) == NULL)
	{
		printf("open filename: %s failed! Please connect Administrator.\n", filename);
		return 0;
	}

	ch = fgetc(fp);

	get_rows = 0;
	sum_chars = 0;
	while(!feof(fp))
	{
		if(ch == '\n')
		{
			get_rows++;
		}
		sum_chars++;
		pre = ch;
		ch = fgetc(fp);
	}

	if(sum_chars > 0 && pre != '\n')
	{
		get_rows++;
	}

	fclose(fp);
	return get_rows;
}

/* first COL = 1
   return count of str
   if not found col:
   return 0   */
FileSizeType file_get_cols(const char *filename)
{
	FILE *fp;
	char ch, pre;
	int i;
	FileSizeType sum_chars;
	assert(filename != NULL);
	
	if((fp = fopen(filename, "r")) == NULL)
	{
		printf("ERROR: open %s failed!\n", filename);
		return 0;
	}

	i = 0;
	sum_chars = 0;
	ch = fgetc(fp);
	while(ch != '\n' && !feof(fp))
	{
		if(ch == '\t')
		{
			i++;
		}
		sum_chars++;
		pre = ch;
		ch = fgetc(fp);
	}
	if(sum_chars > 0 
		&& (pre != '\n' && pre != '\t'))
	{
		i++;
	}
	fclose(fp);
	return i;	
}

/*
  FIRST line is 0;
  get "row" line save to "to".
****************************************************/
FileSizeType file_get_line_save_to_str_by_row(char *to, \
					FileSizeType row,\
					const char *filename)
{
    FILE *fp;
    FileSizeType have, i;
    double rows;
    char ch, *tmp = to;

    if( (fp = fopen(filename, "r") ) == NULL)
    {
        printf("file_get_line_save_to_str_by_row:\n\
            \tError:\n\topen filename: %s failed! Please contact Administrator.\n",\
            filename);
        *to = '\0';
        return 0;
    }

    rows = file_get_rows(filename);

    if(rows == 0.0 || row > rows)
    {
        printf("file_get_line_save_to_str_by_row:\n \
                    \tError:\n\t The file: %s is empty or row too large!\n", filename);
        *to = '\0';
        return 0;
    }

    have = 0;
    i = 1;	/* because FIRST lien is 1 */
    ch = fgetc(fp);
    while(i < row && !feof(fp))	/* skip row-1 lines */
    {
        if(ch == '\n')
        {
            i++;
        }
        ch = fgetc(fp);
    }

    while(ch != '\n')	/* get row line save to "to" */
    {
        *to = ch;
        ch = fgetc(fp);
        to++;
    }
    *to = '\0';

    fclose(fp);
    return 1;

}

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
FileSizeType file_get_str_by_row_col(char *to,\
                const FileSizeType row,\
                const FileSizeType col,\
                const char *filename)
{
    FILE *fp;
    FileSizeType have;
    FileSizeType i;
    char ch, *p, str[STR_BUFF_SIZE] = {'\0'};

    if(col >= SEARCH_STR_COUNT)
    {
        *to = '\0';
        printf("ERROR: you find col = %u is large than SEARCH_STR_COUNT\n", col);
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

/* include <string.h>

   find "search" from "filename",
   only find first FOUND_STR_COUNT result, 
   save row and col of "search" 
   to row[FOUND_STR_COUNT] and col[FOUND_STR_COUNT].
   
   return:
	row[FOUND_STR_COUNT] and col[FOUND_STR_COUNT].
   
   file type MUST seq by '\t'
************************************************************/
FileSizeType file_get_str_row_col_from_file(double row[FOUND_STR_COUNT], \
                                    FileSizeType col[FOUND_STR_COUNT], \
                                    const char *search, \
                                    const char *filename)
{
    FILE *fp;
    FileSizeType have, c, *pc;
    double r, *pr;
    int i;
    char *p, ch, buf[STR_BUFF_SIZE] = {'\0'};

    if((fp = fopen(filename,"r")) == NULL)
    {
        printf("file_get_str_row_col_from_file:\n\
            \tError:\n\topen file: %s failed! Please connect Administrator.\n",\
            filename);
        *row = 0;
        *col = 0;
        return -1;
    }

    for(i = 0; i < FOUND_STR_COUNT; i++)
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

            if(i == FOUND_STR_COUNT)      /* only first FOUND_STR_COUNT result */
            {
                return 1;
            }
        }
    }

    fclose(fp);
    return have;
}

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

/* open a file: "filename", by mode: "mode" 
   mode:
	"r" open file for read; 
	"w" create file for write; 
	"a" append a txtfile; 
	"rb" open a binary file for read; 
	"wb" create a binary file for write; 
	"ab" append to binary file; 
	"r+" open txtfile for read/write; 
	"w+" create a txtfile for read/write; 
	"a+" open a txtfile for read/write; 
	"rb+" open a binary file for read/write; 
	"wb+" create a binary file for read/write; 
	"ab+" open a binary file for read/write;

   OK: return FILE *fp;
   else: return NULL
   
	MUST fclose(fp);
***********************************************/
FILE *file_open_file_by_mode(const char *filename, const char *mode)
{
    FILE *fp;
    
    if( (fp = fopen(filename, mode)) == NULL)
    {
        printf("open filename: %s failed! Please connect Administrator.\n", filename);
        return NULL;
    }
    return fp;
}

/*********************************************************************** 
从一个分隔符是TAB或ENTER的文件filename中，读取每一项，存到数组：to_array,这个数组的
每一项是一个字符串，字符串的长度为MAX_LENTH, 共读出多少项，存入geted_sum
	read infile whitch seq by '\n' or '\t',
	each string save to (*to_array)[STR_BUFF_SIZE],
	how many save to *geted_sum,
***************************************************************************/
void get_char_from_file_seq_TAB(char (*to_array)[STR_BUFF_SIZE], \
				int *geted_sum, \
				const char *filename)
{
	FILE *f;
	char ch;
	char str[STR_BUFF_SIZE], *p_str;
	char (*p_array)[STR_BUFF_SIZE];
	int j, i;
	
	p_str = str;
	p_array = to_array;
	i = 0;
	
	f = fopen(filename, "r");
	
	if((f = fopen(filename,"r")) == NULL)
	{
		printf("Cannot open input_file:%s.\n", filename);
		*geted_sum = 0;
		return;
	}
	
	ch = fgetc(f);	
	while(!feof(f))
	{
		while(ch != '\t'  && ch != '\n')
		{
			*p_str = ch;
			p_str++;
			ch = fgetc(f);
		}
		*p_str = '\0';
		if(strlen(str) > 3)
		{
			if(i >= MAX_COUNT_STR_OF_FILE)
			{
				printf("Your input items is too many!\nbreak!\n");
				*geted_sum = i - 1;
				return;
			}
			strcpy(p_array[i], str);
			i++;
		}
		p_str = str;
		ch = fgetc(f);
	}	
	fclose(f);
	*geted_sum = i;
}

/* 
数组to_array中有sum项，有重复项，把其中的重复的项只保留一项，其他置为"\0" 
 */
void set_null_at_same_for_array(char (*to_array)[STR_BUFF_SIZE], int sum)
{
	int i, j;

	for(i = 0; i < sum; i++)
	{
		if(strcmp(to_array[i], "\0") == 0)
		{
			continue;
		}
		for(j = i + 1; j < sum; j++)
		{
			if(strcmp(to_array[i], "\0") == 0)
			{
				continue;
			}
			if(strcmp(to_array[i], to_array[j]) == 0)
			{
				strcpy(to_array[j], "\0");
			}
		}
	}
}

/* 
数组to_array中有sum项，重复的项为"\0"，把不是"\0"的项写入到文件tofilename中。 
 */
void print_array_to_file(const char *tofilename, char (*to_array)[STR_BUFF_SIZE], int sum)
{
	FILE *out;
	int i;
	
	if((out = fopen(tofilename, "w")) == NULL)
    {
        printf("Cannot create output_file:%s.\n", tofilename);
		return;
    }
    
	for(i = 0; i < sum; i++)
	{
		if(strcmp(to_array[i], "\0") != 0)
		{
			fprintf(out, "%s\n", to_array[i]);
		}
	}	
	fclose(out);
}

/*
去除掉含有重复项的数组中的重复项 
源文件：pinzhong.txt的每一项用'\t','\n'分隔；
目标文件：out.txt第一项为一行。 
*/
void file_read_infile_del_same_write_to_outfile(void)
{
	char str_array[MAX_COUNT_STR_OF_FILE][STR_BUFF_SIZE];
	char (*p_array)[STR_BUFF_SIZE];
	int sum, *psum;
	
	printf("This program for read input_file(seq by '\\t' or '\\n')\n");
	printf("and write to an array. Delete same item in it;\n");
	printf("and write to out_file:D:\\out_pinz.txt! Good lucky!\n\n");
	printf("Usage:\n");
	printf("1. Make file \"D:\\pinz.txt\" at local host;\n");
	printf("2. Copy items from Excel file, count items below MAX_COUNT_STR_OF_FILE:10000.\n");
	printf("3. Run the program.\n");
	printf("4. \"D:\\out_pinz.txt\" is the result.\n\n");
	printf("Press any key to end...\n");
	getchar();
	
	psum = &sum;
	p_array = str_array;
	
	get_char_from_file_seq_TAB(p_array, psum, "d:\\pinz.txt");
	set_null_at_same_for_array(p_array, sum);
	print_array_to_file("d:\\out_pinz.txt", p_array, sum);
}
/*
int main(void)
{
	file_read_infile_del_same_write_to_outfile();
}*/

/* search for *name from first col of filename, 
   return (result rows)
   first row = 0
   not found: return -1;
   require function: list_append; */
FileSizeType file_search_name_line_save_every_str_to_list(pList_node *save,\
				const char *name,\
				const char *filename)
{
	FILE *fp;
	FileSizeType row;
	unsigned char found;
	char ch, *p, str[STR_BUFF_SIZE] = {'\0'};
	
	assert(save != NULL 
		&& name != NULL 
		&& filename != NULL);
	
	if((fp = fopen(filename,"r")) == NULL)
	{
		printf("ERROR: open %s failed!\n", filename);
		return 0;
	}

	row = 0;
	found = 0;
	ch = fgetc(fp);
	while(!feof(fp))
	{
		while(ch != '\n' && !feof(fp))/* search every line */
		{
			p = str;
			while(ch != '\t' 
				&& ch != '\n' 
				&& !feof(fp))/* search firstword of every line */
			{
				*p = ch;
				p++;
				ch = fgetc(fp);
			}
			*p = '\0';
			
			if(strcmp(name, str) == 0)
			{
				found = 1;
				break;
			}
			ch = fgetc(fp);	/* skip '\t' '\n' */
			
		}
		row++;
		ch = fgetc(fp); /* skip '\t' or '\n' */
		if(found == 1)
		{
			break;
		}
	}
	if(found == 0)/* not found */
	{
		fclose(fp);
		save = NULL;
		return -1;
	}
	
	list_append(save, str);
	
	while(ch != '\n' && !feof(fp))
	{
		p = str;
		while(ch != '\t' 
			&& ch != '\n'
			&& !feof(fp))
		{
			*p = ch;
			p++;
			ch = fgetc(fp);
		}
		*p = '\0';
		list_append(save, str);
		
		if(ch == '\t')/* flirt '\n' */
		{
			ch = fgetc(fp);/* skip '\t' */
		}
	}

	fclose(fp);
	return row;	
}




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

/* write str append to file: FILE *fp
   and fclose(fp) 
*********************************************/
void file_write_str_append(FILE *fp, const char *str)
{
    fwrite(str, strlen(str), 1, fp);
    fwrite("\n", 1, 1, fp);
    fclose(fp);
}

/* every line of file, sep by '\t'
   get COL col save to list: *save
   first COL = 1
   return count of str
   if not found col:
   return 0   */
FileSizeType file_get_col_of_str_save_to_list(pList_node *save,\
				const FileSizeType col,\
				const char *filename)
{
	FILE *fp;
	FileSizeType found_strs, i;
	char ch, *p, str[STR_BUFF_SIZE] = {'\0'};
	
	assert(save != NULL && filename != NULL);
	
	i = file_get_cols(filename);
	if(col > i)
	{
		printf("the file: %s\n cols = %ld, but col = %ld\n",\
				filename, i, col);
		*save = NULL;
		return 0;
	}
	
	if((fp = fopen(filename,"r")) == NULL)
	{
		printf("ERROR: open %s failed!\n", filename);
		*save = NULL;
		return 0;
	}

	found_strs = 0;
	
	ch = fgetc(fp);
	while(!feof(fp))
	{
		while(ch != '\n' && !feof(fp))/* search every line */
		{
			i = 1;
			while(i < col 
				&& ch != '\t' 
				&& ch != '\n' 
				&& !feof(fp))
			{
				if(ch == '\t')
				{
					i++;
				}
				ch = fgetc(fp);
			}/* found start of col */
			/* this time:ch == '\t' || ch == '\n' */
			
			if(col > 1)
			{
				ch = fgetc(fp);
			}
		
			p = str;
			while(ch != '\t' 
				&& ch != '\n' 
				&& !feof(fp))
			{
				*p = ch;
				p++;
				ch = fgetc(fp);
			}
			*p = '\0';
			found_strs++;
			list_append(save, str);
			/* this time:ch == '\t' || ch == '\n' */
						
			if(ch != '\n' && !feof(fp))
			{
				while(ch != '\n')
				{
					if(feof(fp))
					{
						break;
					}
					ch = fgetc(fp);
				}
			}/* if not end, skip other char of the line */
			if(ch == '\n')
			{
				ch = fgetc(fp);/* skip '\n' */
			}
		}
	}
	fclose(fp);
	return found_strs;
}

/* every line of file, sep by '\t'
   get ROW row save to list: *save
   first row = 1
   return count of str
   if not found row:
   return 0   */
FileSizeType file_get_row_of_str_save_to_list(pList_node *save,\
				const FileSizeType row,\
				const char *filename)
{
	FILE *fp;
	FileSizeType found_strs, rows;
	char ch, *p, str[STR_BUFF_SIZE] = {'\0'};
	
	assert(save != NULL && filename != NULL);
	
	rows = file_get_rows(filename);
	if(row > rows)
	{
		printf("the file: %s\n rows = %ld, but row = %ld\n",\
				filename, rows, row);
		*save = NULL;
		return 0;
	}
	
	if((fp = fopen(filename,"r")) == NULL)
	{
		printf("ERROR: open %s failed!\n", filename);
		*save = NULL;
		return 0;
	}

	found_strs = 0;
	rows = 1;/* first line */
	
	ch = fgetc(fp);
	while(row > 1 && rows < row && !feof(fp))/* search every line */
	{
		if(ch == '\n')
		{
			++rows;
			if(rows >= row)
			{
				break;
			}
		}
		ch = fgetc(fp);
	}/* ch == '\n' or first char */
	
	if(row > 1)
	{
		ch = fgetc(fp);	
	}
	
	while(ch != '\n' && !feof(fp))
	{
		p = str;
		while(ch != '\t' && ch != '\n' && !feof(fp))
		{
			*p = ch;
			p++;
			ch = fgetc(fp);
		}/* ch == '\t' or '\n' or EOF */
		*p = '\0';
		
		found_strs++;
		list_append(save, str);

		if(ch == '\n')
		{
			break;
		}
		ch = fgetc(fp);
	}
	fclose(fp);
	return found_strs;	
}












