#include<stdio.h>
#include"getmax.h"

int main()
{
    int arr[]={1,23,8,100,56};
    int max=getMax(arr,5);
    printf("max=%d",max);
    return 0;
}