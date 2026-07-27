#include<stdio.h>
int fb(int n)
{
    if(n<=2)
    {
        return 1; 
    }
    else{
        return fb(n-1)+fb(n-2);
    }
}
int main()
{
    printf("你想要第几项？\n");
    int n;
    scanf("%d",&n);
    printf("%d\n",fb(n));
    return 0;
}