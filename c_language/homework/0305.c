#include <stdio.h>

int* sum(int* a, int* b, int* c, int len)
{
    for(int i=0;i<len;i++)
    {
        c[i]=a[i]+b[i];
    }
    return c;
}
int main(void)
{
    int a[] = {1, 2, 3, 4};
    int b[] = {5, 6, 7, 8};
    int c[4];
    sum(a,b,c,4);
    for(int i=0;i<4;i++)
    {
        printf("%d\n",c[i]);
    }
    return 0;
}