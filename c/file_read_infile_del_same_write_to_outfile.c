#include <stdio.h>
#include <string.h>

#define MAX_COUNT	10000
#define MAX_LENTH	256
/*
ȥ���������ظ���������е��ظ��� 
Դ�ļ���pinzhong.txt��ÿһ����'\t','\n'�ָ���
Ŀ���ļ���out.txt��һ��Ϊһ�С� 
*/


/*********************************************************************** 
��һ���ָ�����TAB��ENTER���ļ�filename�У���ȡÿһ��浽���飺to_array,��������
ÿһ����һ���ַ������ַ����ĳ���ΪMAX_LENTH, ���������������geted_sum
	read infile whitch seq by '\n' or '\t',
	each string save to (*to_array)[MAX_LENTH],
	how many save to *geted_sum,
***************************************************************************/
void get_char_from_file_seq_TAB(char (*to_array)[MAX_LENTH], \
				int *geted_sum, \
				const char *filename)
{
	FILE *f;
	char ch;
	char str[MAX_LENTH], *p_str;
	char (*p_array)[MAX_LENTH];
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
			if(i >= MAX_COUNT)
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
����to_array����sum����ظ�������е��ظ�����ֻ����һ�������Ϊ"\0" 
 */
void set_null_at_same_for_array(char (*to_array)[MAX_LENTH], int sum)
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
����to_array����sum��ظ�����Ϊ"\0"���Ѳ���"\0"����д�뵽�ļ�tofilename�С� 
 */
void print_array_to_file(const char *tofilename, char (*to_array)[MAX_LENTH], int sum)
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
void file_read_infile_del_same_write_to_outfile(void)
{
	char str_array[MAX_COUNT][MAX_LENTH];
	char (*p_array)[MAX_LENTH];
	int sum, *psum;
	
	printf("This program for read input_file(seq by '\\t' or '\\n')\n");
	printf("and write to an array. Delete same item in it;\n");
	printf("and write to out_file:D:\\out_pinz.txt! Good lucky!\n\n");
	printf("Usage:\n");
	printf("1. Make file \"D:\\pinz.txt\" at local host;\n");
	printf("2. Copy items from Excel file, count items below MAX_COUNT:10000.\n");
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
int main(void)
{
	file_read_infile_del_same_write_to_outfile();
}
