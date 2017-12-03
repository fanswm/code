#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void)
{
	FILE *fp, *print_it;
	char ch, *p;
	int i, j;
	
	p = &ch;
	
	if((fp = freopen("PRN","w", stdout)) == NULL)
	{
		printf("freopen(\"PRN\",\"w\", stdout)) error!\n");
		return 1;
	}
	/*
	if((print_it = fopen("./t.c", "r")) == NULL)
	{
		printf("open t.c error.\n");
		return 1;
	}
	
	*p = fgetc(print_it);
	while(!feof(print_it))
	{
		//n = fprintf(fp, (const char *) p );
		printf("%c", *p);
		*p = fgetc(print_it);
	}
	printf("\n");
	**/
	
	for(j = 0; j < 8; j++)
	{
		for(i = 0; i < 10; i++)
		{
			printf("%d",i);
		}
	}
	printf("\n");
	
	//fclose(print_it);
	fclose(fp);
	p = NULL;
	print_it = NULL;
	return 0;
}
