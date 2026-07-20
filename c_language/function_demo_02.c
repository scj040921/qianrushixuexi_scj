#include<stdio.h>

double a(double b,int n)
{
    if(n==0)
    {
        return 1;
    }
    else if(n<0)
    {
       b*=a(b,n+1);
       double result =1.0/b;
        return result;
    }
    else
    {
        b*=a(b,n-1);
    }
    
    return b;
}
int main()
{
    double b;
    int n;
    printf("请输入一个数:\n");
    scanf("%lf",&b);
    printf("请输入次数:\n");
    scanf("%d",&n);
    printf("%lf",a(b,n));
    return 0;
}