#include <stdio.h>
#include <time.h>

/*************************************
  quick sort:
        min: low;
        max: high
*****************************************/
void array_quick_sort(int *a, int low, int high);

/* sort array(num) small to large */
void array_sort_small_to_large(int *arr, int num);

/*#include <stdio.h>
#include <time.h>*/

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
int rand_min_max(int *to, int *map, unsigned int max);


