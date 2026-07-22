#include<stdio.h>
#include<stdlib.h>
//变长数组，用变量代替常量做数组下标
//变长数组不可以初始化，初始化发生在编译阶段，数组长度的确定发生在运行时
//初始化列表动作发生在编译期间，结果存入硬盘
//变长数组的数组长度是局部变量，运行时才分配内存
void assignment_rand(int n,int m,int a[n][m])
 {
     for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            a[i][j]=rand()%1000;//随机函数生成的函数一般会比较大，通过取余来缩小        
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }   
 }
 void mycopy(int n,int m,int a[n][m],int b[n][m])
 {
     for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                b[i][j]=a[i][j];
                printf("%d\t",b[i][j]);
            }
            printf("\n");
        }
 }
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    // int a[n][m],b[n][m];
    // //给a中的各个变量赋值
    // for(int i=0;i<n;i++)
    // {
    //     for(int j=0;j<m;j++)
    //     {
    //         a[i][j]=rand()%1000;//随机函数生成的函数一般会比较大，通过取余来缩小        
    //         printf("%d\t",a[i][j]);
    //     }
    //     printf("\n");
    // }   
    //  for(int i=0;i<n;i++)
    //     {
    //         for(int j=0;j<m;j++)
    //         {
    //             b[i][j]=a[i][j];
    //             printf("%d\t",b[i][j]);
    //         }
    //         printf("\n");
    //     }
    int a[n][m],b[n][m];
    assignment_rand(n,m,&a[0]);
    mycopy(n,m,&a[0],&b[0]);
    return 0;
}