#include<stdio.h>

void x(int a,char hex[])
{
    // const char map[]="0123456789ABCDEF";//十进制数与十六进制数的映射表
    // char digits[32];//数组一用于存储16进制转换过程中产生的逆序中间临时结果
    // int count=0;//计数器，统计十六进制数的位数
    // unsigned int n=(unsigned int)a;//防止负数在取余等运算过程中可能造成的错误，是否有符号并不影响十六进制的输出
    // if(n==0)
    // {
    //     digits[count++]='0';//输入为0时，输出为0
    // }else{
    //     while(n>0){
    //         digits[count++]=map[n%16];//短除法进制转换
    //         n/=16;
    //     }
    // }
    // for(int i=count-1;i>=0;i--)
    // {
    //     hex[count-1-i]=digits[i];//吧逆序的临时结果进行反转
    // }
    // hex[count]='\0';//补上终止符
    int i=0;
    if(a<0)
    {
        a*=-1;
    }
    while(a!=0)
    {
        switch(a%16)
        {
            case 0 ... 9:
                hex[i++]=a%16+'0';
                break;
            case 10 ... 15:
                hex[i++]=a%16-10+'A';
                break;
        }
        a/=16;
    }
}
 int main()
 {
    int a;
    printf("请输入一个整数：");
    scanf("%d",&a);
    char hex[32];
    x(a,hex);
    printf("十六进制表示为：%s\n",hex);
    return 0;
 }