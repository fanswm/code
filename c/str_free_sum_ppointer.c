/* free SUM **pp 
	#include <stdlib.h> */
void str_free_sum_ppointer(char **pp, size_t sum)
{
	char **p1, **p2;
	p1 = pp;
	
	while(sum > 0 && p1)
	{
		printf("func: %s: %s\n", __FUNCTION__, *p1);
		free(*p1);
		p2 = p1;
		free(p1);
		sum--;
		p1 = p2;
		p1++;
	}
}