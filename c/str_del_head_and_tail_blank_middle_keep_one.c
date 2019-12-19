/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>*/

/**********************************************************
	del head and tail blank, middle blank keep single.
	#include <string.h>
	#include <stdlib.h>
*************************************************************/
char *str_del_head_and_tail_blank_middle_keep_one(char *to, const char *from)
{
        const char *pfrom;
        char *pto, *p, *pth, *plastblk;
        int isblk, l;

	if(!from)
	{
		return NULL;
	}
        isblk = 0;
        l = strlen(from) + 1;

        pto = (char *) malloc(l);
        memset(pto, '\0', l);

        p = pto;
        pfrom = from;
        while(*pfrom == ' ')	/* del head blank */
        {
                pfrom++;
        }
        while(*pfrom)
        {
                if(*pfrom == ' ')
                {
                        isblk = 1;
                        plastblk = pto;
                        *pto++ = *pfrom++;
                        while(*pfrom == ' ')
                        {
                                pfrom++;
                        }
                }
                else
                {
                        isblk = 0;
                	*pto++ = *pfrom++;
                }
        }
        if(isblk)
        {
                *plastblk = '\0';
        }

	strcpy(to, p);
	free(p);
	p = NULL;
	return to;
}

/*int main(void)
{
	char *p, str[1024];
	p = str;
	str_del_head_and_tail_blank_middle_keep_one(p, "  fan yue   hui  .");
	printf("%s\n", p);
	getch();
}*/
