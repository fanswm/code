/* sort array(num) small to large */
void array_sort_small_to_large(int *arr, int num)
{
	int i, j, tmp;

	for(j = 0; j < num - 1; j++)
	{
		for(i = j + 1; i < num; i++)
		{
			if( *(arr + j) < *(arr + i))
			{
				tmp = *(arr + j);
				*(arr + j) = *(arr + i);
				*(arr + i) = tmp;
			}
		}
	}
}
