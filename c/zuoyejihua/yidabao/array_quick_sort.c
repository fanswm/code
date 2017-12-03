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
        quik_sort(a, low, i - 1);
        quik_sort(a, j+1, high);
    }
    else
    {
        return;
    }
}
