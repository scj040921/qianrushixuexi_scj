#include<stdio.h>
int main()
{
    int a[7]={-2, 5, -1, 6, -4, -8, 6};
    int result=a[0];
    for(int i=0;i<7;i++)
    {
        int sum=0;       
        for(int j=i; j<7-i;j++)
        {
            sum+=a[j];
            if(sum>result)
            {
                result=sum;
            }
        }
    }
    printf("%d\n",result);
    return 0;
}