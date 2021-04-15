#include "getmin.h"

int getMin(int* arr,int count)
{
    int min=arr[0];
    for (int i = 0; i < count; i++)
    {
        if(arr[i]<min)
        {
            min=arr[i];
        }
    }
    
    return min;
}
