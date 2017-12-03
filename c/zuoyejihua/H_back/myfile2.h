#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STR_BUFF_SIZE	1024
#define SEARCH_STR_COUNT	4
#define FOUND_STR_COUNT	5
#define MAX_COUNT_STR_OF_FILE	10000
#define RESULT_STR_LENTH   200

typedef unsigned long FileSizeType;

/*  create "addressBook" by name:filename. if not have:create.

    if OK, return 1;
    else return 0       */
size_t file_create_file(const char *filename);

unsigned int is_blank(char ch);

void format_c_file(char *filename, char *newfilename);

/*********************************************************************** 
从一个分隔符是TAB或ENTER的文件filename中，读取每一项，存到数组：to_array,这个数组的
每一项是一个字符串，字符串的长度为MAX_LENTH, 共读出多少项，存入geted_sum
	read infile whitch seq by '\n' or '\t',
	each string save to (*to_array)[STR_BUFF_SIZE],
	how many save to *geted_sum,
***************************************************************************/
void file_get_char_seq_TAB_save_to_parray(char (*to_array)[STR_BUFF_SIZE], \
					int *geted_sum, \
					const char *filename);
/*********************************************************************** 
从一个分隔符是TAB或ENTER的文件filename中，读取每一项，存到数组：to_array,这个数组的
每一项是一个字符串，字符串的长度为MAX_LENTH, 共读出多少项，存入geted_sum
	read infile whitch seq by '\n' or '\t',
	each string save to (*to_array)[MAX_LENTH],
	how many save to *geted_sum,
***************************************************************************/
void file_get_char_seq_TAB_save_to_parray(char (*to_array)[MAX_LENTH], \
					int *geted_sum, \
					const char *filename);

/* get "filename" file length by "mode".
    mode:"r"  or "rb"
    return "0" or "+num": OK!

    "-num": failed!

    return file lenth, include '\t' '\n', ' ' */
double file_get_file_lenth(const char *filename,\
                        const char *mode);
			
/* read line of FILE *from, save to str "to". */
void file_get_line_save_to_str_by_fp(char *to, FILE *from);

/* get filename file rows
have 1 row, return 1(not 0) 
include EMPTY lines
***********************************/
FileSizeType file_get_rows(const char *filename);

/* first COL = 1
   return count of str
   if not found col:
   return 0   */
FileSizeType file_get_cols(const char *filename);

/*
  FIRST line is 0;
  get "row" line save to "to".
****************************************************/
size_t file_get_line_save_to_str_by_row(char *to, \
					size_t row,\
					const char *filename);
					
size_t file_get_str_by_row_col(char *to,\
                const size_t row,\
                const size_t col,\
                const char *filename);
size_t file_get_str_row_col_from_file(double row[FOUND_STR_COUNT], \
                                    size_t col[FOUND_STR_COUNT], \
                                    const char *search, \
                                    const char *filename);
/* get file neirong, save to: str_of_file.
	the str_of_file must be large */
void file_get_txtfile_to_str(const char *filename, char *str_of_file);

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
FILE *file_open_file_by_mode(const char *filename, const char *mode);

/*********************************************************************** 
从一个分隔符是TAB或ENTER的文件filename中，读取每一项，存到数组：to_array,这个数组的
每一项是一个字符串，字符串的长度为MAX_LENTH, 共读出多少项，存入geted_sum
	read infile whitch seq by '\n' or '\t',
	each string save to (*to_array)[STR_BUFF_SIZE],
	how many save to *geted_sum,
***************************************************************************/
void get_char_from_file_seq_TAB(char (*to_array)[STR_BUFF_SIZE], \
				int *geted_sum, \
				const char *filename);

/* 
数组to_array中有sum项，有重复项，把其中的重复的项只保留一项，其他置为"\0" 
 */
void set_null_at_same_for_array(char (*to_array)[STR_BUFF_SIZE], int sum);

/* 
数组to_array中有sum项，重复的项为"\0"，把不是"\0"的项写入到文件tofilename中。 
 */
void print_array_to_file(const char *tofilename, char (*to_array)[STR_BUFF_SIZE], int sum);

/*
去除掉含有重复项的数组中的重复项 
源文件：pinzhong.txt的每一项用'\t','\n'分隔；
目标文件：out.txt第一项为一行。 
*/
void file_read_infile_del_same_write_to_outfile(void);
/* search for *name from first col of filename, 
   return (result rows)
   first row = 0
   not foun: return -1;
   require function: list_append; */
FileSizeType file_search_name_line_save_every_str_to_list(pList_node *save,\
				const char *name,\
				const char *filename);
				
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
                                                const char *filename);
/* write str append to file: FILE *fp
   and fclose(fp) 
*********************************************/
void file_write_str_append(char *str, FILE *fp);

/* every line of file, sep by '\t'
   get COL col save to list: *save
   first COL = 1
   return count of str
   if not found col:
   return 0   */
FileSizeType file_get_col_of_str_save_to_list(pList_node *save,\
				const FileSizeType col,\
				const char *filename);
				
/* every line of file, sep by '\t'
   get ROW row save to list: *save
   first row = 1
   return count of str
   if not found row:
   return 0   */
FileSizeType file_get_row_of_str_save_to_list(pList_node *save,\
				const FileSizeType row,\
				const char *filename);








