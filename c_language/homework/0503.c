#include<stdio.h>
float myPower(float x,int n)
{
   
    float result;
    // for(int i=0;i<n;i++)
    // {
    //     result*=x;
    // }
    if(n==0)
    {
     return 1;  
    }
    else if(n>0)
    {
        result=x*myPower(x,n-1);
    }
    else if(n<0)
    {
        result=1/x*myPower(x,n+1);
    }
    return result;
}
int main()
{
    float x;
    int n;
    printf("请输入底数（浮点数）和指数（整数）\n");
    // while(1)
    // {
    //     if(scanf("%f %d",&x,&n)==2&&getchar()=='\n')
    //         break;
    //     printf("输入错误，请重新输入\n");
    //     while(getchar()!='\n');
    // }
    scanf("%f %d",&x,&n);
    printf("%f\n",myPower(x,n));
    return 0;

}