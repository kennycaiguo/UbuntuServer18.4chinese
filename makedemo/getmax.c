#include "getmax.h"

int getMax(int*arr,int count)
{
    int max=arr[0];
    for (int i = 0; i < count; i++)
    {
        if(arr[i]>max)
        {
            max=arr[i];
        }
    }
    return max;
}