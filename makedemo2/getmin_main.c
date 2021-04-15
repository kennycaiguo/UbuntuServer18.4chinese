#include<stdio.h>
#include"getmin.h"

int main()
{
    int arr[]={1,23,8,100,56};
    int min=getMin(arr,5);
    printf("min=%d\n",min);
    return 0;
}
