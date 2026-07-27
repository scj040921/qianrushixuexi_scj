#include<stdio.h>
int sum(int *arr,int len)
{
    int sum=0;
    for(int i=0;i<len;i++)
    {
        sum+=arr[i];
    }
    return sum;
}
int main()
{
    int arr[]={1,2,3};
    int len=sizeof(arr)/sizeof(int);
    printf("%d\n",sum(arr,len));
    return 0;
}