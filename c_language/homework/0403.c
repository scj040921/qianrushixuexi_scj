#include<stdio>
int main()
{
    int m,n;
    int a[m][n];
    int *b[m];
    int temp =0;
    for(int i=0;i<m;i++)
    {
        b[i]=a;
        a+=n;
        for(int j=0;j<n;j++)
        {
            temp+=b[i][j];
        }
    }
}