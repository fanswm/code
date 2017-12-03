/*********************************************************
        after nth char of str(from ldft to rigth),
        insert char:"insert" after nth char;
        return head pointer.

        #include <string.h>
        #define BUF_SIZE        1024
**************************************************************/
char *insert_n_blank_to_str(char *from, char insert, unsigned int n)
{
	char *t1, *t2, to[BUF_SIZE];
	int i = 0;

	t1 = from;
	t2 = to;

	for(i = 1; i <= n; i++)
	{
		if( !(*t1) )			/*如果是空字符,则停止*/
		{
			break;
		}
		*t2 = *t1;
		t2++;
		t1++;
	}
	*t2 = insert;
	t2++;

	while(*t1++)
	{
		*t2 = *t1;
		t2++;
	}

	*t2 = '\0';
	strcpy(from,to);
	return from;
}

int main()
{

	char *a, aa[20] = "123456789";
	char *b,bb[13];


	a = aa;
	b = bb;

	b = insert_n_blank_to_str(a,3);
	printf("old is:%s,new is:%s\n",a, b);

}
