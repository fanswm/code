#include "myarray.h"

/*************************************
  quick sort:
        min: low;
        max: high
*****************************************/
void array_quick_sort(int *a, int low, int high)
{
    int i = low;
    int j = high;
    int temp = a[i];

    if( low < high)
    {
        while(i < j)
        {
            while( (a[j] >= temp) && (i < j) )
            {
                j--;
            }
            a[i] = a[j];
            while( (a[i] <= temp) && (i < j) )
            {
                i++;
            }
            a[j]= a[i];
        }
        a[i] = temp;
        array_quick_sort(a, low, i - 1);
        array_quick_sort(a, j+1, high);
    }
    else
    {
        return;
    }
}

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

/*************************************
把map[]中的数(共max个)随机排列到to[]中。
map[]中不能有0的记录
map和to同样大
如果成功，返回1，否则返回0；

sort map[]--(count: max)
rand sort to "to[]"
map[] not include "0";
map[] length = to[] length;
return:
        ok:1;
        failed:0;
 #include <time.h>
*****************************************/
int rand_min_max(int *to, int *map, unsigned int max)
{
	int i, t, j, randmax;

	randmax = max - 1;			/*产生 0 - (max - 1)之间的随机数*/
	for(i = 0; i < max - 1; i++)
	{
		srand( (unsigned)time( NULL ) );
		t = rand() % randmax;

		to[i] = map[t];

		j = randmax;
		while( (map[j] == 0) && (j > 0) )	/*跳过一切是0的记录*/
		{
			j--;
		}
		map[t] = map[j];		/*用最后一个数填补空位*/
		map[j] = 0;				/*等于0，记录为已发牌*/

		randmax--;
	}

	to[max - 1] = map[0];		/*最后把map[0]移到to[max - 1]中*/
	return 1;
}


