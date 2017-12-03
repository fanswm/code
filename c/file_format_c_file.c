#include <stdio.h>
#include <string.h>
#include <ctype.h>

unsigned int is_blank(char ch)
{
	return( (ch == ' ' || ch == '\t') ? 1 : 0 );
}

void format_c_file(char *filename, char *newfilename)
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

int main(void)
{
	format_c_file("D:\\code\\python\\t.c", "D:\\code\\python\\newt.c");
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
