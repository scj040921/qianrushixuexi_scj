#include<stdio.h>

void x(int a,char hex[])
{
    const char map[]="0123456789ABCDEF";
    char digits[32];
    int count=0;
    unsigned int n=(unsigned int)a;
    if(n==0)
    {
        digits[count++]='0';
    }else{
        while(n>0){
            digits[count++]=map[n%16];
            n/=16;
        }
    }
    for(int i=count-1;i>=0;i--)
    {
        hex[count-1-i]=digits[i];
    }
    hex[count]='\0';
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