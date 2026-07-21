#include<stdio.h>
int main()
{
    int a[2][3]={{1,2,3},{4,5,6}};
    int (*b[2])[3];
    b[0]=&a[0];
    b[1]=&a[1];
    int sum=0;
    for(int k=0;k<2;k++)
    {
        for(int i=0;i<3;i++)
        {
            sum+=(*b[k])[i];
        }   
    }
    printf("%d\n",sum);
    return 0;
}