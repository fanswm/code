
/********************************************
	how many "1" is the "num" have?
****************************************************/
size_t num_count_1(unsigned long num)
{
	size_t count;
	unsigned long n;
	n = num;
	
	count = 0;
	while(n > 0)
	{
		if(n & 1)
		{
			count++;
		}
		n >>= 1;
	}
	return count;
}

/*int main(void)
{
	printf("3 have 1: %d\n", num_count_1(185));
}*/

