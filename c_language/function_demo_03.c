#include<stdio.h>
int main(int argc,const char *(argv[]))
//argv是一个指针数组，argv[0]指向存放程序本身路径/名字的字符串
//argv[1]指向用户输入的第一个参数
//argc是参数的个数
{
//输出所有外部参数
for(int i=0;i<argc-1;i++)
{
    printf("%s\n",argv[i+1]);
}
//输出“bcd”
printf("%s\n",argv[1]+1);
//输出“3”
printf("%c\n",argv[2][2]);
return 0;

}