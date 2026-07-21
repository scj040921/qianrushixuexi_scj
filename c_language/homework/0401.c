#include<stdio.h>
union node
    {
        int a;
        char b;
    };
int main(int argc,char const *argv[])
{
    //取首字节判断大小端序
    // int a=0x12345678;
    // if(*(char *)&a==0x78)
    // {
    //     printf("小端序\n");
    // }
    // else
    // {
    //     printf("大端序\n");
    // }
    //使用联合体（首字节地址重叠）
    union node n;
    n.a=0x12345678;
    if(n.b==0x78)
    {
        printf("小端序\n");
    }
    else
    {
        printf("大端序\n");
    }
    
    return 0;
}