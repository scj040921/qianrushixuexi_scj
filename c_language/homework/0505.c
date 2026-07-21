#include<stdio.h>
int fb(int n)
{
    if(n==1||n==2)
    {
        return 1;
    }
    return fb(n-1)+fb(n-2);
}
int main()
{
    int n;
    printf("你要第几项");
    scanf("%d",&n);
    printf("%d",fb(n));

    return 0;
}